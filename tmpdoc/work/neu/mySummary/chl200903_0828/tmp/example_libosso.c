/**
 * This file is part of maemo-examples package
 * 
 * This maemo code example is licensed under a MIT-style license,
 * that can be found in the file called "COPYING" in the same
 * directory as this file.
 * Copyright (c) 2007-2008 Nokia Corporation. All rights reserved.
 */

#include <hildon/hildon-program.h>
#include <hildon/hildon-banner.h>

#include <gtk/gtk.h>
#include <libosso.h>

#define OSSO_EXAMPLE_NAME    "example_libosso"
#define OSSO_EXAMPLE_SERVICE "org.maemo."OSSO_EXAMPLE_NAME
#define OSSO_EXAMPLE_OBJECT  "/org/maemo/"OSSO_EXAMPLE_NAME
#define OSSO_EXAMPLE_IFACE   "org.maemo."OSSO_EXAMPLE_NAME
#define OSSO_EXAMPLE_MESSAGE "HelloWorld"


/* Application UI data struct */
typedef struct _AppData AppData;
struct _AppData {
    HildonProgram *program;
    HildonWindow *window;
    osso_context_t *osso_context;
};

/* Callback for exit D-BUS event */
void exit_event_handler(gboolean die_now, gpointer data)
{
	AppData *appdata;
	appdata = (AppData *) data;
	g_print("exit_event_handler called\n");
	/* Do whatever application needs to do before exiting */
	hildon_banner_show_information(GTK_WIDGET(appdata->window), NULL,
			"Exiting...");
}

/* Callback for normal D-BUS messages */
gint dbus_req_handler(const gchar * interface, const gchar * method,
                      GArray * arguments, gpointer data,
                      osso_rpc_t * retval)
{
    AppData *appdata;
    appdata = (AppData *) data;

    osso_system_note_infoprint(appdata->osso_context, method, retval);
    osso_rpc_free_val(retval);

    return OSSO_OK;
}

/* Callback for hardware D-BUS events */
void hw_event_handler(osso_hw_state_t *state, gpointer data)
{
    AppData *appdata;
    appdata = (AppData *) data;

    if (state->shutdown_ind)
    {
        hildon_banner_show_information(GTK_WIDGET(appdata->window), NULL, 
                                       "Shutdown event!");
    }
    if (state->memory_low_ind)
    {
        hildon_banner_show_information(GTK_WIDGET(appdata->window), NULL, 
                                       "Memory low event!");
    }
    if (state->save_unsaved_data_ind)
    {
        hildon_banner_show_information(GTK_WIDGET(appdata->window), NULL, 
                                       "Must save unsaved data event!");
    }
    if (state->system_inactivity_ind)
    {
        hildon_banner_show_information(GTK_WIDGET(appdata->window), NULL, 
                                       "Minimize application inactivity event!");
    }
}

/* Main application */
int main(int argc, char *argv[])
{
    /* Create needed variables */
    HildonProgram *program;
    HildonWindow *window;
    osso_context_t *osso_context;
    osso_return_t result;
    GtkWidget *main_vbox;
    GtkWidget *label;
    AppData *appdata;

    /* Initialize the GTK. */
    gtk_init(&argc, &argv);

    /* Initialize maemo application */
    osso_context = osso_initialize(OSSO_EXAMPLE_SERVICE, "0.0.1", TRUE, NULL);/*第一步*/

    /* Check that initialization was ok */
    if (osso_context == NULL) {
        return OSSO_ERROR;
    }

    /* Create the hildon program and setup the title */
    program = HILDON_PROGRAM(hildon_program_get_instance());
    g_set_application_name("App Title");

    /* Create HildonWindow and set it to HildonProgram */
    window = HILDON_WINDOW(hildon_window_new());
    hildon_program_add_window(program, window);

    /* Create AppData */
    appdata = g_new0(AppData, 1);
    appdata->program = program;
    appdata->window = window;
    appdata->osso_context = osso_context;

    /* Add vbox to appview */
    main_vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), main_vbox);

    /* Add button to vbox */
    label = gtk_label_new("Waiting for DBUS message...");
    gtk_box_pack_start(GTK_BOX(main_vbox), label, FALSE, TRUE, 0);

    /* Add handler for session bus D-BUS messages */
    result = osso_rpc_set_cb_f(appdata->osso_context, 
                               OSSO_EXAMPLE_SERVICE, 
                               OSSO_EXAMPLE_OBJECT, 
                               OSSO_EXAMPLE_IFACE,
                               dbus_req_handler, appdata);/*第二步*/

    if (result != OSSO_OK) {
        g_print("Error setting D-BUS callback (%d)\n", result);
        return OSSO_ERROR;
    }

    /* Add handler for Exit D-BUS messages */
    result = osso_application_set_exit_cb(appdata->osso_context,
                                          exit_event_handler,
                                          (gpointer) appdata);
    if (result != OSSO_OK) {
        g_print("Error setting exit callback (%d)\n", result);
        return OSSO_ERROR;
    }

    /* Add handler for hardware D-BUS messages */
    result = osso_hw_set_event_cb( appdata->osso_context,
        NULL, hw_event_handler, (gpointer) appdata );

    if (result != OSSO_OK)
    {
        g_print("Error setting HW state callback (%d)\n", result);
        return OSSO_ERROR;
    }

    /* Connect signal to X in the upper corner */
    g_signal_connect(G_OBJECT(window), "delete_event",
      G_CALLBACK(gtk_main_quit), NULL);

    /* Begin the main application */
    gtk_widget_show_all(GTK_WIDGET(window));
    gtk_main();

    /* Deinitialize OSSO */
    osso_deinitialize(osso_context);/*第三步*/

    /* Exit */
    return 0;
}


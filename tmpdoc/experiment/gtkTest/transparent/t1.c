#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
    GtkWidget *window = NULL;
    GtkWidget *fixed = NULL;
    GdkPixbuf *pixbuf = NULL;
    GdkPixmap *pixmap = NULL;

    GtkWidget *eventbox;
    GtkWidget *image;
    GdkBitmap *bitmap;


    gtk_init(&argc,&argv);

    /* Create the window */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"User Define Button  Demo");
    gtk_widget_set_app_paintable(window,TRUE);
    gtk_widget_realize (window);

    gtk_widget_set_size_request(window, 400, 300);
    g_signal_connect (G_OBJECT (window), "delete_event", G_CALLBACK (gtk_main_quit), NULL);

    fixed = gtk_fixed_new();
    gtk_container_add (GTK_CONTAINER(window), fixed);

    eventbox = gtk_event_box_new();

    //load background
    pixbuf = gdk_pixbuf_new_from_file ("/bg.jpg",NULL);
    image = gtk_image_new_from_pixbuf (pixbuf);

    pixmap = gdk_pixmap_new (window->window, gdk_pixbuf_get_width(pixbuf), gdk_pixbuf_get_height(pixbuf), -1);
    gdk_pixbuf_render_to_drawable(pixbuf, pixmap,
                window->style->fg_gc[GTK_STATE_NORMAL],
                0,0,0,0,
                gdk_pixbuf_get_width(pixbuf),
                gdk_pixbuf_get_height(pixbuf),
                GDK_RGB_DITHER_NORMAL,0,0);
    g_object_unref(pixbuf);
    gdk_window_set_back_pixmap (window->window, pixmap, FALSE);

      // Load button
      pixbuf = gdk_pixbuf_new_from_file ("/button_auto.png",NULL);
    image = gtk_image_new_from_pixbuf (pixbuf);

      gtk_container_add(GTK_CONTAINER(eventbox), image);
      gtk_fixed_put (GTK_FIXED (fixed), eventbox, 50,50);
   
    //  Set button mask
      gdk_pixbuf_render_pixmap_and_mask(pixbuf, NULL, &bitmap, 255);
      gtk_widget_shape_combine_mask(eventbox, bitmap, 0, 0);

      gtk_widget_show_all(window);
      gtk_main();
        return 0;
}

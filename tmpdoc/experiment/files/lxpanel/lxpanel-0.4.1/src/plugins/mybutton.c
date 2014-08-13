/**
 * Copyright (c) 2006 LxDE Developers, see the file AUTHORS for details.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib/gi18n.h>
#include <pthread.h>

#include "panel.h"
#include "misc.h"
#include "plugin.h"
#include "glib-mem.h"

#include "dbg.h"

#define DEFAULT_TIP_FORMAT    "%A %x"
#define DEFAULT_CLOCK_FORMAT  "%R"

typedef struct {
    Panel* panel;
    GtkWidget *main;
} mybutton;

static void
update_label_orient( Plugin* p );

static GtkWidget *create_calendar()
{
}

static void *
actionProcess( void *arg )
{
}

static  gboolean
clicked( GtkWidget *widget, GdkEventButton* evt, Plugin* plugin)
{
}

static gint
clock_update(gpointer data )
{
}


static int
mybutton_constructor(Plugin *p, char** fp)
{
    line s;
    mybutton *dc;

    ENTER;
    dc = g_slice_new0(mybutton);
    g_return_val_if_fail(dc != NULL, 0);
    p->priv = dc;

    dc->panel = p->panel;

    dc->main = gtk_button_new_with_label("HELLO");
    gtk_widget_show_all(dc->main);

    p->pwid = dc->main;

    RET(1);
}


static void
mybutton_destructor(Plugin *p)
{
}

static void apply_config( Plugin* p )
{
}

static void mybutton_config( Plugin *p, GtkWindow* parent )
{
}

static void save_config( Plugin* p, FILE* fp )
{
}

static void
update_label_orient( Plugin* p )
{
}

PluginClass mybutton_plugin_class = {
    fname: NULL,
    count: 0,

    type : "MYBUTTON",
    name : N_("mybutton"),
    version: "1.0",
    description : N_("this is mybutton"),

    constructor : mybutton_constructor,
    destructor  : mybutton_destructor,
    config : mybutton_config,
    save : save_config,
    orientation : update_label_orient
};

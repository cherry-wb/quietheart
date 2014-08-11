//http://www.lupaworld.com/bbs/thread-30352-1-2.html
#include "eggtrayicon.h"

   void
   create_tray (tray_demo * tray)
   {
           GtkWidget *image;
           GtkWidget *event_box;
           GtkTooltips *tooltips;
           EggTrayIcon *tray_icon;

           tooltips = gtk_tooltips_new ();
           tray_icon = egg_tray_icon_new ("Tray icon demo");
           event_box = gtk_event_box_new ();
           gtk_container_add (GTK_CONTAINER (tray_icon), event_box);
           g_signal_connect (G_OBJECT (event_box), "button-press-event",
                             G_CALLBACK (tray_button_press_event_cb), tray);
           gtk_tooltips_set_tip (GTK_TOOLTIPS(tooltips), event_box, _("Try a left/right click"), NULL)   ;

           image = load_image (GCN_ICON);
           gtk_container_add (GTK_CONTAINER (event_box), image);

           gtk_widget_show_all (GTK_WIDGET (tray_icon));

           return;
   }


#include<gtk/gtk.h>
gint
main (gint argc, gchar *argv[])
{

  GtkWidget *window;
  GtkWidget *eventBox1;
  GtkWidget *eventBox2;
  GtkWidget *hbox;
  GtkWidget *label1;
  GtkWidget *label2;
  //GdkColor color;
  gtk_init(&argc, &argv);
  
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
 
  g_signal_connect(window, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  //gtk_window_set_default_size(GTK_WINDOW(window), 800, 480); 
  //gdk_color_parse("green", &color);
  //gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);
  hbox = gtk_hbox_new(TRUE, 0);
  gtk_container_add(GTK_CONTAINER(window), hbox);
  eventBox1 = gtk_event_box_new();
  gtk_widget_set_events (eventBox, GDK_BUTTON_PRESS_MASK);

  g_signal_connect (G_OBJECT (eventBox1), "button_press_event",
	              G_CALLBACK (gtk_main_quit), NULL);

  gtk_box_pack_start(GTK_BOX(hbox), eventBox1, TRUE, TRUE, 0); 
  label1 = gtk_label_new("first");
  gtk_container_add(GTK_CONTAINER(eventBox2), label1);

  eventBox2 = gtk_event_box_new();

  gtk_box_pack_start(GTK_BOX(hbox), eventBox2, TRUE, TRUE, 0);
  label2 = gtk_label2_new("second");
  gtk_container_add(GTK_CONTAINER(eventBox2), label2);
  
  gtk_widget_show_all(window);

  gtk_main();
  return 0;
}

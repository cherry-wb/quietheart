#include <cairo.h>
#include <gtk/gtk.h>

gint orig_x = 0;
gint orig_y = 0;

/*代表图片的结构*/
cairo_surface_t *image;


static gboolean on_expose_event(GtkWidget *widget,
		GdkEventExpose *event,
		gpointer data)
{
/*该类型包含当前设备的状态，包括坐标以及形状等*/
  cairo_t *cr;

  cr = gdk_cairo_create(widget->window);
  //cairo_set_source_surface(cr, image, orig_x, orig_y);
  /*这里的orig_x和orig_y可以控制图片的显示位置*/
  cairo_set_source_surface(cr, image, 50, 50);
  cairo_paint(cr);
  cairo_destroy(cr);

  return FALSE;
}

int
main (int argc, char *argv[])
{

  GtkWidget *window;

  gtk_init(&argc, &argv);
  
  image = cairo_image_surface_create_from_png("tvButton.png");
  /*不支持jpg格式的图片？
   */
  //image = cairo_image_surface_create_from_png("bg1.jpg");
  //image = cairo_image_surface_create_from_png("desktop1.png");
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
 
  g_signal_connect(window, "expose-event",
      G_CALLBACK(on_expose_event), NULL);
  g_signal_connect(window, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);
  
 
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 480); 
  gtk_widget_set_app_paintable(window, TRUE);

  gtk_widget_show_all(window);

  gtk_main();
  cairo_surface_destroy(image);

  return 0;
}



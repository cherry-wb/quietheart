#include <cairo.h>
#include <gtk/gtk.h>

gint orig_x = 0;
gint orig_y = 0;

/*gint off_x = 0;
gint off_y = 0;

gboolean is_drag = FALSE;
gint drag_item = 0;*/

cairo_surface_t *image1;
//cairo_surface_t *image2;


static gboolean on_expose_event(GtkWidget *widget,
		GdkEventExpose *event,
		gpointer data)
{
  cairo_t *cr;

  cr = gdk_cairo_create(widget->window);
  cairo_set_source_surface(cr, image1, orig_x, orig_y);
  cairo_paint(cr);

  /*gint x2;
  if((orig_x >= 0)
		&& (orig_x <= 800))
	  x2 = orig_x - 800;
  else
	  x2 = orig_x + 800;

  cairo_set_source_surface(cr, image2, x2, orig_y);
  cairo_paint(cr);*/

  cairo_destroy(cr);

  return FALSE;
}


/*gboolean motion_event(GtkWidget *widget, GdkEventMotion *event)
{
	int x, y;
	GdkModifierType state;

	if(event->is_hint)
		gdk_window_get_pointer(event->window, &x, &y, &state);
	else
	{
		x = event->x;
		y = event->y;
		state = event->state;
	}

	if(state & GDK_BUTTON1_MASK)
	{
		if(is_drag)
		{
			orig_x = x - off_x;
			if(orig_x <= -800)
				orig_x = orig_x + 1600;
			else if(orig_x >= 800)
				orig_x = orig_x - 1600;
			gtk_widget_queue_draw(widget);
		}
	}
	return TRUE;
}

gboolean button_press_event(GtkWidget *widget, GdkEventButton *event)
{
	is_drag = TRUE;
	off_x = event->x - orig_x;
}

gboolean button_release_event(GtkWidget *widget, GdkEventButton *event)
{
	is_drag = FALSE;
}
*/

int
main (int argc, char *argv[])
{

  GtkWidget *window;

  gtk_init(&argc, &argv);
  
  image1 = cairo_image_surface_create_from_png("desktop1.png");
  //image2 = cairo_image_surface_create_from_png("desktop2.png");

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
 
  /*gtk_widget_add_events (window, GDK_BUTTON_PRESS_MASK);
  gtk_widget_add_events (window, GDK_BUTTON_RELEASE_MASK);
  gtk_widget_add_events (window, GDK_POINTER_MOTION_MASK);
  gtk_widget_add_events (window, GDK_POINTER_MOTION_HINT_MASK);*/

  g_signal_connect(window, "expose-event",
      G_CALLBACK(on_expose_event), NULL);
  g_signal_connect(window, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);
  /*g_signal_connect(window, "motion_notify_event", 
      G_CALLBACK(motion_event), NULL);
  g_signal_connect(window, "button_press_event", 
      G_CALLBACK(button_press_event), NULL);
  g_signal_connect(window, "button_release_event", 
      G_CALLBACK(button_release_event), NULL);*/
 
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 480); 
  gtk_widget_set_app_paintable(window, TRUE);

  gtk_widget_show_all(window);

  gtk_main();
  cairo_surface_destroy(image1);
  //cairo_surface_destroy(image2);

  return 0;
}



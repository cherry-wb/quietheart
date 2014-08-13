#include <cairo.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>

gint orig_x = 0;
gint orig_y = 0;

gint off_x = 0;
gint off_y = 0;

gint start_x = 0;
gint end_x = 0;
gint offset = 0;

gint image_x = (800 - 128) / 2;
gint image_y = (480 - 128) / 2;
gint image_off_x = 0;
gint image_off_y = 0;

gboolean is_moving = FALSE;
gboolean is_lock = FALSE;

gboolean is_drag = FALSE;
gint drag_item = 0;

cairo_surface_t *image1;
cairo_surface_t *image2;
cairo_surface_t *image3;

gboolean on_timeout(gpointer data);
gboolean on_timeout_2(gpointer data);

static gboolean on_expose_event(GtkWidget *widget,
		GdkEventExpose *event,
		gpointer data)
{
	cairo_t *cr;

	cr = gdk_cairo_create(widget->window);
	cairo_set_source_surface(cr, image1, orig_x, orig_y);
	cairo_paint(cr);

	// cairo_set_source_surface(cr, image3, orig_x + (800 - 128) / 2, orig_y + (480 - 128) / 2);
	cairo_set_source_surface(cr, image3, orig_x + image_x, orig_y + image_y);
	cairo_paint(cr);

	gint x2;
	if((orig_x >= 0)
			&& (orig_x <= 800))
		x2 = orig_x - 800;
	else
		x2 = orig_x + 800;

	cairo_set_source_surface(cr, image2, x2, orig_y);
	cairo_paint(cr);

	cairo_destroy(cr);
	return FALSE;
}


gboolean motion_event(GtkWidget *widget, GdkEventMotion *event)
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
			if((x > 800)
				&& (!is_lock))
			{
				offset = 50;
				is_lock = TRUE;
				g_timeout_add(100, on_timeout_2, (gpointer)widget);
				is_moving = TRUE;
			}
			else
			{
				image_x = x - image_off_x;
				image_y = y - image_off_y;
				gtk_widget_queue_draw(widget);
			}
		}
	}
	return TRUE;
}

gboolean button_press_event(GtkWidget *widget, GdkEventButton *event)
{
/*
	is_drag = TRUE;
	off_x = event->x - orig_x;
*/
	if((event->x >= orig_x + image_x)
		&& (event->x <= orig_x + image_x + 128)
		&& (event->y >= orig_y + image_y)
		&& (event->y <= orig_y + image_y + 128))
	{
		image_off_x = event->x - image_x;
		image_off_y = event->y - image_y;
		is_drag = TRUE;
	}
	else
	{
		start_x = event->x;
	}
}


gboolean on_timeout(gpointer data)
{
	GtkWidget *widget = GTK_WIDGET(data);
	static gint count = 0;
	count++;

	if(orig_x > 0)
	{
		orig_x -= (offset / 10) * count * count;
		if(orig_x > 0)
		{
			gtk_widget_queue_draw(widget);
			return TRUE;
		}
		else
		{
			orig_x = 0;
			count = 0;
			gtk_widget_queue_draw(widget);
			is_moving = FALSE;
			return FALSE;
		}
	}
	else
	{
		orig_x -= (offset / 10) * count * count;

		if(orig_x > -800)
		{
			gtk_widget_queue_draw(widget);
			return TRUE;
		}
		else
		{
			orig_x = 800;
			count = 0;
			gtk_widget_queue_draw(widget);
			is_moving = FALSE;
			return FALSE;
		}
	}
}


gboolean on_timeout_2(gpointer data)
{
	GtkWidget *widget = GTK_WIDGET(data);
	static gint count = 0;
	count++;

	if(orig_x < 800)
	{
		if(orig_x < 0)
		{
			orig_x += (offset / 10) * count * count;

			if(orig_x < 0)
			{
				gtk_widget_queue_draw(widget);
				return TRUE;
			}
			else
			{
				orig_x = 0;
				count = 0;
				gtk_widget_queue_draw(widget);
				is_moving = FALSE;
				is_lock = FALSE;
				return FALSE;
			}
		}
		else
		{
			orig_x += (offset / 10) * count * count;
			if(orig_x < 800)
			{
				gtk_widget_queue_draw(widget);
				return TRUE;
			}
			else
			{
				orig_x = 800;
				count = 0;
				gtk_widget_queue_draw(widget);
				is_moving = FALSE;
				is_lock = FALSE;
				return FALSE;
			}
		}
	}
	else
	{
		orig_x += (offset / 10) * count * count;

		orig_x = orig_x - 1600; 
		gtk_widget_queue_draw(widget);
		return TRUE;
	}
}

gboolean button_release_event(GtkWidget *widget, GdkEventButton *event)
{
/*
	is_drag = FALSE;
*/
	end_x = event->x;

	if(is_drag)
	{
		is_drag = FALSE;
		return FALSE;
	}

	if((start_x - end_x) >= 50 )
	{
		offset = start_x - end_x;
		g_timeout_add(100, on_timeout, (gpointer)widget);
		is_moving = TRUE;
	}
	else if((end_x - start_x) >= 50 )
	{
		offset = end_x - start_x;
		g_timeout_add(100, on_timeout_2, (gpointer)widget);
		is_moving = TRUE;
	}

	return TRUE;
}

GdkFilterReturn event_filter(GdkXEvent *gdk_xevent,
		GdkEvent *event, gpointer data)
{
	XEvent *xev = (XEvent *)gdk_xevent;
	if(is_moving)
	{
		if((xev->type == ButtonPressMask)
			|| (xev->type == ButtonReleaseMask)
			|| (xev->type == ButtonMotionMask))
		{
			g_print("we are moving!\n");
			return GDK_FILTER_REMOVE;
		}
	}
	return GDK_FILTER_CONTINUE;
}

int
main (int argc, char *argv[])
{

  GtkWidget *window;
  GtkWidget *image;

  gtk_init(&argc, &argv);
  
  image1 = cairo_image_surface_create_from_png("desktop1.png");
  image2 = cairo_image_surface_create_from_png("desktop2.png");
  image3 = cairo_image_surface_create_from_png("mozicon128.png");

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
 
  gtk_widget_add_events (window, GDK_BUTTON_PRESS_MASK);
  gtk_widget_add_events (window, GDK_BUTTON_RELEASE_MASK);
  gtk_widget_add_events (window, GDK_POINTER_MOTION_MASK);
  gtk_widget_add_events (window, GDK_POINTER_MOTION_HINT_MASK);

  g_signal_connect(window, "expose-event",
      G_CALLBACK(on_expose_event), NULL);
  g_signal_connect(window, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(window, "motion_notify_event", 
      G_CALLBACK(motion_event), NULL);
  g_signal_connect(window, "button_press_event", 
      G_CALLBACK(button_press_event), NULL);
  g_signal_connect(window, "button_release_event", 
      G_CALLBACK(button_release_event), NULL);
 
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 480); 
  gtk_widget_set_app_paintable(window, TRUE);

  gtk_widget_show_all(window);
  gdk_window_add_filter(window->window, event_filter, NULL);

  gtk_main();
  cairo_surface_destroy(image1);
  cairo_surface_destroy(image2);
  cairo_surface_destroy(image3);

  return 0;
}


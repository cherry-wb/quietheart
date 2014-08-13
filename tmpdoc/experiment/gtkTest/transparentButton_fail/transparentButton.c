#include <gtk/gtk.h>

static gboolean
transparent_expose (GtkWidget      *widget,
                    GdkEventExpose *event)
{
g_print("here,transparent_expose");
  cairo_t *cr;
  cr = gdk_cairo_create (widget->window);
  cairo_set_operator (cr, CAIRO_OPERATOR_CLEAR);
  gdk_cairo_region (cr, event->region);

  cairo_fill (cr);
  cairo_destroy (cr);
  return FALSE;
}

static gboolean
window_expose_event (GtkWidget      *widget,
                     GdkEventExpose *event)
{
g_print("here,window_expose");
  GdkRegion *region;
  GtkWidget *child;
  cairo_t *cr;
  /* get our child (in this case, the event box) */
  child = gtk_bin_get_child (GTK_BIN (widget));
  /* create a cairo context to draw to the window */
  cr = gdk_cairo_create (widget->window);
  /* the source data is the (composited) event box */
  gdk_cairo_set_source_pixmap (cr, child->window,
                               child->allocation.x,
                               child->allocation.y);
  /* draw no more than our expose event intersects our child */
  region = gdk_region_rectangle (&child->allocation);
  gdk_region_intersect (region, event->region);
  gdk_cairo_region (cr, region);
  cairo_clip (cr);
  /* composite, with a 50% opacity */
  cairo_set_operator (cr, CAIRO_OPERATOR_OVER);
  cairo_paint_with_alpha (cr, 0.3);
  /* we're done */
  cairo_destroy (cr);
  return FALSE;
}



int main( int   argc,
          char *argv[] )
{
  /* GtkWidget 是构件的存储类型 */
  GtkWidget *window;
  GtkWidget *fixed;
  GtkWidget *button;

GdkScreen *screen;
  GdkColormap *rgba;
  GdkColor red;

  /* 初始化 */
  gtk_init (&argc, &argv);
    
  /* 创建一个新窗口 */
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Fixed Container");
gtk_window_set_default_size(GTK_WINDOW(window), 300,300);
 gdk_color_parse ("red", &red);
  gtk_widget_modify_bg (window, GTK_STATE_NORMAL, &red);

  /* 为窗口的 "destroy" 事件设置一个信号处理函数 */ 
  g_signal_connect (G_OBJECT (window), "destroy",
		    G_CALLBACK (gtk_main_quit), NULL);
 
  /* 设置窗口的边框宽度 */
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  /* 创建一个固定容器 */
  fixed = gtk_fixed_new ();





  gtk_container_add (GTK_CONTAINER (window), fixed);
  //gtk_widget_show (fixed);
 
  button = gtk_button_new_with_label("Stop!!");

 screen = gtk_widget_get_screen (button);
  rgba = gdk_screen_get_rgba_colormap (screen);
  gtk_widget_set_colormap (button, rgba);


gtk_widget_set_app_paintable (GTK_WIDGET (button), TRUE);
  g_signal_connect (button, "expose-event",
                    G_CALLBACK (transparent_expose), NULL);
  gtk_fixed_put(GTK_FIXED(fixed), button, 200,200);
  //gtk_widget_show(button);
  /* 显示窗口 */
  gtk_widget_show_all(window);

gdk_window_set_composited (button->window, TRUE);
  /* Set up the compositing handler.
   * Note that we do _after_ so that the normal (red) background is drawn
   * by gtk before our compositing occurs.
   */
  /*g_signal_connect_after (window, "expose-event",
                          G_CALLBACK (window_expose_event), NULL);*/

    
  /* 进入事件循环 */
  gtk_main ();
    
  return 0;
}

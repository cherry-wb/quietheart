#include <gtk/gtk.h>

/* 我准备偷点懒，用一些全局变量储存固定容器里构件的位置。 */
gint x = 50;
gint y = 50;
struct MyTData tmp;
int t;
struct MyTData
{
	GtkWidget *fix;
	GtkWidget *button;
};
/* This callback function moves the button to a new position
 * in the Fixed container. */
static void stop_auto_move(GtkWidget *widget,
		gpointer data)
{
	g_source_remove(*((gint*)data));
}
static gint auto_move_button(gpointer data)
{
	x = (x + 10) % 800;
	y = (y + 50) % 480;
	gtk_fixed_move(GTK_FIXED(((struct MyTData*)data)->fix), ((struct MyTData*)data)->button, x, y);
	return TRUE;
}
/* 这个回调函数将按钮移动到固定容器的新位置。 */
void move_button( GtkWidget *widget,
                  GtkWidget *fixed )
{
  x = (x + 30) % 300;
  y = (y + 50) % 300;
  gtk_fixed_move (GTK_FIXED (fixed), widget, x, y); 
}

int main( int   argc,
          char *argv[] )
{
  /* GtkWidget 是构件的存储类型 */
  GtkWidget *window;
  GtkWidget *fixed;
  GtkWidget *button;

  /* 初始化 */
  gtk_init (&argc, &argv);
    
  /* 创建一个新窗口 */
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Fixed Container");

  /* 为窗口的 "destroy" 事件设置一个信号处理函数 */ 
  g_signal_connect (G_OBJECT (window), "destroy",
		    G_CALLBACK (gtk_main_quit), NULL);
 
  /* 设置窗口的边框宽度 */
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  /* 创建一个固定容器 */
  fixed = gtk_fixed_new ();
  gtk_container_add (GTK_CONTAINER (window), fixed);
  gtk_widget_show (fixed);
 
  button = gtk_button_new_with_label("Stop!!");
  tmp.fix = fixed;
  tmp.button = button;
  gtk_fixed_put(GTK_FIXED(fixed), button, 200,200);
  gtk_widget_show(button);
  t = g_timeout_add(5000, auto_move_button, &tmp);/*就是第一下也得等5秒以后再动*/
  g_signal_connect(G_OBJECT(button), "clicked",
		  G_CALLBACK(stop_auto_move), &t);

  /* 显示窗口 */
  gtk_widget_show (window);
    
  /* 进入事件循环 */
  gtk_main ();
    
  return 0;
}

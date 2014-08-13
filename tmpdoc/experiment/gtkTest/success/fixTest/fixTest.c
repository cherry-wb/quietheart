/*程序功能：
 * 利用fixbox在特定的位置添加控件。
 * 给窗口添加背景之后，利用fix不会覆盖窗口背景。
 * 但给fix添加背景也添加不上去。
 * */
#include <gtk/gtk.h>

gint my_button1(GtkWidget *button, gpointer data)
{
	g_print("button1 pressed\n");
}

gint my_button2(GtkWidget *button, gpointer data)
{
	g_print("button2 pressed\n");
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
 
  /*按钮1*/
  button = gtk_button_new_with_label("button1");
  gtk_fixed_put(GTK_FIXED(fixed), button, 200,200);
  g_signal_connect(G_OBJECT(button), "clicked",
		  G_CALLBACK(my_button1), NULL);

  /*按钮2*/
  button = gtk_button_new_with_label("button2");
  gtk_fixed_put(GTK_FIXED(fixed), button, 400,200);
  g_signal_connect(G_OBJECT(button), "clicked",
		  G_CALLBACK(my_button2), NULL);

  /* 显示窗口 */
  gtk_widget_show_all(window);
    
  /* 进入事件循环 */
  gtk_main ();
    
  return 0;
}

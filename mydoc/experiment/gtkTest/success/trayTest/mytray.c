/*程序功能：
 * 运行程序，在系统托盘上面显示系统图标，并且可以把你自己的控件添加到这个图标上
 * */

/*网上说：
1首先在你的源码里引用头文件 eggtrayicon.h
2调用 GtkWidget *egg_tray_icon_new(void) 来创建一个通知图标控件,如 tray_icon.
3在 tray_icon 加入自己的控件,如图标或者其它.

但是我直接用eggtrayicon.c不行，里面有一些错误，需要这样改一下：
1)进入eggtrayicon.c
2)把#include <config.h>注释掉：
//#include <config.h>//lvkaidel
3)把#define _(x) dgettext (GETTEXT_PACKAGE, x)修改成如下：
#define _(x) gettext (x)//lvkaiadd
*/
#include<gtk/gtk.h>
#include "eggtrayicon.h"

/*点击图标的响应函数*/
gboolean tray_button_press_event(GtkWidget *button, GdkEventButton *event, gpointer data)
{
	g_print("hello press event\n");
}

/*调用这个函数，创建系统图标*/
void
create_tray (void)
{
	GtkWidget *image;
	GtkWidget *event_box;
	EggTrayIcon *tray_icon;

	/*tray_icon*/
	/*创建一个系统托盘控件,但是它上面什么都没有,需要后面的添加图标*/
	tray_icon = egg_tray_icon_new ("Tray icon demo");

	/*event_box*/
	event_box = gtk_event_box_new ();
	gtk_container_add (GTK_CONTAINER (tray_icon), event_box);
	g_signal_connect (G_OBJECT (event_box), "button-press-event",
			G_CALLBACK (tray_button_press_event), NULL);

	/*image*/
	image = gtk_image_new_from_stock(GTK_STOCK_HOME,GTK_ICON_SIZE_BUTTON);
	gtk_container_add (GTK_CONTAINER (event_box), image);

	gtk_widget_show_all (GTK_WIDGET (tray_icon));

	return;
}

int main(int argc, char *argv[])
{
	GtkWidget *win;
	gtk_init(&argc, &argv);

	/*这里启动程序*/
	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(win), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);


	/*这里给程序添加系统托盘图标*/
	create_tray ();
	gtk_widget_show_all(win);
	gtk_main();
	return 0;
}

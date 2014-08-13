/*程序功能：通过object对象保存上下文的信息。
 *g_object_set_data(GObject *object, gchar*　key, gpointer user_data)
 *这个函数是让object对象携带user_data这个指针值.
 *
 * g_object_get_data(GObject *object, gchar*　key)
 *这个函数，利用key指向的字符串取出user_data值.
 * */


#include <stdio.h>
#include <glib-object.h>
#include <gtk/gtk.h>

/*这个是键，相当于要存的数据的别名*/
#define STRING_KEY  "string_key"

int main(int argc, char**argv)
{
	gtk_init(&argc, &argv);

	GtkWidget* label = gtk_label_new("this is a new lable");
	/*这个字符串是待存的数据*/
	char* string = "helloworld";

	/*把数据string以键值STRING_KEY存放起来*/
	g_object_set_data(G_OBJECT(label), STRING_KEY, string);

	/*把刚才存到label中的以STRING_KEY为键的数据取出来*/
	char* var = g_object_get_data(G_OBJECT(label), STRING_KEY);
	printf("the string = %s \n", var);/*var就是helloworld*/

	return ;
}

/*my own component*/

#ifndef __MYOWNCOMPONENT_H
#define __MYOWNCOMPONENT_H
#include <gdk/gdk.h>
#include <gtk/gtk.h>

/*等价于G_BEGIN_DECLS*/
#ifdef __cplusplus
extern "C"
{
#endif

/*对象类型转换，最新的代码都不用GTK_CHECK_CAST,有宏把它定义为后者*/
//#define MYCOMPONENT(obj) GTK_CHECK_CAST(obj, mycomponent_get_type(), MyComponent)
#define MYCOMPONENT(obj) G_TYPE_CHECK_INSTANCE_CAST(obj, mycomponent_get_type(), MyComponent)

/*类型转换，最新的代码都不用GTK_CHECK_CLASS_CAST,有宏把它定义为后者*/
//#define MYCOMPONENT_CLASS(class) GTK_CHECK_CLASS_CAST(class, mycomponent_get_type(), MyComponentClass)
#define MYCOMPONENT_CLASS(class) G_TYPE_CHECK_CLASS_CAST(class, mycomponent_get_type(), MyComponentClass)

/*判断是否是指定的对象的类型,最新的代码都不用GTK_CHECK_TYPE,有宏把它定义为后者*/
//#define IS_MYCOMPONENT(obj) GTK_CHECK_TYPE(obj, mycomponent_get_type())
#define IS_MYCOMPONENT(obj) G_TYPE_CHECK_INSTANCE_TYPE(obj, mycomponent_get_type())

typedef struct _MyComponent MyComponent;
typedef struct _MyComponentClass MyComponentClass;

struct _MyComponent
{
	GtkHBox hBox;
	GtkWidget *button1;
	GtkWidget *button2;
};

struct _MyComponentClass
{
	GtkHBoxClass parent_class;
	//void (*my_component)(MyComponent *ttt);
	void (*my_component)(void);
};

/*可能还是用GType好吧，有#define GType GtkType*/
//GtkType mycomponent_get_type(void);
GType mycomponent_get_type(void);

GtkWidget* mycomponent_new(void);

void mycomponent_print(MyComponent *ttt);

/*等价于G_END_DECLS*/
#ifdef __cplusplus
}
#endif

#endif

#include"myComponent.h"
static void mycomponent_class_init(MyComponentClass *class);
static void mycomponent_init(MyComponent *myc);
GType mycomponent_get_type(void)
{
	static guint typeid = 0;
	if(!typeid)
	{
		/*GtkTypeInfo type_info = 
		{
			"MyComponent",
			sizeof(MyComponent),
			sizeof(MyComponentClass),
			(GtkClassInitFunc) mycomponent_class_init,
			(GtkObjectInitFunc) mycomponent_init,
			(GtkArgSetFunc)NULL,
			(GtkArgGetFunc)NULL
		};*/
		 GTypeInfo type_info =
        {
			sizeof (MyComponentClass),
			NULL,
	        NULL,
        	(GClassInitFunc) mycomponent_class_init,
		    NULL,
		    NULL,
	        sizeof (MyComponent),
	    	0,
		    (GInstanceInitFunc) mycomponent_init,
       };

/*		typeid = gtk_type_unique(gtk_hbox_get_type(), &type_info);*/
        typeid = g_type_register_static (GTK_TYPE_HBOX, "MyComponent", &type_info, 0);

	}
	return typeid;
}

enum
{
	MYCOMPONENT_SIGNAL,
	LAST_SIGNAL
};

static gint mycomponent_signals[LAST_SIGNAL] = {0};

static void mycomponent_class_init(MyComponentClass *class)
{
	//GtkObjectClass *obj = (GtkObjectClass*)class;
	GObjectClass   *object_class = G_OBJECT_CLASS(class);
	/*mycomponent_signals[MYCOMPONENT_SIGNAL] = 
		gtk_signal_new("mycomponent",
				GTK_RUN_FIRST,
				obj->type,
				GTK_SIGNAL_OFFSET(MyComponentClass, my_component),
				gtk_signal_default_marshaller,
				GTK_TYPE_NONE,
				0);
	gtk_object_class_add_signals(obj, mycomponent_signals, LAST_SIGNAL);*/
	/*实际自己定义的新的信号产生的方式是：
	 * 1）给一个已有的“标准”事件如button-press-event等添加一个回调函数
	 * 2）在上面添加的“标准”事件的回调函数中，添加发射自定义新信号的语句emit
	 */
  g_signal_new ("mycomponent",
                G_OBJECT_CLASS_TYPE (object_class),
                G_SIGNAL_RUN_FIRST,
                G_STRUCT_OFFSET (MyComponentClass, my_component),
                NULL,
                NULL,
                g_cclosure_marshal_VOID__VOID,
                G_TYPE_NONE,
                0);
	class->my_component=NULL;
}
static void mycomponent_init(MyComponent *myc)
{
	GtkWidget *hbox;
	hbox = gtk_hbox_new(TRUE, 3);
	//gtk_container_add(GTK_CONTAINER(myc), hbox);//教程这样，但不知好不好
	gtk_box_pack_start(GTK_BOX(myc), hbox, TRUE, TRUE, 0);
	myc->button1 = gtk_button_new_with_label("first of mycomponent");
	gtk_box_pack_start(GTK_BOX(hbox), myc->button1, TRUE, TRUE, 0);

	myc->button2 = gtk_button_new_with_label("second of mycomponent");
	gtk_box_pack_start(GTK_BOX(hbox), myc->button2, TRUE, TRUE, 0);

	gtk_widget_show_all(hbox);

}

GtkWidget* mycomponent_new(void)
{
	/*新建一个对象，这里最新的代码最好不用gtk_type_new*/
	//return GTK_WIDGET(gtk_type_new(mycomponent_get_type()));
	//return GTK_WIDGET(g_object_new(mycomponent_get_type(), NULL));

	/*在这里设置父类hBox对象的属性，实际应该就是new该父类对象需要的参数*/
	return GTK_WIDGET(g_object_new(mycomponent_get_type(),
				"homogeneous", TRUE,
				"spacing", 30,
				NULL));
}

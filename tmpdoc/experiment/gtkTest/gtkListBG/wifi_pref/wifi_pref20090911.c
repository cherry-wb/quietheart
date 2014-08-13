/*问题:
 1.build_wifi_list中循环添加元素从1开始吗？那么扫描的时候第0个位置没有东西？
 2.下面的方法计算strength的时候，已经超过了1？
add_net.strength=(double)(100+pp[i].Singal_level)/100;
 * */
#include<gtk/gtk.h>
#include<string.h>
#include"applet.h"

/*如果在pc机器上面编译的话设置非0这样会省去一些没有硬件的麻烦*/
#ifndef MY_PC_DEBUG
#define MY_PC_DEBUG 0
#endif
#define MY_DEBUG_OUT 1

#define IMG_DIR "./resource/"
#define IMG_FILE IMG_DIR"./nm-adhoc.png"
#define IMG_ENCRYPTED IMG_DIR"./network-wireless-encrypted_wifi.png"
#define IMG_UNENCRYPTED IMG_DIR"./nm-device-wired.png"

#define SCANBTN_X 0
#define SCANBTN_Y 250
#define CONTBTN_X 200
#define CONTBTN_Y 250
#define OKBTN_X 600
#define OKBTN_Y 250
#define CACLBTN_X 700
#define CACLBTN_Y 250

/*information of wireless*/
typedef struct libin_wifi libin_wifi;
//struct libin_wifi* pp;
#if MY_PC_DEBUG == 0
libin_wifi* pp;
#else
/*字符串如果是空就不能strcmp了*/
libin_wifi pp[] = {
	{(unsigned char)0, NULL, '\0', NULL,NULL, NULL, '\0', NULL,NULL,NULL,NULL,NULL, 0, 0},
	{(unsigned char)1, NULL, '\0', NULL,NULL, "neu1", '\0', "off",NULL,NULL,NULL,NULL, -10, 0},
	{(unsigned char)2, NULL, '\0', NULL,NULL, "neu2", '\0', "on",NULL,NULL,NULL,NULL, -20, 0},
	{(unsigned char)3, NULL, '\0', NULL,NULL, "neu3", '\0', "off",NULL,NULL,NULL,NULL, -30, 0},
	{(unsigned char)4, NULL, '\0', NULL,NULL, "neu4", '\0', "off",NULL,NULL,NULL,NULL, -40, 0},
	{(unsigned char)5, NULL, '\0', NULL,NULL, "neu5", '\0', "off",NULL,NULL,NULL, -50, 0},
	{(unsigned char)0, NULL, '\0', NULL,NULL, NULL, '\0', NULL,NULL,NULL,NULL,NULL, 0, 0},
	};
#endif
static GtkWidget *build_wifi_list(libin_wifi* pp);
static void clear_wifi_list(GtkWidget *gtk_list);
static GtkWidget* list_element_new(const char* radiontext,
		const char* imagepath, gdouble length,GSList** group);
static gboolean select_radio(GtkToggleButton *button, gpointer data);
static void Scan_Button_Pressed(GtkButton *button, gpointer   data);

/*buttons*/
static GtkWidget *Scan_Button = NULL;
static GtkWidget *Connect_Button = NULL;
static GtkWidget *Ok_Button = NULL;
static GtkWidget *Cancel_Button = NULL;

/*list element content*/
typedef struct _Element
{
	GtkWidget* hbox ;
	GtkWidget* radiobutton;
	GtkWidget* radiolabel;
	GtkWidget* image;
	GtkWidget* bar;
}Element;

	//g_object_set_data (G_OBJECT (element->radiobutton), "network", g_strdup (pp[i].ESSID));
	//tag_essid = g_object_get_data (G_OBJECT (element->radiobutton), "network");

static void Scan_Button_Pressed(GtkButton *button, gpointer data)
{
	GtkWidget *gtk_list = GTK_WIDGET(data);
#if MY_DEBUG_OUT == 1
	g_print("test scan button pressed\n");
#endif
	gtk_widget_set_sensitive(Scan_Button, FALSE);
	gtk_widget_set_sensitive(Connect_Button, FALSE);
	gtk_widget_set_sensitive(Ok_Button, FALSE);

	clear_wifi_list(gtk_list);
	//popup();
	/*int i;
	for(i=1;i<=10;i++)
	{
		pp[i].NET_NUMBER=0;
	}
	pp = scanning();
	build_wifi_list(pp);
	*/
	sleep(1);
	gtk_widget_set_sensitive(Scan_Button, TRUE);
	gtk_widget_set_sensitive(Connect_Button, TRUE);
	gtk_widget_set_sensitive(Ok_Button, TRUE);
}
static gboolean select_radio(GtkToggleButton *button, gpointer data)
{
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)))
	{
		;
#if MY_DEBUG_OUT == 1
		g_print("%s selected\n", (gchar*)data);
#endif
	}
	gchar *network = g_object_get_data(G_OBJECT(button), "network");
	gchar *password = g_object_get_data(G_OBJECT(button), "password");
#if MY_DEBUG_OUT == 1
	g_print("select network is:%s\n", network);
	g_print("network password is:%s\n", password);
#endif
	//gtk_image_set_from_file(img,file);
}
static GtkWidget* list_element_new(const char* radiontext,const char* imagepath,
											gdouble length,GSList** group)
{
	GtkWidget* ebox = NULL;
	Element*  element = g_malloc0(sizeof(Element));
	element->hbox = NULL;
	element->radiobutton = NULL;
	element->radiolabel = NULL;
	element->image = NULL;
	element->bar = NULL;

	/*eventbox*/
	ebox = gtk_event_box_new();
	gtk_event_box_set_visible_window((GtkEventBox *)ebox, FALSE);
	g_object_set_data (G_OBJECT (ebox), "element_content", element);
	
	/*hbox*/
	element->hbox = gtk_hbox_new(FALSE,0);
#if MY_DEBUG_OUT == 1
	g_print("add hbox to ebox\n");
#endif
	gtk_container_add(GTK_CONTAINER(ebox),element->hbox);
#if MY_DEBUG_OUT == 1
	g_print("add hbox to ebox ok\n");
#endif
	/*radiobutton*/
	element->radiobutton = gtk_radio_button_new(*group);
	element->radiolabel = gtk_label_new(radiontext);
	*group=gtk_radio_button_group(GTK_RADIO_BUTTON(element->radiobutton));
	//gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(element->radiobutton),FALSE);
   	//set_label_fg_color(element->radiolabel);
	//element->radiobutton = gtk_radio_button_new_with_label(*group, radiontext);
	g_signal_connect(G_OBJECT(element->radiobutton), "toggled",
			G_CALLBACK(select_radio), "radio button clicked");
#if MY_DEBUG_OUT == 1
	g_print("add label to radio\n");
#endif
	gtk_container_add(GTK_CONTAINER(element->radiobutton), element->radiolabel);
#if MY_DEBUG_OUT == 1
	g_print("add label to radio ok\n");
#endif

	gtk_box_pack_start(GTK_BOX(element->hbox) ,element->radiobutton,FALSE,FALSE,10);
	
	/*image*/
	if(strlen(imagepath) == 0)
	{
		element->image = gtk_image_new();
	}
	else
	{
		element->image = gtk_image_new_from_file (imagepath);
	}
	//gtk_widget_set_size_request(GTK_WIDGET(element->image), SECURITY_IMAGE_WIDTH, ELEMENT_HEIGTH);
	gtk_box_pack_start(GTK_BOX(element->hbox) ,element->image,FALSE,FALSE,10);

	/*progress bar*/
	element->bar = gtk_progress_bar_new ();
	//gtk_widget_set_usize(GTK_WIDGET(element->bar), BAR_WIDTH, ELEMENT_HEIGTH);
	//gtk_widget_set_size_request (element->bar, 50, 30);
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (element->bar), length);
	gtk_box_pack_start(GTK_BOX(element->hbox) ,element->bar,FALSE,FALSE,10);

	return ebox;
}

static GtkWidget *build_wifi_list(libin_wifi* pp)
{
	GtkWidget *gtk_list;
	GList *items;
	GList *copy;
	GtkWidget *listitem;
	GtkWidget *elementItem;
	GSList *group;
	GtkWidget *radio;

	gint i;
	
	//must initialize here for first use!
	items = NULL;
	copy = NULL;
	group = NULL;

	/*gtklist*/
	gtk_list = gtk_list_new();
	//gtk_widget_size_request()
	Element*  element_content = NULL;

	for(i=1;i<=pp[i].NET_NUMBER;i++)
	{//.NET_NUMBER==0means the last??
		listitem = gtk_list_item_new();
		items = g_list_append(items, listitem);
		elementItem	= list_element_new(pp[i].ESSID, IMG_FILE,
				(double)(100+pp[i].Singal_level)/100, &group);
		char *onState = "on";
		char *offState = "off";
		if(!strcmp("on",pp[i].Encryption_key))
		{//if crypted
			elementItem	= list_element_new(pp[i].ESSID, IMG_ENCRYPTED,
					(double)(100+pp[i].Singal_level)/100, &group);
		}
		/*else if(!strcmp("off",pp[i].Encryption_key))
		{
			elementItem	= list_element_new(pp[i].ESSID, IMG_FILE,
					(double)(100+pp[i].Singal_level)/100, &group);
			//elementItem	= list_element_new(pp[i].ESSID, IMG_UNENCRYPTED,
			//		(double)(100+pp[i].Singal_level)/100, &group);
		}*/
		else
		{
			elementItem	= list_element_new(pp[i].ESSID, IMG_FILE,
					(double)(100+pp[i].Singal_level)/100, &group);
		}
		gtk_container_add(GTK_CONTAINER(listitem), elementItem);
		gtk_widget_show_all(listitem);
		//gtk_container_add(GTK_CONTAINER(gtk_list), listitem);
		element_content = g_object_get_data (G_OBJECT (elementItem), "element_content");
		g_object_set_data (G_OBJECT (element_content->radiobutton), "network", g_strdup (pp[i].ESSID));
		g_object_set_data (G_OBJECT (element_content->radiobutton), "password", pp[i].Encryption_key);
	}
	/*for(i = 0; i < 5; ++i)
	{
		listitem = gtk_list_item_new();
		items = g_list_append(items, listitem);
		elementItem	= list_element_new("name", IMG_FILE, 0.8, &group);
		//gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button),TRUE);
#if MY_DEBUG_OUT == 1
	g_print("add element to listitem\n");
#endif
		gtk_container_add(GTK_CONTAINER(listitem), elementItem);
#if MY_DEBUG_OUT == 1
	g_print("add element to listitem ok\n");
#endif
		gtk_widget_show_all(listitem);
	}*/
	copy = g_list_copy(items);
	g_list_free(items);
	items = NULL;
	gtk_list_append_items(GTK_LIST(gtk_list), copy);
	return gtk_list;
}
static void clear_wifi_list(GtkWidget *gtk_list)
{
	gtk_list_clear_items(GTK_LIST(gtk_list), 0, -1);
}
gint main(gint argc, gchar *argv[])
{

	GtkWidget *window;
	GtkWidget *vbox;

	GtkWidget *gtk_list;

	GtkWidget *fixed;
	GtkWidget *button;

	gtk_init(&argc, &argv);

	/*window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);
	gtk_window_set_title(GTK_WINDOW(window), "test radio");

	/*vbox*/
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	/*gtklist*/
#if MY_PC_DEBUG == 0
	pp = scanning();
#endif
	gtk_list = build_wifi_list(pp);

	gtk_box_pack_start(GTK_BOX(vbox), gtk_list, FALSE, FALSE, 0);

	/*fixed*/
	fixed = gtk_fixed_new();
	gtk_box_pack_start(GTK_BOX(vbox), fixed, FALSE, FALSE, 0);

	/*button*/
	button = gtk_button_new_with_label("scan");
	Scan_Button = button;
	g_signal_connect (Scan_Button, "clicked", G_CALLBACK (Scan_Button_Pressed), gtk_list);
	gtk_fixed_put(GTK_FIXED(fixed), Scan_Button, SCANBTN_X, SCANBTN_Y);

	button = gtk_button_new_with_label("connect");
	Connect_Button = button;
	gtk_fixed_put(GTK_FIXED(fixed), Connect_Button, CONTBTN_X, CONTBTN_Y);

	button = gtk_button_new_with_label("ok");
	Ok_Button = button;
	gtk_fixed_put(GTK_FIXED(fixed), button, OKBTN_X, OKBTN_Y);

	button = gtk_button_new_with_label("cancel");
	Cancel_Button = button;
	gtk_fixed_put(GTK_FIXED(fixed), Cancel_Button, CACLBTN_X, CACLBTN_Y);

	gtk_widget_show_all(fixed);

	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}

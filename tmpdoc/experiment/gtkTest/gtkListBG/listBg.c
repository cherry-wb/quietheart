#include<gtk/gtk.h>
#define IMG_DIR "./resource/"
#define IMG_FILE IMG_DIR"./nm-adhoc.png"
#define IMG_ENCRYPTED IMG_DIR"./network-wireless-encrypted_wifi.png"
#define IMG_UNENCRYPTED IMG_DIR"./nm-device-wired.png"
#define IMG_BG1

#define LIST_WIDTH 800
#define LIST_HEIGHT 300

#define RADIO_BTN_WIDTH 200
#define RADIO_BTN_HEIGHT 30

#define ITEM_IMG_WIDTH 30
#define ITEM_IMG_HEIGHT 30

#define ITEM_BAR_WIDTH 500
#define ITEM_BAR_HEIGHT 30

#define CTL_BTN_WIDTH 90
#define CTL_BTN_HEIGHT 30

#define SCANBTN_X 0
#define SCANBTN_Y 50
#define CONTBTN_X 200
#define CONTBTN_Y 50


/*list element content*/
typedef struct _Element
{
	GtkWidget* hbox ;
	GtkWidget* radiobutton;
	GtkWidget* radiolabel;
	GtkWidget* image;
	GtkWidget* bar;
}Element;

static void fill_list(GtkWidget *gtk_list);

static GtkWidget* list_element_new(const char* radiontext,
		const char* imagepath, gdouble length,GSList** group);

static gboolean select_radio(GtkToggleButton *button, gpointer data);

static void Scan_Button_Pressed(GtkButton *button, gpointer   data);

static void Connect_Button_Pressed(GtkButton *button, gpointer data);


static gboolean select_radio(GtkToggleButton *button, gpointer data)
{
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)))
	{
		g_print("%s selected\n", (gchar*)data);
	}
}
static void Scan_Button_Pressed(GtkButton *button, gpointer data)
{
	g_print("scan pressed\n");
}

static void Connect_Button_Pressed(GtkButton *button, gpointer data)
{
	g_print("connect pressed\n");
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

	gtk_widget_set_size_request (element->radiobutton, RADIO_BTN_WIDTH, RADIO_BTN_HEIGHT);
	gtk_box_pack_start(GTK_BOX(element->hbox) ,element->radiobutton,FALSE,FALSE,10);
	
	/*image*/
	if(NULL == imagepath)
	{
		element->image = gtk_image_new();
	}
	else
	{
		element->image = gtk_image_new_from_file (imagepath);
	}
	gtk_widget_set_size_request (element->image, ITEM_IMG_WIDTH, ITEM_IMG_HEIGHT);
	//gtk_widget_set_size_request(GTK_WIDGET(element->image), SECURITY_IMAGE_WIDTH, ELEMENT_HEIGTH);
	gtk_box_pack_start(GTK_BOX(element->hbox) ,element->image,FALSE,FALSE,10);

	/*progress bar*/
	element->bar = gtk_progress_bar_new ();
	//gtk_widget_set_usize(GTK_WIDGET(element->bar), BAR_WIDTH, ELEMENT_HEIGTH);
	//gtk_widget_set_size_request (element->bar, 50, 30);
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (element->bar), length);

	gtk_widget_set_size_request (element->bar, ITEM_BAR_WIDTH, ITEM_BAR_HEIGHT);

	gtk_box_pack_start(GTK_BOX(element->hbox) ,element->bar,FALSE,FALSE,10);

	return ebox;
}

static void fill_list(GtkWidget *gtk_list)
{
	//GtkWidget *gtk_list;
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

	Element*  element_content = NULL;

	for(i = 0; i < 5; ++i)
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
	}
	copy = g_list_copy(items);
	g_list_free(items);
	items = NULL;
	gtk_list_append_items(GTK_LIST(gtk_list), copy);
	//return gtk_list;
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
	gtk_list = gtk_list_new();
	fill_list(gtk_list);
	gtk_widget_set_size_request (gtk_list, LIST_WIDTH, LIST_HEIGHT);
	gtk_box_pack_start(GTK_BOX(vbox), gtk_list, FALSE, FALSE, 0);

	/*fixed*/
	fixed = gtk_fixed_new();
	gtk_box_pack_start(GTK_BOX(vbox), fixed, FALSE, FALSE, 0);

	/*button*/
	button = gtk_button_new_with_label("Scan");
	g_signal_connect (button, "clicked",
			G_CALLBACK (Scan_Button_Pressed), gtk_list);
	gtk_widget_set_size_request (button, CTL_BTN_WIDTH, CTL_BTN_HEIGHT);
	gtk_fixed_put(GTK_FIXED(fixed), button, SCANBTN_X, SCANBTN_Y);

	button = gtk_button_new_with_label("Connect");
	g_signal_connect (button, "clicked",
			G_CALLBACK (Connect_Button_Pressed), gtk_list);
	gtk_widget_set_size_request (button, CTL_BTN_WIDTH, CTL_BTN_HEIGHT);
	gtk_fixed_put(GTK_FIXED(fixed), button, CONTBTN_X, CONTBTN_Y);

	gtk_widget_show_all(fixed);

	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}

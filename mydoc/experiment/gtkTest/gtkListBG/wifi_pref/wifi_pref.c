/*问题:
 1.fill_wifi_list中循环添加元素从1开始吗？那么扫描的时候第0个位置没有东西？
answer:从1开始。
 2.下面的方法计算strength的时候，已经超过了1？
add_net.strength=(double)(100+pp[i].Singal_level)/100;
answer:Singal_level是负数。
 * */
#include <errno.h>
#include<unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include<string.h>
#include<gtk/gtk.h>
#include"applet.h"
//#include <hildon-widgets/hildon-program.h>


/*如果在pc机器上面编译的话设置非0这样会省去一些没有硬件的麻烦*/
#ifndef MY_PC_DEBUG
#define MY_PC_DEBUG 0
#endif
#define MY_DEBUG_OUT 2

#define IMG_DIR "./resource/"
#define IMG_FILE IMG_DIR"./nm-adhoc.png"
#define IMG_ENCRYPTED IMG_DIR"./network-wireless-encrypted_wifi.png"
#define IMG_UNENCRYPTED IMG_DIR"./nm-device-wired.png"

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
#define OKBTN_X 600
#define OKBTN_Y 50
#define CACLBTN_X 700
#define CACLBTN_Y 50


#define  NUM 100
/*declarations*/
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

static int is_connected = 0;
static gchar *selectEssid = NULL;
static gchar *selectPassword = NULL;


int  ret_size=0;
char GATEWAY[NUM];
char IP[NUM];
char NETMASK[NUM];

/*functions*/
static void fill_wifi_list(GtkWidget *gtk_list, libin_wifi* pp);

static void clear_wifi_list(GtkWidget *gtk_list);

static GtkWidget* list_element_new(const char* radiontext,
		const char* imagepath, gdouble length,GSList** group);

static gboolean scanning_call_back(gpointer data);

static gboolean select_radio(GtkToggleButton *button, gpointer data);

static void Scan_Button_Pressed(GtkButton *button, gpointer   data);

static void Connect_Button_Pressed(GtkButton *button, gpointer data);

static void Cancel_Button_Pressed(GtkButton *button, gpointer data);

static void Ok_Button_Pressed(GtkButton *button, gpointer data);

static gboolean connect_call_back(gpointer user_data);
static gboolean connect_wifi(gpointer user_data);
static void wifi_dhclient();
static gboolean disconnect_idle_call_back(gpointer user_data);
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


static void Scan_Button_Pressed(GtkButton *button, gpointer data)
{
	GtkWidget *gtk_list = GTK_WIDGET(data);
#if MY_DEBUG_OUT == 2
	g_print("go into scan button pressed\n");
#endif
	gtk_widget_set_sensitive(Scan_Button, FALSE);
	gtk_widget_set_sensitive(Connect_Button, FALSE);
	gtk_widget_set_sensitive(Ok_Button, FALSE);

	clear_wifi_list(gtk_list);
	//popup();
	//g_idle_add(sleep, 1);
#if MY_DEBUG_OUT == 2
	g_print("before idle\n");
#endif
	g_idle_add(scanning_call_back, gtk_list);
#if MY_DEBUG_OUT == 2
	g_print("after idle\n");
	sleep(2);
#endif
#if MY_DEBUG_OUT == 2
	g_print("go outof scan button pressed\n");
#endif
}

static void Connect_Button_Pressed(GtkButton *button, gpointer data)
{
#if MY_DEBUG_OUT == 1
	g_print("test connect button pressed\n");
#endif
	if(is_connected == 0)
	{
#if MY_DEBUG_OUT == 1
		g_print("begin to connect.\n");
#endif
		is_connected = 1;
		gtk_widget_set_sensitive(Scan_Button, FALSE);
		gtk_widget_set_sensitive(Connect_Button, FALSE);
		g_idle_add(connect_call_back, NULL);		
		//gtk_button_set_label(GTK_BUTTON(Connect_Button), "Disconnect");
	}
	else
	{
#if MY_DEBUG_OUT == 1
		g_print("begin to disconnect.\n");
#endif
		is_connected = 0;
		gtk_widget_set_sensitive(Scan_Button, FALSE);
		gtk_widget_set_sensitive(Connect_Button, FALSE);
		g_idle_add(disconnect_idle_call_back, NULL);
		//gtk_button_set_label(GTK_BUTTON(Connect_Button), "Connect");
	}
}

static gboolean connect_wifi(gpointer user_data)
{
	wifi_dhclient();
	gtk_widget_set_sensitive(Scan_Button, TRUE);
	gtk_widget_set_sensitive(Connect_Button, TRUE);
	return FALSE;
}

static void wifi_dhclient()
{
	/*char r_buf[NUM];
	int  fd = 0;
	int i = 0;

	if((mkfifo("/tmp/fifoserver",O_CREAT|O_EXCL)<0)&&(errno!=EEXIST))
	{
		printf("cannot create fifoserver\n");
	}
#if MY_DEBUG_OUT == 1
	g_print("Preparing for reading bytes...\n");
#endif
	fd=open("/tmp/fifoserver",O_RDONLY|O_NONBLOCK,0);
#if MY_DEBUG_OUT == 1
	g_print("wifi_dhclient()3 fd = %d\n",fd);
#endif
	if(fd==-1)
	{
		printf("open read error\n");
		// exit(1); 
	}
	printf("wifi_dhclient()4\n");
	*/
#if MY_PC_DEBUG == 0
	system("cd /lib;./dhclient");
#else
	g_print("do the connect...\n");
	sleep(2);
#endif

	/*
	memset(GATEWAY,0,sizeof(GATEWAY));
	ret_size=read(fd,GATEWAY,NUM);
#if MY_DEBUG_OUT == 1
	g_print("ret_size = %d\n",ret_size);
#endif
	if(ret_size==-1)
	{
		if(errno==EAGAIN)
		{
			printf("no data avlaible\n");
		}
	}
#if MY_DEBUG_OUT == 1
	g_print("GATEWAY == %s\n",GATEWAY);
#endif

	memset(NETMASK,0,sizeof(NETMASK));
	ret_size=read(fd,NETMASK,NUM);
	if(ret_size==-1)
	{
		if(errno==EAGAIN)
		{
			printf("no data avlaible\n");
		}
	}
#if MY_DEBUG_OUT == 1
	g_print("NETMASK == %s\n",NETMASK);
#endif

	memset(IP,0,sizeof(IP));
	ret_size=read(fd,IP,NUM);
	if(ret_size==-1)
	{
		if(errno==EAGAIN)
		{
			printf("no data avlaible\n");
		}
	}
#if MY_DEBUG_OUT == 1
	g_print("IP == %s\n",IP);
#endif

	unlink("/tmp/fifoserver");
#if MY_DEBUG_OUT == 1
	g_print("wifi_dhclient()8\n");
#endif
*/
}

static void Ok_Button_Pressed(GtkButton *button, gpointer data)
{
#if MY_DEBUG_OUT == 1
	g_print("test ok button pressed\n");
#endif
}

static void Cancel_Button_Pressed(GtkButton *button, gpointer data)
{
#if MY_DEBUG_OUT == 1
	g_print("test cancel button pressed\n");
#endif
	gtk_widget_set_sensitive(Scan_Button, TRUE);
	gtk_widget_set_sensitive(Connect_Button, TRUE);
	/*...must add others things...*/
	if(strcmp("Connect",gtk_button_get_label(GTK_BUTTON(Connect_Button))))
	{
		is_connected = 0;
	}
	else
	{
		is_connected = 1;
	}
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
	selectEssid = network;
	selectPassword = password;
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

static void fill_wifi_list(GtkWidget *gtk_list, libin_wifi* pp)
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
			//elementItem	= list_element_new(pp[i].ESSID, IMG_FILE,
			//		(double)(100+pp[i].Singal_level)/100, &group);
			elementItem	= list_element_new(pp[i].ESSID, NULL,
					(double)(100+pp[i].Singal_level)/100, &group);
		}
		gtk_container_add(GTK_CONTAINER(listitem), elementItem);
		gtk_widget_show_all(listitem);
		//gtk_container_add(GTK_CONTAINER(gtk_list), listitem);
		element_content = g_object_get_data (G_OBJECT (elementItem), "element_content");
		g_object_set_data (G_OBJECT (element_content->radiobutton), "network", g_strdup (pp[i].ESSID));
		g_object_set_data (G_OBJECT (element_content->radiobutton), "password", pp[i].Encryption_key);
		if(1 == i)
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(element_content->radiobutton),TRUE);
			select_radio(GTK_TOGGLE_BUTTON(element_content->radiobutton), NULL);
		}
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
	//return gtk_list;
}

static gboolean scanning_call_back(gpointer data)
{
#if MY_DEBUG_OUT == 2
	g_print("go into scanning_call_back\n");
#endif
	GtkWidget *gtk_list = GTK_WIDGET(data);
#if MY_PC_DEBUG == 0
	int i;
	for(i=1;i<=10;i++)
	{
		pp[i].NET_NUMBER=0;
	}
	pp = scanning();
	fill_wifi_list(gtk_list, pp);
#else

#if MY_DEBUG_OUT == 2
	sleep(1);
	g_print("scanning_call_back after sleep\n");
#endif
	fill_wifi_list(gtk_list, pp+1);

#endif
	gtk_widget_set_sensitive(Scan_Button, TRUE);
	gtk_widget_set_sensitive(Connect_Button, TRUE);
	gtk_widget_set_sensitive(Ok_Button, TRUE);

#if MY_DEBUG_OUT == 2
	g_print("go outof scanning_call_back\n");
#endif
	return FALSE;
}

static gboolean connect_call_back(gpointer user_data)
{
       char *dev;
       char * key=NULL;
       dev="eth0";
#if MY_PC_DEBUG == 0
       iwconfig_eth0_key(dev,"off");
#endif
       //if(net)
        //  g_free(net);
       /*else if (!strcmp(tag_key,"on")) 
       {     net=g_strdup(tag_essid);
             //GtkWidget *dialog_window_temp=popup_widow_password (applet->wifi_list_window);
             if (gtk_dialog_run(GTK_DIALOG(dialog_window_temp)) == GTK_RESPONSE_ACCEPT)
             {  printf("Connect_Button_Pressed-KEY\n");
                key = gtk_entry_get_text (GTK_ENTRY (g_object_get_data(G_OBJECT (dialog_window_temp), "entry")));
                printf("key=%s\n",key);
                printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
	        iwconfig_eth0_key(dev,key);
	        iwconfig_eth0_key(dev,"on");
                iwconfig_eth0_essid(dev,net);
		gtk_widget_destroy(dialog_window_temp); 
                g_idle_add(connect_wifi, applet);
                return FALSE;
             }
        }*/

	   //net=g_strdup(tag_essid);
#if MY_DEBUG_OUT == 1
	   g_print("dev=%s\n",dev);
	   g_print("selectEssid=%s\n",selectEssid);
	   g_print("selectPassword=%s\n",selectPassword);
#endif
	   //g_print("tag_key=%s\n",tag_key);
	   //如果是关闭密码状态
	   if(strcmp(selectPassword,"on"))
	   {
#if MY_PC_DEBUG == 0
		   iwconfig_eth0_essid(dev,selectEssid); 
#endif
		   //g_idle_add(connect_wifi, NULL);
		   connect_wifi(NULL);
	   } 
		gtk_button_set_label(GTK_BUTTON(Connect_Button), "Disconnect");
     /*else
       {  
	   GtkWidget *dialog_window_temp=popup_widow_password (applet->wifi_list_window);
           if (gtk_dialog_run(GTK_DIALOG(dialog_window_temp)) == GTK_RESPONSE_ACCEPT)
           {   printf("Connect_Button_Pressed-KEY\n");
               key = gtk_entry_get_text (GTK_ENTRY (g_object_get_data(G_OBJECT (dialog_window_temp), "entry")));
               printf("key=%s\n",key);
               printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
	       iwconfig_eth0_essid(dev,net);
	       iwconfig_eth0_key(dev,key);
	       iwconfig_eth0_key(dev,"on");
		gtk_widget_destroy(dialog_window_temp); 
               g_idle_add(connect_wifi, applet);
           }
          else        
           {
                gtk_widget_destroy(dialog_window_temp);
		GtkWidget * IP_Con_Button = glade_xml_get_widget(applet->wifi_list_window->windowXML, "IP_Button");
		GtkWidget * Scan_Button = glade_xml_get_widget(applet->wifi_list_window->windowXML, "Scan_Button");
		GtkWidget * Connect_Button = glade_xml_get_widget(applet->wifi_list_window->windowXML, "Connect_Button");
		gtk_widget_set_sensitive(IP_Con_Button, TRUE);
		gtk_widget_set_sensitive(Scan_Button, TRUE);
		gtk_widget_set_sensitive(Connect_Button, TRUE);
                nma_set_state (applet, NM_STATE_DISCONNECTED);
           }         
      }*/
	
   return FALSE;
}

static gboolean disconnect_idle_call_back(gpointer user_data)
{
#if MY_PC_DEBUG == 0
	system("ifdown eth0");
	system("ifconfig eth0 down");
#else
	g_print("do the disconnect...\n");
	sleep(2);
#endif
	gtk_button_set_label(GTK_BUTTON(Connect_Button), "Connect");
	gtk_widget_set_sensitive(Scan_Button, TRUE);
	gtk_widget_set_sensitive(Connect_Button, TRUE);
	return FALSE;
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

	//HildonProgram *program;
	//HildonWindow *window;

	//program = HILDON_PROGRAM(hildon_program_get_instance());
	//g_set_application_name("Hello maemo!");

	//window = HILDON_WINDOW(hildon_window_new());
	//hildon_program_add_window(program, window);

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
	gtk_list = gtk_list_new();
	fill_wifi_list(gtk_list, pp);
	gtk_widget_set_size_request (gtk_list, LIST_WIDTH, LIST_HEIGHT);
	gtk_box_pack_start(GTK_BOX(vbox), gtk_list, FALSE, FALSE, 0);

	/*fixed*/
	fixed = gtk_fixed_new();
	gtk_box_pack_start(GTK_BOX(vbox), fixed, FALSE, FALSE, 0);

	/*button*/
	button = gtk_button_new_with_label("Scan");
	Scan_Button = button;
	g_signal_connect (Scan_Button, "clicked",
			G_CALLBACK (Scan_Button_Pressed), gtk_list);
	gtk_widget_set_size_request (Scan_Button, CTL_BTN_WIDTH, CTL_BTN_HEIGHT);
	gtk_fixed_put(GTK_FIXED(fixed), Scan_Button, SCANBTN_X, SCANBTN_Y);

	button = gtk_button_new_with_label("Connect");
	Connect_Button = button;
	g_signal_connect (Connect_Button, "clicked",
			G_CALLBACK (Connect_Button_Pressed), gtk_list);
	gtk_widget_set_size_request (Connect_Button, CTL_BTN_WIDTH, CTL_BTN_HEIGHT);
	gtk_fixed_put(GTK_FIXED(fixed), Connect_Button, CONTBTN_X, CONTBTN_Y);

	button = gtk_button_new_with_label("Ok");
	Ok_Button = button;
	g_signal_connect (Ok_Button, "clicked",
			G_CALLBACK (Ok_Button_Pressed), gtk_list);
	gtk_widget_set_size_request (Ok_Button, CTL_BTN_WIDTH, CTL_BTN_HEIGHT);
	gtk_fixed_put(GTK_FIXED(fixed), button, OKBTN_X, OKBTN_Y);

	button = gtk_button_new_with_label("Cancel");
	Cancel_Button = button;
	g_signal_connect (Cancel_Button, "clicked",
			G_CALLBACK (Cancel_Button_Pressed), gtk_list);
	gtk_widget_set_size_request (Cancel_Button, CTL_BTN_WIDTH, CTL_BTN_HEIGHT);
	gtk_fixed_put(GTK_FIXED(fixed), Cancel_Button, CACLBTN_X, CACLBTN_Y);

	gtk_widget_show_all(fixed);

	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}

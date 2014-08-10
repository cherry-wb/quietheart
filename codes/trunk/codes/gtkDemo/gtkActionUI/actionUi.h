#ifndef ACTION_UI__H
#define ACTION_UI__H

#include<gtk/gtk.h>
/*定义了每个构件的层次关系*/
/*有待添加popup菜单*/
static const gchar* ui_markup =
 "<ui>"
 /*这里是一个菜单栏*/
  "<menubar>"
   "<menu action='Menu1'>" //menu1,这是一个单级菜单
    "<menuitem action='menuitem1.1'/>" //menuitem1.1
    "<separator/>"
    "<menuitem action='menuitem1.2'/>" //menuitem1.2
   "</menu>"
   "<menu action='Menu2'>" //menu2一个多级菜单？
    "<menu action='Menu2.1'>" //menu2.1多级菜单的子菜单
     "<menuitem action='menuitem2.1.1'/>"//menuitem2.1.1
     "<menuitem action='menuitem2.1.2'/>"//menuitem2.1.2
    "</menu>"
    "<separator/>"
    "<menuitem action='menuitem2.2'/>" //menuitem2.2
    "<menu action='Menu2.3'>" //menu2.3又一个子菜单
     "<menuitem action='menuitem2.3.1'/>" //menuitem2.3.1
     "<separator/>"
     "<menuitem action='menuitem2.3.2'/>" //menuitem2.3.2
    "</menu>"
   "</menu>"
  "</menubar>"
  /*这里是一个工具栏*/
  "<toolbar name='toolbar_navigation'>"
   "<toolitem action='menuitem1.2'/>"
   "<toolitem action='Back'/>"
   "<toolitem action='Forward'/>"
   "<toolitem action='RefreshStop'/>"
   "<toolitem action='Home'/>"
  "</toolbar>"
 "</ui>";

 /*声明每项的回调函数*/
void
on_action_window_new_activate(GtkAction*, gchar*);

void
on_action_tab_new_activate(GtkAction*, gchar*);

void
on_action_toolbar_bookmarks_activate(GtkAction*, gchar*);

void
on_action_panels_activate(GtkAction*, gchar*);

void
on_action_refresh_stop_activate(GtkAction*, gchar*);

void
on_action_back_activate(GtkAction*, gchar*);

void
on_action_forward_activate(GtkAction*, gchar*);

void
on_action_home_activate(GtkAction*, gchar*);

/*定义每一个构件相应的动作属性集合*/
 /*每一项结构定义如下：
  * typedef struct {
  *   const gchar     *name; //action名字标识
  *   const gchar     *stock_id; //对应的图标stock id
  *   const gchar     *label; //和翻译相关的？
  *   const gchar     *accelerator; //快捷键
  *   const gchar     *tooltip; //tooltips提示信息
  *   GCallback  callback; //回调函数
  * } GtkActionEntry;
  *
  * */
//实际完全可以定义一个GtkActionEntry,这里定义两个便于学习更多的应用方法
//需要注意的是：这里带下划线的是显示给用户的名字，前面的名称只是一个标识。
static const GtkActionEntry menu_entries[] =
{
 { "Menu1", NULL, "_FileMenu1" },
 { "menuitem1.1", GTK_STOCK_FILE 
 , NULL, "<Ctrl>n"
 , "Open a new window", G_CALLBACK(on_action_window_new_activate) },
 { "menuitem1.2", GTK_STOCK_NEW //这个既是菜单的又是工具栏的
 , NULL, "<Ctrl>t"
 , "Open a new tab", G_CALLBACK(on_action_tab_new_activate) },
 { "Menu2", NULL, "_ViewMenu2" }, //试试此处不一致的后果
 { "Menu2.1", NULL, "_ToolbarsMenu2.1" },
 { "menuitem2.1.1", NULL
 , "_Bookmarkbarmenuitem2.1.1", ""
 , "hm?", G_CALLBACK(on_action_toolbar_bookmarks_activate)
 },
 { "menuitem2.1.2", NULL
 , "_Downloadbarmenuitem2.1.2", ""
 , "hm?", NULL/*G_CALLBACK(on_action_toolbar_downloads_activate)*/
 },
 { "menuitem2.2", NULL
 , "_Panelsmenuitem2.2", "F9"
 , "hm?", G_CALLBACK(on_action_panels_activate)
 },
 { "Menu2.3", NULL, "_HistoryMenu2.1" },
 { "menuitem2.3.1", NULL
 , "_Enabledmenuitem2.3.1", ""
 , "hm?", NULL/*G_CALLBACK(on_action_reloadevery_enable_activate)*/
 },
 { "menuitem2.3.2", NULL
 , "_30 secondsmenuitem2.3.2", ""
 , "Refresh Every _30 Seconds", NULL },
 { "RefreshStop", GTK_STOCK_REFRESH/*GTK_STOCK_REFRESH*/
 , NULL, ""
 , NULL, G_CALLBACK(on_action_refresh_stop_activate) },

};
static const guint menu_entries_n = G_N_ELEMENTS(menu_entries);

static const GtkActionEntry toolbar_entries[] =
{
 { "Back", GTK_STOCK_GO_BACK
 , NULL, "<Alt>Left"
 , "hm?", G_CALLBACK(on_action_back_activate) },
 { "Forward", GTK_STOCK_GO_FORWARD
 , NULL, "<Alt>Right"
 , "hm?", G_CALLBACK(on_action_forward_activate) },
 { "Home", GTK_STOCK_HOME
 , NULL, "<Alt>Home"
 , "hm?", G_CALLBACK(on_action_home_activate) },
};
static const guint toolbar_entries_n = G_N_ELEMENTS(toolbar_entries);

#endif

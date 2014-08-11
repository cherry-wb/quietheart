/*程序功能：获取hal层中的一个属性，这里是电源管理中canSuspend这个字符串属性。
 * */
#include<stdio.h>
#include<dbus/dbus-glib.h>
#define MY_DBUS_SERVICE "org.freedesktop.Hal"
#define MY_DBUS_OBJPATH "/org/freedesktop/Hal/devices/computer"
#define MY_DBUS_INTERFACE "org.freedesktop.Hal.Device.SystemPowerManagement"
gint main(gint argc, gchar *argv[])
{
	gboolean ret;
	GError *error = NULL;
	DBusGConnection *connection;
	DBusGProxy *proxy;
	gboolean can_suspend = TRUE;

	/*建立连接*/
	//connection = dbus_g_bus_get (DBUS_BUS_SESSION, &error);
	connection = dbus_g_bus_get (DBUS_BUS_SYSTEM, &error);
	if (error != NULL)
	{
		g_warning ("Failed to open connection to bus: %s\n",
				error->message);

		g_error_free (error);

		return;
	}
	
	/*建立请求代理*/
	//proxy = dbus_proxy_new ();
	proxy = dbus_g_proxy_new_for_name (connection,
			MY_DBUS_SERVICE,
			MY_DBUS_OBJPATH,
			MY_DBUS_INTERFACE);

	/*利用请求代理进行远程调用*/
	/*ret = */
	dbus_g_proxy_call (proxy, "GetPropertyBoolean", NULL,
			G_TYPE_STRING,"power_management.can_suspend",
			G_TYPE_INVALID,
			G_TYPE_BOOLEAN, &can_suspend,
			G_TYPE_INVALID);
	/*if (ret == FALSE)
	{
		can_suspend = FALSE;
	}*/

	if(can_suspend)
	{
		g_print("this computer can suspend!\n");
	}
	else
	{
		g_print("this computer cann't suspend!\n");
	}
	return 0;
}

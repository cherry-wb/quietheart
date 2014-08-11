/*程序功能：检查cpu的负载。
 *每隔一秒检查一下cpu，如果cpu负载低于一定程度就打印idle相关信息。
 *如果在10秒内cpu负载低于一定程度就打印close screen。
 *如果cpu负载高了就将closescreen退后10秒。
 * */
#include<stdio.h>
#include<gtk/gtk.h>
//#define IDLE_LIMIT 5
#define IDLE_LIMIT 2
struct MyLoad
{
	long unsigned old_idle;
	long unsigned old_total;
};
static struct MyLoad cpu_load;
static gint idle_timer = -1;/*定时器号*/
static gint test_timer = 0;/*测试用的数据*/
/*获得cpu相应的负载值用于计算*/
static gboolean
get_cpu_values (long unsigned *cpu_idle, long unsigned *cpu_total)
{
	long unsigned cpu_user;
	long unsigned cpu_nice;
	long unsigned cpu_system;
	int len;
	char tmp[5];
	char str[80];
	FILE *fd;
	char *suc;

	fd = fopen("/proc/stat", "r");
	if (!fd)
	{
		return FALSE;
	}
	suc = fgets(str, 80, fd);
	len = sscanf(str, "%s %lu %lu %lu %lu", tmp,
			&cpu_user, &cpu_nice, &cpu_system, cpu_idle);
	fclose(fd);
	*cpu_total = cpu_user + cpu_nice + cpu_system + *cpu_idle;
	return TRUE;
}

/*起点初始化，负载要根据上一次的和当前之差获得,所以要有一个起始值*/
static void init_load(struct MyLoad *load)
{
	gboolean ret;
	ret = get_cpu_values (&(load->old_idle), &(load->old_total));
	if (ret == FALSE)
	{
		g_print("can't read load!\n");
	}
}

/*获得当前负载*/
static gdouble get_current_load(struct MyLoad *load)
{
	double	      percentage_load;
	long unsigned cpu_idle;
	long unsigned cpu_total;
	long unsigned diff_idle;
	long unsigned diff_total;
	gboolean ret;

	ret = get_cpu_values (&cpu_idle, &cpu_total);
	if (ret == FALSE)
	{
		return 0.0;
	}

	diff_idle = cpu_idle - load->old_idle;
	diff_total = cpu_total - load->old_total;

	if(diff_idle > 0)
	{
		percentage_load = (double) diff_total / (double) diff_idle;
	}
	else
	{
		percentage_load = 100;
	}

	load->old_idle = cpu_idle;
	load->old_total = cpu_total;

	return percentage_load;
}
static gint do_close(gpointer data)
{
	g_print("close the screen!\n");
	return TRUE;
}
static gint check_load(gpointer data)
{/*定时调用检测的函数*/
	gdouble  load;
	gboolean idle_action;
	load = get_current_load (&cpu_load);
	g_print("the load is %f\n", load);
	idle_action = TRUE;
	if (load > IDLE_LIMIT)
	{//cpu很忙
		//gpm_debug ("Detected that the CPU is busy");
		idle_action = FALSE;
		if(idle_timer > 0)
		{//忙则重置计时器
			g_source_remove(idle_timer);
			idle_timer = -1;
			test_timer = 0;
		}
	}
	if(idle_action == TRUE)
	{//当前cpu空闲
		test_timer ++;
		g_print("cpu is idle!!test_timer is: %d\n",test_timer);
		if(idle_timer < 0)
		{//如果空闲10秒则打印close
			idle_timer = g_timeout_add(5000, do_close, NULL);
		}
	}
	return TRUE;
}
gint main(gint argc, gchar *argv[])
{

	GtkWidget *window;
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(GTK_WIDGET(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);
	init_load(&cpu_load);
	g_timeout_add(1000, check_load, NULL);
	
	gtk_widget_show(window);
	gtk_main();
	return 0;

}

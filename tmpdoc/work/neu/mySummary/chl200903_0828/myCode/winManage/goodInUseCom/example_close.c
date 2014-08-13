#include "winManage.h"
/*根据窗口标题关闭窗口*/
gint main(gint argc, gchar *argv[])
{
	if(argc == 2)
	{
		close_win_by_title(argv[1]);
	}
	else
	{
		g_print("usage: %s windowTitle\n",argv[0]);
	}
	return 0;
}

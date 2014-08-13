#include"aspawn_launch.h"
int main(int argc, char *argv[])
{
	/*this show the usage of the function*/
	if(2 != argc)
	{
		g_print("usage: %s applicationCommand\n",argv[0]);
		return 1;
	}
	else
	{
		/*launch application by command*/
		g_print("the command you input is %s .\n", argv[1]);
		launchApp(argv[1]);
		/*get the count of the window exists*/
		int count = getWindowCount();
		g_print("the count of the windows exists is %d .\n", count);
		return 0;
	}
}

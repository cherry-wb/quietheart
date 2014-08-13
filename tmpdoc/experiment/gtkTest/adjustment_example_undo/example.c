#include<gtk/gtk.h>

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv[]);
	create_range_controls();
	gtk_main();
	return 0;
}

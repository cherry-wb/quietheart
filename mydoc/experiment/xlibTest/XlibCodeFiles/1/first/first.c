#include <X11/Xlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>

Window w;
GC gc;
Display *dpy;

void init_X()
{

	if (( dpy = XOpenDisplay(NULL) ) == NULL)
	{
		perror("Can't connect to X server");
		exit(1);
	}
	w = XCreateSimpleWindow
	(
		dpy,DefaultRootWindow(dpy),
		0,0,500,500,0,
		0,0
	);

	gc = XCreateGC(dpy, w, 0, 0);
	XStoreName(dpy,w,"ALGO");
	XMapWindow(dpy, w);
	XFlush(dpy);

	XSetForeground(dpy,gc,0xaabbaa);
}


void event_X()
{
	XEvent an_event;
	int done = 1;


	XSelectInput
	(
		dpy, w, 
		ExposureMask | KeyPressMask |
		ButtonPressMask | Button1MotionMask |											           Button2MotionMask | StructureNotifyMask
	);

	
	while (done)
	{
		XNextEvent(dpy, &an_event);
		switch (an_event.type)
		{
			case Expose:
				printf("need redraw window\n");
				done=0;
				break;

			default:
				break;
		}
	}
}

int core()
{
	int i;
	float x=0,y=0;
	float r,u=0;

	srand(time(0));

	for(i=0;i<=500000;i++)
	{
		r=rand()%100;
	
		if (r < 1) 
		{
			x = 0;
			y = .16 * y;
		}

		if (r>=1 && r<86)
		{
			u = .85 * x + .04 * y;
			y = -0.04*x + 0.85 * y + 1.6;
			x = u;
		}
	
		if (r>=86 && r<97)
		{
			u = .2 * x - .26 * y;
			y = .23 * x + .22 * y + 1.6;
			x = u;
		}

		if (r>=97)
		{
			u = -.15 * x + .28 * y;
			y = 0.26 * x + .24 * y +.44;
			x = u;
		}
	
		  	XDrawPoint(dpy,w,gc, 45*x+230,480-45*y);
	}	
	return 0;
}

int main()
{
	init_X ();
		core();
		event_X ();
	return 0;
}


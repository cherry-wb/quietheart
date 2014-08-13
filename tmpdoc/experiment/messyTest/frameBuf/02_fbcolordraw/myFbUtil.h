#ifndef __MYFBUTIL_H
#define __MYFBUTIL_H

struct MyFb
{
	struct fb_fix_screeninfo fb_fix;
	struct fb_var_screeninfo fb_var;
	unsigned long fb_mem_offset;
	void *fb_mem;
	int fb;
	size_t fb_realMapLen;
};

//init 
struct MyFb* initFb(const char *f);
//release resource,must call in pair with initFb
int releaseFb(struct MyFb*);
//print fb information
int printFbInfo(struct MyFb* fbTest);
//drawDot on fbTest,position is(x,y);color is(r,g,b).r,g,b in [0,1.0]
int drawDot(struct MyFb* fbTest, uint32_t x, uint32_t y, float r, float g, float b);
#endif

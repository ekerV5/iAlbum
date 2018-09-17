#include <stdio.h>
#include "fb.h"

int main(int argc, char *argv[])
{
	printf("Intelligent Album Application Start.\n");

	int ret = fb_open();
	if(ret < 0)
	{
		printf("fb_open error.\n");
		return -1;
	}
	
	fb_draw_background(WIDTH, HEIGHT, GREEN);
	
	fb_close();
	
	return 0;
}

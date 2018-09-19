#include <stdio.h>
#include "fb.h"
#include "600480.h"
#include "666500.h"
#include "1024768.h"

int main(int argc, char *argv[])
{
	printf("Intelligent Album Application Start.\n");

	int ret = fb_open();
	if(ret < 0)
	{
		printf("fb_open error.\n");
		return -1;
	}
	
	fb_draw_picture(gImage_600480, 600, 480);
	// fb_draw_picture(gImage_666500, 666, 500);
	// fb_draw_picture(gImage_1024768, 1024, 768);
	// fb_draw_background(WIDTH, HEIGHT, GREEN);
	
	fb_close();
	
	return 0;
}

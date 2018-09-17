#ifndef __FB_H__
#define __FB_H__

#define BLACK       0x00000000
#define WHITE       0xffffffff
#define RED         0x00ff0000
#define GREEN       0xff00ff00
#define BLUE        0xff0000ff

#define WIDTH       800	
#define HEIGHT      480

int fb_open(void);
void fb_close(void);
void fb_draw_background(unsigned int width, unsigned int height, unsigned int color);

#endif
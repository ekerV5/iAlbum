#include <linux/fb.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include "config.h"
#include "fb.h"

#define FB_DEV    "/dev/fb0"

// 全局变量
unsigned int *pfb = NULL;    // pfb指向framebuffer内存地址首地址
int fd = -1;                 // 打开fb后得到的fd
 
int fb_open(void)
{
	int ret = -1;
	struct fb_fix_screeninfo finfo;
	struct fb_var_screeninfo vinfo;

	// 第1步：打开设备
	fd = open(FB_DEV, O_RDWR);
	if(fd < 0)
	{
		perror("open error");
		return -1;
	}
	debug("open %s success.\n", FB_DEV);

	// 第2步：获取设备的硬件信息
	ret = ioctl(fd, FBIOGET_FSCREENINFO, &finfo);
	if(ret < 0)
	{
		perror("ioctl error");
		return -1;
	}
	debug("smem_start = 0x%lx, smem_len = %u.\n", finfo.smem_start, finfo.smem_len);

	ret = ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
	if(ret < 0)
	{
		perror("ioctl error");
		return -1;
	}
	debug("xres = %u, yres = %u.\n", vinfo.xres, vinfo.yres);
	debug("xres_virtual = %u, yres_virtual = %u.\n", vinfo.xres_virtual, vinfo.yres_virtual);
	debug("bpp = %u.\n", vinfo.bits_per_pixel);

	// 第3步：进行mmap
	unsigned long len = vinfo.xres_virtual * vinfo.yres_virtual * vinfo.bits_per_pixel / 8;
	debug("len = %ld\n", len);
	pfb = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(pfb == NULL)
	{
		perror("mmap error");
		return -1;
	}
	debug("pfb = %p.\n", pfb);

	return 0;
}

void fb_close(void)
{	
	close(fd);
}

// 绘制屏幕背景色
void fb_draw_background(unsigned int width, unsigned int height, unsigned int color)
{
	unsigned int x, y;

	for(y=0; y<height; y++)
	{
		for(x=0; x<width; x++)
		{
			*(pfb + y * WIDTH + x) = color;
		}
	}
}
TOPDIR := $(shell pwd)
export TOPDIR

CROSS_COMPILE = arm-linux-

AS      = $(CROSS_COMPILE)as
LD      = $(CROSS_COMPILE)ld
CC      = $(CROSS_COMPILE)gcc
CPP     = $(CC) -E
AR      = $(CROSS_COMPILE)ar
NM      = $(CROSS_COMPILE)nm
STRIP   = $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump

# export导出的变量是给子目录下的Makefile使用的
export AS LD CC CPP AR NM STRIP OBJCOPY OBJDUMP

# 编译器在编译时的参数设置
CFLAGS := -Wall -O2 -g -DDEBUG
# 添加头文件路径，不添加的话include目录下的头文件编译时找不到
CFLAGS += -I$(TOPDIR)/include -I$(TOPDIR)/display

# 链接器的在链接时的参数设置
LDFLAGS :=

export CFLAGS LDFLAGS

# 定义将来编译生成的可执行程序的名字
TARGET := iAlbum

# 添加项目中所有用到的源文件，有顶层目录下的.c文件和子文件夹
# 添加顶层目录下的.c文件
obj-y += main.o

# 添加顶层目录下的子文件夹（注意目录名后面加一个/）
obj-y += $(TOPDIR)/display/

all: 
	make -C ./ -f $(TOPDIR)/Makefile.build
	$(CC) $(LDFLAGS) -o $(TARGET) built-in.o

cp:
	cp $(TARGET) ~/nfsroot

clean:
	rm -f $(shell find -name "*.o")
	rm -f $(TARGET)

distclean:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.d")
	rm -f $(TARGET)
	
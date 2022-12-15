#CC = arm-none-linux-gnueabi-gcc

LOCAL_PATH := $(shell pwd)

LOCAL_SRC_FILES := libcharset/lib/localcharset.c lib/iconv.c lib/relocatable.c

LOCAL_CFLAGS := -DPACKED= -D_GNU_SOURCE -Wno-multichar -DLIBDIR="c" -DBUILDING_LIBICONV -DIN_LIBRARY
LOCAL_CFLAGS += -O2 -fomit-frame-pointer --verbose -fPIC -shared -s

LOCAL_C_INCLUDE := -I $(LOCAL_PATH)
LOCAL_C_INCLUDE += -I $(LOCAL_PATH)/include/
LOCAL_C_INCLUDE += -I $(LOCAL_PATH)/libcharset/
LOCAL_C_INCLUDE += -I $(LOCAL_PATH)/lib/
LOCAL_C_INCLUDE += -I $(LOCAL_PATH)/libcharset/include/
LOCAL_C_INCLUDE += -I $(LOCAL_PATH)/srclib

LOCAL_MODULE := $(TARGETDIR)/libiconv.so

all:
	$(CC) $(LOCAL_CFLAGS) $(LOCAL_C_INCLUDE) -o $(LOCAL_MODULE) $(LOCAL_SRC_FILES)

install:
	mv $(LOCAL_MODULE) $(TARGETDIR)

.PHONY:clean
clean:
	rm -f *.a *.o $(LOCAL_SRC_FILES:.c=.o) $(LOCAL_MODULE) 

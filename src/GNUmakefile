PROJ := liblayout.a

ROOT ?= ..

include $(ROOT)/make/static-library.gmk

CXXFLAGS += -I../include -D_WIN32_IE=0x0500
CFLAGS += -I../include -D_WIN32_IE=0x0500
LDFLAGS += -mwindows

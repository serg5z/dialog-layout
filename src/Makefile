PROJ = layout.lib
!ifndef ROOT
ROOT = ..\..
!endif

OBJ=layout.obj
    
!include $(ROOT)\make\static-library.mak

# any modifications to the flags should go _after_ win32.mak
cflags = $(cflags) -D_CRT_SECURE_NO_DEPRECATE -I..\include
rcflags = $(rcflags) -I..\include

#dependency information goes here

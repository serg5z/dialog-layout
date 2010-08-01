!ifndef ROOT
ROOT=$(MAKEDIR)
!endif

!ifndef BUILD
BUILD=$(MAKEDIR)\build
!endif

!ifndef LIBRARY
LIBRARY=$(MAKEDIR)\lib
!endif

all:
  cd src
  $(MAKE) ROOT=$(ROOT) BUILD=$(BUILD) LIBRARY=$(LIBRARY)
  @cd ..
        
clean:
  @cd src
  $(MAKE) ROOT=$(ROOT) BUILD=$(BUILD) LIBRARY=$(LIBRARY) clean 
  @cd ..

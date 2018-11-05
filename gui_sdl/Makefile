ifneq ($(CROSS_COMPILE),)
$(info CROSS_COMPILE=$(CROSS_COMPILE))
endif

ifeq ($(MARIO_LANG),)
MARIO_LANG = js
endif

ifeq ($(MARIO_VM),)
MARIO_VM = ../../mario_vm
endif
MARIO_COMP = $(MARIO_VM)/compilers/$(MARIO_LANG)

CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
AR := $(CROSS_COMPILE)ar
LD := $(CROSS_COMPILE)g++

mario_OBJS= $(MARIO_VM)/mario_utils.o $(MARIO_VM)/mario_bc.o $(MARIO_VM)/mario_vm.o $(MARIO_VM)/mario_lex.o $(MARIO_COMP)/compiler.o

MARIO_GUI=yes

GUI_OBJS= $(mario_OBJS) \
	sdl/native_sdl.o \
	native_gui.o 

CFLAGS =  -g -I$(MARIO_VM) -Wall -fPIC -DMARIO_DEBUG -DMARIO_CACHE -DMARIO_THREAD
LDFLAGS =  -lm -lpthread
CFLAGS +=  -I/usr/local/include/SDL2
LDFLAGS += -L/usr/local/lib -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf


GUI=gui
INST_DST=/usr/local/mario
GUI_TARGET=native_$(GUI).so

$(GUI_TARGET): $(GUI_OBJS)
	$(LD) -shared -o $(GUI_TARGET) $(GUI_OBJS) $(LDFLAGS)

clean:
	rm -fr $(GUI_TARGET) $(GUI_OBJS)

install: 
	mkdir -p $(INST_DST)/test.js/$(GUI)
	cp test.js/* $(INST_DST)/test.js/$(GUI)
	cp $(GUI_TARGET) $(INST_DST)/libs

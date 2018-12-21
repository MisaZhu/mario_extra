ifneq ($(CROSS_COMPILE),)
$(info CROSS_COMPILE=$(CROSS_COMPILE))
endif

ifeq ($(MARIO_LANG),)
MARIO_LANG = js
endif

ifeq ($(MARIO_VM),)
MARIO_VM = ../../mario_vm
endif

CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
AR := $(CROSS_COMPILE)ar
LD := $(CROSS_COMPILE)g++

mario_OBJS= $(MARIO_VM)/utils/mario_basic.o \
						$(MARIO_VM)/utils/mario_array.o \
						$(MARIO_VM)/utils/mario_string.o \
						$(MARIO_VM)/vm/mario_bc.o \
						$(MARIO_VM)/vm/mario_vm.o \
						$(MARIO_VM)/vm/mario_lex.o

native_OBJS= native_regex.o


CFLAGS =  -I$(MARIO_VM)/vm -I$(MARIO_VM)/utils -Wall -fPIC -DMARIO_DEBUG -DMARIO_CACHE -DMARIO_THREAD

ifneq ($(MARIO_DEBUG), no)
CFLAGS += -g -DMARIO_DEBUG
else
CFLAGS += -O2
endif

CXXFLAGS =  $(CFLAGS) -std=c++11
LDFLAGS =  -lm -lpthread -lstdc++

INST_DST=/usr/local/mario
TARGET=native_regex.so

all: $(mario_OBJS) $(native_OBJS)
	$(LD) -shared -o $(TARGET) $(mario_OBJS) $(native_OBJS) $(LDFLAGS)

clean:
	rm -fr $(TARGET) $(mario_OBJS) $(native_OBJS)

install: 
	mkdir -p $(INST_DST)/natives
	cp $(TARGET) $(INST_DST)/natives
	mkdir -p $(INST_DST)/test/$(MARIO_LANG)/regex
	cp lang/$(MARIO_LANG)/test/* $(INST_DST)/test/$(MARIO_LANG)/regex

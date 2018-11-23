ifneq ($(CROSS_COMPILE),)
$(info CROSS_COMPILE=$(CROSS_COMPILE))
endif

ifeq ($(MARIO_LANG),)
MARIO_LANG = js
endif

ifeq ($(MARIO_VM),)
MARIO_VM = ../../mario_vm/vm
endif

CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
AR := $(CROSS_COMPILE)ar
LD := $(CROSS_COMPILE)g++

mario_OBJS= $(MARIO_VM)/mario_utils.o $(MARIO_VM)/mario_bc.o $(MARIO_VM)/mario_vm.o $(MARIO_VM)/mario_lex.o 
basic_OBJS= native_regex.o


CFLAGS =  -g -I$(MARIO_VM) -Wall -fPIC -DMARIO_DEBUG -DMARIO_CACHE -DMARIO_THREAD
CXXFLAGS =  $(CFLAGS) -std=c++11
LDFLAGS =  -lm -lpthread

INST_DST=/usr/local/mario
TARGET=native_regex.so

all: $(mario_OBJS) $(basic_OBJS)
	$(LD) -shared -o $(TARGET) $(mario_OBJS) $(basid_OBJS) $(LDFLAGS)

clean:
	rm -fr $(TARGET) $(mario_OBJS) $(basic_OBJS)

install: 
	mkdir -p $(INST_DST)/natives
	cp $(TARGET) $(INST_DST)/natives
	mkdir -p $(INST_DST)/test/$(MARIO_LANG)/regex
	cp lang/$(MARIO_LANG)/test/* $(INST_DST)/test/$(MARIO_LANG)/regex

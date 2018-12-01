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

mario_OBJS= $(MARIO_VM)/mario_utils.o $(MARIO_VM)/mario_bc.o $(MARIO_VM)/mario_vm.o
native_OBJS= native_basic.o \
	system/native_system.o \
	socket/native_socket.o  \
	fs/native_fs.o \
	dir/native_dir.o \
	thread/native_thread.o \
	timer/native_timer.o \
	dns/dnsc.o dns/query.o dns/request.o dns/response.o dns/native_dns.o


CFLAGS =  -I$(MARIO_VM) -Wall -fPIC -DMARIO_DEBUG -DMARIO_CACHE -DMARIO_THREAD

ifneq ($(MARIO_DEBUG), no)
CFLAGS += -g -DMARIO_DEBUG
else
CFLAGS += -O2
endif

CXXFLAGS =  $(CFLAGS)
LDFLAGS =  -lm -lpthread

INST_DST=/usr/local/mario
TARGET=native_basic.so

all: $(mario_OBJS) $(native_OBJS)
	$(LD) -shared -o $(TARGET) $(mario_OBJS) $(native_OBJS) $(LDFLAGS)

clean:
	rm -fr $(TARGET) $(mario_OBJS) $(native_OBJS)

install: 
	mkdir -p $(INST_DST)/natives
	cp $(TARGET) $(INST_DST)/natives
	mkdir -p $(INST_DST)/libs/$(MARIO_LANG)
	cp lang/$(MARIO_LANG)/libs/* $(INST_DST)/libs/$(MARIO_LANG)
	mkdir -p $(INST_DST)/test/$(MARIO_LANG)/basic
	cp lang/$(MARIO_LANG)/test/* $(INST_DST)/test/$(MARIO_LANG)/basic

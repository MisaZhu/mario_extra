ifeq ($(CROSS_COMPILE),)
CROSS_COMPILE=arm-none-linux-gnueabi-
endif

ifeq ($(MARIO_LANG),)
MARIO_LANG = js
endif

ifeq ($(MARIO_VM),)
MARIO_VM = ../../mario_vm
endif
MARIO_COMP = $(MARIO_VM)/compilers/$(MARIO_LANG)

CC := $(CROSS_COMPILE)g++
CXX := $(CROSS_COMPILE)g++
AR := $(CROSS_COMPILE)ar
LD := $(CROSS_COMPILE)g++

mario_OBJS= $(MARIO_VM)/mario_utils.o $(MARIO_VM)/mario_bc.o $(MARIO_VM)/mario_vm.o $(MARIO_VM)/mario_lex.o $(MARIO_COMP)/compiler.o


OBJS= $(mario_OBJS) \
	native_ev3.o \
	Ports.o \
	Port.o \
	Sound.o \
	Motor.o \
	DCMotor.o \
	ServoMotor.o \
	Ultrasonic.o \
	Infrared.o \
	Button.o \
	Remote.o \
	Touch.o \
	Gyro.o \
	ColorSensor.o \
	ev3dev.o


CXXFLAGS =  -I$(MARIO_VM) -g -Wall -DMARIO_DEBUG -DMARIO_CACHE -fPIC -std=c++0x  -I. -DEV3DEV_PLATFORM=EV3
LDFLAGS = -lstdc++

CXXFLAGS +=  -DMARIO_THREAD
LDFLAGS += -lpthread

CFLAGS =  $(CXXFLAGS)

NAME=lego_ev3
TARGET=native_$(NAME).so
INST_DST=/usr/local/mario

all: $(OBJS)
	$(LD) -shared -o $(TARGET) $(OBJS) $(LDFLAGS)

clean:
	rm -fr $(TARGET) $(OBJS) *.dSYM

install:
	mkdir -p $(INST_DST)/libs
	cp $(TARGET) $(INST_DST)/libs
	mkdir -p $(INST_DST)/test.js/$(NAME)
	cp test.js/* $(INST_DST)/test.js/$(NAME)

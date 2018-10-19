ifeq ($(CROSS_COMPILE),)
CROSS_COMPILE=arm-none-linux-gnueabi-
endif


ifeq ($(MARIO_JS),)
MARIO_JS = ../mario_js
endif

CC := $(CROSS_COMPILE)g++
CXX := $(CROSS_COMPILE)g++
AR := $(CROSS_COMPILE)ar
LD := $(CROSS_COMPILE)gcc

OBJS= $(MARIO_JS)/mario_js.o  \
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


CXXFLAGS =  -I$(MARIO_JS) -g -Wall -DMARIO_DEBUG -DMARIO_CACHE -fPIC -std=c++0x  -I. -DEV3DEV_PLATFORM=EV3
LDFLAGS = -lstdc++

CXXFLAGS +=  -DMARIO_THREAD
LDFLAGS += -lpthread

CFLAGS =  $(CXXFLAGS)

TARGET=native_ev3.so
INST_DST=/usr/local/mario

all: $(OBJS)
	$(LD) -shared -o $(TARGET) $(OBJS) $(LDFLAGS)

clean:
	rm -fr $(TARGET) $(OBJS) *.dSYM

install:
	mkdir -p $(INST_DST)/libs
	cp $(TARGET) $(INST_DST)/libs
	mkdir -p $(INST_DST)/test.js
	cp test.js/* $(INST_DST)/test.js

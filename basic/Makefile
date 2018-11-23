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

CFLAGS =  -g -I$(MARIO_VM) -I$(MARIO_JS) -Wall -fPIC -DMARIO_DEBUG -DMARIO_CACHE -DMARIO_THREAD
CXXFLAGS =  $(CFLAGS)
LDFLAGS =  -lm -lpthread


INST_DST=/usr/local/mario
SYS=sys
REGEX=regex

REGEX_TARGET=$(REGEX)/native_$(REGEX).so
SYS_TARGET=$(SYS)/native_$(SYS).so

all: $(SYS_TARGET) $(REGEX_TARGET)

include $(SYS)/build.mk
include $(REGEX)/build.mk

clean:
	rm -fr $(CLEAN)

install: 
	mkdir -p $(INST_DST)/natives
	cp $(SYS_TARGET) $(INST_DST)/natives
	cp $(REGEX_TARGET) $(INST_DST)/natives
	mkdir -p $(INST_DST)/libs/$(MARIO_LANG)
	cp lang/$(MARIO_LANG)/libs/* $(INST_DST)/libs/$(MARIO_LANG)
	mkdir -p $(INST_DST)/test/$(MARIO_LANG)
	cp lang/$(MARIO_LANG)/test/* $(INST_DST)/test/$(MARIO_LANG)

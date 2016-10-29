COMMON_DIR = ../common

COMMON_HEADER_FILE = $(COMMON_DIR)/*.h

COMMON_SOURCE_FILE = $(COMMON_DIR)/*.c


COMMON_OBJ := $(wildcard*.o)

OBJECTS = $(COMMON_OBJ)

all: $()

$(COMMON_OBJ):%.o:%.c

wait_exp: common 
	gcc wait_exp.c $(COMMON_OBJ)  -o wait_exp

common:
	cd $(COMMON_DIR)
	gcc -c 

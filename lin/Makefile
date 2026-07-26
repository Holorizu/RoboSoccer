# Check for Windows or Linux (ion know shi bout other OS fck you)
OS ?= $(shell echo %OS% 2>/dev/null)
ifeq ($(OS), Windows_NT)
	IS_WINDOWS := 1
else
	UNAMEOS = $(shell uname)
	ifeq ($(UNAMEOS), Linux)
	IS_LINUX := 1
endif

# Defining Compiler and Compiler flags 
CC := gcc
CFLAGS := -lraylib -Iinclude -Llib

TARGET := main$(EXE_EXT)

# OS Specific flags

ifeq($(IS_WINDOWS), 1)
	CFLAGS += -lgdi32 -lwinmm 
endif

ifeq($(IS_LINUX), 1)
	CFLAGS += -lGL -lm -lpthread -ldl -lrt -lX11
endif

# Compile that shit
$(CC) $(CFLAGS) main.c -o $(TARGET)


#default:
#	gcc ../main.c -lraylib -lGL -lm -lpthread -Llib -Iinclude -ldl -lrt -lX11 -o ../main

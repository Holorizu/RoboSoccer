# Check for Windows or Linux (ion know shi bout other OS fck you)

ifeq ($(OS), Windows_NT)
	IS_WINDOWS := 1
else
	UNAMEOS :=  $(shell uname)
	ifeq ($(UNAMEOS), Linux)
		IS_LINUX := 1
	endif
endif

# Defining Compiler and Compiler flags 
CC := gcc
CFLAGS := -Wall -Iinclude -Llib
LDLIBS := -lraylib


# OS Specific flags

ifeq ($(IS_WINDOWS), 1)
	EXE_EXT := .exe
	CFLAGS += -lgdi32 -lwinmm 
endif

ifeq ($(IS_LINUX), 1)
	CFLAGS += -lGL -lm -lpthread -ldl -lrt -lX11
endif

TARGET := main$(EXE_EXT)

all: $(TARGET)
	@echo "Successfully built: $(TARGET) ngga"

# Compile that shit
$(TARGET): main.c
	$(CC) main.c -o $(TARGET) $(LDLIBS) $(CFLAGS) 


.PHONY: all clean
clean:
	rm -f $(TARGET) 2>/dev/null || del /Q $(TARGET) 2>nul



#default:
#	gcc ../main.c -lraylib -lGL -lm -lpthread -Llib -Iinclude -ldl -lrt -lX11 -o ../main

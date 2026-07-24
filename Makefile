

default:
	gcc main.c -lraylib -lGL -lm -lpthread -Llib -Iinclude -ldl -lrt -lX11 -o main

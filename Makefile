

all: up down


up: brightness.c
	clang -g -Wall -o brightness-up -D BRIGHTNESS_UP brightness.c


down: brightness.c
	clang -g -Wall -o brightness-down -D BRIGHTNESS_DOWN brightness.c





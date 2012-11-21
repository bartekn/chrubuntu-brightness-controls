

all: up down


up: brightness-up.c
	clang -g -Wall -o brightness-up brightness-up.c


down: brightness-down.c
	clang -g -Wall -o brightness-down brightness-down.c





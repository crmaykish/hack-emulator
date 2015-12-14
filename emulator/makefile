OBJS = main.c emulator.c cpu.c screen.c
CC = gcc
LINKER_FLAGS = -lSDL2
OBJ_NAME = emulator.out
all : $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)

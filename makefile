OBJS = emu.c
CC = gcc
LINKER_FLAGS = -lSDL2
OBJ_NAME = emu.out
all : $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)

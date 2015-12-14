OBJS = main.c assembler.c parser.c binary.c str_utils.c
CC = gcc
LINKER_FLAGS = -g
OBJ_NAME = assembler.out
all : $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)

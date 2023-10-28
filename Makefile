CC = gcc
FLAGS = -Wall -mcmodel=large -I./includes

PROG = cpu.out
SRCS = emulator.c data_path.c controller.c __*.c

$(PROG): $(SRCS)
	$(CC) $(FLAGS) $(SRCS) -o $(PROG)

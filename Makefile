CC = gcc
FLAGS = -Wall -mcmodel=large -I./includes

SRCS = data_path.c controller.c cpu.c __*.c

PROG = emulator.out
PROGSRCS = $(SRCS) emulator.c

TEST = ./test/test.out
TESTSRCS = $(SRCS) ./test/main.c


test: $(TEST)
	./$(TEST)

$(TEST): $(TESTSRCS)
	$(CC) $(FLAGS) $(TESTSRCS) -o $(TEST)

$(PROG): $(PROGSRCS)
	$(CC) $(FLAGS) -DNDEBUG $(PROGSRCS) -o $(PROG)

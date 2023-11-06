CC = gcc
BIN = cpu.out

cpu.out: *.c
	$(CC) -o $(BIN) __cpu_emu.c -mcmodel=large

test: cpu.out
	./$(BIN)

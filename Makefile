CC=gcc
CCFLAGS=-std=c99 -Wall -Werror -pedantic -m32 -rdynamic
LIBS=-ldl -lcurses

%.so: algorithm_src/%.c
	$(CC) -c $(CCFLAGS) -shared -Iinclude -fpic $< -o $@

mazerunner: src/* include/mazerunner/* lib/* include/display.h tremaux.so stupid.so wall_hugger.so random.so
	$(CC) $(CCFLAGS) -Iinclude lib/display.o src/*.c -o mazerunner $(LIBS)

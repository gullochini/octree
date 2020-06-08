CFLAGS  = -Wall -Werror -pedantic -O2
C_OBJS = $(patsubst %.c,%.o,$(wildcard *.c))
C_PROGRAM = test_gc

%.o : %.c
	gcc $(CFLAGS) -c $< -o $@

$(C_PROGRAM): $(C_OBJS)
	gcc $^ -o $@

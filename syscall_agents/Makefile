vpath %.h ../headers

CC = gcc
FLAGS = -c -g -o

OBJS = $(patsubst %.c,%.o,$(wildcard *.c))

all : $(OBJS)

$(OBJS) : %.o : %.c
	$(CC) $(FLAGS)  $@ $<

.PHONY : clean
clean :
	-rm $(OBJS)
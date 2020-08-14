vpath %.h ../headers
vpath %.c ../tools

export MAKE = make -w
TARGET = daemon
CFLAGS  = -g -o

OBJS = $(patsubst %.c,%.o,$(wildcard *.c)) \
	$(patsubst %.c,%.o,$(wildcard ../tools/*.c)) \
	$(patsubst %.c,%.o,$(wildcard ../syscall_agents/*.c))


HEADERS = $(wildcard ../headers/*.h)

.PHONEY:all

all : subsystem $(TARGET)

subsystem:
	cd ../syscall_agents && $(MAKE)
	cd ../tools && $(MAKE)

$(TARGET):$(OBJS) $(HEADERS)
	cc $(CFLAGS) $(TARGET) $(OBJS)

daemon.o:daemon.c $(HEADERS)
	cc -c -g -o daemon.o daemon.c
.PHONEY:clean
clean:
	-rm $(wildcard *.o) $(TARGET)
	-cd ../syscall_agents && $(MAKE) clean
	-cd ../tools && $(MAKE) clean


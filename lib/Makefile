vpath %.h ../headers
vpath %.c ../tools

CFLAGS  =-shared -fPIC -g -o
TARGET = agent_lib.so
export MAKE = make -w

OBJS = $(patsubst %.c,%.o,$(wildcard *.c)) \
	$(patsubst %.c,%.o,$(wildcard ../tools/*.c)) \
	$(wildcard ../syscall_wrappers/*.o)

HEADERS = $(wildcard ../headers/*.h)

.PHONEY:all

all : subsystem $(TARGET)

subsystem:
	cd ../syscall_wrappers && $(MAKE)

$(TARGET):$(OBJS)
	cc $(CFLAGS) $(TARGET) $(OBJS)

lib.o:lib.c $(HEADERS)
	cc -g -c -o lib.o lib.c

.PHONEY:clean
clean:
	-rm lib.o $(TARGET)
	-cd ../syscall_wrappers  && $(MAKE) clean

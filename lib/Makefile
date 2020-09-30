vpath %.h ../headers
vpath %.c ../tools

CFLAGS =-shared -fPIC -g -o
TARGET = agent_lib.so
export MAKE = make -w

LIB = $(patsubst %.c,%.o,$(wildcard *.c))
TOOLS =	$(patsubst %.c,%.o,$(wildcard ../tools/*.c))
WRAPPERS =	$(patsubst %.c,%.o,$(wildcard ../syscall_wrappers/*.c))

HEADERS = $(wildcard ../headers/*.h)

.PHONEY:all

all : subsystem $(TARGET)

subsystem:
	cd ../syscall_wrappers && $(MAKE)

$(TARGET):$(LIB) $(WRAPPERS)
	cc $(CFLAGS) $(TARGET) $(LIB) $(WRAPPERS) $(TOOLS)

lib.o:lib.c $(HEADERS)
	cc -g -c -o lib.o lib.c

.PHONEY:clean
clean:
	-rm lib.o $(TARGET)
	-cd ../syscall_wrappers  && $(MAKE) clean

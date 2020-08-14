lsca_daemon:lsca_daemon.o semaphore_helper.o
	cc -o lsca_daemon lsca_daemon.o semaphore_helper.o

lsca_daemon.o:semaphore_helper.h daemon.h

semaphore_helper.o:semaphore_helper.h daemon.h

.PHONEY:clean

clean:
	rm *.o


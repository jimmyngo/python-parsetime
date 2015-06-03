CC 		= cc
CFLAGS 		= -Wall

SRCS   	= parsetime.c

.PHONY: all install clean dist distclean

all: 
	$(CC) -o parsetime $(CFLAGS) $(SRCS)

.c.o:
	$(CC) -c $(CFLAGS) $*.c

clean:
	rm -f $()

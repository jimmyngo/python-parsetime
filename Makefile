CC 		= cc
CFLAGS 		= -Wall

SRCS   	= parsetime.
PARSER_SRCS	= parsetime.l parsetime.y

.PHONY: all install clean dist distclean

all: $(CSRCS)

.c.o:
	$(CC) -c $(CFLAGS) $*.c

clean:
	rm -f $()

.depend: $(CSRCS)
	gcc $(CFLAGS) -MM $(CSRCS) > .depend


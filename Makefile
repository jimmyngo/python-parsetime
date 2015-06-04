CC 		= cc
CFLAGS 		= -Wall

SRCS   	= parsetime.c

.PHONY: all install clean dist distclean

all: parsetime extension

parsetime:
	$(CC) -o parsetime $(CFLAGS) $(SRCS)

parsetime.so:
	python setup.py build_ext -i

.c.o:
	$(CC) -c $(CFLAGS) $*.c

clean:
	rm -f parsetime.so parsetime

extension: parsetime.so

test: test_parsetime

test_parsetime:
	python test/test_parsetime.py

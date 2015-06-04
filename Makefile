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
	rm -f parsetime.so parsetime test/parsetime.so

extension: parsetime.so

test: test_parsetime

test/parsetime.so:
	ln parsetime.so test/parsetime.so

test_parsetime: extension test/parsetime.so
	python test/test_parsetime.py

CC 		= cc
CFLAGS 		= -Wall

CSRCS 		= parsetime.c
COBJS 		= $(CSRCS:.c=.o)

.PHONY: all install clean dist distclean parsetime extension

all: parsetime extension

$(COBJS): %.o : %.h

parsetime: $(COBJS)
	$(CC) -o $@ $(CFLAGS) $^

# Build extension
extension: $(COJBS)
	python setup.py build_ext -i

# Copy and test extension
test: test_parsetime

test/parsetime.so:
	rm -f test/parsetime.so
	ln parsetime.so test/parsetime.so

test_parsetime: extension test/parsetime.so
	python test/test_parsetime.py

# Clean
clean:
	rm -f parsetime.so parsetime test/parsetime.so

.depend: $(CSRCS)
	$(CC) $(CFLAGS) -MM $(CSRCS) > .depend

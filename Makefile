YACC		= yacc
LEX		= lex
CC 		= cc
CFLAGS 		= -Wall

CSRCS   	= y.tab.c y.tab.h lex.yy.c
PARSER_SRCS	= parsetime.l parsetime.y

.PHONY: all install clean dist distclean

all: $(CSRCS)

y.tab.c y.tab.h: parsetime.y
	$(YACC) -d parsetime.y

lex.yy.c: parsetime.l
	$(LEX) -i parsetime.l

.c.o:
	$(CC) -c $(CFLAGS) $*.c

clean:
	rm -f $()
	rm -f subs.sed *.o *.s core a.out *~ *.bak stamp-built
	rm -f parsetest

parsetest: lex.yy.c y.tab.c
	$(CC) -o parsetest $(CFLAGS) -DTEST_PARSER -DNEED_YYWRAP lex.yy.c y.tab.c

.depend: $(CSRCS)
	gcc $(CFLAGS) -MM $(CSRCS) > .depend


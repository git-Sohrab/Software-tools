CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
OBJS = parsedate_tester.o parsedate.o
INCL = parsedate.h

parsedate_tester:	$(OBJS)
	$(CC)  -o $@ $^

%.o:	 %.c $(INCL)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(OBJS) parsedate_tester

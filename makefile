CC = gcc
CCFLAGS = -Wall -std=c99

## A2: Creates executible by linking together object files: A2.o myfuncs.o print_utils.o
A2: A2.o myfuncs.o print_utils.o
	$(CC) $(CCFLAGS) -o A2 A2.o myfuncs.o print_utils.o

## A2.o: Creates object file A2.o by compiling A2.c
A2.o: A2.c
	$(CC) $(CCFLAGS) -c A2.c

## myfuncs.o: Creates object file myfuncs.o by compiling myfuncs.c
myfuncs.o: myfuncs.c myfuncs.h print_utils.h
	$(CC) -Wall -c myfuncs.c

## print_utils.o: Creates object file print_utils.o by compiling print_utils.c
print_utils.o: print_utils.c print_utils.h
	$(CC) $(CCFLAGS) -c print_utils.c

## clean: Deletes all object files
.PHONY: clean help
clean:
	rm *.o

help: makefile
	@sed -n 's/^##//p' $<
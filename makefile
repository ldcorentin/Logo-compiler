CFLAGS = -g -DDEBUG

all: logo

logo: lex.yy.c logoBison.tab.c logoBison.tab.h structure.o
	gcc ${CFLAGS} -o logo logoBison.tab.c lex.yy.c structure.o  -lm

test : structure.o test.o 
	gcc structure.o test.o -o exec -lm

test.o : test.c
	gcc -c test.c -o test.o

lex.yy.c: logoFlex.l logoBison.tab.h
	flex logoFlex.l

logoBison.tab.c logoBison.tab.h: logoBison.y
	bison -d logoBison.y

structure.o: structure.c
	gcc -c structure.c -o structure.o

cleanLogo:
	rm logo logoBison.tab.c lex.yy.c logoBison.tab.h structure.o

cleanTest:
	rm exec test.o structure.o


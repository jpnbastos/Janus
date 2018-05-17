all: cif

cif.tab.c cif.tab.h:	cif.y
	bison -d cif.y

lex.yy.c: cif.l cif.tab.h
	flex cif.l

cif: lex.yy.c cif.tab.c cif.tab.h
	gcc -o cif cif.tab.c lex.yy.c


clean:
	rm cif cif.tab.c lex.yy.c cif.tab.h

 # -------------------------------------------------------------------
 #            Arquivo: Makefile
 # -------------------------------------------------------------------
 #              Autor: Bruno Müller Junior
 #               Data: 08/2007
 #      Atualizado em: [09/08/2020, 19h:01m]
 #
 # -------------------------------------------------------------------

$DEPURA=1

compilador: lex.yy.c compilador.tab.c compilador.o compilador.h Types.o Symbol.o
	gcc lex.yy.c compilador.tab.c compilador.o Symbol.o Types.o -o compilador -lfl -ly -lc

lex.yy.c: compilador.l compilador.h
	flex compilador.l

compilador.tab.c: compilador.y compilador.h Symbol.h Types.h
	bison compilador.y -d -v

compilador.o : compilador.h compiladorF.c
	gcc -c compiladorF.c -o compilador.o

Symbol.o: Symbol.c Symbol.h
	gcc -c Symbol.c -o Symbol.o

Types.o: Types.c Types.h
	gcc -c Types.c -o Types.o

clean :
	rm -f compilador.tab.* lex.yy.c compilador.o compilador

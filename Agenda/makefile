MenuAgenda: MenuAgenda.o usuario.o agenda.o
	gcc -o MenuAgenda MenuAgenda.o usuario.o agenda.o
	
MenuAgenda.o: MenuAgenda.c usuario.h agenda.h
	gcc -c MenuAgenda.c

usuario.o: usuario.c usuario.h
	gcc -c usuario.c
	
agenda.o: agenda.c agenda.h
	gcc -c agenda.c

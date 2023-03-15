quiz		:	main.o session.o parse.o data.o
	cc -o $@ main.o session.o parse.o data.o

main.o session.o parse.o data.o		:	*.h

main.o		:	main.c
	cc -c main.c

parse.o		:	parse.c
	cc -c parse.c

data.o		:	data.c
	cc -c data.c

session.o	:	session.c
	cc -c session.c

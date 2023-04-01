quiz		:	main.o session.o parse.o data.o array.o
	cc -o $@ main.o session.o parse.o data.o array.o

main.o session.o parse.o data.o array.o		:	*.h

main.o		:	main.c
	cc -c main.c

parse.o		:	parse.c
	cc -c parse.c

data.o		:	data.c
	cc -c data.c

session.o	:	session.c
	cc -c session.c

array.o		:	array.c
	cc -c array.c

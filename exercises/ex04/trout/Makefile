

util.o: util.h util.c
	gcc -c util.c

trout.o: trout.h trout.c
	gcc -c trout.c

main.o: trout.h main.c
	gcc -c main.c

trout: trout.o main.o
	gcc -Wall trout.o main.o util.o -o trout
	# #gcc -g -o trout main.c trout.c util.c
	# gcc main.c util.c trout.c -o trout
	# #gcc message_hider.c encrypt.c -o message_hider

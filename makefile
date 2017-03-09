OBJS = main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

taylor : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o taylor

main.o : main.cpp src/algo.cpp src/function.h src/ln_profe.h src/test.h
	$(CC) $(CFLAGS) main.cpp

clean :
	\rm *.o taylor

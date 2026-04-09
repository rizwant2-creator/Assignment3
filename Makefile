CC = gcc
CFLAGS = -Wall -std=c99

all: dashboard

dashboard: DB.c DB_impl.c dashboard.c DB.h DB_impl.h
	$(CC) $(CFLAGS) -o dashboard DB.c DB_impl.c dashboard.c

DB.o: DB.c DB.h DB_impl.h
	$(CC) $(CFLAGS) -c DB.c 

DB_impl.o: DB_impl.c DB.h DB_impl.h
	$(CC) $(CFLAGS) -c DB_impl.c

clean:
	rm -f *.o dashboard
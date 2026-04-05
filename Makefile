CC = gcc
CFLAGS = -Wall -std=c99

all: dashboard

dashboard: DB.c DB_impl.c dashboard.c DB.h DB_impl.h
	$(CC) $(CFLAGS) -o dashboard DB.c DB_impl.c dashboard.c

clean:
	rm -f *.o dashboard
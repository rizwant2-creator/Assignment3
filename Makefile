CC = gcc
CFLAGS = -Wall -std=c99

all: dashboard

dashboard: DB.c DB_impl.c dashboard.c DB.h DB_impl.h
	$(CC) $(CFLAGS) -o dashboard DB.c DB_impl.c dashboard.c

DB.o: DB.c DB.h DB_impl.h
	$(CC) $(CFLAGS) -c DB.c 

DB_impl.o: DB_impl.c DB.h DB_impl.h
	$(CC) $(CFLAGS) -c DB_impl.c

test: testing/test
	./testing/test
testing/test: testing/test.c DB.c DB_impl.c DB.h DB_impl.h
	$(CC) $(CFLAGS) -o testing/test testing/test.c DB.c DB_impl.c

clean:
	rm -f *.o dashboard neighbourhood_id.csv neighbourhood_name.csv structural_material.csv surface_material.csv table_type.csv ward.csv testing/test
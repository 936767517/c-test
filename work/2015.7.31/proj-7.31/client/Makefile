CFLAGS+=-I../include  -pthread
LDFLAGS+=-pthread

all:client

client: client.o
	gcc $^ -o $@ $(FLAGS) $(LDFLAGS)
clean:
	rm -f *.o client


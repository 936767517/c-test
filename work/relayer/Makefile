CFLAGS+= -pthread
LDFLAGS+= -pthread
all:main
main:main.o relayer.o
	gcc &^ -o $@ $(CFLAGS) $(LDFLAGS)
clean:
	rm -rf *.o main

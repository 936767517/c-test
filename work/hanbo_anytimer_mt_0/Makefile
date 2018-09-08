CFLAGS += -pthread
LDFLAGS+=-pthread
all:main
main:main.o anytimer.o
	gcc $^ -o $@ $(CFLAGS) $(LDFLAGS)
clean:
	rm -rf *.o main

FLAG	=-Wall -lxylist

TARGET	=main

OBJECT	=main.o stack.o

CC 		=gcc

$(TARGET):$(OBJECT)
	$(CC) $(FLAG) $^ -o $@

$(OBJECT):%.o:%.c
	$(CC) $(FLAG) -c $< -o $@

clean:
	rm -f $(OBJECT) $(TARGET)

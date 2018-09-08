FLAGS 	= -Wall

TARGET	= main

OBJECTS	= main.o itoa.o

CC		= gcc

$(TARGET):$(OBJECTS)
	$(CC) $^ -o $@

$(OBJECTS):%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

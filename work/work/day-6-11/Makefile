TARGET = main
OBJECTS = work2.o  arrayfu.o
cc = gcc
$(TARGET) : $(OBJECTS)
	$(CC) $^ -o $@
$(OBJECTS) : %.o:%.c
	$(CC) -c $< -o $@
clean:
	rm -f $(TARGET) $(OBJECTS)


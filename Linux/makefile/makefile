CC = gcc
CFLAGS = -W -Wall
TARGET = PLAY
OBJECTS = add.o mul.o play.o 

all : $(TARGET)

clean :
	rm *.o $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

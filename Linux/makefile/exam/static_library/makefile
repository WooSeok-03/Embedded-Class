CC = gcc
CFLAGS = -W -Wall
TARGET = libexam.a
OBJECT = exam.o

all : $(TARGET) EXAM

clean :
	rm *.o *.a EXAM

$(TARGET) : $(OBJECT)
	ar rc $(TARGET) $(OBJECT)

EXAM :
	$(CC) $(CFLAGS) -o EXAM test.c -L./ -lexam


CC = gcc
CFLAGS = -W -Wall
TARGET = libexam.so.0.0.0

all : $(TARGET) link enrollment EXAM

clean :
	rm *.o *.so *.so.0.0.0 *.so.1 EXAM

exam.o : exam.c
	$(CC) $(CFLAGS) -fPIC -c exam.c

$(TARGET) : exam.o
	$(CC) $(CFLAGS) -shared -Wl,-soname=libexam.so.0 -o libexam.so.0.0.0 exam.o
	
link : libexam.so.0.0.0
	ln -s libexam.so.0.0.0 libexam.so
	ln -s libexam.so.0.0.0 libexam.so.1

enrollment : libexam.so.0.0.0
	sudo cp libexam.so.0.0.0 /usr/local/lib
	sudo ldconfig

EXAM : 
	$(CC) $(CFLAGS) -o EXAM test.c -L./ -lexam

CC = g++
CFLAGS = -std=c++17 -g

TARGETS = imageproc main.o image.o

all:	imageproc

imageproc:	main.o image.o
	$(CC) $(CFLAGS) -o imageproc main.o image.o

main.o:	main.cpp image.h 
	$(CC) $(CFLAGS) -c main.cpp

image.o:	image.cpp image.h stb_image.h stb_image_write.h
	$(CC) $(CFLAGS) -c image.cpp

clean:
	-rm -f ${TARGETS}
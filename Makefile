CC = g++

OBJS = isoparse.o Box.o Container.o

all: isoparse.exe

isoparse.exe: isoparse.o Box.o Container.o
	 $(CC)  -o isoparse.exe isoparse.o Box.o Container.o

isoparse.o: isoparse.cpp
	 $(CC) -c isoparse.cpp
     
Box.o: Box.cpp
	 $(CC)  -c Box.cpp

Container.o: Container.cpp
	 $(CC)  -c Container.cpp

clean:
	 rm isoparse.o Box.o Container.o isoparse.exe

CC = g++

OBJS = isoparse.o Box.o IsoContainer.o

all: isoparse.exe

isoparse.exe: isoparse.o Box.o IsoContainer.o
	 $(CC)  -o isoparse.exe isoparse.o Box.o IsoContainer.o

isoparse.o: isoparse.cpp
	 $(CC) -c isoparse.cpp
     
Box.o: Box.cpp
	 $(CC)  -c Box.cpp

IsoContainer.o: IsoContainer.cpp
	 $(CC)  -c IsoContainer.cpp

clean:
	 rm isoparse.o Box.o IsoContainer.o isoparse.exe *.mp4

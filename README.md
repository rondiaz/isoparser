# isoparser
Sample app which parses ISO base media file

This is an exercise to write a C++ application that prints the layout of the sample ISO media file and extracts the 
contents of the rDAT box.  

It does the following:
1. Read the sample file from
http://demo.castlabs.com/tmp/text0.mp4
2. Iterate through the file and print the size and type of each box found to the console.
3. If the box of type MDAT is found, extract and print the content of that box.

Which problem can occur if the content of the MDAT box is very large?
The size of the box data is represented in 4 bytes (32 bits).  If content in MDAT box is greater than 0xFFFFFFFF
then we would nto be able to correctly parse of capture the content.

Toolchain:
The sample code was built using GNU toolchain that comes with Ubuntu linux distribution.

Building sample code:
$ make clean
$ make

Running sample code:
After successfully running Makefile:
$ ./isoparse
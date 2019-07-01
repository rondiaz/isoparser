#include <unistd.h>
#include <stdio.h>
#include "Box.h"
#include "Container.h"


int main(int argc, char **argv) {

	printf("Start executable\n");

	Box isoBox0;
	Box isoBox(4, 16, (uint8_t*) "test", (uint8_t*) "root");

	Container isoContainer;

	isoContainer.Open((uint8_t*) "text0.mp4");

	isoContainer.Parse();

	isoContainer.Close();

	printf("End executable\n");
	return 0;
}

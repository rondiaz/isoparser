#include "Container.h"


int main(int argc, char **argv) {

	Container isoContainer;

	uint8_t u8Result = isoContainer.Open((uint8_t*) "text0.mp4");

	if (u8Result == 0)
	{
		// If there no opening the Container, then parse it
		isoContainer.Parse();
	}

	isoContainer.Close();

	return 0;
}

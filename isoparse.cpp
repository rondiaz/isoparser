#include "Container.h"

// File:  isoparse.cpp
//
// Description:
//   This file provides a sample app to parse a ISO format file and display the boxes, sizes, and data found in the sample file


int main(int argc, char **argv) {

	Container isoContainer;

	// Open the container used for ISO media file
	uint8_t u8Result = isoContainer.Open();

	if (u8Result == 0)
	{
		// If there no opening the Container, then parse it
		isoContainer.Parse();
	}

	// Close the container
	isoContainer.Close();

	return 0;
}

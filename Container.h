/*
 * Container.h
 *
 *  Created on: Jun 28, 2019
 *      Author: rdiaz
 */

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <stdio.h>
#include <stdint.h>

// Object:
//	Container
// Description:
//	The initial implementation of the Container class captures the properties and methods used for the
//	container used to hold the ISO media file.

class Container {
public:
	Container();
	virtual ~Container();

	int8_t Open();
	int8_t Close();
	int8_t Parse();

private:
	FILE *m_fd;					// File descriptor of the IOS media file
	uint32_t m_u32Size;			// Size of the media file
	uint32_t m_u32Offset;		// Byte offset info media file when parsing the data
	uint8_t* m_u8Buffer;		// Pointer to the file data
};

#endif /* CONTAINER_H_ */

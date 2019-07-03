/*
 * IsoContainer.h
 *
 *  Created on: Jun 28, 2019
 *      Author: rdiaz
 */

#ifndef ISOCONTAINER_H_
#define ISOCONTAINER_H_

#include <stdio.h>
#include <stdint.h>

// Object:
//	IsoContainer
// Description:
//	The initial implementation of the IsoContainer class captures the properties and methods used for the
//	container used to hold the ISO media file.

class IsoContainer {
public:
	IsoContainer();
	virtual ~IsoContainer();

	int8_t Open();
	int8_t Close();
	int8_t Parse();

private:
	FILE *m_fd;					// File descriptor of the IOS media file
	uint32_t m_u32Size;			// Size of the media file
	uint32_t m_u32Offset;		// Byte offset info media file when parsing the data
	uint8_t* m_u8Buffer;		// Pointer to the file data
};

#endif /* ISOCONTAINER_H_ */

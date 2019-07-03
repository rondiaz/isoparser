/*
 * IsoContainer.cpp
 *
 *  Created on: Jun 28, 2019
 *      Author: rdiaz
 */

#include <string.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
using namespace std;

#include "IsoContainer.h"
#include "Box.h"

IsoContainer::IsoContainer() {
	// TODO Auto-generated constructor stub
}

IsoContainer::~IsoContainer() {
	// TODO Auto-generated destructor stub
	// Free up allocated memory
	if (m_u8Buffer)
	{
		delete []m_u8Buffer;
		m_u8Buffer = 0;
	}
}

int8_t IsoContainer::Open()
{
	system("wget http://demo.castlabs.com/tmp/text0.mp4");
	uint8_t name[] = "text0.mp4";

	ifstream isoFstream ((const char*) name, ios::in|ios::binary|ios::ate);
	if (!isoFstream.is_open())
	{
		cout << __FUNCTION__ << ":  ERROR opening  " << name << "\n" ;
		return -1;
	}
	streampos size = isoFstream.tellg();
	m_u8Buffer = new uint8_t [size];
    if (m_u8Buffer == NULL)
    {
		cout << __FUNCTION__ << ":  ERROR allocating memory\n ";
		isoFstream.close();
    	return -1;
    }
    // Copy the file contents to the buffer
	isoFstream.seekg (0, ios::beg);
	isoFstream.read ((char*) m_u8Buffer, size);
	isoFstream.close();
	m_u32Size = size;
	return 0;
}

int8_t IsoContainer::Close()
{
	// Free up allocated memory
	if (m_u8Buffer)
	{
		delete []m_u8Buffer;
		m_u8Buffer = 0;
	}
	return 0;
}

int8_t IsoContainer::Parse()
{
	// Parse the box objects and its properties in the media file
	if (!m_u8Buffer)
	{
		cout << __FUNCTION__ << ":  ERROR buffer memory not allocated\n ";
		return -1;
	}

	// Start at the beginning of the file
	uint32_t u32Offset = 0;

	// Parse until we reach EOF
	while (u32Offset < m_u32Size && m_u8Buffer)
	{
		uint32_t u32Size = 0;	// Size of the box data
		uint8_t u8Type[4];		// Box type

		// Size of the box data is first 4 bytes of the box
		u32Size =  m_u8Buffer[u32Offset + 0] << 24 | m_u8Buffer[u32Offset + 1] << 16 | m_u8Buffer[u32Offset + 2] << 8 | m_u8Buffer[u32Offset + 3];

		// Box type is in bytes 3-7 of the box
		memset(u8Type, 0, sizeof(u8Type));
	    memcpy(u8Type, m_u8Buffer+u32Offset+4, sizeof(u8Type));

	    // Allocate memory for the box data.  The box data is passed into the Box object and the data is deleted when Box is destroyed.
	    uint8_t *u8Data = new uint8_t[u32Size];
	    if (u8Data)
	    {
	    	// Box data starts at byte 8 of the box
	    	memcpy(u8Data, m_u8Buffer + u32Offset + 8, u32Size);
	    }
	    else
	    {
			cout << __FUNCTION__ << ":  ERROR allocating memory for Box data\n ";
	    }

		Box *pBox = new Box(u32Size, u8Type, u32Offset, u8Data);
		if (pBox)
		{
			pBox->Dump();
			delete pBox;
		}
		else
		{
			cout << __FUNCTION__ << ":  ERROR allocating memory for Box\n ";
			if (u8Data)
			{
				// Sicne we were not able to create a Box object, when need to cleanup and delete memory allocated for box data
				delete []u8Data;
				u8Data = 0;
			}
		}

	    if (memcmp(u8Type, "moof", sizeof(u8Type)) == 0 || memcmp(u8Type, "traf", sizeof(u8Type)) == 0)
	    	// Becuase moof and traf contain sub-boxes, offset to next box (sub-box) is 8 bytes (4 byte size data + 4 byte type data)
	    	u32Offset+= 8;
	    else
	    	// Otherwise offset to next box is based on the box data size
	    	u32Offset += u32Size;
	}

	return 0;
}

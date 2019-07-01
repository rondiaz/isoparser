/*
 * Container.cpp
 *
 *  Created on: Jun 28, 2019
 *      Author: rdiaz
 */

#include <stdio.h>
#include <string.h>
#include "Container.h"
#include "Box.h"

Container::Container() {
	// TODO Auto-generated constructor stub
	m_fd = 0;
	m_u32Size = 0;
	m_u32Offset = 0;
	m_u8Buffer = 0;
}

Container::~Container() {
	// TODO Auto-generated destructor stub
}

int8_t Container::Open(uint8_t* name)
{
	m_fd = fopen((const char*) name, "rb");
	if (!m_fd)
	{
		printf("%s:  ERROR opening %s\n", __FUNCTION__, name);
		return -1;
	}
	printf("%s:  SUCCESSFULLY opened Container %s\n", __FUNCTION__, name);

    fseek (m_fd , 0 , SEEK_END);
    int32_t i32Size = ftell (m_fd);
    if (i32Size == -1L)
    {
    	printf("%s:  ERROR getting file size\n", __FUNCTION__);
    	return -1;
    }
//    printf("file size from ftell = %d\n", i32Size);
    rewind (m_fd);

    // allocate memory to contain the whole file:
    m_u8Buffer = new uint8_t[ sizeof(uint8_t) * i32Size ];
    if (m_u8Buffer == NULL)
    {
    	printf("%s:  ERROR allocating memory\n", __FUNCTION__);
    	return -1;
    }
    // copy the file into the buffer:
    uint32_t u32Result = (uint32_t) fread (m_u8Buffer,1,i32Size, m_fd);
//    printf("file size from fread = %u\n", u32Result);
    if (u32Result != (uint32_t) i32Size)
    {
    	printf("%s:  ERROR copying file into buffer\n", __FUNCTION__);
    	return -1;
    }

    m_u32Size = u32Result;

	return 0;
}

int8_t Container::Close()
{
	if (m_u8Buffer)
	{
		delete []m_u8Buffer;
		m_u8Buffer = 0;
	}
	if (m_fd)
	{
		printf("%s:  Close Container\n", __FUNCTION__);
		return fclose(m_fd);
	}
	return 0;
}

int8_t Container::Parse()
{
	if (!m_u8Buffer)
	{
		printf("%s:  ERROR buffer NULL\n", __FUNCTION__);
		return -1;
	}

	uint32_t u32Offset = 0;

	while (u32Offset < m_u32Size && m_u8Buffer)
	{
		uint32_t u32Size = 0;
		uint8_t u8Type[4];

		u32Size =  m_u8Buffer[u32Offset + 0] << 24 | m_u8Buffer[u32Offset + 1] << 16 | m_u8Buffer[u32Offset + 2] << 8 | m_u8Buffer[u32Offset + 3];

		memset(u8Type, 0, sizeof(u8Type));
	    memcpy(u8Type, m_u8Buffer+u32Offset+4, sizeof(u8Type));

	    uint8_t *u8Data = new uint8_t[u32Size];
	    if (u8Data)
	    {
	    	memcpy(u8Data, m_u8Buffer + u32Offset + 8, u32Size);
	    }
	    else
	    {
			printf("%s:  ERROR allocating memory for Box data\n", __FUNCTION__);
	    }

		Box *pBox = new Box(u32Size, u8Type, u32Offset, u8Data);
		if (pBox)
		{
			pBox->Dump();
			delete pBox;
		}
		else
			printf("%s:  ERROR allocating memory for Box\n", __FUNCTION__);
	    if (memcmp(u8Type, "moof", sizeof(u8Type)) == 0 || memcmp(u8Type, "traf", sizeof(u8Type)) == 0)
	    	u32Offset+= 8;
	    else
	    	u32Offset += u32Size;
	}

	return 0;
}

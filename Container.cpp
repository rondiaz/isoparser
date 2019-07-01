/*
 * Container.cpp
 *
 *  Created on: Jun 28, 2019
 *      Author: rdiaz
 */

#include "Container.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

Container::Container() {
	// TODO Auto-generated constructor stub
	m_fd = 0;
	m_size = 0;
	m_buffer = 0;
	m_offset = 0;
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
	printf("%s:  SUCCESSFULLY opened %s\n", __FUNCTION__, name);

    fseek (m_fd , 0 , SEEK_END);
    int32_t i32Size = ftell (m_fd);
    printf("file size from ftell = %d\n", i32Size);
    rewind (m_fd);

    // allocate memory to contain the whole file:
    m_buffer = (uint8_t*) malloc (sizeof(uint8_t) * i32Size);
    if (m_buffer == NULL)
    {
    	printf("%s:  ERROR allocating memory\n", __FUNCTION__);
    	return -1;
    }
    // copy the file into the buffer:
    size_t result = fread (m_buffer,1,i32Size, m_fd);
    printf("file size from fread = %lu\n", result);
    if (result != i32Size)
    {
    	printf("%s:  ERROR copying file into buffer\n", __FUNCTION__);
    	return -1;
    }

    m_size = result;

	return 0;
}

int8_t Container::Close()
{
	if (m_fd)
	{
		printf("%s:  Closing file\n", __FUNCTION__);
		return fclose(m_fd);
	}
	return 0;
}

const uint8_t BOX_NAME_SIZE = 4;

int8_t Container::Parse()
{
	if (!m_buffer)
	{
		printf("%s:  ERROR buffer NULL\n", __FUNCTION__);
		return -1;
	}
	uint64_t u64Offset = 0;
	uint64_t u64Size = 0;
	uint64_t byte0 = 0;
	uint64_t byte1 = 0;
	uint64_t byte2 = 0;
	uint64_t byte3 = 0;
	uint8_t  u8BoxName[16];

	uint8_t iter = 0;

	while (u64Offset < m_size && m_buffer)
	{
		byte0 = m_buffer[u64Offset + 0];
		byte1 = m_buffer[u64Offset + 1];
		byte2 = m_buffer[u64Offset + 2];
		byte3 = m_buffer[u64Offset + 3];
/*
		printf("%s:  byte0 = ", __FUNCTION__);
		printf("%" PRIu64 "\n", byte0);
		printf("%s:  byte1 = ", __FUNCTION__);
		printf("%" PRIu64 "\n", byte1);
		printf("%s:  byte2 = ", __FUNCTION__);
		printf("%" PRIu64 "\n", byte2);
		printf("%s:  byte3 = ", __FUNCTION__);
		printf("%" PRIu64 "\n", byte3);
*/
		u64Size =  byte0 << 32 | byte1 << 16 | byte2 << 8 | byte3;

		printf("%s:  u64Size = ", __FUNCTION__);
		printf("%" PRIu64 "\n", u64Size);

		memset(u8BoxName, 0, sizeof(u8BoxName));
	    memcpy(u8BoxName, m_buffer+u64Offset+4, BOX_NAME_SIZE);

	    printf("%s:  BoxName=%s\n", __FUNCTION__, u8BoxName);

	    if (strcmp((const char*) u8BoxName, "moof") == 0 || strcmp((const char*) u8BoxName, "traf") == 0)
	    	u64Offset+= 8;
	    else
	    	u64Offset += u64Size;

		printf("%s:  u64Offset = ", __FUNCTION__);
		printf("%" PRIu64 "\n", u64Offset);
/*
		iter++;
		if (iter == 8)
		break;  */
	}

	return 0;
}

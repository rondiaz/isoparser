/*
 * Box.cpp
 *
 *  Created on: Jun 28, 2019
 *      Author: rdiaz
 */

#include <stdio.h>
#include <string.h>
#include "Box.h"

Box::Box() {
	// TODO Auto-generated constructor stub
	m_u32Size = 0;
	memset(m_u8Type, 0, sizeof(m_u8Type));
	m_u32Offset = 0;
	m_u8Data = 0;
}

Box::~Box() {
	// TODO Auto-generated destructor stub
	if (m_u8Data)
	{
		delete []m_u8Data;
		m_u8Data = 0;
	}
}

Box::Box(
			uint32_t u32Size,
			uint8_t* u8Type,
			uint32_t u32Offset,
			uint8_t* u8Data
		)
{
	m_u32Size 		= u32Size;

	memset(m_u8Type, 0, sizeof(m_u8Type));
	memcpy(m_u8Type, u8Type, sizeof(m_u8Type));

	m_u32Offset 	= u32Offset;

	m_u8Data = u8Data;
}

void Box::Dump()
{
	uint8_t u8Buf[8];
	memset(u8Buf, 0, sizeof(u8Buf));
	// Use buffer to display string readable box type
	memcpy(u8Buf, m_u8Type, sizeof(m_u8Type));
/*
	printf("Box::%s:  \n", __FUNCTION__);
	printf("     type = %s\n", u8Buf);
	printf("     size = %d\n", m_u32Size);
	printf("     offset = %d\n", m_u32Offset);
*/
	printf("Found Box of type %s and size = %d\n", u8Buf, m_u32Size);
	if (memcmp(m_u8Type, "mdat", sizeof(m_u8Type)) == 0)
	{
		printf("Content of mdat box is:\n");
		for (uint32_t u32Index = 0; u32Index < m_u32Size; u32Index++)
		{
			printf("%c", m_u8Data[u32Index]);
		}
	}
}


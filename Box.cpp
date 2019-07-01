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
	printf("%s %d\n", __FUNCTION__, __LINE__);

}

Box::~Box() {
	// TODO Auto-generated destructor stub
}

Box::Box( 	uint16_t offset,
			uint16_t size,
			uint8_t* name,
			uint8_t* parent)
{
	printf("%s %d\n", __FUNCTION__, __LINE__);

	m_offset 	= offset;
	m_size 		= size;
	memset(m_name, 0, sizeof(m_name));
	memcpy(m_name, name, sizeof(m_name));
	memset(m_parent, 0, sizeof(m_parent));
	memcpy(m_parent, parent, sizeof(m_parent));

	printf("%s:  m_offset=%d, m_size=%d, m_name=%s, m_parent=%s\n", __FUNCTION__, m_offset, m_size, m_name, m_parent);
}


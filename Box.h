/*
 * Box.h
 *
 *  Created on: Jun 28, 2019
 *      Author: rdiaz
 */

#ifndef BOX_H_
#define BOX_H_

#include <stdint.h>

class Box {
public:
	Box();
	virtual ~Box();

	Box( uint16_t offset,
		 uint16_t size,
		 uint8_t* name,
		 uint8_t* parent);

private:
	uint8_t m_name[16];
	uint16_t m_offset;
	uint16_t m_size;
	uint8_t m_parent[16];
};

#endif /* BOX_H_ */

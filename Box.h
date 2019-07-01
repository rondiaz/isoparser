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

	Box(
		  uint32_t u32Size,
		  uint8_t* u8Type,
		  uint32_t u32Offset,
		  uint8_t* u8Data
		);

	void Dump();

private:
	uint8_t m_u8Type[4];
	uint32_t m_u32Size;
	uint32_t m_u32Offset;
	uint8_t *m_u8Data;
};

#endif /* BOX_H_ */

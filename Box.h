/*
 * Box.h
 *
 *  Created on: Jun 28, 2019
 *      Author: rdiaz
 */

#ifndef BOX_H_
#define BOX_H_

#include <stdint.h>

// Object:
//	Box
// Description:
//	The initial implementation of the Box class captures the basic properties of the Box object found
//	in ISO media file format.

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

	void Dump();			// Dump box property info to console output

private:
	uint8_t m_u8Type[4];	// 4-byte box type
	uint32_t m_u32Size;		// size of the data
	uint32_t m_u32Offset;	// byte offset into the ISO media file
	uint8_t *m_u8Data;		// pointer to the data buffer
};

#endif /* BOX_H_ */

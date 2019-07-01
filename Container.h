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

class Container {
public:
	Container();
	virtual ~Container();

	int8_t Open(uint8_t* name);
	int8_t Close();
	int8_t Parse();

private:
	FILE *m_fd;
	uint32_t m_u32Size;
	uint32_t m_u32Offset;
	uint8_t* m_u8Buffer;
};

#endif /* CONTAINER_H_ */

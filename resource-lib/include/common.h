#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <SDL.h>

#ifndef __HEADER_COMMON_H
#define __HEADER_COMMON_H

using namespace std;

// types
typedef unsigned char 	uint8;
typedef unsigned short 	uint16;
typedef unsigned int 	uint32;
typedef unsigned long	uint64;

// useful defines
#define PACKED __attribute__((packed))

// file types
#define PACK(a, b, c, d) 		((uint32)d|(c<<8)|(b<<16)|(a<<24))
#define OPX_RES_MAGIC			0x4949
#define OPX_RES_VERSION			PACK(1, 0, 0, 0)

// return statuses
#define OPX_STATUS_OK 0
#define OPX_STATUS_ERROR 1

#endif
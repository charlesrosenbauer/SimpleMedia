#ifndef __SIMPLE_MEDIA_HEADER__
#define __SIMPLE_MEDIA_HEADER__


#include "stdint.h"


typedef struct{
	uint32_t	magic;
	uint32_t	h, w;
	uint64_t	fsize;
	uint64_t	rBlocks;
	uint64_t	gBlocks;
	uint64_t	bBlocks;
	uint64_t	aBlocks;
}SM_Img_Header;


typedef struct{
	uint32_t	magic;
	uint32_t	h, w, audioRate;
	uint64_t	fsize;
	uint64_t	blockct;
	uint8_t		framerate;
}SM_Str_Header;


typedef struct{
	uint32_t	magic;
	uint32_t	audioRate;
	uint64_t	fsize;
	uint64_t	blockct;
}SM_Aud_Header;


typedef struct{
	uint32_t	magic;
	uint32_t	h, w, audioRate;
	uint64_t	fsize;
	uint64_t	blockct;
	uint8_t		framerate;
}SM_Vid_Header;


typedef struct{
	uint8_t		blocktype;
	uint8_t		paddingA;		// Find some other data to store here
	uint16_t	paddingB;		// ...
	
	uint32_t	size;
	uint64_t	byteTable[4];
}SM_BitTable;

typedef struct{
	uint8_t		blocktype;
	uint8_t		offset;
	uint8_t		range;
	uint8_t		padding;
	
	uint32_t	size;
}SM_BitRange;




typedef enum{
	SMIT_RAW	= 0x0000,		// Up to 2 ^ 8+5 raw bytes
	SMIT_HRLE	= 0x2000,		// Up to 2 ^ 8+5 bytes equal to previous byte
	SMIT_VRLE	= 0x4000,		// Up to 2 ^ 8+5 bytes equal to above byte
	SMIT_HDF3	= 0x6000,		// Up to 2 ^ 8+5 3-bit segments of +/- deltas from previous byte
	SMIT_VDF3	= 0x8000,		// Up to 2 ^ 8+5 3-bit segments of +/- deltas from above byte
	SMIT_HDF5	= 0xA000,		// Up to 2 ^ 8+5 5-bit segments of +/- deltas from previous byte
	SMIT_VDF5	= 0xC000,		// Up to 2 ^ 8+5 5-bit segments of +/- deltas from above byte
	SMIT_PALT	= 0xE000,		// Up to 2 ^ 8+5 4-bit segments of indices into previous bytes
	
	SMIT_MASK	= 0xE000,
	SMIT_LEN	= 0x1FFF
}SM_Img_BlockType;

typedef uint16_t SM_Img_Block;


int encodeImage(uint32_t*, int, int, SM_Img_Header*, void*);


#endif

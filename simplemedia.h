#ifndef __SIMPLE_MEDIA_HEADER__
#define __SIMPLE_MEDIA_HEADER__


#include "stdint.h"


typedef struct{
	uint32_t	magic;
	uint32_t	h, w, framect;
	uint64_t	fsize;
	uint64_t	blockct;
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
}SM_BitRange



/*
	Repeat last pixel N times. N = len + bottom 5 bits of key
*/
typedef struct{
	uint8_t		key;	
	uint8_t		len;
}SM_Img_RLE;


/*
	Repeat last pixel N times, with increment added each time.
	N     = len
	delta = bottom 5 bits of key
*/
typedef struct{
	uint8_t		key;
	uint8_t		len;
}SM_Img_Delta_RLE;




#endif

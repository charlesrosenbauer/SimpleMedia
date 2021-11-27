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


#endif

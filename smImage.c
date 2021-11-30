#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"

#include "simplemedia.h"


inline void splitRGBA(uint32_t p, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a){
	*a = p >> 24;
	*r = p >> 16;
	*g = p >>  8;
	*b = p;
}

inline int countEql(uint8_t a, uint8_t b, int* ct){
	int c = *ct;
	*ct   = (a == b)? c+1 : 0;
	return  (a != b)? c-1 : 0;
}

inline int ctEqlMsg(uint8_t a, uint8_t b, int* ct, int k, char* msg){
	int c = *ct;
	if     ((a != b) && (c >= k)) printf("%s %i\n", msg, c);
	*ct   = (a == b)? c+1 : 0;
	return  (a != b)? c-1 : 0;
}


int encodeImage(uint32_t* px, int h, int w, SM_Img_Header* hd, void* buffer){
	
	int rlen = 0;
	int size = h * w;
	
	int runHA = 0;
	int runVA = 0;
	int runHR = 0;
	int runVR = 0;
	int runHG = 0;
	int runVG = 0;
	int runHB = 0;
	int runVB = 0;
	
	
	
	uint8_t ha = 0, hr = 0, hg = 0, hb = 0;
	uint8_t va = 0, vr = 0, vg = 0, vb = 0;
	for(int i = 0; i < size; i++){
		uint32_t p = px[i];
		uint8_t  r, g, b, a;
		splitRGBA(p, &r, &g, &b, &a);
	
		if(i > w){
			splitRGBA(px[i-w], &vr, &vg, &vb, &va);
		}
		
		ctEqlMsg(a, ha, &runHA, 5, "HA Run");
		ctEqlMsg(r, hr, &runHR, 5, "HR Run");
		ctEqlMsg(g, hg, &runHG, 5, "HG Run");
		ctEqlMsg(b, hb, &runHB, 5, "HB Run");
		ctEqlMsg(a, va, &runVA, 5, "VA Run");
		ctEqlMsg(r, vr, &runVR, 5, "VR Run");
		ctEqlMsg(g, vg, &runVG, 5, "VG Run");
		ctEqlMsg(b, vb, &runVB, 5, "VB Run");
	
		ha = a;
		hr = r;
		hg = g;
		hb = b;
	}
	
	return rlen;
}

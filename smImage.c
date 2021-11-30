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

inline uint8_t gray(uint32_t p){
	uint32_t r = (p >> 16) & 0xff;
	uint32_t g = (p >>  8) & 0xff;
	uint32_t b = (p      ) & 0xff;
	return (r + g + b) / 3;
}


typedef struct{
	uint8_t       last;			// Horizontal RLE and Delta
	int8_t        minDelta;		// Delta Range
	int8_t        maxDelta;		// Delta Range
	int           offsets[256];	// Palette
	int           hrun, vrun;	// Runs
	uint64_t      bits[4];		// Bits
	int           pct;			// Bit popcount
	
	SM_Img_Block* blocks;		// Block management
	int           bct, lastIx, byteIx;
}ChannelData;

ChannelData makeChannelData(SM_Img_Block* bs){
	ChannelData ret = (ChannelData){.last=0, .minDelta=0, .maxDelta=0, .hrun=0, .vrun=0, .pct=0, .blocks=bs, .bct=0, .lastIx=0, .byteIx=0};
	for(int i = 0; i < 256; i++) ret.offsets[i] = 0;
	for(int i = 0; i <   4; i++) ret.bits   [i] = 0;
	return ret;
}

void resetChannelData(ChannelData* c){
	c->minDelta = 0x7f;
	c->maxDelta = 0xff;
	c->hrun     = 0;
	c->vrun     = 0;
	for(int i = 0; i < 4; i++) c->bits[i] = 0;
	c->pct      = 0;
	c->lastIx   = c->byteIx;
}

void updateChannelData(ChannelData* d, uint8_t p, uint8_t v){
	d->byteIx++;
	d->pct        += ((1l << (p & 0x3f)) & d->bits[p>>6]) != 0;
	d->bits[p>>6] |=  (1l << (p & 0x3f));

	int vrun = 0;
	int hrun = 0;
	if(p == v){
		d->vrun++;
	}else{
		vrun = d->vrun;
		d->vrun = 0;
	}
	
	if(p == d->last){
		d->hrun++;
	}else{
		hrun = d->hrun;
		d->hrun = 0;
	}
	
	/*
		Priorities:
		* HRLE
		* VRLE
		* Raw <= 8 values
		* HD3
		* VD3
		* Palette
		* Raw <=32 values
		* HD5
		* VD5
		* Raw
	*/
	
	const int RUNK  =   5;
	const int RUN8  =  50;
	const int RUN32 = 100;
	hrun = (hrun < RUNK)? 0 : hrun;
	vrun = (vrun < RUNK)? 0 : vrun;
	if(hrun > vrun){
		// TODO: Add hrun block
		printf("HRUN %i\n", hrun);
		resetChannelData(d);
	}else if(vrun != 0){
		// TODO: Add vrun block
		printf("VRUN %i\n", vrun);
		resetChannelData(d);
	}else if((d->pct <=  8) && ((d->byteIx - d->lastIx) > RUN8)){
		// TODO: Add Raw 8 block
		printf("RAW 8 %i\n", d->byteIx - d->lastIx);
		resetChannelData(d);
	}else if(0){
		// TODO: Deal with delta-3s and palettes
	}else if((d->pct <= 32) && ((d->byteIx - d->lastIx) > RUN32)){
		// TODO: Add Raw 32 block
		printf("RAW 32 %i\n", d->byteIx - d->lastIx);
		resetChannelData(d);
	}else if(0){
		// TODO: Deal with delta-5s and full raws
	}
}




int encodeImage(uint32_t* px, int h, int w, SM_Img_Header* hd, void* buffer){
	
	int rlen = 0;
	int size = h * w;
	
	ChannelData rd, gd, bd, ad, ld;
	rd = makeChannelData(malloc(sizeof(SM_Img_Block) * rlen));
	gd = makeChannelData(malloc(sizeof(SM_Img_Block) * rlen));
	bd = makeChannelData(malloc(sizeof(SM_Img_Block) * rlen));
	ad = makeChannelData(malloc(sizeof(SM_Img_Block) * rlen));
	ld = makeChannelData(malloc(sizeof(SM_Img_Block) * rlen));
	
	uint8_t va = 0, vr = 0, vg = 0, vb = 0, vl = 0;
	for(int i = 0; i < size; i++){
		uint32_t p = px[i];
		uint8_t  r, g, b, a, l;
		splitRGBA(p, &r, &g, &b, &a);
		l = gray (p);
	
		if(i > w){
			splitRGBA(px[i-w], &vr, &vg, &vb, &va);
			vl = gray(px[i-w]);
		}
		
		updateChannelData(&rd, r, vr);
		updateChannelData(&gd, g, vg);
		updateChannelData(&bd, b, vb);
		updateChannelData(&ad, a, va);
		updateChannelData(&ld, l, vl);
	}
	
	free(rd.blocks);
	free(gd.blocks);
	free(bd.blocks);
	free(ad.blocks);
	free(ld.blocks);
	
	return rlen;
}

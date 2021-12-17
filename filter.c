#include "stdint.h"

#include "experiment.h"



void pixVDiff(uint32_t* px, uint32_t* out, int h, int w){
	int ix = 0;
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			uint32_t p  =  px[ix];
			uint32_t v  = (i > 0)? px[ix-w] : px[ix];
			
			uint8_t* pb = (uint8_t*)&p;
			uint8_t* vb = (uint8_t*)&v;
			for(int k = 0; k < 4; k++) pb[k] = pb[k] - vb[k];
			
			out[ix] = p;
			ix++;
		}
	}
}

void pixHDiff(uint32_t* px, uint32_t* out, int h, int w){
	int ix = 0;
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			uint32_t p  =  px[ix];
			uint32_t l  = (j > 0)? px[ix-1] : px[ix];
			
			uint8_t* pb = (uint8_t*)&p;
			uint8_t* lb = (uint8_t*)&l;
			for(int k = 0; k < 4; k++) pb[k] = pb[k] - lb[k];
			
			out[ix] = p;
			ix++;
		}
	}
}

void pixVAbsDiff(uint32_t* px, uint32_t* out, int h, int w){
	int ix = 0;
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			uint32_t p  =  px[ix];
			uint32_t v  = (i > 0)? px[ix-w] : px[ix];
			
			uint8_t* pb = (uint8_t*)&p;
			uint8_t* vb = (uint8_t*)&v;
			for(int k = 0; k < 4; k++){ pb[k] = pb[k] - vb[k]; pb[k] = (pb[k] > 127)? pb[k]-128 : pb[k]; }
			
			out[ix] = p;
			ix++;
		}
	}
}

void pixHAbsDiff(uint32_t* px, uint32_t* out, int h, int w){
	int ix = 0;
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			uint32_t p  =  px[ix];
			uint32_t l  = (j > 0)? px[ix-1] : px[ix];
			
			uint8_t* pb = (uint8_t*)&p;
			uint8_t* lb = (uint8_t*)&l;
			for(int k = 0; k < 4; k++){ pb[k] = pb[k] - lb[k]; pb[k] = (pb[k] > 127)? pb[k]-128 : pb[k]; }
			
			out[ix] = p;
			ix++;
		}
	}
}

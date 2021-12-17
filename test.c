#include "stdint.h"
#include "stdlib.h"

#include "SDL/SDL.h"

#include "simplemedia.h"
#include "experiment.h"






int main(){
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* image  = SDL_LoadBMP("media/009.bmp");
	SDL_Surface* screen = SDL_SetVideoMode(image->w, image->h, 32, 0);
	SDL_BlitSurface(image, 0, screen, 0);
	
	pixVAbsDiff(screen->pixels, screen->pixels, image->h, image->w);
	
	SDL_Flip(screen);
	SDL_Delay(15000);
	
	int         pxct = screen->h * screen->w;
	
	uint32_t*    rps = malloc(sizeof(uint32_t) * pxct);
	uint32_t*    gps = malloc(sizeof(uint32_t) * pxct);
	uint32_t*    bps = malloc(sizeof(uint32_t) * pxct);
	uint32_t* pixels = screen->pixels;
	
	int ct = encodeImage(pixels, image->h, image->w, NULL, NULL);
	
	/*
	for(int i = 0; i < pxct; i++){
		uint32_t p =  pixels[i];
		uint32_t r =  (p >> 16) & 0xff;
		uint32_t g =  (p >>  8) & 0xff;
		uint32_t b =  (p      ) & 0xff;
		p          =  (r + g + b) / 3;
		rps[i]     = ((p - r) & 0xff);
		gps[i]     = ((p - g) & 0xff);
		bps[i]     = ((p - b) & 0xff);
		rps[i]     = (rps[i] > 127)? (255 - rps[i]) & 0xff : rps[i];
		gps[i]     = (gps[i] > 127)? (255 - gps[i]) & 0xff : gps[i];
		bps[i]     = (bps[i] > 127)? (255 - bps[i]) & 0xff : bps[i];
		rps[i]     = (rps[i] & 0xff) << 16;
		gps[i]     = (gps[i] & 0xff) <<  8;
		bps[i]     = (bps[i] & 0xff);
		p         *=   0x010101;
		pixels[i]  =   p;
	}
	
	SDL_Flip(screen);
	SDL_Delay(3000);
	
	for(int i = 0; i < pxct; i++) pixels[i] = rps[i];
	SDL_Flip(screen);
	SDL_Delay(3000);
	
	for(int i = 0; i < pxct; i++) pixels[i] = gps[i];
	SDL_Flip(screen);
	SDL_Delay(3000);
	
	for(int i = 0; i < pxct; i++) pixels[i] = bps[i];
	SDL_Flip(screen);
	SDL_Delay(3000);
	*/
	
	SDL_Quit();
}

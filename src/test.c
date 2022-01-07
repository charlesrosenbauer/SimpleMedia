#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"


int loadFile(char* fname, char** buffer, int64_t* fsize){
	FILE*  pFile = fopen (fname,"r");
	size_t result;
	if (pFile == NULL){ printf("Cannot locate file %s.", fname); return 0; }
	fseek (pFile , 0 , SEEK_END);
	*fsize = ftell (pFile);
	rewind (pFile);

	// allocate memory to contain the whole file:
	*buffer = malloc((sizeof(char)*(*fsize)) + 4);
	if (buffer == NULL) { printf("Memory error",stderr); exit(2); }

	// copy the file into the buffer:
	result = fread (*buffer,1,(*fsize),pFile);
	if (result != (*fsize)) { printf("Reading error",stderr); exit(3); }
	
	fclose(pFile);
	return 1;
}


typedef enum{
	MD_RLE		= 0x0,	// Run length encoding
	MD_RDE		= 0x1,	// Run delta  encoding
	MD_1BB		= 0x2,	// 1 bit bytes
	MD_1BD		= 0x3,	// 1 bit deltas
	MD_2BB		= 0x4,	// 2 bit bytes
	MD_2BD		= 0x5,	// 2 bit deltas
	MD_3BB		= 0x6,	// 3 bit bytes
	MD_3BD		= 0x7,	// 3 bit deltas
	MD_4BB		= 0x8,	// 4 bit bytes
	MD_4BD		= 0x9,	// 4 bit deltas
	MD_A		= 0xA,	// Placeholder
	MD_B		= 0xB,
	MD_C		= 0xC,
	MD_D		= 0xD,
	MD_E		= 0xE,
	MD_RAW		= 0xF	// Raw bytes
}CompressorMode;

typedef struct{
	uint32_t	blockct;
	uint32_t	rawsize;
	uint32_t	outsize;
	// u16 blocks after this : 12b size + 4b mode
	// u8  bytes  after that : raw data bytes
	// One nice thing about this approach is that it should be possible to
	// thread this pretty efficiently. Just iterate over blocks, spawning
	// threads, and keeping track of where each block starts.
}CompressHeader;


int decompress(uint32_t* buffer, int size, uint8_t** out){
	CompressHeader* head = (CompressHeader*)buffer;
	if((head->blockct + head->blockct + head->rawsize + sizeof(CompressHeader)) > size) return -1;
	
	*out = malloc( sizeof(uint8_t) * head->outsize);
	uint16_t* blocks = &((uint16_t*)buffer)[sizeof(CompressHeader) / 2];
	
	int rawIx = 0;
	int outIx = 0;
	for(int i = 0; i < head->blockct; i++){
		int             len = blocks[i] >>  4;
		CompressorMode mode = blocks[i] & 0xf;
		switch(mode){
			// TODO: Fill this out
		}
	}
	
	return head->outsize;
}


int main(int argc, char** args){
	for(int f = 1; f < argc; f++){
		char*    file;
		int64_t  size;
		if(loadFile(args[f], &file, &size)){
			int     cts[256];
			int     dfs[256];
			uint8_t last = file[size-1];
			for(int i = 0; i <  256; i++){ cts[i] = 0; dfs[i] = 0; }
			for(int i = 0; i < size; i++){ cts[file[i]]++; dfs[(uint8_t)file[i] ^ last]++; last = file[i]; }
			for(int i = 0; i <  256; i++)  printf("%i : %i\n", i, cts[i]);
			for(int i = 0; i <  256; i++)  printf("%i : %i\n", i, dfs[i]);
			
			int		css[32];
			int		dss[32];
			for(int i = 0; i <   32; i++){ css[i] = 0; dss[i] = 0; }
			for(int i = 0; i <  256; i++){ css[32-__builtin_clz(cts[i])]++; dss[32-__builtin_clz(dfs[i])]++; }
			for(int i = 0; i <   32; i++) printf("%i : %i\n", i, css[i]);
			for(int i = 0; i <   32; i++) printf("%i : %i\n", i, dss[i]);
		}
	}
}

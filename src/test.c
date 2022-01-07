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

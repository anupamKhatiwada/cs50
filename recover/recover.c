#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t byte;


int main(int argc, char *argv[])
{


    if(argc!=2) return 1;

    FILE *file = fopen(argv[1],"r");
    FILE *newfile=NULL;

    const int BLOCK_SIZE=512;

    byte* buffer = malloc(BLOCK_SIZE);
    char* filename=malloc(8);

    byte found = 0,count=0;

    while(fread(buffer,BLOCK_SIZE,1,file)==1){

        if(buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff && (buffer[3] & 0xf0) == 0xe0){
              if(!found) found=1;
              else {fclose(newfile);++count;}


            //   Open new file

            sprintf(filename,"%03i.jpg",count);
            newfile=fopen(filename,"w");
            fwrite(buffer,BLOCK_SIZE,1,newfile);


        }else{
            if(!found) continue;

            fwrite(buffer,BLOCK_SIZE,1,newfile);

        }


    }

    fclose(file);
    fclose(newfile);
    free(buffer);
    free(filename);


    return 0;



}
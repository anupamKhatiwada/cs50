#include <stdio.h>
#include <cs50.h>

void printPattern(int height){
    int counter=0;

    for(int i=0;i<height;i++){

        for(int j=0,n=2*height+2;j<n;j++){
            if((j>=(n/2-2-counter) && j<=(n/2-2)) || (j>=(n/2+1) && j<=(n/2+1+counter))) printf("#");
            else if(j>n/2+1+counter)
            {
                printf("\n");
                break;
            }
            else printf(" ");
        }
        // printf("\n");
        counter++;
    }
    printf("\n");
}

int main(void){

    int height;
    do{
        height=get_int("Height: ");
    }while(height<1 || height>8);

    printPattern(height);


}
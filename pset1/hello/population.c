#include <cs50.h>
#include <stdio.h>

int calculate(int startValue,int endValue,int count){
    if(startValue>=endValue) return count;

    return calculate(startValue+startValue/3-startValue/4,endValue,count+1);
}

int main(void)
{
    // TODO: Prompt for start size
    int startSize,endSize;
    do{
        startSize=get_int("Start size: ");
    }while(startSize<9);

    // TODO: Prompt for end size

     do{
        endSize=get_int("End size: ");
    }while(endSize<startSize);

    // TODO: Calculate number of years until we reach threshold



    // TODO: Print number of years
    printf("Years: %i\n",calculate(startSize,endSize,0));

}
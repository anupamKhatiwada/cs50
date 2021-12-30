#include <stdio.h>
#include <cs50.h>
#include <math.h>

// The below function returns sum of all the digits of the argument
int digitSum(int n,int sum){

    if(n==0) return sum;

    return digitSum(n/10,sum+(n%10));
}

int checkSum(long number){
    int counter=0;
    // long copy=number;

    int mulDigits=0,nonMulDigits=0;

    // Get every other digit from the end
    while(number>0){

        // Let's get each digit from the back
        int currentDigit=number%10;

        // If the counter%2>0 then this is a valid digit which is to be multiplied by two
        if(counter%2>0) mulDigits+=digitSum(currentDigit*2,0);
        else nonMulDigits+=currentDigit;

        counter++;

        number=number/10;


    }

    int total=mulDigits+nonMulDigits;

    return total%10;




}

int main(void){

    long n=get_long("Number: ");


    int i = checkSum(n);

    if(i!=0) printf("INVALID\n");
    else{
        int numberOfDigits=floor(log10(n) + 1);

        if((numberOfDigits==13 || numberOfDigits==16) && (int)(n / pow(10, numberOfDigits-1))==4){
            printf("VISA\n");
        }else if(numberOfDigits==15 && ((int)(n / pow(10, numberOfDigits-2))==34 || (int)(n / pow(10, numberOfDigits-2))==37)){
            printf("AMEX\n");
        }else if(numberOfDigits==16 && ((int)(n / pow(10, numberOfDigits-2))>=51 && (int)(n / pow(10, numberOfDigits-2))<=55)){
            printf("MASTERCARD\n");
        }else printf("INVALID\n");


}
}
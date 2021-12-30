#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int calculateGrade(string s);

int main(void){

    string receivedString=get_string("Text: ");


    int grade = calculateGrade(receivedString);





    if(grade<1) printf("Before Grade 1\n");
    else if(grade>=1 && grade<16) printf("Grade %i\n",grade);
    else printf("Grade 16+\n");



}

int calculateGrade(string s){

    int letters=0,words=1,sentences=0;

    for(int i=0,n=strlen(s);i<n;i++){

        if((s[i]>=65 && s[i]<=90) || (s[i]>=97 && s[i]<=122)) letters++;

        if(s[i]==32) words++;

        if(s[i]==46 || s[i]==33 || s[i]==63) sentences++;

    }


    // printf("letters %i\n  words %i\n sentences %i\n",letters,words,sentences);

    double L=((double)letters/words)*100;
    double S=((double)sentences/words)*100;

    int index=round(0.0588 * L - 0.296 * S - 15.8);

    // printf("This is the grade %i\n",index);

    return index;


}
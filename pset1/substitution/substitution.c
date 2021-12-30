#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>


int validateString(string s);

string encipher(string s, string pattern);

int main(int argc, string argv[]){

    // If incorrect number of arguments provided

    if(argc!=2){
        printf("Enter the correct number of arguments. \n");
        return 1;
    }

    int result = validateString(argv[argc-1]);

    if(result!=0){

        // This means that the provided string is invalid
        // Do the necessary

        printf("Invalid key!\n");
        return 1;

    }

    // If the key is valid convert the inserted value to the ciphered value
    // First take in the value to encipher

    string toEncrypt = get_string("plaintext:");

    printf("ciphertext: %s\n",encipher(toEncrypt,argv[argc-1]));



    return 0;




}

int validateString(string s){

    // Write the different validation conditions

    /*

        The different validation conditions are:
        1. Should contain exactly twenty six characters.
        2. Should contain each character only once.
        3. Should contain only uppercase or lower case characters.
           Numbers and special characters are not allowed.

    */


    // Let's do all three validations within one for loop


    // Let us take a reference empty array for implementing search
    // Add the int values of all the characters of the string to this array at the respective index

    bool reference[26]={0};

    int n = strlen(s);

    if(n!=26) return 1;

    for(int i=0;i<n;i++){

        if(!((s[i]>='a' && s[i]<='z') || (s[i]>='A' && s[i]<='Z'))) return 1;

        // For each variable checked, check if it was encountered before
        // If it was return 1 but think about how search will be implemented

        // How to implement the search??
        // Implement using the ascii table and the reference array above

        // We now convert s[i] to uppercase so as to covert all values to uppercase
        // Case determination of cipher string will be done on the basis of the string to be converted



        /*
            Since we are changing the string here let's check
            if it is changing the original string that is being passed. It will, because strings
            which are internally character arrays are passed by reference.

            Let's still print this and see it in action (Done in the encipher method).
            It is behaving as expected.

        */

        if(islower(s[i])){
            s[i]=(char)((int)s[i]-32);
        }


        if(reference[(int)s[i]-65]==false) reference[(int)s[i]-65]=true;
        else return 1;

    }

    return 0;


}

string encipher(string s, string pattern){

    /*
        In this phase we have validated the pattern and
        are sure that the pattern we are taking is indeed valid.

        Now we need to match the characters in the string being passed and convert it with
        characters from the pattern. Let's think how this can be achieved.

    */

    for(int i=0,n=strlen(s);i<n;i++){


    /*

        Had forgotten to add this condition. It states that if the
        current character is not an alphabet skip it and do not do any processing on it.

    */
        if(!((s[i]>='a' && s[i]<='z') || (s[i]>='A' && s[i]<='Z'))) continue;

        if(islower(s[i])){
            // Making the value uppercase and subtract 65 to see what index you'll get in a zero based array
            s[i]=(char)(pattern[(int)s[i]-32-65]+32);
        }else {
            s[i]=(char)pattern[(int)s[i]-65];
        }

    }





    return s;
}
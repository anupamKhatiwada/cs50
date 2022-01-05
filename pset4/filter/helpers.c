#include "helpers.h"
#include <stdio.h>




typedef uint8_t byte;

/*

    The below function is moronic because of the nature of integer arithmetic in C.
    We need to write a decent roundOff function or fix this one.

*/

byte roundOff(byte n){
    return n>=0?(byte)(n+0.5):(byte)(n-0.5);
}


int roundedAverage(int sum,int counter);



// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    byte average,modulo;





    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){

            /*

                The below assignment statement provides a very nice problem.
                The fact is when we are adding the three values of rgb we need to make sure the
                average is less than or equal to 255.

                Let's do some experimentation.


                It says that greyscale incorrectly filters single pixel image without whole
                number average.


                That is if the sum of all three does not give a whole number average we need to
                we need to round it off so that it does do that.

                For a problem without whole number average we need to do something.

                The problem is with rounding off the values. The issue for eg with this
                particular problem is after the three values are added when we divide it
                by the number of values. The addition part will always yeild some whole number.

                When we divide it by the number of elements (in our case 3) it will yeild a whole
                number because of integer division. This is a problem because for ex.
                the value we get is 123.333 we should return 123 whereas if it is 123.666 or 123.5
                we should return 124. How do we achieve this with just integer values.


                One way to go about this is to use the modulo operator.

                We know that the modulo operator always returns a whole number value.
                We can use this return value to do the rounding off of a particular number
                using only 8-bit integer type.

                How do we go about the process of finding this??



                On a seperate note all these number conversion issues we are facing with
                C gives us an actual overview of what real programming with "Lower level languages"
                looks like where the compiler does not let you get away with things such as these
                and the programmer explicitely has to think about all these things.


                byte modulo = (a+b+c)%3;

                We found the modulo. Looking at the value of the modulo we can make some
                observations:
                - If modulo is 0,1 we dont add anything.
                - If modulo is 2 we add one to the value of the average unless the value of average
                  is 255 in which case we cap the value to 255.


                These are observations ie declarative statements. We need to now arrive to imperative
                conclusions using our declarative observations to be certain when we need to add 1
                and when we don't.

                What conclusions do we draw?

                The conclusions we draw are:
                - If the modulo is half or more than half the divisor we add 1.
                - Otherwise we don't.


                How do we write this logic?



                Below is a gret piece of logic to write the round off function as
                the normal function does not work for a lot of examples.



            */

            // average=(image[i][j].rgbtBlue+image[i][j].rgbtRed+image[i][j].rgbtGreen)/3;
            // modulo = (image[i][j].rgbtBlue+image[i][j].rgbtRed+image[i][j].rgbtGreen)%3;


            // if(modulo==2) average+=1;


            average = (byte)roundedAverage(image[i][j].rgbtBlue+image[i][j].rgbtRed+image[i][j].rgbtGreen,3);


            /*

                All checks passed although we haven't explicitely checked if average is more than 255?

                This is really fun. We don't need to explicitely check if average is more than 255
                because if it was 255 that means value of that pixel was white. Adding one to that
                would in 8-bit integer addition yeild 0 which is black which is what we need for grey
                scale.


                MINDFUCK!!


            */





            // printf("%i\n",average);

            image[i][j].rgbtBlue=average;
            image[i][j].rgbtRed=average;
            image[i][j].rgbtGreen=average;
        }
    }



    return;
}





// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    byte oR, oG, oB, sR, sG, sB;

    RGBTRIPLE s;

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){

            // s=image[i][j];


            // oR = s.rgbtRed;
            // oG = s.rgbtGreen;
            // oB = s.rgbtBlue;



            oR = image[i][j].rgbtRed;
            oG = image[i][j].rgbtGreen;
            oB = image[i][j].rgbtBlue;


            /*

                The sepia function is not working. This is probably because if
                the limitations of 8-bit integer addition.

                Intuition was spot on! The issue was because of limitations of
                8-bit integer addition.



                We still have an issue.


                We need a proper decimal to integer converter.


                Let us examine this particular number and keeping in mind the nature of
                8-bit integer rule let us make some observations about the nature of this number.





                Let us look at a very abstaracted view of how the below
                values will be evaluated bearing in mind 8-bit integer arithmetic.
                The result of the evaluation should result an 8-bit number and the tree
                variables visible are also of the 8-bit integer data type.

                (0.393 * oR + 0.769 * oG + 0.189 * oB)

                - 0.393 * some_value will yeild some sort of decimal value.
                - So will each of the three additions.
                - Do we round of at this stage or do we round off after adding all three as
                  decimal values.
                - Will the two processes yeild different values?
                - In which case which does the processor use?


                - The process taken by the processor is substitution ie. first all the variables
                  were opened and their values were added.
                - In the second step the decimal value was typecasted into an 8-bit integer.
                - We need todo the rounding off here at this stage and also think about what
                  to do if the value is above 255.



                - We need to do the same thing as above. ie add one to the resulting value
                  if the decimal is 0.5 or above.
                - This is again comedic because we are dealing with 8-bit integers and so we need
                  to handle that particular scenario when adding one will make it 255.







                  Let us now look at the below code. We are multiplying a decimal number with
                  an 8-bit integer, adding it to two similar combinations and then storing the
                  result in another 8-bit integer.

                  How does this process work?

                  We have made previous observations showing that it can take values more than
                  255 and then fit it into an 8-bit integer. It does so with the modulus operator
                  by doing number%256;




                  we need to write a round off function again.
                  Complexity in both the first and this question is writing the round off function.


                  What do we need to for the round off?

                  We need to check the values after the decimal.based on that we need to round
                  it off ie if its 0.5 or higer we add 1 else we dont.

                  How do we know if does or doesn't satisfy the conditions?


                ADD 0.5!!!!!!!!!



            */


            sR = 0.393 * oR + 0.769 * oG + 0.189 * oB<255?0.393 * oR + 0.769 * oG + 0.189 * oB + 0.5:255;
            sG = 0.349 * oR + 0.686 * oG + 0.168 * oB<255?0.349 * oR + 0.686 * oG + 0.168 * oB + 0.5:255;
            sB = 0.272 * oR + 0.534 * oG + 0.131 * oB<255?0.272 * oR + 0.534 * oG + 0.131 * oB + 0.5:255;



            image[i][j].rgbtRed = sR;
            image[i][j].rgbtGreen = sG;
            image[i][j].rgbtBlue = sB;

        }
    }

    return;
}

/*

    The below function takes an array and rotates it.
    Internally uses swap.


    How am I able to return the below function? It is of tyoe void so I can return it
    although void types don't take a return value. But they will return a function.
    So void functions can return void functions.


    Void functions can return void functions and void values.

    One more thing to notice is that although we were not able to do swap directly
    with variables with primitive types such as int , we are able to them with the more
    advanced types such as structs. Structs much like arrays are also PASSED BY REFERENCE
    ie their memory location is passed and not a copy of their value. Same in C as in JAVA
    and all other languages we have encountered.

*/

void rotate(int first, int last, RGBTRIPLE arr[]){
    if(first>=last) return;
    RGBTRIPLE test = arr[first];
    arr[first]=arr[last];
    arr[last]=test;
    return rotate(++first,--last,arr);

}

/*

        arr[first] stores the address of this (dare I say it.. object!) {.....}.

        RGBTRIPLE test = arr[first] means test  will also store the address of object.

        arr[first]=arr[last] means arr[first] will store the address of last object.

        arr[last]=test last will store the address of test's content ie the address
        of the first object.


*/


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{


      for(int i=0;i<height;i++){

        rotate(0,width-1,image[i]);
    }




    return;
}




/*

00 01 02 03 04 05
10 11 12 13 14 15
20 21 22 23 24 25
30 31 32 33 34 35
40 41 42 43 44 45


What do we observe?

We observe that for each particular index of [i][j]
there will be nine elements surrounding it including itself.
These nine elements are


i<0 || i>=height || j<0 || j>=width ? value is 0.

[i-1][j-1]      [i-1][j]    [i-1][j+1]
[i][j-1]        [i][j]      [i][j+1]
[i+1][j-1]      [i+1][j]    [i+1][j+1]

For each point calculate the average of these nine values.
if any value doesn't satisfy above boolean condition take its value as 0.


What do I return?

A function to calculate average.

Take arguments and return rounded average.

arr[i-1][j-1]   +   arr[i-1][j] +   arr[i-1][j+1] +
arr[i][j-1]     +   arr[i][j]   +   arr[i][j+1]   +
arr[i+1][j-1]   +   arr[i+1][j] +   arr[i+1][j+1]


We have 9 8-bit integers. Each integer value can hold numbers from 0-255.Can we add all the values
together knowing they are 8-bit integers, and without storing the sum divide it with a certain value
that makes sure its value is less than 255 and store it in an 8-bit variable?

There are two ways to do this operation and both generate slightly different processes.

- One way to do it would be to take previous average, add current value and divide by two.
- With this particular implementation we can round off the averages at each step.
- Not sure what the implications of performing this operation at stage will be and what will be
  the difference between that and adding all the values, finding average and rounding off after that.


- The other way to do this would be to add all the values and find the average.
- This will give us an insight into how the processor actually works with data.
- We can add two 8 bit binary numbers whose sum can be over 255 and then divide it by two
  to make sure its value is less than 255 and store it in an 8 bit integer no problem?
- If this is possible it shows that in the processor during the time of processing
  the buffer data is not bound by size of the data type in memory.

  We will calcuate average with second method.

  Average will not be the average of nine values rather it wii be the average of the number of
  values that are not 0.

  How do we write the function to depict this process.



*/




int roundedAverage(int sum,int counter){
   int average = sum/counter;
   int modulo = sum%counter;

   if(counter%2==0){
       return modulo>=(counter/2)?++average:average;
   }

   return modulo>(counter/2)?++average:average;
}




// colour variable RGB ---> 0,1,2
byte average(int i, int j,int height, int width, RGBTRIPLE image[height][width], byte colour){

  int sum=0,counter=0;
    // byte avg=colour==0?image[i][j].rgbtRed:colour==1?image[i][j].rgbtGreen:image[i][j].rgbtBlue;

  /*

    Another way to implement this would be to iterate over the 9 elements.

  */

//   for(int m=i-1;m<=i+1;m++){
//       for(int n=j-1;n<=j+1;n++){

//           if(m<0 || n<0 || m>=height || n>=width) continue;

//           ++counter;

//           if(colour==0) average+=image[m][n].rgbtRed;
//           if(colour==1) average+=image[m][n].rgbtGreen;
//           if(colour==2) average+=image[m][n].rgbtBlue;

//       }
//   }

//   return average/counter<255?(byte)(average/counter+0.5):255;




  int arr[] = {i-1,j-1,   i-1,j,   i-1,j+1,  i,j-1,  i,j,   i,j+1,  i+1,j-1,   i+1,j,   i+1,j+1};





  for(int t=0;t<17;t+=2){

          /*

            Let us perform two operations here.
            Firstly we will check if both the numbers are valid.
            By both we mean the number at current position and the number after that.

          */

          if(arr[t]>=0 && arr[t]<height && arr[t+1]>=0 && arr[t+1]<width){





            //   Perform average calculation operation here

                ++counter;

                if(colour==0) sum+=image[arr[t]][arr[t+1]].rgbtRed;


                if(colour==1) sum+=image[arr[t]][arr[t+1]].rgbtGreen;


                if(colour==2) sum+=image[arr[t]][arr[t+1]].rgbtBlue;


          }

  }


    /*

        The below line of code does not work.

        The reason it does not work is because average/counter operation will by default
        return an integer whose value will be the same value as the floating point number with
        all the decimal values ignored. This is no good for us because in that case we will always be
        adding 0.5 to an integer number and the later type conversion will give the same integer back.




        We will use modular arithmetic to to solve the above problem we have encountered.
        We should also take note the immense use the modulo operator has been for us.
        It is an incredible opeartion and it finds application in simplifying some really complex
        scenarios.





        Let us do two things:
        - Lets store the values of average/counter and average%counter in two variables
          because we want to use them for the round off function.

    */

    // This should ideally give a value less than 255
    // byte avg = sum/counter, modulo = sum%counter;


    // if(counter%2==0){
    //     modulo>=(counter/2)?++avg:avg;
    // }else modulo>(counter/2)?++avg:avg;

    byte avg = roundedAverage(sum,counter);


    /*

        At this stage we could imagine our logic being something like this.

        modulo>=(counter/2) average+=1;

        BUT there is one more problem due to which the above lines of code will produce incorrect
        results. If the modulo is an odd number then  counter/2 will return
        an integer ignoring the decimal part. This resulting value will be less than the actual half
        value as that would be integer. If this value is equal to modulo we will erronously add 1
        when we shouldn't have. Take the example of 10 and 3.


        We need to fix this latent bug.

        Let us make a couple for observations for the above boolean condition and its impact.


        These obeservations are:

        - If the counter is even then the above boolean condition holds true ie.
            modulo>=(counter/2) ++average;

        - If the counter is odd we need to makke slight changes to the condition.
          Basically the point is in case of an odd counter as in case of 10 and 3
          we observed that the above conditional statement will not satisfy.

          modulo>(counter/2) ++average;





        We have encuntered this in the greyscale problem and this is the path we took to solve the
        issue (we hardcoded the conditional in the previous case. As we also need it hee and maybe
        even other places we will be converting it to a function now.).




    */




    return avg;

//   return sum/counter<255?(byte)(sum/counter):255;








    /*


        There is something really great about the above array.
        What it is, is the fact that all the even indexes (n%2==0)
        contain items of i and all the odd indexes contain items of j.

        This symmetry forms the base of our algorithm to find the average of all valid rgb values.

        For this particular i and j values we need to add all the values that are not
        zero and find their average.

        One observation we can make by looking at the indexes of the values required are
        that we have 4 different values namely

        i-1  i+1  j+1  j-1

        if any of these particular combinations does not satisfy the specific boolean
        conditions namely result should not be negetive , the values containing
        i should be less than height and the values containing j should be less than
        width.

        First find the four values:


            (i-1)<0 || (i-1)>=height all values containing i-1 should not be counted.

        The above is a fine declarative statement that tells us nothing about how to not
        count anything that contains i-1.

        How do we count the things that don't contain i-1 ?


    */


}



// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE sample[height][width];

     for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){

            /*

                So obviously we are getting the wrong answer. What is going on?

                Another observation we have made is that with the code that we have entered
                the whole image is composed of just blue pixels.

                So obviously someting is happening that is turing every pixel blue.

                Let's find out.

                In this particular function we are generally not doing anything related to business
                logic. We are passing the parameters at each point in the loop to the average function
                which after doing the necessary operations on the operands returns the average of the
                colour values of the surrounding pixels based on the colour being fed into the average
                function.

            */


            sample[i][j].rgbtRed = average(i,j,height,width,image,0);
            sample[i][j].rgbtGreen = average(i,j,height,width,image,1);
            sample[i][j].rgbtBlue = average(i,j,height,width,image,2);




        }
    }



    /*

        These are the three approaches. We'll try each approach one at a time to see if it works.

    */


    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){

            // Approach 1
            image[i][j]=sample[i][j];


            // Approach 2
            // image[i][j].rgbtRed=sample[i][j].rgbtRed;
            // image[i][j].rgbtGreen=sample[i][j].rgbtGreen;
            // image[i][j].rgbtBlue=sample[i][j].rgbtBlue;

        }
    }

    // Approach 3
    // image=sample;




    return;
}

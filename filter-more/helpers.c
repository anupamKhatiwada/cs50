#include "helpers.h"
#include <stdio.h>
#include <math.h>


typedef uint8_t byte;



int roundedAverage(int sum,int counter){
   int average = sum/counter;
   int modulo = sum%counter;

   if(counter%2==0){
       return modulo>=(counter/2)?++average:average;
   }

   return modulo>(counter/2)?++average:average;
}



byte average(int i, int j,int height, int width, RGBTRIPLE image[height][width], byte colour){

  int sum=0,counter=0;

  int arr[] = {i-1,j-1,   i-1,j,   i-1,j+1,  i,j-1,  i,j,   i,j+1,  i+1,j-1,   i+1,j,   i+1,j+1};

  for(int t=0;t<17;t+=2){



          if(arr[t]>=0 && arr[t]<height && arr[t+1]>=0 && arr[t+1]<width){


                ++counter;

                if(colour==0) sum+=image[arr[t]][arr[t+1]].rgbtRed;


                if(colour==1) sum+=image[arr[t]][arr[t+1]].rgbtGreen;


                if(colour==2) sum+=image[arr[t]][arr[t+1]].rgbtBlue;


          }

  }


    byte avg = roundedAverage(sum,counter);

    return avg;


}


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

     byte average;

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){

            average = (byte)roundedAverage(image[i][j].rgbtBlue+image[i][j].rgbtRed+image[i][j].rgbtGreen,3);

            image[i][j].rgbtBlue=average;
            image[i][j].rgbtRed=average;
            image[i][j].rgbtGreen=average;
        }
    }

    return;
}


void rotate(int first, int last, RGBTRIPLE arr[]){
    if(first>=last) return;
    RGBTRIPLE test = arr[first];
    arr[first]=arr[last];
    arr[last]=test;
    return rotate(++first,--last,arr);

}



// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

      for(int i=0;i<height;i++){

        rotate(0,width-1,image[i]);
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE sample[height][width];

     for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){




            sample[i][j].rgbtRed = average(i,j,height,width,image,0);
            sample[i][j].rgbtGreen = average(i,j,height,width,image,1);
            sample[i][j].rgbtBlue = average(i,j,height,width,image,2);




        }
    }





    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){


            image[i][j]=sample[i][j];


        }
    }


    return;
}


/*

    As we have implemented the previous three filters in the previous filter problem we will be
    be copy pasting their solutions to this. We might optimize a few things here as well.



    Let's think about how we'll implement the edges filter.
    The algorithm for calculating the edges has been provided to us.
    A lot of the things in that algorithm are the same as the blur function so we will
    copy paste the code of blur as much as possible and maybe make a few optimizations as well.



    Let's think about the edges filter. We observe that apart from the formula to calculate
    the edges, everything in this particular problem is same as the blur problem apart from the
    formula itself. So we can think of the implementations of the two functions as somewhat equivalent
    and we can start thinking about how to implement the functions in a functional manner.


    Let's write this particular function first and then look at other things.


    Let us think about how we can pass a function to another function.
    Obviously this is possible and we have done this before as based on the substitution model
    first all the operands are evaluated. So in the function definition we can just
    pass in a variable of the data type that will be returned by the function we'll pass
    when in the function call. But that raises another issue or does it. Let's find out.


    First thing we should think about is what this generic formula returns.
    The generic formula is almost same as the average function ie. it has the same structure.
    Incase of average it returns a byte ie. a value between 0 and 255.

    Let us take that as the initial case and declare that the generic formula will also return
    a byte as both should obviously return the same thing.

*/


byte genericFormula(int i, int j, int height, int width, RGBTRIPLE image[height][width],int colour){


    /*

        In case of the generic formula let us not implement exactly as average.
        We'll implement it the other way that is iterating from i-1 to i+1 and from j-1 to j+1.

    */


        int sum=0,counter=0;


        for(int m=i-1;m<=i+1;m++){
            for(int n=j-1;n<=j+1;n++){

                // Here we pass in the validation conditions which in this case are the same as average
                if(m<0 || n<0 || m>=height || n>=width) continue;


                /*

                    Here we should implement the function specific functionality.


                    There is an issue with our implementation of the generic formula.


                    The issue is that we cannot directly pass a function into another function
                    in the same way that we can in case of say JavaScript. We use function pointers
                    to achieve this. We will go deeper into pointers in general and function
                    pointers in particular in due time.

                    Currently let us skip the implementation of the generic formula function
                    and move on to implementing the edges function.

                */





            }
        }




    return 0;

}

// a represents whether we need to find Gx or Gy. 0 for x and 1 for y.
int findG(int i,int j, int height, int width, RGBTRIPLE image[height][width],int colour, byte a){


    /*

        We will start by iterating over the grid of 9 pixels.


        We see that edges works properly for pixels in the middle ie. a pixel whose all 8
        surrounding pixels are valid (We're assuming it runs multiple test cases for each
        scenario thus we can assume that the statement saying that it works properly for the
        middle pixel is correct).

        We also observe that the edges program does not work properly for pixels in the corner
        or on the edges. Thus to an extent, we can safely assume that the problem with
        our implementation lies in this particular function and not in the function that
        squares gx and gy and finds the square root of the resulting sum.

        Neither does it exist in the actual definition of the edges function.


        For this very reason let's start reasoning upwards from what we already know.
        We know (which is a very strong word) that the problem is with pixels at the edges
        and those at the corners.

        What differentiates these pixels from other pixels?
        The fact that some pixels in their convolutinal matrix are invalid.

        Thw way we are supposed to deal with the values of these invalid pixels is to consider
        that these invalid pixels are completely black ie. all their RGB values are 0.


        We know that our function majorly is correct. The issues it faces is due to the change
        in starter values in case a particular pixel is not valid.

        We will be looking deeper into this problem today.



        Let's suppose the particular pixel in consideration is invalid. What imapact will it have
        on the starter value changes that should take place upon iterating.


        Let us run through the first use case. Let us consider the top-left corner pixel.

        The i,j values for this pixel are 0,0.

        So the convolutional matrix iteration will start from i-1 ie. -1
        and will go to i+1 ie from -1 to 1 for rows and from j-1 ie. -1 to j+1 ie.1 for columns.

        So the entire first row ie. indexes [i-1][j-1],[i-1][j] and [i-1][j+1] are invalid.
        For this row, while iterating over it the starter should move from -1 to 1.

        let us what is happening in the code that we have written.



        We can see a bunch of errors with our code. We'll go in and try sort them out.

        The way we are working with starter now is slightly problematic.
        Since the values of i-1 or j-1 at edges or corners don't have a straight forward nature
        as the values which are in the middle, using modular arithmetic
        is not necessarily a good idea. Rather than using modular arithmetic for this
        we should do it in a more direct way since there are only 9 elements in the matrix.

        Let us do it in a step by step fashion where we set the starter value while we iterate.

    */


    int sum = 0, starter=-1, sign = -1;

    byte counter=0;

    /*
        The counter is initially 0. We will use it to keep track of where we are in our two
        dimensional iteration.

        This is kind of like hardcoding but since we are dealing with just 9 elements its a good idea.

    */


    for(int m=i-1;m<=i+1;m++){



        if(a==0){

            /*

                Don't use modular arithmetic for this problem.
                Causes issues for pixels with negetive indexes ie. invalid pixels.

                We should not think of the starter value in terms of the particular
                index to which it might be applied. This causes problems and its probably
                possible (quite sure it is possible) but it does increase complexity.
                Rather we can also do it simply in an iterative manner by changing it iteratively
                using a counter variable as a reference. It will not look as clever but it will get
                the work done in a very efficient manner with hopefully less complexity.


                By using counter we will not have to keep track of where we are in the iteration
                process in terms of indexes. We can just update the counter value and keep track of
                that.


                What is the logic of updating the counter?

                We will update the counter each time we iterate horizontally. So the final value of the
                counter when the iteration is over will be 9. Each time the value of the counter
                is divisable by 3 we know that iteration over the elements of a particular row is over.

                The initialization in both cases is correct. We just need to work on the updation.

            */


            if(counter%3==0){
                if(counter%2==0) starter=-1;
                else starter=-2;
            }

        }

        else{
            /*

                How many times will the below block of code be evaluated?
                Only once.

            */

            if (counter>2 && counter<6){
                sign=1;
                starter=1;
                counter+=3;
                continue;
            }

        }




        for(int n=j-1;n<=j+1;n++){


            /*

                First let us check if the the pixel in question is valid.
                We are continuing because we don't need to add anything
                which is the same as adding 0.


                This poses a slight problem.

                The problem is with the starter values. Irrespective of if the pixel is valid
                we need to update the starter value at each stage. We cannot do this if
                we use continue so we'll just put things inside an if statement if the pixel is valid.

            */

            // if(m<0 || n<0 || m>=height || n>=width) continue;


            /*

                The reason for the incorrect answer might exist in the below lines of code.

                What we are doing in the below lines of code is to check the validity
                of a particular pixel in the convolutional matrix.

                if the value is invalid we are not doing anything ie. we are not adding that
                particular value to the sum. This seems logical as the value itself is zero
                so adding it to the sum makes no difference.

                Since we are not calculating the average I see no reason why there should
                be problem nor why it would be incorrect.

                Since we can't seem to find an issue with it, we will examine the starter
                logic again. Although since the program works for the middle pixel (atleast
                that is what we have assumed) the starter logic should be okay.

                We will start by examining the starter logic.


                The issue IS with the starter logic especially the edge and corner cases
                as we had previously been informed by check50. We can also see that the starter logic will
                work for middle pixels which can be easily observed upon doing few mental checks.

                This also shows that our problem in the whole is correct. All the other functions are
                logically sound and working well.

                We just need to resolve the starter logic to get this function to work.




            */

            // Adding only the values that are valid
            if(m>=0 && n>=0 && m<height && n<width){

                // Based on the colour add the values to the sum
                if(colour==0) sum+=(image[m][n].rgbtRed*starter);
                else if(colour==1) sum+=(image[m][n].rgbtGreen*starter);
                else sum+=(image[m][n].rgbtBlue*starter);

            }


            /*

                When we iterate over a column we need to update starter value irrespective
                of the validity of the pixel so we'll do it here.


                How do we update the starter?

                We can write a nice and clever algorithm to update the starter value based
                on modular arithmetic (I love modular arithmetic!!).
                we will do this while iterating over rows.

                We will update teh counter variable outside the if block because
                we will be updating the counter regardless of whether we are trying to
                find Gx or Gy.

                Update the counter at the very end. Since we are not using continue it will not
                cause problems.

                Again we can and will use modular arithmetic because it gives me a hard on!

                Is the value of the counter%3==0 means that we are in a new row. We will
                make use of this fact for our own purposes.

            */




            if(a==0){


                /*

                    At this stage if the counter is divisable by 0 we know we have started a new row.
                    How should we update the value when we start a new row?

                    Another fun math question that arises at this point is apart from the
                    obvious what is the difference between 0 and 3. Please ponder.

                    The difference between 0 and 3 is that 0 is divisable by everything
                    whereas 3 is only divisable by 1 and 3.

                    Man I love modular arithmetic!!

                    We are done with the logic of how to change Gx whose matrix is easier
                    to work with because its symmetry is more aligned to how the process of iteration
                    over a matrix works.

                */


                    /*


                        By this point we have started the new row already and we have processed
                        the first element also. Bear this in mind because this is a very
                        important fact and tends to introduce subtle bugs. It also shows
                        how the value of variables at different stages of the process effect
                        the process itself.


                        We know now that we have started a new row.
                        If counter is divisable by both 2 and 3 we know that we are
                        either at first row or the last row else we have started the second row.

                        Did we introduce the subtle bug here as well. Let's check.


                        What do we know by this point? By this point we know one thing ie. the
                        value of starter is set properly.

                        We also know that the processing of this particular element has happened
                        so whatever changes we make to the starter will show its effects for the
                        next element.

                    */




                /*

                    By this point we know that the value of the starter at the start of the row
                    is correct. We just need to update it. What are the factors involved in updating
                    the value of the starter?
                    The factors are that if the starter is being updated in the first or third row
                    then the value of the starter should be incremented by 1, other wise it should be
                    incremented by 2.

                    How do we know which row we are in?
                    By analysing the value of the counter.
                    If value of the counter is between 2 and 6 not including either then
                    we know we are in the second row so the starter value should be incremented
                    by two. Otherwise it should be incremented by 1.

                */

                if(counter>2 && counter<6) starter+=2;
                else starter+=1;

            }
            else{


                /*

                    We have solved the issue of updating the starter for evaluating the value of Gx.
                    Now we need to do the same for Gy.

                    In case of Gy we are using continue so we will not even enter the nested
                    loop if the value of the starter is 0.

                    So we have two scenarios here.
                    - First scenario is that we are in the first row.
                    - Second is when we are in the third row.

                    What is the difference between the two scenarios?
                    Very little. Just the fact that in one case it is negetive and
                    the opposite in the other case.

                    Also we will not be incrementing the value if the starter, rather we will be
                    setting it to something.

                    How will we set the value of the starter?
                    We will use modular arithmetic in this case. Be careful with this as there is
                    the possibility of introducing a subtle bug at this stage.

                    The logic behind this is:
                    - If the counter%3==0 and counter%2==0 set the value of the starter as 2*sign
                    - Set the value of the starter as 1*sign
                    - After the second row is over and we have set the value of starter to one
                      the same logic will suffice for the third row.

                */


                if(counter%3==0 && counter%2==0) starter=(2*sign);
                else starter=(1*sign);

            }

            // We will do the updation here as this really simplifies modular arithmetic.
            // Does it really ?! -_-

            /*

                There is crucial bug here. Incase of Gy in the second row we are using continue
                so the counter never gets updated for the second row.
                Let's try and solve thos by adding three to counter before doing continue.

            */

            ++counter;


        }



    }


    return sum;



}


/*

    Now that we have found the Gx and Gy for a particular pixel we need to feed these two values
    to a function which will square both the numbers, find the square root of the resulting
    sum, round it and if its value is more than 255, cap the value to 255.

*/


int sqSum(int gx,int gy){

    /*

        Firstly we need to add the sqares of the two operands. Then we'll proceed to finding the
        square root of the resulting sum.

    */

    int sum = gx*gx+gy*gy;

    /*

        Now we need to calculate the squareroot of this sum. Two ways to approach this issue.
        First way is to write our own custom implementation of the square root function.
        The second way is to use the default implementation of the square root function
        defined in the math.h library.


        Since we don't want to write the binary search implementation now, let's just use the
        default implementation provided in the math.h library.
        Note that the implementation provided in the library works with double
        and also returns a double so we need to handle the type conversion issues that will arise.



        As the sqrt() function in math.h works with doubles we cannot use the round off
        function we have defined in our own library. But since we get a nice double value to work
        with and not just a byte we will be adding 0.5 to the resulting value and typecasting it to an
        integer to get our required rounded off value.

    */

        int returnValue = (int)(sqrt((double)sum)+0.5);


        return returnValue<255?returnValue:255;


}






// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    /*


        After going through the problem statement we now know how to approach the problem.
        We multiply each value in the 3X3 grid with the required values from the grid.
        Which ever of the 9 indexes are invalid, we consider their values to be 0.


        Basically our algorithm is that for each pixel we calculate the Gx and Gy value,
        find the sum of their squares and then find the square root of the sum.
        This value is to be assigned to the original pixel in question. We mightneed to round off
        the value to the nearest whole number (We already have a method in a header
        file to achieve this). We also need to cap the resulting to 255.


        First let us begin by writing functions to calculate the Gx and Gy for each pixel.

    */


    RGBTRIPLE newImage[height][width];



    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){


            newImage[i][j].rgbtRed = sqSum(
                                            findG(i,j,height,width,image,0,0),
                                            findG(i,j,height,width,image,0,1)
                                        );

            newImage[i][j].rgbtGreen = sqSum(
                                            findG(i,j,height,width,image,1,0),
                                            findG(i,j,height,width,image,1,1)
                                        );

            newImage[i][j].rgbtBlue = sqSum(
                                            findG(i,j,height,width,image,2,0),
                                            findG(i,j,height,width,image,2,1)
                                        );



        }
    }

     for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){

            // Approach 1
            image[i][j]=newImage[i][j];


            // Approach 2
            // image[i][j].rgbtRed=sample[i][j].rgbtRed;
            // image[i][j].rgbtGreen=sample[i][j].rgbtGreen;
            // image[i][j].rgbtBlue=sample[i][j].rgbtBlue;

        }
    }


    return;
}

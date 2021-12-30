/*

                                Merge Sort Implementation

    We need to implement merge sort for this problem.

    There are two steps to the merge sort program. One is the sorting. The other and more
    important one is the merging. The reason sorting is less important because when the array size
    becomes one it is already sorted as an array of size 1 is a sorted array.

    We need to implement the merge function first. It takes a couple of arrays, merges them and
    and outputs another array. This seems like the easiest implementation but as this is inefficient
    in terms of the space it will consume we will try to implement this using just another empty
    array of the same size as the original array.

*/


#include <stdio.h>


void merge(int originalArray[], int mergedArray[], int s1, int e1, int s2, int e2);


void mergeSort(int originalArray[],int mergedArray[], int start, int end);

int counter=7;


int main(void){


    int arrToSort[]={4,3,2,1,7,6,5};


    int mergedArray[]={0,0,0,0,0,0,0};



    /*

        We need to break down the elements till we reach an array of one element or we are focused
        on one element. At that point we will start merging as an array of one element is always sorted.

    */

    mergeSort(arrToSort,mergedArray,0,6);


    /*

        Make one observation about the below lines of code. The observation being that below, the
        lines of code which cause the coed smell copy the merged array (or parts of the merged array)
        back to the original array but we are not printing the original array rather we are printing
        the merged array. This very fact seems very redundant. There is something unnecessary
        definitely happening.


    */



    for(int i=0;i<7;i++){
        printf("%i\n",arrToSort[i]);
    }


}

/*
    Here we'll start working with the assumption that the size of the merged array will be
    equal to the sum of sizes of the two arrays to merge (Even this might not be true. The
    merged array can also be a standard array ofthe same size as the original array. We
    might need to just work with its indexes).

    We might not even receive two arrays to merge. We might get one array where we have to merge
    upto a certain index.


    Let's hope the below function works even for corner cases.




*/

void merge(int originalArray[], int mergedArray[], int s1, int e1, int s2, int e2){


    if(s1==s2) return;



    /*


    We need to first write a decent merge function. Let's generically implement merge behavior
    for any two arrays.


    Lets jot down the algorithm to do this.
    - As both the arrays we receive to merge irrespective of length will always be sorted
      we will take advantage of this fact.
    - First we start with comparing the first two elements of both the arrays.
    - We will take the smaller element and place it at the start index of the mergedArray.
    - Keep track of the index and the array from where you remove the element because that is
      where you will start from next time.
    - We will then increment the start index.
    - If we pass in arrays we'll have problems with the length and end of the array.
        So we have decided to not pass in the entire arrays rather pass the original array and
        the indexes of the start and end for both merge regions. Not sure if this will work but let's
        see if we can make sense of this.


     What are my questions?

     - Will this work with one single element?
     - Can we reduce the number of arguments? Explore more into this.


    */

    int startIndex=s1;

    while(s1<=e1 && s2<=e2){

        if(originalArray[s1]<=originalArray[s2]){


            /*

                original array
                1   3   5   7   2   4   6   8
                    s1              s2



                merged array
                1   2   0   0   0   0   0   0
                        si



                Based on the above exercise we notice that we are not really able to achieve
                what we set out to do namely modify the original array and not just the merge array.
                Thus we still have to copy part of the merged array into the original array and that
                part will obviously be sorted. But again the question of overhead arises.

                If after the merge function is over and we have to again add the values back to the
                original array (something that we are doing below which is causing the overhead) the
                overhead issue still remains. we will have just moved it from the mergeSort function
                to the merge function.

                This problem still remains a cause of concern because of the extra overhead it causes.

            */

            mergedArray[startIndex]=originalArray[s1];
            ++s1;

        }else{

            mergedArray[startIndex]=originalArray[s2];
            ++s2;
        }



        ++startIndex;

    }




    /*

    By this point we have added all the things we need to add to the merged array.
    Only things left to add to the merged array are elements remaining in the longer array or
    more specifically the elements remaining which are already sorted. To do this we need to
    find which of the things have been added and which are to be added.



    Below lines of code describe that whatever elements remain we need to add them. But be careful with this
    code. It has a particular stink to it. It is most probably buggy for a alot of corner cases.


    Let us think of the logic and implement the below lines of code again and see if we can catch some
    subtle bugs that might exist with it.


    The logic is quite straight forward. It states that while merging two sorted arrays into a new
    array of size equal to the sum of sizes of the two arrays, whenever one of the array is completed
    the remaining elements of the previous array are to be added to the new array directly as they are
    already sorted by definition.

    */




/*

     What are my questions?

     - Will this work with one single element?
     - Does it work with odd and even arrays?
     - Can we reduce the number of arguments? Explore more into this.


*/

    // Doing seperate checks is essential. There is a very subtle bug in the below lines of code.



    /*

        This is the wrong way to do it. Maybe not. This solution SEEMS valid for all cases except when
        all the four indexes are same ie we are trying to merge one element with it self.

        Lets try merging one element each and visualize the result.


    */




    int s=-1,e=-1;


    if(s1>e1){
        s=s2;e=e2;
    }



    if(s2>e2){
        s=s1;e=e1;
    }







    if(s!=-1 && e!=-1){

        for(int i=s;i<=e;i++){
            mergedArray[startIndex++]=originalArray[i];

        }


    }



}


/*

    The below is the actual merge sort function where we break an array down till we can
    look at individual characters. Then once we obtain this perspective we can rest assured because
    any element by itself is by definition sorted. Then we can start merging the elements
    creating the new array which will eventually ie. after multiple merges will be sorted.

*/



/*


   Merged array should be the same size as the original array
   Although we can sort the entire array we will explicitely define start and end
   because want to be able to sort any part of any array with this.

   By default add start=0 and end = size of array-1


*/

void mergeSort(int originalArray[], int mergedArray[], int start, int end){



    if(start==end) {


        return;

    }

    int breakpoint=(start+end)/2;



    mergeSort(originalArray,mergedArray,start,breakpoint);



    mergeSort(originalArray,mergedArray,breakpoint+1,end);




      /*


        Found the issue!!!!!!!!!


        The reason the function is not working as expected is because we are calling
        merge based on the original array each time. This of course is counter intuitive because
        the original array is obviously not composed of two sorted halves. We need to look deeper into this
        to debug the function and get it to work predictably.


        One possible solution of the top of the mind is every time merge is called and something is
        merged, weshould copy whatever was merged back to the original array. This might not be the
        most ideal solution as it causes a lot of overhead ehich will fuck up the efficiency of
        the algorithm. But we will do it as the first and naive solution and then we will probably
        look for better solutions.


    */


    merge(originalArray,mergedArray,start,breakpoint,breakpoint+1,end);

    /*

        Let us implement the naive approach here. Let's not do it inside the merge function itself
        because we don't want to make it dirty or cause an unecessary code smell.


        Implementing this solution does work. I don't know how to calculate efficiency for this
        but I would assume it is pretty bad.



        The below lines of code although cause my skin to burn but they also point out a very
        fundamental issue. The issue is that once we merge something in the merged array we need to
        copy that result back to the original array because the merging there is done based on the
        contents of the original array. Is there a way we can remove this overhead?? That's definitely some
        thing to ponder.


        One way to approach this issue would be to take your mind off the particular problem for sometime.
        Let it percolate in the diffused state and in the meanwhile learn more about recursion and solve some
        more recursive problems. Then implement merge sort again after a number of days maybe in java and
        see if you can figure it out then. If so compare and contrast. Later on go through the taught solutions
        from the courses and ponder more about it.


    */


    // -------Hate the stink of the overhead the below lines of code causes----------------------------- //


    /*

        The below lines of code are our bane. We need to get rid of these particular lines of code.
        Let's think about how we can go about doing this.

        - First to remove these lines of code let us think about what these lines of code actually do.
          What do they do? They copy the merged array back to the original array. Why are we doing this?

        - In the merge function we are merging things in the merged array but at each stage of the
          mergeSort function we are working on the original array and not the merged array.
          To remove the below overhead we need to do this operation within the merge function
          and not run a seperate loop outside to do it. Let's see if we can achieve that.


        Still unable to remove this issue. We'll look more into it when we go through some merge
        sort implementations.



    */



    for(int i=start;i<=end;i++){
        originalArray[i]=mergedArray[i];
    }


    /*

        There is one more fundamental issue here. Are we creating the new merged array which
        is the array to be returned (Although in our case every function is void and we don't really
        return anything) or are we returning the original array which we have by now sorted
        using the merged array as a buffer to implement various computations.


    */



}
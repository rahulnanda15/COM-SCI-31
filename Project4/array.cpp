//
//  main.cpp
//  CS31_Project4
//
//  Created by Rahul Nanda on 11/6/23.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int reduplicate(string a[], int n)
{
    if (n<0) //Returning error if number of interesting elements is negative
    {
        return -1;
    }
    if (n==0) //Returning 0 for 0 interesting elements
    {
        return 0;
    }
    for (int i=0;i<n;i++) //Looping n times, as given by the function's argument
    {
        a[i]=a[i]+a[i]; //Concatenating and duplicating each element in the array
    }
    return n; //Returning n if program succeeds
}

int locate(const string a[], int n, string target)
{
    if (n<0) //Returning error if number of interesting elements is negative
    {
        return -1;
    }
    for (int i=0;i<n;i++) //Looping through n times, as given by the function's argument
    {
        if (a[i]==target) //Checking if each element is equal to the target
        {
            return i; //Returning target location if found
        }
    }
    return -1; //Returning -1 if target is not found in the array
}

int locationOfMax(const string a[], int n)
{
    if (n<=0) //Returning an error is number of interesting elements is 0 or negative
    {
        return -1;
    }
    int maxLocation=0; //Setting a variable to track the position of the max element
    for (int i=0;i<n;i++) //Iterating through the array n times
    {
        if(a[i]>a[maxLocation]) //Using '>' to ensure maxLocation is prioritizes the smallest position number if two strings are equal
        {
            maxLocation=i; //Changing the max location if a new max string element is found
        }
    }
    return maxLocation; //Return position of the max string
}

int circleLeft(string a[], int n, int pos)
{
    if (n<=0 || pos >= n || pos <0) //Returning an error is pos is greater than number of interested elements and for 0/negative arguments for n
    {
        return -1;
    }
    string eliminatedString=a[pos]; //Setting a temporary variable to store target element
    for (int i=pos;i<n-1;i++)
    {
        a[i]=a[i+1]; //Replacing each element starting with a[pos] with the element after it
    }
    a[n-1]=eliminatedString; //Moving the eliminated string to the end of the array
    
    return pos; //Return pos from the argument
}

int enumerateRuns(const string a[], int n) //Note that a[] is a constant and can not be changed
{
    if (n<0) //Returning an error for negaitve interesting elements
    {
        return -1;
    }
    if (n==0)
    {
        return 0; //Skipping the entire set of instructions if number interesting elements is 0
    }
    int sequenceCount=1; //Setting a variable to count number of sequences as 1 since loops undercount by 1 due to looping condition n-1
    for (int i=0;i<n-1;i++) //Looping to the end of the array
    {
        for (int j=i+1;j<n;j++) //Looping to the end of the array to be able to compare elements
        {
            if(a[i]!=a[j]) //Comparing element to the next one; if previous elements were equal to one another, this compares a[i] to the subsequent element yet to be compared
            {
                i=j-1; //Skips all elements that were already checked by setting i=j-1
                sequenceCount++; //If elements not equal, indicates a new sequence is starting
                break; //Returning to outer loop
            }
        }
        
    }
    return sequenceCount; //Return sequenceCount
}

int flip(string a[], int n)
{
    if (n<0) //Returning an error for negative interesting elements
    {
        return -1;
    }
    string tempStore; //Using a temporary variable to store an element to be swapped
    
    for (int i=0;i<n/2;i++) //Looping through only half the array to avoid double swapping
    {
        tempStore=a[i]; //Storing element to be swapped in temporary variable
        a[i]=a[n-1-i]; //Swapping elements to place array in reverse order
        a[n-1-i]=tempStore;
    }
    return n; //Return number of interesting elements
}

int locateDifference(const string a1[], int n1, const string a2[], int n2)
{
    if (n1<0 || n2<0) //Returning an error for negative interesting elements
    {
        return -1;
    }
    int RANGE; //Initializing a variable to store length of shortest array
    if (n1<n2)
    {
        RANGE=n1; //Setting RANGE to length of a1 if it is the shortest
    }
    else
    {
        RANGE=n2; //Opposite as if condition
    }
    for (int i=0;i<RANGE;i++) //Loop through arrays RANGE times to avoid going out of range of shortest array
    {
        if (a1[i]!=a2[i]) //If elements differ:
        {
            return i; //Return position where difference occurs
        }
    }
    return RANGE; //Return RANGE if both arrays are the same
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if (n2<=0 || n1<=0 || n2 >= n1) //Return error for negative array lengths and if substring array is greater than parent array
    {
        return -1;
    }
    if (n2==0||n1==0)
    {
        return 0;
    }
    int count; //Count variable to determine if substring array is same length as array created with similar elements from a1
    string compareArray[10000]; //Creating array to place sub-arrays in a1 to compare to a2
    for (int i=0; i<n1;i++)
    {
        if (a2[0]==a1[i]) //Start comparison where first element of a2 equals an element of a1
        {
            count=0; //Restart count when comparison starts
            for (int j=0;j<n2;j++)
            {
                compareArray[j]=a1[i+j]; //Setting values in compareArray as equal to elements in a1 starting at where a1[i]==a2[0]
            }
            for (int k=0;k<n2;k++)
            {
                if (compareArray[k]==a2[k]){ //Compares subsequence a2 to the subsequence gathered in a1 and placed into compareArray
                    count++; //Increment count for number of elements equal in both a2 and compareArray
                }
                
            }
            if (count==n2){ //If compareArray's length is equal to length of a2, subsequence is in a1
                return i;
            }
        }
    }
    return -1; //Return -1 if subsequence not in a1
    
}

int locateAny(const string a1[], int n1, const string a2[], int n2)
{
    if (n1<0||n2<0) //Return an error for negative array length
    {
        return -1;
    }
    for (int i=0;i<n1;i++) //Looping through length of a1
    {
        for (int j=0;j<n2;j++)
        {
            if (a1[i]==a2[j]) //For each element in a1, compare it to each element in a2 to check if equal
            {
                return i; //Position of earliest element in a1 equal to any element in a2
            }
        }
    }
    return -1;
}

int divide(string a[], int n, string divider)
{
    if (n<0) //Returning an error if number of interesting elements is negative
    {
        return -1;
    }
    
    int lessThanDivide=0; //Variable that counts the number of elements less than divider
    int moreThanDivide=0; //Variable that counts the number of elements more than divider
    
    for (int i=0;i<n;i++) //Loops through the length of the array
    {
        if (a[i]<divider) //For any element less than divider
        {
            lessThanDivide++; //Increment variable
        }
        else if (a[i] > divider) //Increment variable for any element less than divider
        {
            moreThanDivide++;
        }
    }
    string tempSwap; //Initializing variable to complete future swaps
    for (int i=0;i<n;i++)
    {
        if(a[i]<divider) //For elements less than divider, push them to the beginning of the array only if they are not within the section that elements less than divider should be in
        {
            if(i>=lessThanDivide)
            {
                tempSwap=a[i]; //Circle right
                for (int k=1;k<i;k++)
                {
                    a[i]=a[i-1];
                }
                a[0]=tempSwap;
                
            }
        }
        else if(a[i]>divider) //For elements more than divider, push them to the end of the array only if they are not within the section that elements more than divider should be in
        {
            if(i<n-moreThanDivide)
            {
                tempSwap=a[i]; //Circle left
                for(int j=i;j<n-1;j++)
                {
                    a[j]=a[j+1];
                }
                a[n-1]=tempSwap;
                i=i-1; //Because elements are effectively pushed left, incrementing i would skip checking an element so i stays the same after subtracting 1 and incrementing in the loop condition
            }
            
        }
    }
    
    for (int i=0;i<n;i++)
    {
        if (a[i]>=divider)
        {
            return i; //Return the position of the element in the array that is first not less than divider
        }
    }
    return n; //If no such element exists not less than the divider, return n
    
}

int main()
{
    
    string h[7] = { "nikki", "ron", "asa", "vivek", "", "chris", "donald" };
    assert(locate(h, 7, "chris") == 5);
    assert(locate(h, 7, "asa") == 2);
    assert(locate(h, 2, "asa") == -1);
    assert(locationOfMax(h, 7) == 3);

    string g[4] = { "nikki", "ron", "chris", "tim" };
    assert(locateDifference(h, 4, g, 4) == 2);
    assert(circleLeft(g, 4, 1) == 1 && g[1] == "chris" && g[3] == "ron");

    string c[4] = { "ma", "can", "tu", "do" };
    assert(reduplicate(c, 4) == 4 && c[0] == "mama" && c[3] == "dodo");
    string re1[10]={"mama","mama","mama","reg","gt"};
    

    string e[4] = { "asa", "vivek", "", "chris" };
    assert(subsequence(h, 7, e, 4) == 2);

    string q[5] = { "ron", "ron", "ron", "chris", "chris" };
    assert(enumerateRuns(q, 5) == 2);

    string f[3] = { "vivek", "asa", "tim" };
    assert(locateAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "tim" && f[2] == "vivek");

    assert(divide(h, 7, "donald") == 3);
    
}

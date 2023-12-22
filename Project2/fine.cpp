//
//  fine.cpp
//  Project 2
//
//  Created by Rahul Nanda on 10/16/23.
//

#include <iostream>
#include <string> //importing string library
using namespace std;

int main(){
    
    cout << "Identification: ";
    string identification;
    getline(cin, identification); //using getline to create 'string' input with multiple words for identification
    
    cout << "Overstated amount (in millions): ";
    double overstatedAmount; //setting overstatedAmount input as double to handle decimals
    cin >> overstatedAmount;
    
    cin.ignore(10000, '\n'); //when reading in a number with cin and next input is string with getline(), cin.ignore() clears characters from input buffer
    
    cout << "Location: ";
    string location;
    getline(cin, location); //using getline to create 'string' input with multiple words for location
    
    double fine; //initializing fine double variable
    cout.setf(ios::fixed); //fixed or scientific are a few options for formatting doubles
    cout.precision(3); //rounds subsequent doubles to three decimal places
    
    if (identification == "")
    {
        cout << "---" << endl;
        cout << "You must enter a property identification."; //error handling for empty input field for identification
    }
    else if (overstatedAmount<=0)
    {
        cout << "---" << endl;
        cout << "The overstated amount must be positive."; //error handling for non-positive overstatedAmount
    }
    else if (location == "")
    {
        cout << "---" << endl;
        cout << "You must enter a location."; //error handling for empty input field for location
    }
    else
    { //else conditions executed when NO ERRORS are detected
        if (overstatedAmount <= 60)
        {
            fine = 0.1111*overstatedAmount; //fine calculation for overstatedAmount less than or equal to 60
        }
        else if (overstatedAmount <= 150)
        {
            if (location == "new york" || location == "florida")
            {
                fine = (0.1111*60)+(0.18*(overstatedAmount-60)); //fine calculation for overstatedAmount less than or equal to 150, greater than 60 (for FL, NY)
            }
            else
            {
                fine = (0.1111*60)+(0.153*(overstatedAmount-60)); //fine calculation for overstatedAmount less than or equal to 150, greater than 60 (for not FL, NY)
            }
        }
        else if (overstatedAmount>150)
        {
            if (location == "new york" || location == "florida")
            {
                fine = (0.1111*60)+(0.18*90)+(0.21*(overstatedAmount-150)); //fine calculation for overstatedAmount greater than 150 (for FL, NY)
            }
            else
            {
                fine = (0.1111*60)+(0.153*90)+(0.21*(overstatedAmount-150)); //fine calculation for overstatedAmount greater than 150 (not for FL, NY)
            }
        }
        
        cout << "---" << endl;
        cout << "The fine for " << identification << " is $" << fine << " million."; //formatted fine output
    }
}

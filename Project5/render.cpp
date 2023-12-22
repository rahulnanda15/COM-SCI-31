#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <cassert>
using namespace std;
    
//FUNCTION PROTOTYPES
int render(int lineLength, istream& inf, ostream& outf);
bool isLastWordinLine(int endPosition, char text[] , int characterCount, int maxLineNum);
bool isPunctuation(char curChar);
bool paragraphBreak(int p, char* input);
bool isPunctuation(char curChar);


int main()
{
    
    ifstream infile("/Users/rahulnanda/Desktop/results.txt");
    //ifstream infile("/u/ma/ugrad/nanda/results.txt");
    if (!infile)
    {
        cerr << "Error: Cannot open results.txt!" << endl;
        return 1;
    }
    assert(render(11, infile, cout)==1);
     
     
}

//Checks if current word token is just spaces
bool noWordPortions(char string[], int begin, int end)
{
    for(int i=begin;i<=end;i++)
    {
        if(!isspace(string[i]))
        {
            return false;
        }
    }
    return true;
}

//Checks if current character is punctuation
bool isPunctuation(char curChar)
{
    if(curChar=='.'||curChar=='?'||curChar=='!'||curChar==':')
    {
        return true;
    }
    return false;
}

//Checks if current character is the start of a paragraph break @P@
bool isParagraphBreak(char* input, int p)
{
    if(input[p]!='\0' && input[p+1]!='\0' && input[p+2]!='\0') //Checks if subsequent 3 chars are out of bounds before being checked
    {
        if(input[p]=='@' && input[p+1]=='P' && input[p+2]=='@' && (input[p+3]=='\0' || isspace(input[p+3]))) //Checks if @P@ are consecutive characters
        {
            if(input[p-1]!='\0' && !isspace(input[p-1])) //Returns false if @P@ is preceeded by anything but a space
            {
                return false;
            }
            return true;
        }
        else{
            return false;
        }
    }
    else
    {
        return false;
    }
}


int render(int lineLength, istream& inf, ostream& outf)
{
    if(lineLength<1){
        return 2;
    }
    const int MAX_INPUT_LINE_LENGTH = 181; //181 is used since manually add ' ' to end of input line to help tokenize
    char line[MAX_INPUT_LINE_LENGTH];
    
    int beginPos=0; //beginPos and endPos are used to tokenize word-portions => beginPos is the beginning of a word portion, endPos is the end of a word portion
    int endPos=0;
    
    int q=0; //Var to hard code special edge case (SEE BELOW)
    
    int posOverflow; //position counter used for overflowing word portions
    
    int characterCount=0;
    int wordPortionLength;
    
    bool isFirstWordInLine=true;
    bool dashBefore=false; //Preceeding word ends in a hyphen
    bool newlineAdded=false;
    bool isWords=false; //Any words at all in output
    bool curPunct=false; //Preceeding word ending in punctuation
    bool pBreak=false; //Queue a paragraph break
    bool overflow=false; //Preceeding word length greater than line length
    
    
    while(inf.getline(line,MAX_INPUT_LINE_LENGTH)) //Read line by line
    {
        strcat(line," "); //Manually adds ' ' to end of input line
        beginPos=0;
        endPos=0;
        for(int i=0;line[i]!='\0';i++) //Iterate until end of line
        {
            //Hard coded the '@P@' edge case where input starts with @P@
            if(q==0)
            {
                if(line[q]=='@' && line[q+1]!='\0' && line[q+1]=='P' && line[q+2]!='\0' && line[q+2]=='@' && (line[q+3]=='\0' || isspace(line[q+3])))
                {
                    beginPos=endPos+4;
                    q++;
                    continue;
                }
            }
            else{
                q++;
            }
            
            if(isParagraphBreak(line, i))
            {
                if(isWords)
                {
                    pBreak=true; //Avoids queuing a paragraph break if output is empty so far
                }
                characterCount=0;
                isFirstWordInLine=true;
                beginPos=endPos+4; //Skips forward 4 positions to go over the @P@
                continue;
                
            }
            if(isspace(line[i]))
            {
                
                endPos=i; //beginPos is beginning of word portion, endPos is now position of isspace(line[i]) or where word-portion ends
                if(noWordPortions(line,beginPos,endPos)) //Skips printing when input line starts with space characters
                {
                    beginPos=endPos+1;
                    continue;
                }
                else{
                    posOverflow=characterCount;
                    wordPortionLength=endPos-beginPos;
                    characterCount=characterCount+wordPortionLength; //Adds length of word portion to number of characters currently in output line
                    
                    if(!isFirstWordInLine && !dashBefore)
                    {
                        characterCount++; //Add to the character count to account for the space => Only printed before word when not first word in line
                    }
                    if(overflow && curPunct)
                    {
                        characterCount++; //Add to the character count when there is punctuation in preceeding word if it is overflowing
                    }
                }
                
                if(characterCount>lineLength)
                {
                    if(wordPortionLength>lineLength)
                    {
                        overflow=true;
                        int counter=0;
                        if (pBreak) //If paragraph break was queued from preceeding word, execute break before printing any non space chars
                        {
                            outf << '\n' << '\n';
                            characterCount=0;
                            posOverflow=0;
                        }
                        else if(!isFirstWordInLine)
                        {
                            outf << "\n";
                            characterCount=0;
                            posOverflow=0;
                        }
                        while(counter<wordPortionLength) //Print overflowing word char by char until line fills up
                        {
                            if(posOverflow>=lineLength)
                            {
                                outf << '\n';
                                characterCount=0;
                                posOverflow=0;
                                isFirstWordInLine=true;
                            }
                            
                            outf << line[counter+beginPos];
                            pBreak=false;
                            if(isPunctuation(line[counter+beginPos]) && (line[counter+beginPos+1]=='\0' || isspace(line[counter+beginPos+1])))
                            {
                                curPunct=true; //Indicating word ends with punctuation so can add extra space later
                            }
                            else{
                                curPunct=false;
                            }
                            isWords=true;
                            
                            counter++;
                            posOverflow++;
                        }
                        beginPos=endPos+1; //Move forward to next word portion
                        characterCount=posOverflow;
                        isFirstWordInLine=false; //No longer first word in line if a word-portion hsa now been printed
                        continue;
                    }
                    else{
                        newlineAdded=true;
                        outf << '\n'; //Newline when line fills up
                        characterCount=0;
                        isFirstWordInLine=true;
                    }
                    
                }
                if(pBreak)
                {
                    outf << '\n' << '\n'; //Execute queued paragraph break before printing next word portion
                }
                if (!isFirstWordInLine && !dashBefore)
                {
                    outf << " "; //Printing a space before each word if not first word in line
                    if(curPunct) //Adding an extra space if punctuation detected in prev word portion
                    {
                        outf << " ";
                        characterCount++;
                    }
                }
                for(int j=beginPos;j<endPos;j++) //Print word portion char by char
                {
                    if(newlineAdded)
                    {
                        characterCount++;
                    }
                    isWords=true;
                    outf << line[j];
                    pBreak=false;
                    
                    if(isPunctuation(line[j]) && (line[j+1]=='\0' || isspace(line[j+1])))
                    {
                        curPunct=true; //Queuing punctuation so can add extra space before next word portion
                    }
                    else{
                        curPunct=false;
                    }
                                                                                  
                    isFirstWordInLine=false;
                }
                beginPos=endPos+1;
                dashBefore=false;
                newlineAdded=false;
            }
            
            if(line[i]=='-' && line[i+1]!='\0' && !isspace(line[i+1])){ //Tokenizing word portion whenever word ends with a hyphen
                dashBefore=true;
                endPos=i;
                
                posOverflow=characterCount;
                wordPortionLength=(endPos-beginPos)+1;
                characterCount=characterCount+wordPortionLength; //Adding length of word portion to num chars in output line
                if(!isFirstWordInLine)
                {
                    characterCount++; //Add to the count to account for the space => Only printed before word when not first word in line
                }
                if(overflow && curPunct) //Adding to character count to account for extra space from punctuation in overflowing word
                {
                    characterCount++;
                }
                if(characterCount>lineLength)
                {
                    if(wordPortionLength>lineLength)
                    {
                        overflow=true;
                        int counter=0;
                        
                        if (pBreak) //If paragraph break was queued from preceeding word, execute break before printing any non space chars
                        {
                            outf << '\n' << '\n';
                            characterCount=0;
                            posOverflow=0;
                        }
                        else if(!isFirstWordInLine) //Otherwise, just print one newline to precede overflowing word
                        {
                            outf << "\n";
                            characterCount=0;
                            posOverflow=0;
                        }
                    
                        while(counter<wordPortionLength) //Print entire overflow word; when line fills up, add a newline
                        {
                            if(posOverflow>=lineLength)
                            {
                                outf << '\n';
                                characterCount=0;
                                posOverflow=0;
                                isFirstWordInLine=true;
                            }
                            isWords=true;
                            outf << line[counter+beginPos];
                            pBreak=false;
                            
                            if(isPunctuation(line[counter+beginPos]) && (line[counter+beginPos+1]=='\0' || isspace(line[counter+beginPos+1])))
                            {
                                curPunct=true; //Queuing punctuation so can add extra space before next word portion
                            }
                            else{
                                curPunct=false;
                            }
                            
                            counter++;
                            posOverflow++;
                        }
                        beginPos=endPos+1;
                        characterCount=posOverflow;
                        isFirstWordInLine=false;
                        continue;
                    }
                    else
                    {
                        newlineAdded=true;
                        outf << '\n'; //If word portion not bigger than line length and line has been filled up, only print one newline
                        isFirstWordInLine=true;
                        characterCount=0;
                    }
                    
                }
                if(pBreak) //Execute paragraph break if queued
                {
                    outf << '\n' << '\n';
                }
                if (!isFirstWordInLine)
                {
                    outf << " "; //Printing a space before each word if not first word in line
                    if(curPunct) //Adding an extra space if punctuation detected in prev word portion
                    {
                        outf << " ";
                        characterCount++;
                    }
                }
                for(int j=beginPos;j<=endPos;j++) //Output the word portion word by word
                {
                    if(newlineAdded)
                    {
                        characterCount++;
                    }
                    isWords=true;
                    outf << line[j];
                    pBreak=false;
                    if(isPunctuation(line[j]) && (line[j+1]=='\0' || isspace(line[j+1]))) //Keep track of if end of word portion is punctuation
                    {
                        curPunct=true;
                    }
                    else{
                        curPunct=false;
                    }
                }
                newlineAdded=false;
                beginPos=endPos+1;
            }
        }
    }
    if(isWords)
    {
        outf << '\n'; //Print newline if there are any words anywhere on output
    }
    if(overflow)
    {
        return 1; //Return 1 if there was any overflowing words
    }
    return 0; //Return 0 for succeess
}

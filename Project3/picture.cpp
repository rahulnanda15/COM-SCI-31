#include "grid.h"
#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

//GLOBAL VARIABLES
const int HORIZ = 0;
const int VERT = 1;

const int FG = 0;
const int BG = 1;

bool checkEmpty(int y, int x){
    if (getChar(y,x)==' '){
        return true;
    }
    return false;
}

int onGridVert(int x, int y, int dist){
    if (dist<0){
        for (int i=x;i>=x-abs(dist);i--) //for loop condition must account for i+distance
        {
            if (i>=getRows() || i<=0 || y<=0 || y>=getCols()){
                return 0; //is out of grid
            }
        }
        return 1; //is on the grid
    }
    else{
        for (int i=x;i<=x+dist;i++) //for loop condition must account for i+distance
        {
            if (i>=getRows() || i<=0 || y<=0 || y>=getCols()){
                return 0; //is out of grid
            }
        }
        return 1; //is on the grid
    }
}

int onGridHoriz(int x, int y, int dist){
    if (dist>0){
        for (int i=y;i<=y+dist;i++) //for loop condition must account for i+distance
        {
            if (x>=getRows() || x<=0 || i<=0 || i>=getCols()){
                return 0; //off the grid
            }
        }
        return 1; //on the grid
    }
    else{
        for (int i=y;i>=y-abs(dist);i--) //for loop condition must account for i+distance
        {
            if (x>=getRows() || x<=0 || i<=0 || i>=getCols()){
                return 0; //off the grid
            }
        }
        return 1; //on the grid
    }
}

int plotVerticalLine(int r, int c, int distance, char ch, int background){
    if (distance<0){
        for (int i=r;i>=r-abs(distance);i--) //for loop condition must account for i+distance
        {
            if (i>=getRows() || i<=0 || c<=0 || c>=getCols()){
                break;
                return 0;
            }
            else{
                if (background==1){
                    if(checkEmpty(i,c)){
                        setChar(i, c, ch);
                    }
                    else{
                        continue;
                    }
                }
                else{
                    setChar(i, c, ch);
                }
            }
        }
    }
    else{
        for (int i=r;i<=r+distance;i++) //for loop condition must account for i+distance
        {
            if (i>=getRows() || i<=0 || c<=0 || c>=getCols()){
                break;
                return 0;
            }
            else{
                if (background==1){
                    if(checkEmpty(i,c)){
                        setChar(i, c, ch);
                    }
                    else{
                        continue;
                    }
                }
                else{
                    setChar(i, c, ch);
                }
            }
        }
    }
    return 1;
}
int plotHorizontalLine(int r, int c, int distance, char ch, int background){
    if (distance>0){
        for (int i=c;i<=c+distance;i++) //for loop condition must account for i+distance
        {
            if (r>=getRows() || r<=0 || i<=0 || i>=getCols()){
                break;
                return 0;
            }
            else{
                if (background==1){
                    if(checkEmpty(r,i)){
                        setChar(r, i, ch);
                    }
                    else{
                        continue;
                    }
                }
                else{
                    setChar(r, i, ch);
                }
            }
        }
    }
    else
    {
        for (int i=c;i>=c-abs(distance);i--) //for loop condition must account for i+distance
        {
            if (r>=getRows() || r<=0 || i<=0 || i>=getCols()){
                break;
                return 0;
            }
            else{
                if (background==1){
                    if(checkEmpty(r,i)){
                        setChar(r, i, ch);
                    }
                    else{
                        continue;
                    }
                }
                else{
                    setChar(r, i, ch);
                }
            }
        }
    }
    return 1;
}
bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg){
    if (fgbg!=0 && fgbg!=1){
        return false;
    }
    if (!isprint(plotChar)){
        return false;
    }
    if (dir==HORIZ){
        if (onGridHoriz(r, c, distance)==1){
            plotHorizontalLine(r, c, distance, plotChar, fgbg);
        }
        else{
            return false;
        }
    }
    else if (dir==VERT){
        if(onGridVert(r, c, distance)==1){
            plotVerticalLine(r, c, distance, plotChar, fgbg);
        }
        else{
            return false;
        }
    }
    else {
        return false;
    }
    return true;
}

int performCommands(string commandString, char& plotChar, int& mode, int& badPos){
    int gridError=0;
    int badPosGrid;
    int syntaxCounter=0;
    bool syntaxError=false;
    if (!isprint(plotChar)){
        return 2;
    }
    if (mode!=FG && mode != BG){
        return 2;
    }
    string setPoint;
    string lineLength;
    
    int currentR = 1;
    int currentC = 1;
    if(commandString[commandString.size()-1]=='H'||commandString[commandString.size()-1]=='h'||commandString[commandString.size()-1]=='V'||commandString[commandString.size()-1]=='v')
    {
        if(commandString[commandString.size()-2]!='B'&&commandString[commandString.size()-2]!='b'&&commandString[commandString.size()-2]!='F'&&commandString[commandString.size()-2]!='f')
        {
            if (syntaxCounter==0){
                badPos=commandString.size();
                syntaxCounter++;
                
            }
            else if (commandString.size()<badPos){
                badPos=commandString.size();
                
            }
            syntaxError=true;
        }
    }
    for(int j=1;j<commandString.size()-1;j++){
        if((commandString.at(j)=='h'|| commandString.at(j)=='V'||commandString.at(j)=='v'||commandString.at(j)=='H')&& isdigit(commandString.at(j+1))){
            if(commandString.at(j-1)=='b'||commandString.at(j-1)=='B'||commandString.at(j-1)=='F'||commandString.at(j-1)=='f'){
                if(j>1){
                    if(commandString.at(j-2)!='b'&&commandString.at(j-2)!='B'&&commandString.at(j-2)!='f'&&commandString.at(j-2)!='F'){
                        if (syntaxCounter==0){
                            badPos=j;
                            syntaxCounter++;
                            
                        }
                        else if(j+1<badPos){
                            badPos=j;
                            
                        }
                        syntaxError=true;
                    }
                }
                else if (commandString.at(j-1)!='f'&&commandString.at(j-1)!='F'&&commandString.at(j-1)!='B'&&commandString.at(j-1)!='b'){
                    if (syntaxCounter==0){
                        badPos=j;
                        syntaxCounter++;
                        
                    }
                    else if(j+1<badPos){
                        badPos=j;
                        
                    }
                    syntaxError=true;
                }
            }
        }
    }
    for(int j=0;j!=commandString.size();j++){
        if (commandString.at(j)=='+'){
            if (syntaxCounter==0){
                badPos=j;
                syntaxCounter++;
                
            }
            else if (j<badPos){
                badPos=j;
                
            }
            syntaxError=true;
        }
        else if (commandString.at(j)=='h'||commandString.at(j)=='H'||commandString.at(j)=='v'||commandString.at(j)=='V')
        {
            if(j==0){
                if(!isdigit(commandString.at(j+1)) && commandString.at(j+1)!='-'){
                    if (syntaxCounter==0){
                        badPos=j+1;
                        syntaxCounter++;
                       
                    }
                    else if(j+1<badPos){
                        badPos=j+1;
                        
                      
                    }
                    syntaxError=true;
                }
            }
        }
        else if(!isdigit(commandString.at(j))){
            if(commandString.at(j)!='C'&&commandString.at(j)!='c'&&commandString.at(j)!='F'&&commandString.at(j)!='f'&&commandString.at(j)!='B'&&commandString.at(j)!='b'&&commandString.at(j)!='v'&&commandString.at(j)!='V'&&commandString.at(j)!='H'&&commandString.at(j)!='h'&&commandString.at(j)!='-')
            {
                if(j>0){ //Other letters can only be in command if after b, B, f, F
                    if(commandString.at(j-1)!='b'&&commandString.at(j-1)!='B'&&commandString.at(j-1)!='F'&&commandString.at(j-1)!='f'){
                        if(syntaxCounter==0){
                            badPos=j;
                            syntaxCounter++;
                            
                        }
                        else if (j<badPos){
                            badPos=j;
                            
                        }
                        syntaxError=true;
                    }
                }
                else if(j>1){ //Satisfy error in "bbz" command where 2 FG characters precede random character
                    if (commandString.at(j-1)=='b'||commandString.at(j-1)=='B'||commandString.at(j-1)=='f'||commandString.at(j-1)=='F'){
                        if(commandString.at(j-2)=='b'||commandString.at(j-2)=='B'||commandString.at(j-2)=='f'||commandString.at(j-2)=='F'){
                            if(syntaxCounter==0){
                                badPos=j;
                                syntaxCounter++;
                               
                            }
                            else if(j<badPos){
                                badPos=j;
                                
                            }
                            syntaxError=true;
                        }
                    }
                }
                else { //Other letters can not start a command
                    if(syntaxCounter==0){
                        badPos=0;
                        syntaxCounter++;
                       
                    }
                    else{
                        badPos=0;
                       
                    }
                    syntaxError=true;
                }
            }
            if(commandString.at(j)=='-'){
                if (commandString.at(commandString.size()-1)=='-'){
                    if(commandString.at(commandString.size()-2)!='b'&&commandString.at(commandString.size()-2)!='B'&&commandString.at(commandString.size()-2)!='f'&&commandString.at(commandString.size()-2)!='F'){
                        if(syntaxCounter==0){
                            syntaxCounter++;
                            badPos=commandString.size();
                            
                        }
                        else if (commandString.size()-1<badPos){
                            badPos=commandString.size();
                            
                        }
                        syntaxError=true;
                    }
                }
                else if(j==0){
                    if(syntaxCounter==0){
                        syntaxCounter++;
                        badPos=0;
                        
                    }
                    else{
                        badPos=0;
                        
                    }
                    syntaxError=true;
                }
                else if (j==1){
                    if(commandString.at(j-1)!='h'&&commandString.at(j-1)!='H'&&commandString.at(j-1)!='v'&&commandString.at(j-1)!='V'&&commandString.at(j-1)!='b'&&commandString.at(j-1)!='B'&&commandString.at(j-1)!='f'&&commandString.at(j-1)!='F'){
                        if(syntaxCounter==0){
                            syntaxCounter++;
                            badPos=1;
                            
                        }
                        else{
                            badPos=1;
                        
                        }
                        syntaxError=true;
                    }
                }
                if(j>=1){
                    if(commandString.at(j-1)!='h'&&commandString.at(j-1)!='H'&&commandString.at(j-1)!='v'&&commandString.at(j-1)!='V'&&commandString.at(j-1)!='b'&&commandString.at(j-1)!='B'&&commandString.at(j-1)!='F'&&commandString.at(j-1)!='f'){
                        if(syntaxCounter==0){
                            syntaxCounter++;
                            badPos=j;
                            
                        }
                        else if(j<badPos){
                            badPos=j;
                           
                        }
                        syntaxError=true;
                    }
                    else if(j>1&&(commandString.at(j-2)=='b'||commandString.at(j-2)=='B'||commandString.at(j-2)=='f'||commandString.at(j-2)=='F'))
                    {
                        if(syntaxCounter==0){
                            syntaxCounter++;
                            badPos=j;
                           
                        }
                        else if(j<badPos){
                            badPos=j;
                        
                        }
                        syntaxError=true;
                    }
                    else if(commandString.at(j-1)=='V'||commandString.at(j-1)=='v'||commandString.at(j-1)=='h'||commandString.at(j-1)=='H'){
                        if(!isdigit(commandString.at(j+1))){
                            if(syntaxCounter==0){
                                syntaxCounter++;
                                badPos=j;
                                
                            }
                            else if(j<badPos){
                                badPos=j;
                                
                            }
                            syntaxError=true;
                        }
                    }
                }
            }
        }
        else if (isdigit(commandString.at(j))){
            if(j==0){ //can't start command with a number
                if(syntaxCounter==0){
                    badPos=0;
                    syntaxCounter++;
                    
                }
                else{
                    badPos=0;
                    
                }
                syntaxError=true;
            }
            else if(j==2){
                if(commandString.at(j-1)=='h'||commandString.at(j-1)=='H'||commandString.at(j-1)=='V'||commandString.at(j-1)=='v'){
                    if(commandString.at(j-2)=='b'||commandString.at(j-2)=='B'||commandString.at(j-2)=='F'||commandString.at(j-2)=='f'){
                        if(syntaxCounter==0){
                            syntaxCounter++;
                            badPos=j;
                            
                         }
                        else if (j<badPos){
                            badPos=j;
                            
                        }
                        syntaxError=true;
                    }
                }
            }
            else if(j>2){
                if(isdigit(commandString.at(j-1))&&isdigit(commandString.at(j-2))){
                    if(syntaxCounter==0){
                        badPos=j;
                        syntaxCounter++;
                        
                    }
                    else if(j<badPos){
                        badPos=j;
                        
                    }
                    syntaxError=true;
                }
            }
        }
    }
    for(int i=0;i<commandString.size()-1;i++)
    {
        setPoint="";
        if(commandString.at(i)=='C' || commandString.at(i)=='c'){
            if(i>0){ //allow c to be a character plotted if after f or b
                if(commandString.at(i-1)!='b'&&commandString.at(i-1)!='B'&&commandString.at(i-1)!='F'&&commandString.at(i-1)!='f'){
                    clearGrid();
                }
            }
        }
        if(commandString.at(i)=='b' || commandString.at(i)=='B'){
            if(i>0){
                if(commandString.at(i-1)!='b'&&commandString.at(i-1)!='B'&&commandString.at(i-1)!='f'&&commandString.at(i-1)!='F'){
                    plotChar=commandString.at(i+1); //check if i+1 is a plottable character as well
                    mode=BG;
                    //i++;
                }
            }
            else{
                plotChar=commandString.at(i+1); //check if i+1 is a plottable character as well
                mode=BG;
            }
        }
        else if(commandString.at(i)=='f' || commandString.at(i)=='F'){
            if(i>0){
                if(commandString.at(i-1)!='b'&&commandString.at(i-1)!='B'&&commandString.at(i-1)!='f'&&commandString.at(i-1)!='F'){
                    plotChar=commandString.at(i+1); //check if i+1 is a plottable character as well
                    mode=FG;
                    //i++;
                }
            }
            else{
                plotChar=commandString.at(i+1); //check if i+1 is a plottable character as well
                mode=FG;
            }
        }
        else if(isalpha(commandString.at(i)) && (commandString.at(i)=='h'||commandString.at(i)=='H'||commandString.at(i)=='v'||commandString.at(i)=='V')&&(isdigit(commandString.at(i+1))||(commandString.at(i+1)=='-'&&isdigit(commandString.at(i+1)))))
        {
            setPoint+=commandString.at(i);
            for(int k=i+1;k<commandString.size();k++)
            {
                if (!isalpha(commandString.at(k))){
                    setPoint+=commandString.at(k);
                }
                else
                {
                    break;
                }
            }
            lineLength="";
            for(int n=1;n<setPoint.size();n++)
            {
                lineLength+=setPoint.at(n);
            }
            if (commandString.at(i)=='h' || commandString.at(i)=='H'){
               
                if(onGridHoriz(currentR, currentC, stoi(lineLength))==1)
                {
                    plotLine(currentR, currentC, stoi(lineLength), HORIZ, plotChar, mode);
                    currentR=currentR;
                    currentC=currentC+stoi(lineLength);
                }
                else{
                    badPosGrid=i;
                    gridError=3;
                }
            }
            else if (commandString.at(i)=='v' || commandString.at(i)=='V')
            {
                if(onGridVert(currentR, currentC, stoi(lineLength))==1)
                {
                    plotLine(currentR, currentC, stoi(lineLength), VERT, plotChar, mode);
                    
                    currentR=currentR+stoi(lineLength);
                    currentC=currentC;
                }
                else{
                    badPosGrid=i;
                    gridError=3;
                }
            }
            i++;
        }
        else if ((commandString.at(i)=='c'||commandString.at(i)=='C')&&isdigit(commandString.at(i+1))){
            if (syntaxCounter==0){
                badPos=i=1;
                syntaxCounter++;
                
            }
            else if (i+1<badPos){
                badPos=i+1;
                
            }
            syntaxError=true;
        }
    }
    if(syntaxError==true){
        
        return 1;
    }
    if(gridError==3){
        badPos=badPosGrid;
     
        return 3;
    }
    if(commandString[commandString.size()-1]=='C'||commandString[commandString.size()-1]=='c')
    {
        clearGrid();
    }
    return 0;
}
                                        
int main()
{
    
    int nRows;
    int nCols;
    for (;;)
    {
        cin >> nRows >> nCols;
        cin.ignore(10000,'\n');
        if (nRows >= 1  &&  nRows <= MAXROWS  &&  nCols >= 1  &&  nCols <= MAXCOLS)
        {
            setSize(nRows, nCols);
            break;
        }
        cout << "The numbers must be between 1 and 30." << endl;
    }
    char currentChar = '*';
    int currentMode = FG;

    string setPoint;
    string lineLength;
    
    for(;;)
    {
        string command;
        getline(cin, command);
        if(command=="")
        {
            break;
        }
        int position;
        int status = performCommands(command, currentChar, currentMode, position);
        switch(status){
            case 0:
                draw();
                break;
            case 1:
                
                break;
            case 2:
                
                break;
            case 3:
                
                break;
        }
        
    }
}

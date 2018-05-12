/*Troy Frazier
  trf170130
  Project 5
  */
#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iomanip>
#include "sList.h"
#include "sNode.h"
#include "sReserve.h"
using namespace std;
bool fileOp(fstream&,const int);
void audiSet(fstream&,sList&,const int,const int);
int readLine(fstream&,const int);
void disList(sList&);
int menuTwo(int);
int reservation(sList&,int[],const int);
bool tickBuy(const int,int&);
int seatGet(sList&,const int,string);
void audiOut(fstream&,sList&,const int);
bool bestSeat(int*&,sList&,int);
char bestValidation();
void report(sList&,int*,int,int);
void gatherData(sList&,int&,int&);

const int
AUDINUM  = 3, //Amount of auditoriums in a theater
ADPRICE = 7, // following 3 vars are Adult price, Senior price, and Child price for movie tickets
SEPRICE = 5,
CHPRIICE = 3,
TICKELE = 3; //The amount of different ticket categories

int main()
{
    fstream ioFile;
    int
    userNum =  0,
    xRow[AUDINUM] = {0,0,0}, // holds the max X coordinate for each Auditorium, used for setting the auditorium list
    *tickType = new int[AUDINUM*TICKELE], //Tickets bought of a certain category of one session
    tickTot = 0; //Stores total ticket sales of one session
    string
    userInput; //A hold variable used in validation
    const char
    *hold; // a hold variable used in validation
    bool
    userFlag = true; // loops the UI, if false, program ends
    sList head[AUDINUM]; // creates list heads  = to amount of auditoriums
    for(int count = 0; count < (AUDINUM*TICKELE); count++) // sets tick type  dynamic array to 0s
        *(tickType+count) = 0;
    for(int count = 0; count < AUDINUM; count++){ //Sets (x,y) and closed/open values to every node in an auditorium
        xRow[count] = readLine(ioFile,count+1); //gains Max X coordinate
        if(xRow[count] == -1){
            count = AUDINUM;
            userFlag = false;
        }
        else
            audiSet(ioFile,head[count],xRow[count],count+1); //Sets the auditorium
    }

    while(userFlag){ //Loops the whole program, namely the first UI
        while(userNum < 1 || userNum > 3){ //Main menu validation
            cout << "Pick a number...\n1.Reserve Seats \n2.View Auditorium \n3.Exit \n";
            getline(cin,userInput);
                if(userInput.length() != 1) // if not length of 1 then 1,2,3 are not possible values
                    cout << "Incorrect Input...\n";
                else{
                    hold = userInput.c_str();
                    if(isdigit(*hold)) // proves input is a digit of 0-9
                        userNum = atoi(userInput.c_str());

                }
            }
        switch(userNum){
            case 1:
                // ***Reserve Process***
                userNum = menuTwo(userNum); //Second UI
                tickTot += reservation(head[userNum-1],tickType,userNum); //Process to change closed seats to open/stores tick bought
                break;
            case 2:
                //View Audi
                userNum = menuTwo(userNum); //Second UI
                disList(head[userNum-1]);//Displays a  certain auditorium
                break;
            case 3:
                userFlag = false; //starts end program process
            for(int count = 0; count < AUDINUM; count++) //Saves changes to the program on each auditorium
                audiOut(ioFile,head[count],count+1);
            for(int count = 1; count <= AUDINUM; count++){ //Gives report data on overall open/closed and this session of tickets
                report(head[count-1],tickType,count,tickTot);
            }
            for(int count = 0; count < AUDINUM; count++) //Deletes all Dynamic lists
                head[count].~sList();
                break;
        }
        userNum = 0;
    }
    delete[] tickType; //Deletes dynamic array of this session's tickets
    return 0;
    }
int menuTwo(int userNum){ //Second UI + user validation
    string
    userInput;
    userNum= 0;
    const char
    *hold;
    while(userNum < 1 || userNum > 3){
        cout << "Pick a number...\n1.Auditorium 1  \n2.Auditorium 2 \n3.Auditorium 3 \n";
        getline(cin,userInput);
            if(userInput.length() != 1)
                cout << "Incorrect Input...\n";
            else{
                hold = userInput.c_str();
                if(isdigit(*hold))
                    userNum = atoi(userInput.c_str());
            }
    }
    return userNum;
}
int readLine(fstream& iFile,const int XNUM){ //Gains max X coordinate
    char
    hold = '\0';
    int
    count = 0;
    bool
    fileFlag;
    fileFlag = fileOp(iFile,XNUM); //Opens an individual file
    if(!fileFlag)
        return -1;
    else{
    while(hold != '\n'){ //counts until a line break is reached which finds the max X coordinate defined by a grid
        hold = iFile.get();
        if(hold !='\n')
            count++;
    }
    iFile.close();
    }
    return count;
}
bool fileOp(fstream& ioFile,const int AUDIFILE){//Handles files A1,A2,A3
    switch(AUDIFILE){ //Opens file 1,2,3 from a certain input derived from UI #2
    case 1:
        ioFile.open("A1.txt", ios::in | ios::out);
        break;
    case 2:
        ioFile.open("A2.txt", ios::in | ios::out);
        break;
    case 3:
        ioFile.open("A3.txt", ios::in | ios::out);
        break;
    }
    if(ioFile.fail()){ //Validation of a file
        cout << "Error opening file A" << AUDIFILE << ".txt\n";
        return false;
    }
    return true;
}
void audiSet(fstream& iFile,sList& h,const int XROW,const int AUDI){  //Sets auditorium values
    sReserve *cur;
    int
    count = 1, //Controls y coordinate
    subCount = 1, //Controls x coordinate
    arCount = 0; //Controls array index
    fileOp(iFile,AUDI);
        while(iFile.peek() != EOF){ // loop until END-OF-FILE setting (x,y) and seat type for a selected auditorium
            cur = new sReserve(cur,cur,count,subCount);
            h += cur; //Add node to end of list operator
            iFile >> h[arCount]; //Open/Closed seat operator
            arCount++;
            if(arCount !=  0 && ((arCount) % (XROW)) == 0){
                subCount++;
                count = 1;
            }
            else
                count++;
        }
        iFile.close();
}
void disList(sList& h){ //Displays a selected auditorium
    const int
    XMAX = 10; //Used for x coordinate display
    int
    axisMulti = 1; //Used for x coordinate display for  any axis > 20
        /* **Note this loop was used in Project 3** */
    for(int count = 0; count < h.getFoot()->getSCol(); count++){ //Displays all x margins
        if(count + 1 > 9){ //Restarts the 0-9 margins to ensure alignment
            if(count != 0 && (count + 1) != 10 && (count + 1) % 10 == 0) //Keeps xAxis in correct format for bigger auditoriums
                axisMulti++; //Multiplier used for an x axis > 20
            cout << (count + 1) - (XMAX * axisMulti);
        }
        else if(count < 10)
            cout << count + 1;
    }
    cout << endl;
    for(int count = 0; count < h.getFoot()->getSCol() * h.getFoot()->getSRow(); count++){ //Loop to display seat types
        if(count !=  0 && (count % h.getFoot()->getSCol()) == 0)
            cout << endl;
        cout  << h[count]; //Operator that displays a # or .
    }
    cout << endl << endl; //Formatting purposes
}
int reservation(sList& h,int tickType[],const int AUDI){ //Main module for reservation process + Best Seat process
    int
    userTick, //Total Tickets
    userType[TICKELE] = {0,0,0}, //Holds tick types until seat validation and reservation is complete then transfers to tickType
    *userSeats; //Holds the seat element for verification and action
    bool
    tickFlag = false;//used in validations
    disList(h); //Displays selected auditorium for ease of input
    char
    hold = 'x'; //Used for best seat validation
    while(!tickFlag){ //Total tickets + validation
        cout << "Enter total amount of tickets: ";
        tickFlag = tickBuy(h.getFoot()->getSCol()* h.getFoot()->getSRow(),userTick);
    }
    tickFlag = false;
    while(!tickFlag){ //Adult tickets + validation
        cout << "Enter the amount of adult tickets: ";
        tickFlag = tickBuy(userTick,userType[0]);
    }
    tickFlag = false;
    if(userType[0] != userTick){ // if adults != total tickets
        while(!tickFlag){ //Senior tickets + validation
            cout << "Enter the amount of senior tickets: ";
            tickFlag = tickBuy(userTick,userType[1]);
        }
        tickFlag = false;
        if((userType[0] + userType[1]) != userTick){ // if Adults + Senior != total tickets
            while(!tickFlag){ //Child tickets + validation
                cout << "Enter the amount of kid tickets: ";
                tickFlag = tickBuy(userTick,userType[2]);
            }
        }
    }
    tickFlag = false;
    userSeats = new int[userTick]; //Holds seats = to  amount of tickets
    for(int count = 0; count < userTick; count++){ //Input seat x,y loop
        for(int subCount = 0 ; subCount < 2; subCount++){
            if(subCount == 0){
                cout << "Enter Row number: "; //Y input +  validation
                *(userSeats + count) = h.getFoot()->getSCol() * (seatGet(h,h.getFoot()->getSRow(),"Row") - 1);
            }
            else{
                cout << "Enter Column number: "; //X input + validation
                *(userSeats + count) += seatGet(h,h.getFoot()->getSCol(),"Column");
            }
        }
    }
    for(int count = 0; count < userTick; count++){ //Checks to see if seats are open
        if(h[*(userSeats+count)-1]->getStat()) //If a seat has a true value then seat is already closed
            tickFlag =  true;
    }
    if(tickFlag){ //If a seat or seats is already reserved begin best Seat process
        cout << "seat(s) already reserved... \n"; /* ***Best Seat module goes here *** */
        if(userTick < h.getFoot()->getSCol()){ //If amount of tickets is less then a row then a consecutive seat is possible
            if(bestSeat(userSeats,h,userTick)){ //After a best seat is found ask user is they want such seat else end process
                cout << "Seat(s) at (" << h[*userSeats-1]->getSCol() << "," << h[*userSeats-1]->getSRow() << ") is available.  \n";
                while(hold  == 'x'){ // Y/N validation, x = a flagged validation
                    cout << "Do you want to reserve that seat? (Y/N): ";
                    hold = bestValidation(); //gets user's input
                }
                if(hold == 'N')
                    userTick = 0; //ensures no tickets are sent to main
                else{
                    for(int count = 1; count < userTick; count++) //sets up consecutive seats for reservation process
                        *(userSeats+count) = *(userSeats) + count;
                    tickFlag = false; //allows reservation  process begin
                    }
                }
            }
            else{
                cout  << "No consecutive seats available \n"; // in the case of no seats available
                userTick = 0;
        }
    }
    if(!tickFlag){ //Changes # value to .
        /* *** Begin reservation*** */
        for(int count =  0; count < userTick; count++)
            h[*(userSeats+count)-1]->setStat(true);
        for(int count = 0; count < TICKELE; count++)  //break total tickets into respected categories
            tickType[count+(TICKELE*(AUDI-1))] += userType[count];
    }
    return userTick;
}
bool tickBuy(const int MAXTICK,int& tickNum){ //Validation for total, adult, senior,and child tickets
    bool
    tickFlag = false; //controls validation loop in reserve
    string
    userInput;
    const char
    *hold;
    int
    sLength; //holds string length used because of .length() compiler warnings
    getline(cin,userInput);
    if(userInput.length() <= 3 && userInput.length() > 0){
        hold = userInput.c_str();
        sLength = userInput.length();
        for(int count = 0; count < sLength; count++)
            if(!isdigit(*(hold+count)))
                return false;
        tickNum = atoi(userInput.c_str());
        if(tickNum <= MAXTICK && tickNum >= 0) //ensures no tickets are bought that is more then the seats in an auditorium
            tickFlag = true;
    }
    return tickFlag;
}
int seatGet(sList& h,const int MAXCOORD,string act){ //Validation of a single seat coordinate, X,Y
    int
    seatEle,
    sLength; //String length hold variable; used because of compiler warnings vs direct .length() comparison
    bool
    tickFlag = false;
    string
    userInput;
    const char
    *hold;
        while(!tickFlag){
            getline(cin,userInput);
            if(userInput.length() <= 3 && userInput.length() > 0){
                hold = userInput.c_str();
                sLength = userInput.length();
                for(int count = 0; count < sLength; count++){
                    if(!isdigit(*(hold+count))){
                        count = userInput.length();
                        tickFlag = false;
                    }
                    else
                        tickFlag = true;
                }
                if(tickFlag){
                    seatEle = atoi(userInput.c_str());
                    if(seatEle > MAXCOORD || seatEle < 1) //ensures the seat bounds are between 0 and last seat
                        tickFlag = false;
                }
                if(!tickFlag)
                    cout << "Invalid input, enter " << act << " number: ";
            }
        }
    return seatEle;
}
void audiOut(fstream& oFile, sList& h,const int fileNum){ //Outputs an auditorium
    fileOp(oFile,fileNum);
    for(int count = 0; count < h.getFoot()->getSCol() * h.getFoot()->getSRow(); count++){ //Loop outputs an entire list
        if(count !=  0 && ((count) % (h.getFoot()->getSCol())) == 0)                       //with Respected #,.
            oFile << '\n';
        if(h[count]->getStat())
            oFile << '.';
        else
            oFile  << '#';
    }
    oFile.close();
}
bool bestSeat(int*& seats,sList& h,int tickNum){ //Process finds best seat (if any) and recommends to user
    int
    pX = (h.getFoot()->getSCol() + h[0]->getSCol()) / 2, //gets middle X; is reused in comparing best seat
    pY = (h.getFoot()->getSRow() + h[0]->getSRow()) / 2, // get middle Y; is reused in comparing  best seat
    midPoint = 1, //hold middle element of a list as if it was a 1D array
    count = 0,
    eleCount = 0; //holds a element in a list which is used to compare against other elements to find closer seat
    bool
    seatFlag = false;
    while(h[count]->getSCol() != pX || h[count]->getSRow() != pY){ // finds middle element, adds to midpoint
        count++;
        midPoint++;
    }
    count = 0; //restarts count to find first best seat
    while(!seatFlag){ //Gets first set of open seats
        if(!h[count]->getStat()){
            for(int subCount = 0; subCount < tickNum; subCount++){ //check a seat or seats to see if one or all are open
                if(count+subCount > (h.getFoot()->getSCol() * h.getFoot()->getSRow())){
                    cout << "No open consecutive seats available...\n";//If a starting point does not have enough seats to fill
                    return false;                                     //a set, end loop and module as there are no seats available
                }
                else if(h[subCount+count]->getStat()|| h[count]->getSRow() != h[subCount+count]->getSRow()){
                    seatFlag = false; //Ends for loop if a closed seat is found within a set
                    subCount = tickNum;
                }
                else
                    seatFlag = true;
            }
        }
        if(!seatFlag)
            count++;
        if(h[count]->getSCol() == h.getFoot()->getSCol() && h[count]->getSRow() == h.getFoot()->getSRow()){ // checks if out of bounds
                if(h.getFoot()->getStat()){
                    cout << "No open consecutive seats available...\n";
                    return false;
                }
                else
                    seatFlag = true;
            }
        }
    eleCount = count; //sets the "best seat"
    seatFlag = false;
    while(!seatFlag){ //loop finds a set of seats to compare to the "bests seat" to find "better seat"
        count++;
        if(count+tickNum > (h.getFoot()->getSCol() * h.getFoot()->getSRow()))
            seatFlag = true;
        else if(!h[count]->getStat()){
            for(int subCount = 0; subCount < tickNum; subCount++){
                if(h[subCount+count]->getStat() && h[count]->getSRow() == h[subCount+count]->getSRow()){
                    seatFlag = false;//Ends for loop if a closed seat is found within a set
                    subCount = tickNum;
                }
                else
                    seatFlag = true;
            }
            if(seatFlag){
                    pX = h[count]->getSCol();//sets X coordinate
                    pY = h[count]->getSRow(); //sets Y coordinate
                if(abs(pX-h[midPoint-1]->getSCol())+abs(pY-h[midPoint-1]->getSRow()) == abs(h[eleCount]->getSCol()-h[midPoint-1]->getSCol()) + abs(h[eleCount]->getSRow()-h[midPoint-1]->getSRow())){
        /* ***If the distance between sets from middle are equal in distance then check row value *** */
                    if(abs(pY-h[midPoint-1]->getSRow()) < abs(h[eleCount]->getSRow()-h[midPoint-1]->getSRow())){
                /* *** Finds seat closest to middle via x,y coordinates, if two seats are equal, newest is ignored *** */
                       eleCount = count; //If seat is closer then new seat becomes "best seat"
                       seatFlag = false;
                    }
                       else // if they are equal then by previous if statement they are on the same row and new set is not better
                        seatFlag = false;
                }
                else if(abs(pX-h[midPoint-1]->getSCol()) <= abs(h[eleCount]->getSCol()-h[midPoint-1]->getSCol()) && abs(pY-h[midPoint-1]->getSRow()) <= abs(h[eleCount]->getSRow()-h[midPoint-1]->getSRow())){
        /* ***Compares absolute value of distance between two seats to see if new set is closer to middle *** */
                    if(abs(count-(midPoint-1)) == abs(eleCount-(midPoint-1)))
                        seatFlag = false;
                    else{
                    eleCount = count;
                    seatFlag = false;
                    }
                }
                else // seat is not closer move to next set
                    seatFlag = false;
            }
        }
    }
    *seats = h.getFoot()->getSCol() * (h[eleCount]->getSRow()-1) + h[eleCount]->getSCol(); //set best seat into a pass by reference
    return  true; // allows for the best seat suggestion
}
char bestValidation(){ //validation for best seat suggestion
    string
    userInput;
    const char
    *hold;
    getline(cin,userInput);
    if(userInput.length() == 1){
        hold = userInput.c_str();
        if(*hold == 'n' || *hold == 'N')
            return 'N';
        else if(*hold == 'y' || *hold == 'Y')
            return 'Y';
        else
            return 'x';
    }
    return 'x'; // is the incorrect input  flag
}
void report(sList& h, int* tTypes,int count,int tickTot){ // sends data report at the end of program
   static  int //creates an unchanging op cl used for multiple calling of report
   op[AUDINUM] = {0,0,0},
   cl[AUDINUM] = {0,0,0};
    gatherData(h,op[count-1],cl[count-1]);
    if(count-1 == 0) //if first call display data labels
        cout << "Auditoriums   " << "Open " << "TotClosed " << "TotAdults " << "TotSenior " << "TotChild " << "TotTickets" << endl;
   if(count <= AUDINUM) { //displays every call
        cout << "Auditorium " << count << ":"<< setw(3) << op[count-1] << setw(8) << cl[count-1] << setw(10)
        << *(tTypes+(((count-1)*TICKELE))) << setw(10)
        << *(tTypes+(((count-1)*TICKELE))+1) << setw(10) << *(tTypes+(((count-1)*TICKELE))+2)
        << setw(10) << (*(tTypes+(((count-1)*TICKELE)))*ADPRICE)+(*(tTypes+(((count-1)*TICKELE))+1)*SEPRICE)+(*(tTypes+(((count-1)*TICKELE))+2)*CHPRIICE) << endl;
   }
   if(count == AUDINUM){ //if last call, display totals
        cout << "Total:" << setw(10) << op[0]+op[1]+op[2] << setw(8) << cl[0]+cl[1]+cl[2] << setw(10)
        << *tTypes+*(tTypes+3)+*(tTypes+6) << setw(10)
        << *(tTypes+1)+*(tTypes+4)+*(tTypes+7) << setw(10) << *(tTypes+2)+*(tTypes+5)+*(tTypes+8) << setw(10)
        << (*tTypes+*(tTypes+3)+*(tTypes+6))*ADPRICE+(*(tTypes+1)+*(tTypes+4)+*(tTypes+7))*SEPRICE+(*(tTypes+2)+*(tTypes+5)+*(tTypes+8))*CHPRIICE << endl;
   }
}
void gatherData(sList& h,int& op,int& cl){ // gathers total open closed seats for report
    for(int count = 0; h[count] !=h.getFoot(); count++){
        if(h[count]->getStat())
            cl++;
        else
            op++;
    }
        if(h.getFoot()->getStat())
            cl++;
        else
            op++;
}

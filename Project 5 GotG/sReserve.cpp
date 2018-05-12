/*Troy Frazier
  trf170130
  Project 5
  */
#include "sReserve.h"

sReserve::sReserve(sReserve* nPtr,sReserve* bPtr,int sX,int sY): sNode(sX,sY)
{
    sNext = nPtr;
    sBack = bPtr;
}
fstream& operator>>(fstream& in, sReserve* ptr){
    char
    hold = in.get();
    bool flag = true;
    while(flag){ //Ensures break line does not factor into list
        if(hold == '.'){
            ptr->setStat(true);
            flag = false;
        }
        else if(hold == '#') //Open seat is default status
            flag = false;
        else
            hold = in.get();
    }
    return in;
}
ostream& operator<<(ostream& out, sReserve* ptr){
    if(ptr->getStat())
        cout << ".";
    else
        cout << "#";
    return out;
}


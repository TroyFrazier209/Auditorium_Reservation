/*Troy Frazier
  trf170130
  Project 5
  */
#include "sList.h"

sList::sList(sReserve *ptr) //Overloaded constructor
{
    sHead = ptr;
    sFoot = ptr;
}
void sList::operator+=(sReserve* ptr){ //Adds a node to the end of a list
    sReserve *cur = sFoot;
    if(!cur){ // if head is null
        sHead = ptr;
        sHead->sNext = nullptr;
        sFoot = ptr;
        sFoot->sBack = nullptr;
    }
    else{ // if head is not null
        cur->sNext = ptr;
        cur->sNext->sNext = nullptr;
        sFoot = ptr;
        sFoot->sBack = cur;
        cur = sHead;
        cur->sBack = nullptr;
    }

}
sReserve* sList::operator[](int num){ //finds a particular node assuming node exists, validation happens in main
    sReserve *cur = sHead;
    for(int count = 0;  count < num; count++){
        cur = cur->sNext;
    }
    return cur;
}
sList::~sList(){ //destroys list from head to foot
    sReserve *cur = sHead;
    while(sHead){
        sHead = sHead->sNext;
        delete cur;
        cur = sHead;
    }
}


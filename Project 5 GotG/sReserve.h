/*Troy Frazier
  trf170130
  Project 5
  */
#ifndef SRESERVE_H
#define SRESERVE_H
#include "sNode.h"
#include <iostream>
#include <fstream>
using namespace std;
class sReserve : public sNode
{
    friend class sList;
    public:
        //Constructors
        sReserve(){sNext = nullptr; sBack = nullptr;}
        sReserve(sReserve*,sReserve*,int,int);
        //Mutator
        void setStat(bool stat){sStat = stat;}
        //Operator
        friend fstream& operator >>(fstream&,sReserve*);
        friend ostream& operator<<(ostream&,sReserve*);
        //Accessors
        bool getStat(){return sStat;}
        virtual int getSCol(){return sCol;}
    protected:

    private:
        sReserve *sNext; //links a list forward
        sReserve *sBack; // links a list backward
        bool sStat = false; // false = open seat, true = closed seat
};

#endif // SRESERVE_H

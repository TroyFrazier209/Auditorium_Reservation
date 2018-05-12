/*Troy Frazier
  trf170130
  Project 5
  */
#ifndef SLIST_H
#define SLIST_H
#include "sNode.h"
#include "sReserve.h"
using namespace std;
class sList
{
    public:
        //Constructors
        sList(){sHead = nullptr; sFoot = nullptr;}
        sList(sReserve*);
        //Accessors
        sReserve* getFoot(){return sFoot;}
        sReserve* getHead(){return sHead;}
        //Operators
        void operator +=(sReserve*);
        sReserve* operator[](int);
        //Destructor
        ~sList();

    protected:

    private:
        sReserve *sHead; //holds top of list
        sReserve *sFoot;// holds bottom of list

};

#endif // SLIST_H

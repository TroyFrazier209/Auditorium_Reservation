/*Troy Frazier
  trf170130
  Project 5
  */

#ifndef SNODE_H
#define SNODE_H


class sNode
{
    public:
        //Constructors
        sNode(){sCol = 0; sRow = 0;}
        sNode(int sX, int sY){sCol = sX; sRow = sY;};
        virtual int getSCol()=0; //Abstract module
        int getSRow(){return sRow;}
    protected:
        int sCol; //holds x coordinate
        int sRow; //holds y coordinate
};

#endif // SNODE_H

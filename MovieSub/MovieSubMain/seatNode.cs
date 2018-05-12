using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MovieSubMain
{
    class seatNode
    {
        private bool seatStat; //False for closed seat, True for open seat
        private int seatX;
        private int seatY;
       public seatNode(bool sOp,int X,int Y) //Full Class Constructor
        {
            seatStat = sOp;
            seatX = X;
            seatY = Y;

        }
        //Accessor
        public bool getSeatStat(){ return seatStat;}
        public int getSeatX() { return seatX; }
        public int getSeatY() { return seatY; }
        //Mutator
        public void setSeatStat(bool stat) { seatStat = stat; }
    }
}

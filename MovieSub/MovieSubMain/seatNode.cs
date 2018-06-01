/*Author: Troy Frazier
  Date: 6/24/2017
*/
/*
MIT License

Copyright (c) 2018 Troy Frazier

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
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

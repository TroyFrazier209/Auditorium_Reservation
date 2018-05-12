using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace MovieSubMain
{
    class Audi
    {
        private List<seatNode> seats = new List<seatNode>();
        private int audiNum;
        private FileStream audiIO;
        private StreamReader audiRead;
        private StreamWriter audiWrite;

        //Constructor
        public Audi(int i) { audiNum = i; }
        //Accessors
        public int getAudiNum() { return audiNum; }
        public int getSeatCount() { return seats.Count; }
        public int getMaxX() { return seats[seats.Count - 1].getSeatX(); }
        public int getMaxY() { return seats[seats.Count - 1].getSeatY(); }
        public int getX(int x) { return seats[x].getSeatX(); }
        public int getY(int y) { return seats[y].getSeatY(); }
        public char getSeatChar(int seatIndex)
        {
            if (seats[seatIndex].getSeatStat()) //Open Seat
                return '#';
            else //Closed Seat
                return '*';

        }
        //Mutator
        public void reserveSeat(int index){ seats[index].setSeatStat(false);} //**NOTE** False for closed seats
        //Misc Methods
        public bool setAudi(int _audiNum) // set an entire auditorium with open/closed seat nodes w/coords
        {
            char fileRead;
            string audiName = "A";
            int fileX = 0; //Used to gain file line length
            int x = 1; //x,y used for seat coordinates
            int y = 1;
            bool seatFlag = false;
            audiName += _audiNum;
            try //Open file + the auditorium number and check if said file exists
            {
                audiIO = File.OpenRead(audiName + ".txt");
                audiRead = new StreamReader(audiIO);
            } catch (FileNotFoundException) // ends program with an error message
            {
                Console.WriteLine("File {0} Not found, ending program...",audiName);
                return false;
            }
            fileX = fileLine(fileX);
            if (fileX > 0)
            {
                while (!audiRead.EndOfStream)
                {
                    for (int count = 0; count < fileX; count++)
                    {
                        fileRead = (char)audiRead.Read();
                        if (fileRead == '#')  //Creates an open seat
                            seatFlag = true;                        
                        else if (fileRead == '*')//Creates a closed seat
                            seatFlag = false;
                        else //Incorrect seat format error message
                        {
                            Console.WriteLine("Error,{0} is incorrectly formatted, # = Open, * = Closed",fileRead);
                            return false;
                        }
                        seatNode seat = new seatNode(seatFlag, x, y); //Creates new seat
                        seats.Add(seat); //Adds said seat to list
                        x++;
                    }
                    if (!audiRead.EndOfStream) //Elminate the 2 byte breakline
                    {
                        audiRead.Read(); //Eliminate break line
                        audiRead.Read();
                    }
                    x = 1;
                    y++;
                }
                audiRead.Close();
                audiIO.Close();
                return true;
            }
            else //Error message for incorrectly formatted file
            {
                Console.WriteLine("Error, Auditorium does not have equal rows");
                return false;
            }
        }
        private int fileLine(int fileX) // ensures all auditorium rows are of equal length else return -1
        {
            string fileHold;
            fileHold = audiRead.ReadLine();
            fileX = fileHold.Length;
            while (!audiRead.EndOfStream)
            {
                fileHold = audiRead.ReadLine();
                if (fileX != fileHold.Length)
                    return -1;
            }
            audiIO.Position = 0;
            audiRead.DiscardBufferedData();
            return fileX;
        }
        public void displayAudi()
        {
            int index = 0;
            for (int count = 1; count <= seats[seats.Count - 1].getSeatX(); count++)           
                Console.Write(count % 10); //Displays 1-0 where 0 is a 10th of a set i.e 10,20,30...          
            Console.WriteLine("");
            for (int count = 0; count < seats[seats.Count-1].getSeatY(); count++) //Displays each node with */#
            {
                for (int subCount = 0; subCount < seats[seats.Count-1].getSeatX(); subCount++)
                {
                    //Console.Write("{0},{1} ", getX(index), getY(index)); ///***DEBUG CODE***///
                    Console.Write(getSeatChar(index));
                    index++;
                }
                Console.WriteLine("");
            }
            Console.WriteLine(""); //Format breakline
        }
        public void audiOut(int audiNum)
        {
            string audiName = "A";
            int index = 0;
            audiIO = File.OpenWrite(audiName + audiNum + ".txt");
            audiWrite = new StreamWriter(audiIO);

            for (int count = 0; count < seats[seats.Count - 1].getSeatY(); count++) //Displays each node with */#
            {
                for (int subCount = 0; subCount < seats[seats.Count - 1].getSeatX(); subCount++)
                {
                    audiWrite.Write(getSeatChar(index));
                    index++;
                }
                audiWrite.WriteLine("");

            }
            audiWrite.Close();
            audiIO.Close();
        }
    }
}

/*Author: Troy Frazier
  Date: 6/24/2017
*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
namespace MovieSubMain
{
    class Program
    {
        const float TICKPRICE = 7f; 
        const int AUDITORIUMS = 3; // controls the amount of auditoriums
        static void Main(string[] args)
        {
            int userNum = 0;
            bool audiFlag = true;
            List<Audi> audis = new List<Audi>();
            for(int count = 0; count < AUDITORIUMS && audiFlag; count++) //Intilizes auditoriums
            {
                Audi auditorium = new Audi(count + 1);
                audis.Add(auditorium);
                audiFlag = auditorium.setAudi(count+1);
            }
            if (audiFlag) //If all auditoriums were correctly set
            {
                while (audiFlag)
                {
                    Console.WriteLine("Enter a number...\n1.Reserve Seat\n2.View Auditorium\n3.Report\n4.End Program");
                    userNum = convertInt(Console.ReadLine());
                    switch (userNum)
                    {
                        case 1: //Reserve Seat
                            userNum = userMenu2();
                            reservation(audis[userNum - 1]); //Reservation process begins here
                            break;
                        case 2: //Display Auditorium
                            userNum = userMenu2();
                            audis[userNum - 1].displayAudi();
                            break;
                        case 3: // Report
                            report(audis);
                            break;
                        case 4: //End Program
                            audiFlag = false;
                            break;
                    }
                    
                }
                /*** Output new auditorium information goes here ***/
                for (int count = 0; count < AUDITORIUMS; count++)
                    audis[count].audiOut(count + 1);
            }
        }
        static int userMenu2()
        {
            int userNum = 0;
            bool userFlag = false;
            while (!userFlag)
            {
                Console.WriteLine("Enter a number...");
                for (int count = 1; count <= AUDITORIUMS; count++) {
                    Console.WriteLine("{0}.Auditorium " + count, count);
                }
                userNum = convertInt(Console.ReadLine());
                if (userNum != -1)
                {
                    if (userNum > 0 && userNum <= AUDITORIUMS)
                        userFlag = true;
                    else
                        Console.WriteLine("Not a valid auditorium number");
                }
            }
            return userNum;
        }
        static int reservation(Audi _audi)
        {
            int ticketNum = 0;
            bool userFlag = false;
            string userInput = " ";
            List<int> seatIndex = new List<int>(); //Contains seat indexes for reservations

            _audi.displayAudi();
            while (!userFlag)
            {
                Console.WriteLine("Enter number of tickets being bought");
                ticketNum = convertInt(Console.ReadLine());
                if (ticketNum != -1)
                {
                    if (ticketNum > 0 && ticketNum <= _audi.getSeatCount())
                        userFlag = true;
                    else
                        Console.WriteLine("Not a valid number...(Number is less the zero or greater then seat number)");
                }
            }
            if (ticketNum <= _audi.getMaxX()) // if user bought more tickets then seats in a row skip consec step
            {
                Console.WriteLine("Consecutive seats? (Y for yes)");
                userInput = Console.ReadLine();
                userFlag = false;
            }
            if (userInput == "y" || userInput == "Y") //Consec reserve process
            {
                while (!userFlag)
                {
                    seatIndex.Add(getSeat(_audi, 1));
                    if ((_audi.getX(seatIndex[0]) + ticketNum) - 1 > _audi.getMaxX())
                        //If not enough seats from first seat - 1 ensures no overflow
                        Console.WriteLine("Not enough consecutive seats from first seat...");
                    else
                    {
                        for (int count = 1; count < ticketNum; count++) //Add seats consecutively via + 1 on each index
                            seatIndex.Add(seatIndex[0] + count);
                        userFlag = true;
                    }
                }
            }
            else
            { // Scatter reserve process
                for(int count = 0; count < ticketNum; count++)
                {
                    seatIndex.Add(getSeat(_audi, count + 1)); //Adds a singular index, bounds checked in getSeat()
                }
            }
            /*for (int count = 0; count < seatIndex.Count; count++) //***DEBUG CODE*** // 110-111
                Console.Write("{0},{1} ", obj.getX(seatIndex[count]), obj.getY(seatIndex[count])); */

            //Check if seats are open and then reserves them/Suggests best seat
            userFlag = false;
            for(int count = 0; count < seatIndex.Count; count++)
            {
                if (_audi.getSeatChar(seatIndex[count]) == '*')
                    userFlag = true;
            }
            if (!userFlag)
            {
                //Reserve process
                for (int count = 0; count < seatIndex.Count; count++)
                    _audi.reserveSeat(seatIndex[count]);
            }
            else  //Add a best seat suggestion
            {
                Console.WriteLine("Seat/Seats already reserved...");
            }


            for (int count = seatIndex.Count - 1; count >= 0; count--) //Clears seatIndex List
                seatIndex.Remove(count);
            return 1;
        }
        static int getSeat(Audi _audi,int count)
        {
            int seatIndex = 0;
            int seatX;
            int seatY;
            do
            {
                Console.Write("Enter Row number of seat number {0}: ", count);
                seatY = convertInt(Console.ReadLine());
            } while (seatY < 1 || seatY > _audi.getMaxY());
            do
            {
                Console.Write("Enter column number of seat number {0}: ", count);
                seatX = convertInt(Console.ReadLine());
            } while (seatX < 1 || seatX > _audi.getMaxX());
            seatIndex = (_audi.getMaxX() * (seatY - 1) + seatX) - 1;// Formula to get seat index I.E X(y-1) + x
            //Where X is the constant row length of an audi, y,x are user inputs
            Console.WriteLine("{0},{1}",_audi.getX(seatIndex),_audi.getY(seatIndex));
            return seatIndex;
        }
        static int convertInt(string x)//Attempts to convert a string to an int, returns -1 if unable
        {
            int num = 0;
            try
            {
                num = Convert.ToInt32(x);
            }
            catch (Exception)
            {
                Console.WriteLine("Not an integer...");
                return -1;
            }
            return num;
        }
        static void report(List<Audi> audis)
        {
            int totOpen = 0;
            int totClosed = 0;
            int openSeat = 0;
            int closedSeat = 0;

            Console.WriteLine("Auditoriums \t Open Seats \t Closed Seats \t Ticket Sales");
            for(int count = 0; count < audis.Count; count++)
            {
                Console.Write("Auditorium {0} \t   ",count+1);
                for(int subCount = 0; subCount < audis[count].getSeatCount(); subCount++)
                {
                    //Console.Write(subCount);
                    if (audis[count].getSeatChar(subCount) == '#')
                        openSeat++;
                    else
                        closedSeat++;
                }
                totOpen += openSeat;
                totClosed += closedSeat;
                Console.WriteLine(" {0} \t\t   {1} \t\t     ${2}",openSeat,closedSeat,(closedSeat*TICKPRICE));
                openSeat = 0;
                closedSeat = 0;

            }
        }
    }
}

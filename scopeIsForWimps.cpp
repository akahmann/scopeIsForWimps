/***********************************************************************
* Program:
*    Scope is for Wimps - Calendar Application
* Author:
*    Adam Kahmann
* Summary:
*    A simple application that will display the calendar month of a given
*    month and day. However, I must abide by these rules:
*
*    1. Can't pass parameters into any functions
*    2. Must use multiple functions
*    3. Can't use globabl variables
*    4. Can't use classes
*************************************************************************/
#include <cassert>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>

/*************************************************
 * THIS IS THE PSUEDOCODE OF THE TECHNIQUE I USED
 * TO FIND THE LOCATIONS OF ITEMS ON THE STACK:
 *
 * SET index -4 (use an already existing variable
 *               such as year or month)
 * LOOP until BREAK
 *    DISPLAY index
 *    IF stack location's value IS EQUAL hard coded value
 *       BREAK
 *    INCREMENT index
 *
 * The actual code I used is down below
 *************************************************/

// while(true)
// {
//    std::cout << index << std::endl;
//    if (*(&search + index) == 777)
//       break;
//    index++;
// }

/*************************************************
 * Prompt user for month and return it to main
 *************************************************/
int getMonth()
{
   int month;
   std::cout << "Enter Month: ";
   std::cin  >> month;
   assert(month > 0);
   assert(month < 13);
   return month;
}

/*************************************************
 * Prompt user for year and return it to main
 *************************************************/
int getYear()
{
   int year;
   std::cout << "Enter Year: ";
   std::cin  >> year;
   assert(year > 0);
   return year;
}

/*************************************************
 * Use Zeller's Congruence to find the offset and
 * return it
 *************************************************/
int getOffset()
{
   int search = 9999;
   int year;
   int month;

   //I found the month and year in these locations on the stack
   month = *(&search + 15);
   year = *(&search + 14);

   //Here we will use Zeller's Congruence to find the first calendar day
   if (month == 1)
   {
      month = 13;
      year--;
   }
   if (month == 2)
   {
      month = 14;
      year--;
   }
   int d = 1; //We want to find the first day of the month
   int m = month;
   int k = year % 100;
   int j = year / 100;
   int offset = d + 13*(m+1)/5 + k + k/4 + j/4 + 5*j;
   return offset % 7;
}

/*************************************************
 * Displays the name of the month number
 *************************************************/
void  displayMonthName()
{
   int search = 9999;
   int month = -4;

   //I found the month in this location on the stack
   month = *(&search + 37);

   switch (month)
   {
      case 1 :
         std::cout << "January";
         break;
      case 2 :
         std::cout << "February";
         break;
      case 3 :
         std::cout << "March";
         break;
      case 4 :
         std::cout << "April";
         break;
      case 5 :
         std::cout << "May";
         break;
      case 6 :
         std::cout << "June";
         break;
      case 7 :
         std::cout << "July";
         break;
      case 8 :
         std::cout << "August";
         break;
      case 9 :
         std::cout << "September";
         break;
      case 10 :
         std::cout << "October";
         break;
      case 11 :
         std::cout << "November";
         break;
      case 12 :
         std::cout << "December";
         break;
   }
}

/*************************************************
 * Returns whether the year was a leap year or
 * not
 *************************************************/
bool isLeapYear()
{
   int search = 9999;
   int year;

   year = *(&search + 23);

   return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

/*************************************************
 * Returns the number of days in a month
 *************************************************/
int getMonthDays()
{
   int search = 9999;
   int month;

   //I found the month on this location on the stack
   month = *(&search + 37);

   switch (month)
   {
      case 1 :
         return 31;
      case 2 :
         if (isLeapYear())
            return 29;
         else
            return 28;
      case 3 :
         return 31;
      case 4 :
         return 30;
      case 5 :
         return 31;
      case 6 :
         return 30;
      case 7 :
         return 31;
      case 8 :
         return 31;
      case 9 :
         return 30;
      case 10 :
         return 31;
      case 11 :
         return 30;
      case 12 :
         return 31;
   }
}

/*************************************************
 * Displays the calendar
 *************************************************/
void display()
{
   int search = 9999;
   int year = -4;
   int offset;
   int monthDays;

   //I found the offset and year in these locations on the stack
   offset = *(&search + 23);
   year = *(&search + 24);

   //DISPLAY HEADER
   std::cout << std::endl;
   displayMonthName();
   std::cout << ", " << year << std::endl;
   std::cout << std::setw(4) << "Su" << std::setw(4) << "Mo" << std::setw(4) << "Tu"
        << std::setw(4) << "We" << std::setw(4) << "Th" << std::setw(4) << "Fr"
        << std::setw(4) << "Sa" << std::endl;

   //DISPLAY CALENDAR MONTH
   int numDays = getMonthDays();

   for (int i = 0; i < (offset + 6) % 7; i++)
      std::cout << "    ";
   for (int day = 1; day <= numDays; day++)
   {
      std::cout << std::setw(4) << day;
      if ((offset + 6 + day) % 7 == 0)
         std::cout << std::endl;
      else if (day == numDays)
         std::cout << std::endl;
   }
}

int main()
{
   int month = getMonth();
   int year = getYear();
   int offset = getOffset();
   display();
   return 0;
}
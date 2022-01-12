// SurvivalGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

int rollDice();
int treat();
string decideTreat();
string decideTrick();
bool trickOrTreat(double probabilityOfTreat);
int getTreat(string treatName);


int health = 100;
int stamina = 100;
int staminaUse = 5;

float treatChance = .50;


int main()
{
    srand((unsigned)time(NULL));
    
    //#4. Variables
    char choice;
    int diceRoll = 0;
    fstream writefile("endStats.txt");
    string nameOfTreat;
    string STRING;
    int houseCount = 0;
    //string writeCandy;
    // (some comments were for testing, but I would like to keep them in just in case!)
    //ifstream readFile("endStats.txt");

    cout << "Try to survive!" << endl;

    do{
        //#7. Iterations/Loops: This is the main structure of the game that loops until health or stamina is below 0.
        cout << "health: " << health << endl;
        cout << "stamina: " << stamina << endl;
        cout << "treat chance: " << treatChance << endl;
        cout << "Press t to go trick-or-treating, "//8. Interaction. Player chooses which path to take.
            << "or r to rest. " << endl;

        //#8. Interaction: The player is asked to choose between trick or treating and resting.
        cin >> choice;

        switch (choice)//7.switch case
        {
        case 't':
           
            stamina = stamina - staminaUse;
           cout << "Trick or Treat!" << endl;
           
           if (trickOrTreat(treatChance) == true)
           {
               string writeCandy = "";

               houseCount++;

               cout << "You got a treat!" << endl;
               nameOfTreat = decideTreat();
               cout << "Your treat is " << nameOfTreat << endl;
               getTreat(nameOfTreat);
               
 //#6. File I/O: Used to keep track of the different types of candies by appending a text document to be read from later.
               writefile.open("endStats.txt",ios::app);
               if (writefile.is_open())
                    
               {
                   string writeCandy = nameOfTreat;
                   writefile << writeCandy;
                   writefile << "\n";
                   writefile.close();
               }
               else {
                   cout << "no file" << endl;
               }

           }
           else
           {
               houseCount++;
               cout << "You've been tricked!" << endl;
               cout << "Your trick is " << decideTrick() << endl;
           }
           break;
           
       case 'r':
           //#9. Control: This loop ensures that stamina will not be able to heal past 100.
           cout << "You build a fire and rest for a minute." << endl;
           cout << "Recover 20 stamina." << endl;
           if (stamina < 80)
           {
               stamina = stamina + 20;
           }
           else
           {
               stamina = 100;
           }
           break;
       

           
       default:
           cout << "invalid choice" << endl;
         
       }

        cout << endl << endl;
        cout << " *********************** " << endl;
        cout << " *********************** " << endl;
        cout << endl << endl;

    } while (health > 0 || stamina > 0);

    cout << "game over!" << endl;

    cout << "You visited " << houseCount << " houses." << endl;
    cout << "******************************" << endl;
    cout << "Candies collected:" << endl;
    writefile.open("endStats.txt");
    if(writefile.is_open())
       while (getline(writefile, STRING))
        {
         cout << STRING << endl; 
        }
        writefile.close();
    }
    


int rollDice()
{
    int roll = 0;

    roll = rand() % 20 + 1; //rand() % (max - min + 1) + min

    return roll;
}

string decideTrick()
{
    int trickNumber;
    trickNumber = rollDice();
    string trickName;

    switch (trickNumber)
    {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        health -= 10;
        trickName = "worst (1-5)";
        cout << "+20% chance for tricks" << endl;
        treatChance = treatChance - .20f;
        break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        health -= 7;
        trickName = "pretty bad";
        break;
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        health -= 5;
        trickName = "not bad";
        break;
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
        health -= 2;
        trickName = "best!";
        break;
    }
    return trickName;
}

string decideTreat()
{
    srand((unsigned)time(NULL));

    int treatNumber;
    treatNumber = rollDice();
    string treatName;
    int randomLoc = rand() % 4;

    //#5. Arrays are used to organize candy based on a tier list.
    string lowList[4] = { "Grandma strawberry hardcandy", "Just an apple", "raisins?!", "a toothbrush" };
    string midLowList[4] = { "Banana giggle jiggle","Dershey's Hug","twazzlers","Goobas!" };
    string midHighList[4] = { "Buttered Filange","Geeks Rope","Jolly Farmers","w&w's" };
    string highList[4] = { "Jackpot!","Costume Accessory","Race's Peanut Wheelz","Snackers Bar" };
      

    switch (treatNumber)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        //#5. A random number 0-3 is used to determine a random location in the array.
        treatName = lowList[randomLoc];
        if (health < 98)
        {
            health = health + 2;
        }
        else
        {
            health = 100;
        }
        break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        treatName = midLowList[randomLoc];
        if (health < 95)
        {
            health = health + 5;
        }
        else
        {
            health = 100;
        }
        break;
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        treatName = midHighList[randomLoc];
        if (health < 93)
        {
            health = health + 7;
        }
        else
        {
            health = 100;
        }
        break;
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
        if (health < 90)
        {
            health = health + 10;
        }
        else
        {
            health = 100;
        }
        treatName = highList[randomLoc];
        break;
    }
    return treatName;
}

bool trickOrTreat(double probabilityOfTreat)
{
    return rand() % 100 < (probabilityOfTreat * 100);
}

int getTreat(string treatName)
{
    string nameOfTreat = treatName;

    if (nameOfTreat == "Jackpot!"){
        cout << "Lucky!" << endl;
        health = health + 10;
        stamina = stamina + 10;
        treatChance = treatChance + .10f;
        staminaUse = staminaUse - 5;
    }
    else if (nameOfTreat == "Costume Accessory") {
        cout << "Looking cool! Extra chance for treats!" << endl;
        treatChance = treatChance + .05f;
    }
    else if (nameOfTreat == "Snackers Bar") {
        cout << "Yum!" << endl;
        cout << "+50 stamina" << endl;
        if (stamina > 49)
        {
            stamina = 100;
        }
        else {
            stamina = stamina + 50;
        }
    }
    else if (nameOfTreat == "Race's Peanut Wheelz") {
        cout << "Gotta go fast!" << endl;
        cout << "-5 stamina use" << endl;
        staminaUse = staminaUse - 5;
    }
    else{
        cout << "No extra effect" << endl;
    }
    

    return 0;
}
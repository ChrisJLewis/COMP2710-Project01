/*
* Christopher Lewis
* cjl0027
* project01.cpp
* External sources such as stockoverflow forums were used.
* Compile this by typing the following into console: g++ -o project01 project01.cpp
*/
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std;

class HighScores
{
	public:
   void newHighScore(int inputScore, string inputName);
   void printHighScores();
   void menuOption();
   HighScores();
	private:
   ifstream inStream;
   ofstream outStream;
   void writeHighScores();
   void readHighScores();
   bool readStringLine(string& outputString);
   const static int MAX_HIGHSCORES = 5;
   int score[MAX_HIGHSCORES];
   string scoreName[MAX_HIGHSCORES];
   int numberOfScores;
};

HighScores::HighScores()
{
	fill_n(score, MAX_HIGHSCORES, 0);
	fill_n(scoreName, MAX_HIGHSCORES, "");
}

void HighScores::menuOption()
{
	cout << "2) View top " << MAX_HIGHSCORES << " High Scores\n";
}

void HighScores::readHighScores()
{
   int index = 0;
   int dataInt;
   string dataString;
   inStream.open("highscores.txt");
	
	//If the file does not exist, nothing is to be changed
	//as our data arrays are already initialized.
   if (inStream.fail())
   {
      inStream.close();
      return;
   }
	
	//Actually capturing the data and placing them in local arrays
	//while checking if there is data to be collected and checking if
	//the arrays' max capacities will be exceeded. We are moreoever checking
	//for malicious data.
   while((inStream >> dataInt) && readStringLine(dataString) && index < MAX_HIGHSCORES)
   {
	   if (dataInt <= 0) 
	   {
		   break;
	   }
      score[index] = dataInt;
      scoreName[index++] = dataString;
   }
   inStream.close();
   
   //Returns the final index + 1 to tell our program 
   //how many scores to print.
   numberOfScores = index;
}

//Utility function for fixing the issue with mixing the '>>' operator 
//with getline. An extra getline is called to rid of the \n escape
//sequence that the '>>' leaves behind.
bool HighScores::readStringLine(string& outputString)
{
	getline(inStream, outputString);
	return getline(inStream, outputString, ',');
}

//Function for writing our new highscores to a file.
void HighScores::writeHighScores()
{
   outStream.open("highscores.txt");
   for (int i = 0; i < MAX_HIGHSCORES; i++)
   {
      outStream << score[i] << endl << scoreName[i] << ',' << endl;
   }
   outStream.close();
}

void HighScores::newHighScore(int inputScore, string inputName)
{
	int index = 0;
	//A check to see if the highscores file has been read.
	//If highscore.txt doesnt exist or is empty this runs anyway
	//without issue.
	readHighScores();
	
	//Finding where the new highscore is to be placed.
	while (inputScore < score[index] && score[index++] != 0) {;}
	
	//Check to see if the new highscore is within range of our 
	//top high scores.
	if (index < MAX_HIGHSCORES)
	{
		//If the high score is not at the bottom of the list we 
		//must shift all of the current highscores.
		if (index != (MAX_HIGHSCORES - 1))
		{
			for (int i = (MAX_HIGHSCORES - 1); i > index; i--)
			{
				score[i] = score[i - 1];
				scoreName[i] = scoreName[i - 1];
			}
		}
		score[index] = inputScore;
		scoreName[index] = inputName;
		writeHighScores();
	}
}


void HighScores::printHighScores()
{
	//Updates the current highscores incase of a change during the programs
	//runtime. (A new high score occurred)
	readHighScores();
   cout << "The top " << MAX_HIGHSCORES << " High Scores are:\n";
   for (int i = 0; i < numberOfScores; i++)
   {
		cout << scoreName[i] << " " << score[i] << endl;
   }
   cout << "-no more scores to show-\n\n";
}



//Class for handling user inputs in verifying that the user has in fact
//input a valid response.
class Menu
{
	public:
   int userSelect(int numberOfChoices);
};

//The acutal function for handling user inputs.
int Menu::userSelect(int numberOfChoices)
{
   int choice = -1; //Placeholder for user's choice to ensure it is within range
   cout << "\n\n\tPlease choose an action: ";
   cin >> choice;
   while (cin.fail() || choice > numberOfChoices || choice < 1)
   {
      cin.clear();
      cin.ignore(256, '\n');
      cout << "\tPlease choose an action: ";
      cin >> choice;
   }
   cout << "\n\n";
   return choice;
}

class Encounter
{
	
};


//Class for handling information regarding the player. This is mostly for retrieving the player's 
//current stats and affecting his stats.
class Player
{
	public:
   Player(int& startingHealth, int& startingMoney, int& startingIntl, int& maxHealthIn, int& maxIntlIn);
   Player();
   void affectTime(int& diference);
   void affectHealth(int& difference);
   void affectMoney(int& difference);
   void affectIntl(int& difference);
   void displayStats();
   int getHealth();
   int getMoney();
   int getIntl();
   int getTime();
	private:
   int health;
   int maxHealth;
   int money;
   int intl;
   int maxIntl;
   int time;
   string playerName;
};

Player::Player(int& startingHealth, int& startingMoney, int& startingIntl, int& maxHealthIn, int& maxIntlIn)
{
   health = startingHealth;
   maxHealth = maxHealthIn;
   maxIntl = maxIntlIn;
   money = startingMoney;
   intl = startingIntl;
   time = 30;
}


void Player::displayStats()
{
   cout << "You have:\n\nintelligence: " << intl << endl;
   cout << "time: " << time << endl;
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);
   cout << "money : $" << money << endl;
   cout.unsetf(ios::fixed);
   cout.unsetf(ios::showpoint);
}

//Function for affecting the player's time.
//int difference - the difference of health to be added.
//		It can be negative to show a subtraction of time.
void Player::affectTime(int& difference)
{
	time += difference;
}

//Function for affecting the player's health.
//int difference - the difference of health to be added.
//		It can be negative to show a subtraction of health.
void Player::affectHealth(int& difference)
{
   health += difference;
}

//Function for affecting the player's money.
//int difference - the difference of health to be added.
//		It can be negative to show a subtraction of money.
void Player::affectMoney(int& difference)
{
   money += difference;
}

//Function for affecting the player's intelligence
//int difference - the difference of health to be added. It can
//		           be negative to show a subtraction of intelligence.
void Player::affectIntl(int& difference) 
{
   intl += difference;
}

//Function for getting the time of the player
int Player::getTime()
{
	return time;
}

//Function for getting the player's current health.
int Player::getHealth() 
{
   return health;
}

//Function for getting the player's current money.
int Player::getMoney() 
{
   return money;
}


class System
{
	public:
	gameStart();
   void getName();
   int mainMenu();
	private:
   string playerName;
   Menu playerMenu;
   Encounter playerEncounter;
   HighScores highScores;
};


//Function for the system class that actually begins the game.
//returns - Score of the player
int System::gameStart()
{
	player gamePlayer;
	int score = 0;
	cout << "Entering the game...\n";
	gamePlayer.
}



void System::getName()
{
   cout << "\tWhat's your name? ";
   cin >> playerName;
   cout << "\n\n===========================================================\n|";
	
	//Alignment code for welcoming our user.
   int spaces = (57 - playerName.length()) / 2;
   for (int i = 0; i < spaces; i++) 
   {
      cout << " ";
   }
   cout << playerName;
	
	//A quick check to see if the playername has an
	//even number of characters to ensure proper alignment.
   if (playerName.length() % 2 == 0) 
   {
      spaces += 1;
   }
	
   for (int i = 0; i < spaces; i++)
   {
      cout << " ";
   }
	
   cout << "|\n===========================================================\n\n";
}

int System::mainMenu()
{	
   cout << "1) Start a New Game of Shelby Center and Dragons!\n";
   highScores.menuOption();
   cout << "3) Quit\n";
   switch (playerMenu.userSelect(3)) {
      case 1:	
         highScores.newHighScore(gameStart(), playerName);
         break;
      case 2: 
         highScores.printHighScores();
         break;
      default: 
         return 0;
         break;
   }
}

int main()
{
   System gameSystem;
   gameSystem.getName();
   while (gameSystem.mainMenu()) {;}
   return 0;
}
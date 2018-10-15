/*
* Course: CMPS 2143 - OOP
*
* Purpose: Play John Conway's Game of life and use inheritance to create 
* a world of cells
*
* @author Evan Jackson
* @version 1.0 10/14/18
* @github https://github.com/ejackson007/2143-OOP-Jackson
*/
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>

using namespace sf;

const int FRAMERATE = 1;

struct golCell {
  bool isAlive;
  int neighborCount;
  RectangleShape Rect;
  int Width;
  int Height;

  golCell(){
      Width = 10;
      Height = 10;
      Rect.setSize(sf::Vector2f(Width, Height));
      Rect.setFillColor(Color::Green);
      Rect.setOutlineColor(Color::Black);
      Rect.setOutlineThickness(1);
	  isAlive = 0;
	  neighborCount = 0;
  }

  void setCellPos(int x,int y){
      Rect.setPosition(x*Width, y*Height);
  }
};

struct gameOfLife{
    int Width;
    int Height;
	int genCounter;
	int arrayRow;
	int arrayColumn;
    RenderWindow Window;
    golCell** World;

	/**
	* Creates GameofLife
	* @param (0int width, int height) : size of the world
	* @return n/a
	*/
    gameOfLife(int width,int height) {
        Width = width;
        Height = height;
        Window.create(VideoMode(Width, Height), "Game of Life");

        World = new golCell*[height];

        for(int i=0;i<height;i++){
            World[i] = new golCell[width];
            for(int j=0;j<width;j++){
                World[i][j].setCellPos(i,j);
            }
        }
    }

	/**
	* Draws the world onto sfml
	* @param n/a
	* @return void
	*/
	void drawWorld()
	{
		//does not print on top
		Window.clear();
		for (int i = 0; i < Height; i++)
		{
			for (int j = 0; j < Width; j++)
			{
				// only prints off alive cells
				if (World[i][j].isAlive)
				Window.draw(World[j][i].Rect);
			}
		}
		Window.display();
	}

	/**
	* Takes the infile and puts it into the World
	* @param (infile): the infile defined from command line parameters
	* @return void
	*/
	void makeAlive(std::ifstream& infile)
	{
		std::string line = "";
		// Reads in first two numbers from first line
		infile >> arrayRow >> arrayColumn;

		for (int i = 0; i < arrayRow; i++)
		{
			// read an entire line in from file
			infile >> line;

			//Loop through the line and insert a char at a time into array
			for (int j = 0; j < arrayColumn; j++)
				// -48 to turn ascii to integer
				World[i][j].isAlive = line[j] - 48;
		}

	}

	/**
	* Goes through the array and counts the neighbors that are alive
	* @param n/a
	* @return void
	*/
	void checkNeighbors()
	{
		// goes through the 2d array
		for (int i = 0; i < Height; i++)
		{
			for (int j = 0; j < Width; j++)
			{
				//checks the three neighbors below the cell
				for (int y = j - 1, x = i - 1; x <= i + 1; x++)
				{
					if (x >= 0 && x < Height && y >= 0 && y < Width)
					{
						if (World[x][y].isAlive)
							World[i][j].neighborCount += 1;
					}
				}
				// checks the three neighbors above the cell
				for (int y = j + 1, x = i - 1; x <= i + 1; x++)
				{
					if (x >= 0 && x < Height && y >= 0 && y < Width)
					{
						 if (World[x][y].isAlive)
							 World[i][j].neighborCount += 1;
					}
						
				}
				// checks the neighbors in line, excluding itself from the count
				for (int y = j, x = i - 1; x <= i + 1; x++)
				{
					if (x >= 0 && x < Height && y >= 0 && y < Width && x != i)
					{
						if (World[x][y].isAlive)
							World[i][j].neighborCount += 1;
					}
				}

			}
		}
	}

	/**
	* updates World to the next generation. Goes through the list and checks the neighbor
	* count on each, applies the rules for the game accordingly, and resets the count to 0
	* @param n/a
	* @return void
	*/
	void updateWorld()
	{
		for (int i = 0; i < Height; i++)
		{
			for (int j = 0; j < Width; j++)
			{
				// rules are split with 3 being for alive cells
				// and 1 for dead ones
				if (World[i][j].isAlive)
				{
					// check rule for underpopulation
					if (World[i][j].neighborCount < 2)
					{
						World[i][j].isAlive = false;
						World[i][j].neighborCount = 0;
					}
					// check for overpoulation
					else if (World[i][j].neighborCount > 3)
					{
						World[i][j].isAlive = false;
						World[i][j].neighborCount = 0;
					}
					// needed to reset all neighbor counts to 0
					else
						World[i][j].neighborCount = 0;
				}
				else
				{
					// check neighbor count for dead ones
					if (World[i][j].neighborCount == 3)
					{
						World[i][j].isAlive = true;
						World[i][j].neighborCount = 0;
					}
					// check to make sure no errors occur
					else
					{
						World[i][j].isAlive = false;
						World[i][j].neighborCount = 0;
					}
				}
			}
		}
	}

	/**
	* Prints the contents of the world (sized of what was passed in)
	* @param (outfile): outfile defined in command line parameters
	* @return void
	*/
	void printWorld(std::ofstream & outfile)
	{
		for (int i = 0; i < arrayRow; i++)
		{
			for (int j = 0; j < arrayColumn; j++)
			{
				// since it is a bool, prints as 0's and 1's
				outfile << World[i][j].isAlive;
			}
			outfile << std::endl;
		}
	}

};

void printHeader(std::ofstream& outfile);
	
	/**
	* main function. Decides infile name with command line parameters
	* creats game of life window and object. Cycles through
	* 1000 generations counting neighbors, applying game of life
	* rules for each generation and "updating" the world
	* aka creating the new generation
	* @param (int argc, char **argv) the number of arguments, and strings of each argument
	* which are for the infile, outfile, and number of generations to loop
	* @return 0
	*/
	int main(int argc, char **argv) 
	{
		std::ifstream infile;
		std::ofstream outfile;

		gameOfLife Gol(500, 500);

		//Gol.frameRate = FRAMERATE;
		//Gol.frameCounter = 0;

		//Sets the counter for the 1st generation
		Gol.genCounter = 1;

		//Gol.openFiles(outfile, infile);
		outfile.open(argv[2]);
		infile.open(argv[1]);

		printHeader(outfile);

		Gol.makeAlive(infile);

		while (Gol.Window.isOpen())
		{
			//Event event;
			//while (Gol.Window.pollEvent(event))
				//for (int i = 0; i < Gol.frameRate + 1; i++)
	
			// 1000 at the time is a string, so it must be put into an int
			while (Gol.genCounter < std::stoi(argv[3]))
			{
				Gol.drawWorld();
				//if (event.type == Event::Closed)
					//Gol.Window.close();
				Gol.checkNeighbors();
				Gol.updateWorld();
				Gol.genCounter++;
				// used to monitor the generation count
				std::cout << Gol.genCounter << std::endl;
				// Set limiter to the system clock instead of loop to make it more
				// effective. Emulate a framerate. Learned from: 
			    //http://www.cplusplus.com/reference/thread/this_thread/sleep_for/
				std::this_thread::sleep_for(std::chrono::milliseconds(82));
			}
			Gol.Window.close();
					//}
				//}
			//}

		}

		Gol.printWorld(outfile);
		infile.close();
		outfile.close();
		return 0;
	}


	/**
	* Prints header for outfile
	* @param (outfile): outfile defined in command line parameters
	* @return void
	*/
	void printHeader(std::ofstream& outfile)
	{
		outfile << "@author Evan Jackson\n"
			<< "Version 1.0 10/14/18\n"
			<< "@github https://github.com/ejackson007/2143-OOP-Jackson\n"
			<< "Generation 1000 output\n\n";
	}

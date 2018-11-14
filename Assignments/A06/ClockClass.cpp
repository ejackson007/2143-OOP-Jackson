/*
* Course: CMPS 2143 - OOP
*
* Purpose: Creates a Clock Class to handle the counter
* moving, and bouncing off of the edges
*
* @author Evan Jackson
* @version 1.0 11/14/2018
* @github https://github.com/ejackson007/2143-OOP-Jackson
*/

//I had used the current time while debugging it,
//and Visual Studios gives a warning, so I had to 
//put in an ignore of the warning
#pragma warning(disable : 4996)
#include <SFML/Graphics.hpp>
#include "Group.h"
#include <ctime> 
#include <iostream> 

// https://www.sfml-dev.org/tutorials/2.5/system-time.php

const int WINDOWWIDTH = 500;
const int WINDOWHEIGHT = 500;

using namespace std;

class Counter{
private:
	sf::Clock clock;
	sf::Time start;
	sf::Time end;
	sf::Time elapsed;
	int xPosition, yPosition;
	
public:
	/**
	* Creates Counter
	* @param ()
	* @return n/a
	*/
	Counter()
	{
		start = sf::seconds(0);
		end = sf::seconds(0);
	}

	/**
	* Creates Counter
	* @param (int s, int e)
	* @return n/a
	*/
	Counter(int s, int e)
	{
		start = sf::seconds(s);
		end = sf::seconds(e);
	}

	/**
	* gets the elapsed time
	* @param ()
	* @return round(elapsed)
	*/
	int getElapsed()
	{
		elapsed = clock.getElapsedTime();
		 //used round function to get rid of decimals
		return round(elapsed.asSeconds());
	}

	/**
	* return the start time
	* @param ()
	* @return start of clock
	*/
	int getStart()
	{
		return start.asSeconds();
	}
	
	/**
	* set start time 
	* @param (int x)
	* @return void
	*/
	void setStart(int x)
	{
		start = sf::seconds(x);
	}

	/**
	* returns the end time
	* @param ()
	* @return end of clock
	*/
	int getEnd()
	{
		return end.asSeconds();
	}

	/**
	* set end time
	* @param (int x)
	* @return void
	*/
	void setEnd(int x)
	{
		end = sf::seconds(x);
	}


};

class Clock : public sf::Text{
private:
	/*time_t tt;
	struct tm * ti;*/
	sf::Font font;
	float xTranslation, yTranslation;
	Counter c;
	bool up;

public:
		/**
	* Creates Clock
	* @param ()
	* @return n/a
	*/
	Clock()
	{
		/*time(&tt);
		ti = localtime(&tt);*/
		// Lemon Milk sounds disgusting irl but it looks pretty cool and modern
		if (!font.loadFromFile("LemonMilk.otf"))
			std::cout << "Could not find font\n";

		setFont(font);
		setString("wow");
		setCharacterSize(15);
		setFillColor(sf::Color::White);
		setPosition(150, 367);
		//I set origin later so that it doesnt get messed up.
		//setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
		xTranslation = .05;
		yTranslation = .05;
		up = true;
	}

	
	/*void updatetime()
	{
		time(&tt);
		ti = localtime(&tt);
		setstring(asctime(ti));
	}*/
		/**
	* Sets the start and end time
	* @param (int start, int end)
	* @return n/a
	*/
	void setTime(int x, int y)
	{
		c.setStart(x);
		c.setEnd(y);
		if (x > y)
			up = false;
		else if (x == y)
			setString("CANNOT ENTER SAME NUMBERS");

		if (up)
			setString("Incrementing Clock: " + to_string(x));
		else
			setString("Decrementing Clock: " + to_string(x));
		setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);

	}
		/**
	* updates the text and handles translation
	* @param ()
	* @return n/a
	*/
	void updateText()
	{
		move(xTranslation, yTranslation);
		//If it hits any edge, it changes either the x or y's movement by *-1, flipping it
		if (getPosition().x  + (getLocalBounds().width / 2) >= WINDOWWIDTH || getPosition().x - (getLocalBounds().width / 2) <= 0)
			xTranslation *= -1;

		if (getPosition().y + (getLocalBounds().height / 2) >= WINDOWHEIGHT || getPosition().y - (getLocalBounds().height / 2) <= 0)
			yTranslation *= -1;

		//Set clock to updated time
		if (up)
			setString("Incrementing Clock: " + to_string(c.getStart() + c.getElapsed()));


		else if (!up)
			setString("Decrementing Clock: " + to_string(c.getStart() - c.getElapsed()));
	}

		/**
	* Checks if the program should close
	* @param ()
	* @return n/a
	*/
	bool checkClose()
	{
		if ((c.getStart() + c.getElapsed()) == c.getEnd() + 1)
			return true;
		else if ((c.getStart() - c.getElapsed()) == c.getEnd() - 1)
			return true;
		else
			return false;
	}

		/**
	* Sets color using color object
	* @param ()
	* @return n/a
	*/
	void settextColor(sf::Color c)
	{
		setColor(c);
	}

		/**
	* sets color using rgb values
	* @param ()
	* @return n/a
	*/
	void settextColor(int x, int y, int z)
	{
		setColor(sf::Color(x, y, z));
	}

	/*sf::Text getText()
	{
		return text;
	}*/
};

class BoundingBox : public sf::RectangleShape {
private:
	float width;
	float height;
	float xTranslation, yTranslation;

public:
		/**
	* Creates Bounding Box based on clock size
	* @param ()
	* @return n/a
	*/
	BoundingBox(sf::Text text)
	{
		//I get local bounde to find out how large the drawable is
		//Without needing variables in the drawable itself
		width = text.getLocalBounds().width;
		height = text.getLocalBounds().height;

		setSize(sf::Vector2f(width, height));
		setOrigin(width / 2, height / 2);
		setFillColor(sf::Color::Black);
		setOutlineColor(sf::Color::Yellow);
		//setOutlineThickness(20);
		setPosition(text.getPosition().x, text.getPosition().y);
		xTranslation = .05;
		yTranslation = .05;
	}

		/**
	* updates box position
	* @param ()
	* @return n/a
	*/
	void updateBox()
	{
		move(xTranslation, yTranslation);
		//updates the same as clock class
		if (getPosition().x + (width / 2) >= WINDOWWIDTH || getPosition().x - (width / 2) <= 0)
			xTranslation *= -1;

		if (getPosition().y + (height / 2) >= WINDOWHEIGHT || getPosition().y - (height / 2) <= 0)
			yTranslation *= -1;
	}


		/**
	* sets fill color using color object
	* @param ()
	* @return n/a
	*/
	void setboxColor(sf::Color c)
	{
		setFillColor(c);
	}

		/**
	* sets fill color using rgb values
	* @param ()
	* @return n/a
	*/
	void setboxColor(int x, int y, int z)
	{
		setFillColor(sf::Color(x, y, z));
	}
	
		/**
	* sets outline color using color object
	* @param ()
	* @return n/a
	*/
	void setOboxColor(sf::Color c)
	{
		setOutlineColor(c);
	}

		/**
	* sets outline color using rgb values
	* @param ()
	* @return n/a
	*/
	void setOboxColor(int x, int y, int z)
	{
		setOutlineColor(sf::Color(x, y, z));
	}

	/*sf::Text getText()
	{
		return text;
	}*/
};

	/**
	* Groups Drawables together
	* @param ()
	* @return n/a
	*/
class ClockClass : public Group {
private:
	float x;
	float y;
	float width;
	float height;
	float xTranslation;
	float yTranslation;
	//sf::RectangleShape boundingBox;
public:
	//Draw(sf::Text text)
	//{
	//	width = text.getLocalBounds().width;
	//	height = text.getLocalBounds().height;

	//	boundingBox.setSize(sf::Vector2f(width, height));
	//	boundingBox.setOrigin(width / 2, height / 2);
	//	boundingBox.setFillColor(sf::Color::Black);
	//	boundingBox.setOutlineColor(sf::Color::Yellow);
	//	boundingBox.setOutlineThickness(20);
	//	boundingBox.setPosition(WINDOWHEIGHT / 2, WINDOWWIDTH / 3);

	//	xTranslation = .1;
	//	yTranslation = .1;

	//	this->push_back(boundingBox);

	//}


	/*void updateDraw()
	{
		boundingBox.move(xTranslation, yTranslation);

		if (boundingBox.getPosition().x >= WINDOWWIDTH || boundingBox.getPosition().x <= 0)
			xTranslation *= -1;

		if (boundingBox.getPosition().y >= WINDOWHEIGHT || boundingBox.getPosition().y <= 0)
			yTranslation *= -1;
	}*/

};


int main()
{
	ClockClass G;
	Clock clock;
	//I have to read in Start and End first to get the correct size for the bounding box
	int start, end;
	cout << "START TIME: ";
	cin >> start;
	cout << "END TIME: ";
	cin >> end;

	clock.setTime(start, end);

	//Passes in clock so that I know how large to build it
	//could overload class to use other drawables as well
	BoundingBox box(clock);


	sf::RenderWindow window(sf::VideoMode(WINDOWHEIGHT, WINDOWWIDTH), "SFML works!");

	 while (window.isOpen())
    {
		// I will have to pop and re push to update
		// locations and text to i pop and push every loop
		G.push_back(box);
		G.push_back(clock);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		
        window.clear();
        window.draw(G);
		//window.draw(D);
        window.display();

		//D.updateDraw();
		//Must push and update so that Draw will have new values
		G.pop_back();
		G.pop_back();
		//clock.updateTime();
		box.updateBox();
		clock.updateText();
		//Check if they are equal and can close
		if (clock.checkClose())
			window.close();

    }

	//system("pause");
	return 0; 
}

#include <SFML/Graphics.hpp>

using namespace sf;

const int FRAMERATE = 20;

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
  }

  void setCellPos(int x,int y){
      Rect.setPosition(x*Width, y*Height);
  }

};

struct gameOfLife{
    int Width;
    int Height;
	int frameRate;
	int frameCounter;
    RenderWindow Window;
    golCell** World;
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

	void drawWorld()
	{
		Window.clear();
		for (int i = 0; i < Height; i++)
		{
			for (int j = 0; j < Width; j++)
			{
				Window.draw(World[i][j].Rect);
			}
		}
		Window.display();
	}
};



int main(){

    gameOfLife Gol(1000,1000);

	Gol.frameRate = FRAMERATE;
	Gol.frameCounter = 0;

    while (Gol.Window.isOpen())
    {
        Event event;
        while (Gol.Window.pollEvent(event))
        {
			// used a for loop and if statement to slow the drawing of the the window
			// to the frameRate int. The int is defined with a constant to make the
			// possible reuse and changes easier.
			for (int i = 0; i < Gol.frameRate + 1; i++)
			{
				if (i == Gol.frameRate)
				{
					Gol.drawWorld();
					if (event.type == Event::Closed)
						Gol.Window.close();
					Gol.frameCounter++;
				}
			}
        }

    }

    return 0;
}
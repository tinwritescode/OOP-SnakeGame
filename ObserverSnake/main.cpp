#include "Board.h"
#include "Snake.h"
#include "Fruit.h"

#include <ctime>
#include <conio.h>

int main() {
	//TODO: Make creatory factory for each object

	// Create time seed
	srand(static_cast<unsigned int>(time(0)));

	// Create objects
	Board* board = new Board(30, 20);
	//Snake* snake = dynamic_cast<Snake*>(board->addObject(ObjectType::snake, 10, 10)); // snake is loaded from Map file
	Snake* snake = nullptr;

	// Load map (wall, snake)
	board->loadMap("Map2.dat", snake);
	
	// Create fruit
	int randomX, randomY;
	do {
		randomX = rand() % board->getWidth();
		randomY = rand() % board->getHeight();
	} while (board->isOccupied(randomX, randomY));

	Fruit* fruit = dynamic_cast<Fruit*>(board->addObject(ObjectType::fruit, randomX, randomY));
	fruit->paint();

	// Game loop
	char op;
	Fruit* destinateFruit = nullptr;

	while (!snake->isdead()) {
		// On keypressed
		if (_kbhit())
		{
			// Create a new head segment, delete tail segment
			op = tolower(_getch());
			snake->turnHead(Direction(op));
		}

		snake->move();
		
		// Handle collision
		if (snake->bodyCollision()) {
			snake->setDead();
		}
		else if (snake->wallCollision()) {
			snake->setDead();
		}
		else if (destinateFruit = snake->matchFruit()) {
			snake->eatFruit(destinateFruit);
		}
		
		// if snake get over border
		if (snake->getX() > board->getWidth()) {
			snake->setPos(0, snake->getY());
		}
		else if (snake->getX() < 0) {
			snake->setPos(board->getWidth(), snake->getY());
		}
		else if (snake->getY() > board->getHeight()) {
			snake->setPos(snake->getX(), 0);
		}
		else if (snake->getY() < 0) {
			snake->setPos(snake->getX(), board->getHeight());
		}

		// Paint snake
		snake->paint();	

		// Time for the next move
		Sleep(150);
	}

	std::cout << "Snake dead." << std::endl;

	delete board;
	return 0;
}
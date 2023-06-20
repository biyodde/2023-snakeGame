#include "snakeGame.h"

int input()
{
	int input = getch();
	refresh();
	endwin();
	clear();

	return input;
}

int ready()
{
  initscr();
	noecho();
	move(10, 1);
	printw("Are you ready? (y/n)");
	return input();
}

int playAgain()
{
	move(10, 4);
	printw("  try again?  ");
  move(11, 3);
  printw("     (y/n)     ");
	return input();
}

int main ()
{
	if (ready() == 'y')
	do {
		{
			snakeGame game;
			game.playGame();
		}
	}
	while (playAgain() == 'y');
	return 0;
}

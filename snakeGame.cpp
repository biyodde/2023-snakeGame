#include "snakeGame.h"

position::position(int col, int row)
{
	x = col;
	y = row;
}

position::position()
{
	x = 0;
	y = 0;
}

snakeGame::snakeGame()
{
	growth.x = 0;
	growth.y = 0;
	poison.x = 0;
	poison.y = 0;
	direction = 'l';
	srand(time(NULL));

  initscr();
	nodelay(stdscr,TRUE);
	keypad(stdscr, true);
	noecho();
	curs_set(0);

	posGrowth();
	posPoison();
	makeMap();
	makeSnake();
	printScore();
	printMission();

	refresh();
}

snakeGame::~snakeGame()
{
	nodelay(stdscr, false);
	getch();
	endwin();
}

void snakeGame::makeMap()
{
	for (int i = 0; i < wall; i++)
	{
		move(0, i);
		addch('1');
	}

	for (int i = 0; i < wall; i++)
	{
		move(wall - 1, i);
		addch('1');
	}

	for (int i = 0; i < wall; i++)
	{
		move(i, 0);
		addch('1');
	}

	for (int i = 0; i < wall; i++)
	{
		move(i, wall - 1);
		addch('1');
	}
  move(0, 0);
  addch('2');
  move(0, wall - 1);
  addch('2');
  move(wall - 1, 0);
  addch('2');
  move(wall - 1, wall - 1);
  addch('2');
	return;
}

void snakeGame::makeSnake()
{
	for (int i = 0; i < 3; i++)
	{
		snake.push_back(position(10+i, 10));
	}

  move(snake[0].y, snake[0].x);
  addch(head);
	for (int i = 1; i < snake.size(); i++)
	{
		move(snake[i].y, snake[i].x);
		addch(body);
	}
	return;
}

void snakeGame::moveSnake()
{
	int KeyPressed = getch();
	switch(KeyPressed)
	{
		case KEY_LEFT:
			if (direction == 'r')
      {
        dirFail = true;
      }
      else
      {
        direction = 'l';
      }
			break;
		case KEY_RIGHT:
			if (direction == 'l')
      {
        dirFail = true;
      }
      else
      {
        direction = 'r';
      }
			break;
		case KEY_UP:
			if (direction == 'd')
      {
        dirFail = true;
      }
      else
      {
        direction = 'u';
      }
			break;
		case KEY_DOWN:
			if (direction == 'u')
      {
        dirFail = true;
      }
      else
      {
        direction = 'd';
      }
			break;
	}

	if (!eatgrowth)
	{
		move(snake[snake.size()-1].y, snake[snake.size()-1].x);
		printw(" ");
		refresh();
		snake.pop_back();
	}

	if (eatPoison)
	{
		move(snake[snake.size()-1].y, snake[snake.size()-1].x);
		printw(" ");
		refresh();
		snake.pop_back();
	}

	if (direction == 'l')
  {
    snake.insert(snake.begin(), position(snake[0].x-1, snake[0].y));
  }
	else if (direction == 'r')
  {
	  snake.insert(snake.begin(), position(snake[0].x+1, snake[0].y));
  }
	else if (direction == 'u')
  {
	  snake.insert(snake.begin(), position(snake[0].x, snake[0].y-1));
  }
	else if (direction == 'd')
  {
	  snake.insert(snake.begin(), position(snake[0].x, snake[0].y+1));
  }

	move(snake[0].y, snake[0].x);
	addch(head);
  move(snake[1].y, snake[1].x);
	addch(body);
	refresh();
	return;
}

void snakeGame::printScore()
{
	move(0, 22);
	printw("Score Board");
	move(1, 22);
	printw("B : %d / %d", nowsize, bestsize);
	move(2, 22);
	printw("+ : %d", growthcnt);
	move(3, 22);
	printw("- : %d", poisoncnt);
	move(4, 22);
	printw("G : ");
	return;
}

void snakeGame::printMission()
{
	move(7, 22);
	printw("Mission");
	move(8, 22);
	printw("B : 10");
	move(8, 29);
	if(bestsize >= 10)
		printw("(v)");
	else
		printw("( )");
	move(9, 22);
	printw("+ : 5");
	move(9, 28);
	if(growthcnt >= 5)
		printw("(v)");
	else
		printw("( )");
	move(10, 22);
	printw("- : 2");
	move(10, 28);
	if(poisoncnt >= 2)
		printw("(v)");
	else
		printw("( )");
	move(11, 22);
	printw("G : 1");
	return;
}

void snakeGame::posGrowth()
{
	while(1)
	{
		int posx = rand()%wall+1;
		int posy = rand()%wall+1;

		for (int i = 0; i < snake.size(); i++)
		{
			if (snake[i].x == posx && snake[i].y == posy)
			{
				continue;
			}
		}

		if (posx >= wall-1 || posy >= wall-1)
		{
			continue;
		}

		growth.x = posx;
		growth.y = posy;
		break;
	}

	move(growth.y, growth.x);
	addch(growthshape);
	refresh();
}

void snakeGame::posPoison()
{
	while(1)
	{
		int posx = rand()%wall+1;
		int posy = rand()%wall+1;

		for (int i = 0; i < snake.size(); i++)
		{
			if (snake[i].x == posx && snake[i].y == posy)
			{
				continue;
			}
		}

		if (posx >= wall-1 || posy >= wall-1)
		{
			continue;
		}

		poison.x = posx;
		poison.y = posy;
		break;
	}

	move(poison.y, poison.x);
	addch(poisonshape);
	refresh();
}

bool snakeGame::getGrowth()
{
	if (snake[0].x == growth.x && snake[0].y == growth.y)
	{
		posGrowth();
		growthcnt++;
		nowsize++;
		if(bestsize <= nowsize)
		{
			bestsize = nowsize;
		}
		printScore();
		printMission();

		return eatgrowth = true;
	}
	else
	{
		return eatgrowth = false;
	}
	return eatgrowth;
}

bool snakeGame::getPoison()
{
	if (snake[0].x == poison.x && snake[0].y == poison.y)
	{
		posPoison();
		poisoncnt++;
		nowsize--;
		printScore();
		printMission();

		return eatPoison = true;
	}
	else
	{
		return eatPoison = false;
	}
	return eatPoison;
}

bool snakeGame::fail()
{
	if (snake[0].x == 0 || snake[0].x == wall - 1 || snake[0].y == 0 || snake[0].y == wall - 1)
	{
		return true;
	}

	for (int i = 2; i < snake.size(); i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
		{
			return true;
		}
	}

	if (snake.size() < 3)
	{
		return true;
	}

  if(dirFail)
  {
    return true;
  }

	return false;
}

bool snakeGame::clear()
{
  if(bestsize >= 10 && growthcnt >= 5 && poisoncnt >= 2)
  {
    return true;
  }
  return false;
}

void snakeGame::playGame()
{
  while(1)
  {
      if(fail())
      {
        move(10, 4);
        printw("  GAME OVER  ");
        move(11, 2);
        printw(" press any key.. ");
        break;
      }
      if(clear())
      {
        move(10, 3);
        printw("  GAME CLEAR!  ");
        move(11, 2);
        printw(" press any key.. ");
        break;
      }

      getGrowth();
      getPoison();
      moveSnake();

      usleep(150000); // delay
      }
}

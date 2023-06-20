#include <iostream>
#include <ncurses.h>
#include <vector>
#include <unistd.h>
#ifndef _SNAKEGAME_H_
#define _SNAKEGAME_H_

using namespace std;

struct position
{
	int x, y;
	position(int col, int row);
	position();
};

class snakeGame
{
private:
	int nowsize = 3, bestsize = 3, wall = 21, growthcnt = 0, poisoncnt = 0;
	char direction, head = 'o', body = 'x', growthshape = '*', poisonshape = '#';
	bool eatgrowth = false;
	bool eatPoison = false;
  bool dirFail = false;
	position growth;
	position poison;
	std::vector<position> snake;

	void makeMap();
	void makeSnake();
  void moveSnake();
	void printScore();
	void printMission();
	void posGrowth();
	void posPoison();
  bool getGrowth();
	bool getPoison();
	bool fail();
  bool clear();

public:
	snakeGame();
	~snakeGame();
	void playGame();
};

#endif

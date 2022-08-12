#ifndef GUARD_Game2048_h
#define GUARD_Game2048_h

#include "Board.h"

class Game2048{
public:
	Game2048():board(),begin_time(time(NULL)), end_time(time(NULL)) {};
	explicit Game2048(int num) :board(num), begin_time(time(NULL)), end_time(time(NULL)){};
	~Game2048();

	char Move(std::istream& in);
	void Merge(char c);
	void Add();
	void Display();
	bool Moveable();

	int Score();

private:
	Board board;
	const time_t begin_time;
	time_t end_time;
};

#endif
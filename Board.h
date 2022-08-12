#ifndef GUARD_Board_h
#define GUARD_Board_h

#include <vector>
#include <ctime>
#include <random>

class Board{
public:
	Board();
	explicit Board(int num);
	long long Score();
	void Display();
	void Add();
	bool Full();
	void Move(char c);
	void Merge(char c);
	bool Moveable();

private:
	// data
	// the grid size of board will be N * N, and N is 4 by default.
	const int N;
	std::vector<std::vector<int> > grids;
	long long score;

	// function
	void Move_up();
	void Merge_up();
	void up_down();
	void transposition();
};

#endif
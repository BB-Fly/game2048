#include "Game2048.h"
#include <iostream>
#include <fstream>
#include <string>

using std::cout;		using std::cin;
using std::vector;		using std::endl;
using std::string;		using std::domain_error;
using std::istream;		using std::ofstream;
using std::to_string;

Game2048::~Game2048() {
	// concerning time
	end_time = time(NULL);
	double delta = difftime(end_time,begin_time);
	const int size = 64;
	char local[size];
	ctime_s(local,size,&begin_time);
	string local_time(local);
	for (auto i = local_time.begin(); i != local_time.end();) {
		if (*i == '\n') {
			local_time.erase(i);
		}
		else {
			i++;
		}
	}

	// concerning f_out
	string f_name = "Game2048.csv";
	ofstream f_out(f_name,ofstream::app);
	string s = local_time + ',' + to_string(delta) + ',' + to_string(Score());
	f_out << s << endl;
}

char Game2048::Move(istream& in) {
	if (!in) {
		throw domain_error("Input error! game quit!");
	}
	char tmp;
	string s;
	in >> s;
	tmp = s[0];
	
	if (tmp == 'u' || tmp == 'd' || tmp == 'l' || tmp == 'r' || tmp=='q') {
		return tmp;
	}
	in.clear();
	return '?';
}

int Game2048::Score() {
	return board.Score();
}

void Game2048::Merge(char c) {
	board.Merge(c);
}

void Game2048::Add() {
	board.Add();
}

void Game2048::Display() {
	board.Display();
}

bool Game2048::Moveable() {
	return board.Moveable();
}

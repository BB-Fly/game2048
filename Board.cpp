#include "Board.h"
#include<ctime>
#include<random>
#include<iostream>
#include<string>
#include<stdexcept>

using std::cout;		using std::cin;
using std::vector;		using std::endl;
using std::string;		using std::domain_error;
using std::pair;		using std::make_pair;
using std::swap;

// private function:
void Board::Move_up() {
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = i; k >= 1; k--) {
				if (grids[k][j] != 0 && grids[k - 1][j] == 0) {
					grids[k - 1][j] = grids[k][j];
					grids[k][j] = 0;
					continue;
				}
				break;
			}
		}
	}
}

void Board::Merge_up() {
	Move_up();
	bool tmp = false;
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (grids[i][j] != 0 && grids[i][j] == grids[i - 1][j]) {
				grids[i - 1][j] *= 2;
				grids[i][j] = 0;
				score += grids[i - 1][j];
				tmp = true;
			}
		}
	}
	if (tmp) {
		Merge_up();
	}
}

void Board::up_down(){
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N / 2; i++) {
			swap(grids[i][j],grids[N-i-1][j]);
		}
	}
	return;
}

void Board::transposition() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < i; j++) {
			swap(grids[i][j], grids[j][i]);
		}
	}
	return;
}


// public function:
Board::Board() : N(4), grids(4, std::vector<int>(4, 0)), score(0) {
	int first_i = rand() % N, first_j = rand() % N;
	int second_i = rand() % N, second_j = rand() % N;

	while (first_i == second_i && first_j == second_j) {
		second_i = rand() % N, second_j = rand() % N;
	}

	grids[first_i][first_j] = 2;
	grids[second_i][second_j] = 2;
}

Board::Board(int num) :N(num), grids(num, std::vector<int>(num, 0)), score(0) {
	int first_i = rand() % N, first_j = rand() % N;
	int second_i = rand() % N, second_j = rand() % N;

	while (first_i == second_i && first_j == second_j) {
		second_i = rand() % N, second_j = rand() % N;
	}

	grids[first_i][first_j] = 2;
	grids[second_i][second_j] = 2;
}

long long Board::Score() {
	return this->score;
}

void Board::Display() {

	// the top boeder line;
	cout << "\n|";
	for(int i=0;i<this->N;i++)
		cout << "-----|";
	cout << "\n";

	// the body
	for (int i = 0; i < this->N; i++) {
		cout << "|";
		for (int j = 0; j < this->N; j++) {
			if (grids[i][j] == 0) {
				cout << "     |";
			}
			else if(grids[i][j]<10) {
				cout << "  " << grids[i][j] << "  |";
			}
			else if (grids[i][j] < 100) {
				cout << " " << grids[i][j] << "  |";
			}
			else if (grids[i][j] < 1000) {
				cout << " " << grids[i][j] << " |";
			}
			else if (grids[i][j] < 10000) {
				cout << grids[i][j] << " |";
			}
			else if (grids[i][j] < 100000) {
				cout << grids[i][j] << "|";
			}
			else {
				cout << "2^17 |";
			}
		}

		cout << "\n|";
		for (int i = 0; i < this->N; i++)
			cout << "-----|";
		cout << "\n";
	}

	cout << "your score: " << this->score << "\n";
	cout << "(¡ü:u) (¡ý:d) (¡û:l) (¡ú:r) (quit:q):";
}

void Board::Add() {
	if (Board::Full()) {
		return;
	}

	vector<pair<int, int> > candidates;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (grids[i][j] == 0) {
				candidates.push_back(make_pair(i,j));
			}
		}
	}
	int target = rand()%candidates.size();

	grids[candidates[target].first][candidates[target].second] = rand() % 5 == 0 ? 4 : 2;

	return;
}

void Board::Move(char c) {
	switch(c) {
	case 'u': {
		Move_up();
		break;
	}
	case 'd': {
		up_down();
		Move_up();
		up_down();
		break;
	}
	case 'l': {
		transposition();
		Move_up();
		transposition();
		break;
	}
	case 'r': {
		transposition();
		up_down();
		Move_up();
		up_down();
		transposition();
		break;
	}
	default: {
		throw domain_error("Move failed! invalid character!");
	}
	}
	return;
};

void Board::Merge(char c) {
	switch (c) {
	case 'u': {
		Merge_up();
		break;
	}
	case 'd': {
		up_down();
		Merge_up();
		up_down();
		break;
	}
	case 'l': {
		transposition();
		Merge_up();
		transposition();
		break;
	}
	case 'r': {
		transposition();
		up_down();
		Merge_up();
		up_down();
		transposition();
		break;
	}
	default: {
		throw domain_error("Merge failed! invalid character!");
	}
	}
	return;
}

bool Board::Full() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (grids[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}

bool Board::Moveable() {
	if (!Full()) {
		return true;
	}
	for (int i = 0; i < N-1; i++) {
		for (int j = 0; j < N-1; j++) {
			if (grids[i][j] == grids[i + 1][j] || grids[i][j] == grids[i][j + 1]) {
				return true;
			}
		}
	}
	for (int i = 0; i < N - 1; i++) {
		if (grids[i][N-1] == grids[i + 1][N-1] || grids[N-1][i]==grids[N-1][i+1]) {
			return true;
		}
	}
	return false;
}
#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <vector>
#include <queue>

class Position;
using Positions = std::vector<Position>;
using QueueOfPosition = std::queue<Position>;
using Positions2D = std::vector<Positions>;
using PairOfPositions = std::pair<Position, Position>;


class Position
{
public:
	Position(int i =-1, int j =-1);
	void setI(int i);
	void setJ(int j);
	void setFromIndex(int index, int row, int col);
	int getIndex(int row, int col) const;
	int getI() const;
	int getJ() const;
	~Position();
	bool operator < (const Position& other) const;
	bool operator == (const Position& other) const;
	Position& Position::operator=(const Position & other);
	
private:
	int m_i;
	int m_j;
};
#endif POSITION_H
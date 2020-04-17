#include "Position.h"

Position::Position(int i, int j)
	:m_i(i)
	,m_j(j)
{
}

void Position::setI(int i)
{
	m_i = i;
}

void Position::setJ(int j)
{
	m_j = j;
}

void Position::setFromIndex(int index, int row, int col)
{
	m_i = index / col;
	m_j = index % col;
}

int Position::getIndex(int row, int col) const
{
	return m_i*col + m_j;
}

int Position::getI() const
{
	return m_i;
}

int Position::getJ() const
{
	return m_j;
}

Position::~Position()
{
}

bool Position::operator<(const Position & other) const
{
	if (m_i < other.m_i) {
		return true;
	}
	else if (m_i == other.m_i && m_j < other.m_j) {
		return true;
	}
	return false;	
}

bool Position::operator==(const Position & other) const
{
	if (m_i == other.m_i && m_j == other.m_j) {
		return true;
	}
	return false;
}

Position & Position::operator=(const Position & other)
{
	m_i = other.m_i;
	m_j = other.m_j;
	return *this;
}

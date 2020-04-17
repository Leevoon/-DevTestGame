#ifndef OBJECTIVES_H
#define OBJECTIVES_H

#include "Item.h"
#include "GameStatus.h"
#include <map>

class Objectives
{
public:
	Objectives();
	void setMoveCount(int i);
	void decreaseMoveCount();
	int getMoveCount() const;
	void setObjectives(const ItemType & itemType, int count);
	void decreaseObjectiveCount(const ItemType & itemType, int count);
	int getCountByType(const ItemType &itemType);
	ItemTypes getObjectives();
	GameStatus getGameStatus();
private:
	std::map<ItemType, int> m_itemTypeToCountMapping;
	int m_moveCount;
};
#endif // !OBJECTIVES_H

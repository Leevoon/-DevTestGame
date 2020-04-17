#ifndef BONUSITEM_H
#define BONUSITEM_H
#include "Item.h"

class BonusItem:public Item
{
public:
	BonusItem(int i, int j);
	static ItemPtr getBonusItem(const Positions & positions);
private:
	static bool isHorizontal(const Positions & position);
	static bool isVertical(const Positions & position);
};

#endif // !BONUSITEM_H

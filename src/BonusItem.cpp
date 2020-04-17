#include "BonusItem.h"
#include "GeneralInformation.h"

BonusItem::BonusItem(int i, int j)
	:Item(i,j, GeneralInformation::getInstance()->getBonusItems())
{

}

ItemPtr BonusItem::getBonusItem(const Positions & positions)
{
	ItemPtr resultPtr =new BonusItem(-1,-1);
	if (positions.size() != 4) {
		resultPtr->setType(ItemType::eUnknownType);
		return resultPtr;
	}
	bool isHorizontal = BonusItem::isHorizontal(positions);
	bool isVertical = BonusItem::isVertical(positions);
	if (isHorizontal && !isVertical) {
		resultPtr->setType(ItemType::eHoriziontalBomb);
	}
	else if(!isHorizontal && isVertical){
		resultPtr->setType(ItemType::eVerticalBomb);
	}
	else if (!isHorizontal && !isVertical) {
		resultPtr->setType(ItemType::eBomb);
	}
	else {
		resultPtr->setType(ItemType::eUnknownType);
	}
	return resultPtr;
}

bool BonusItem::isHorizontal(const Positions & positions)
{
	if (positions.size() == 0) {
		return false;
	}
	int j = positions.front().getJ();
	for (auto const & pos : positions) {
		if (pos.getJ() != j) {
			return false;
		}
	}
	return true;
}

bool BonusItem::isVertical(const Positions & positions)
{
	if (positions.size() == 0) {
		return false;
	}
	int i = positions.front().getI();
	for (auto const & pos : positions) {
		if (pos.getI() != i) {
			return false;
		}
	}
	return true;
}

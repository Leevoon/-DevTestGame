#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <vector>

#include "Position.h"

enum ItemType
{
	eBlue,
	eGreen,
	eOrange,
	eRed,
	eViolet,
	eVerticalBomb,
	eHoriziontalBomb,
	eBomb,
	eUnknownType,
};

class Item;

//pointer of Item
using ItemPtr = Item * ;
//vector of Item
using Items = std::vector<Item>;
//vector of ItemType
using ItemTypes = std::vector<ItemType>;
//vector of Item pointers
using ItemPtrs = std::vector<ItemPtr>;

class Item
{
public:
	Item(int i, int j, const ItemTypes & itemTypes = ItemTypes{ eBlue,
		eGreen,
		eOrange,
		eRed,
		eViolet});
	Item(const Item &other);
	Item(const ItemType  &type);

	/*generateNewType, The function will generate new item type
	*/
	void generateNewType();
	void setType(const ItemType  &type);
	ItemType getType() const;
	void setRow(int row);
	int getRow() const;
	void setCol(int col);
	int getCol() const;
	Position getPosition() const;
	~Item();
private:
	Position m_position;
	ItemType m_type;
};
#endif // !ITEM_H

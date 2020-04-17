#include "Item.h"
#include <random>
#include "GeneralInformation.h"

Item::Item(int i, int j, const ItemTypes & itemTypes)
	: m_position(i,j)
{
	std::random_device rd;
	static std::mt19937 rng(rd());
	static std::uniform_int_distribution<int> uid(0, int(itemTypes.size()-1)); 
	int pos = uid(rng);
	m_type=itemTypes.at(pos%itemTypes.size());
	
}

Item::Item(const Item & other)
{
	m_type = other.m_type;
}

Item::Item(const ItemType &type)
{
	m_type = type;
}

void Item::generateNewType()
{
	auto currentItems = GeneralInformation::getInstance()->getCurrentOrdinaryItems();
	//m_type = static_cast<ItemType>(std::rand() % GeneralInformation::getInstance()->getCurrentOrdinaryItems().size());
	std::random_device rd;
	static std::mt19937 rng(rd());
	static std::uniform_int_distribution<int> uid(0, int(currentItems.size() - 1));
	int pos = uid(rng);
	m_type = currentItems.at(pos % currentItems.size());
}

void Item::setType(const ItemType & type)
{
	m_type = type;
}

ItemType Item::getType() const
{
	return m_type;
}

void Item::setRow(int row)
{
	m_position.setI(row);
}

int Item::getRow() const
{
	return m_position.getI();
}

void Item::setCol(int col)
{
	m_position.setJ(col);
}

int Item::getCol() const
{
	return m_position.getJ();
}

Position Item::getPosition() const
{
	return m_position;
}

Item::~Item()
{
}

#include "SimpleBoard.h"
#include "OrdinaryItem.h"

SimpleBoard::SimpleBoard(int row, int col, int figuresCount)
	:m_row(row)
	,m_col(col)
	,m_figuresCount(figuresCount)
{
	initializeWithEmptyValues();
}

void SimpleBoard::setItems(const ItemPtrs & items)
{
	m_items = items;
}

void SimpleBoard::setItem(const ItemPtr & item)
{
	m_items.at(item->getPosition().getIndex(m_row, m_col)) = item;
}

ItemPtrs SimpleBoard::getItems() const
{
	return m_items;
}

ItemType SimpleBoard::getItemTypeByPosition(const Position & position)
{
	return m_items.at(position.getIndex(m_row, m_col))->getType();
}

void SimpleBoard::swap(int firstPos, int secondPos)
{
	std::swap(m_items.at(firstPos), m_items.at(secondPos));
}

void SimpleBoard::update()
{
	for (auto & item : m_items) {
		delete item;
	}
	m_items.clear();
	initialize();
}

void SimpleBoard::updateItemByPosition(const Position & position)
{
	m_items.at(position.getIndex(m_row, m_col))->generateNewType();
}

void SimpleBoard::clearMatchings(const Positions & positions)
{
	for (auto const &pos : positions) {
		if (m_items.at(pos.getIndex(m_row, m_col))->getType() < 5) {
			m_items.at(pos.getIndex(m_row, m_col))->setType(ItemType::eUnknownType);
		}
	}
}

Positions SimpleBoard::clearBonusMatchings(const Position & position)
{
	Positions deletedItems;
	QueueOfPosition bonusItems;
	
	clearBonusMatchingsHelper(position, deletedItems, bonusItems);
	deletedItems.push_back(position);
	while (bonusItems.size())
	{
		auto element = bonusItems.front();
		bonusItems.pop();
		clearBonusMatchingsHelper(element, deletedItems, bonusItems);
	}
	return deletedItems;
}

void SimpleBoard::regulate(const Positions & positions)
{
	Positions poses = positions;
	std::sort(poses.begin(), poses.end());
	for (auto const & pos : poses) {
		auto from = getNearestPosition(pos);
		replaceItems(from, pos);
	}
	
}

bool SimpleBoard::isSpecificItem()
{
	for (auto const & item : m_items) {
		if (item->getType() > 4) {
			return true;
		}
	}
	return false;
}

SimpleBoard::~SimpleBoard()
{
	for (auto & item : m_items) {
		delete item;
	}
}

Position SimpleBoard::getNearestPosition(const Position & pos)
{
	int index = -1;
	for (auto i = pos.getI(); i >= 0; --i) {
		Position currentPosition(i, pos.getJ());
		int currentIndex = currentPosition.getIndex(m_row, m_col);
		if (m_items.at(currentIndex)->getType() != ItemType::eUnknownType) {
			index = currentIndex;
			break;
		}
	}
	if (index != -1) {
		Position res;
		res.setFromIndex(index, m_row, m_col);
		return res;
	}
	return Position();
}

void SimpleBoard::replaceItems(const Position & from, const Position & to)
{
	if (from.getI() == -1 && from.getJ() == -1) {
		for (auto i = 0; i <= to.getI(); ++i) {
			Position first{ i , to.getJ() };
			m_items.at(first.getIndex(m_row, m_col))->generateNewType();
		}
	}
	else {
		if (m_items.at(to.getIndex(m_row, m_col))->getType() != ItemType::eUnknownType) {
			return;
		}
		int step = to.getI() - from.getI();
		for (auto i = from.getI(); i >= 0; i--) {
			Position first{ i , from.getJ() };
			Position second{ i + step,from.getJ() };
			m_items.at(second.getIndex(m_row, m_col))->setType(m_items.at(first.getIndex(m_row, m_col))->getType());
			m_items.at(first.getIndex(m_row, m_col))->setType(ItemType::eUnknownType);
		}
		for (auto i = 0; i < step; ++i) {
			Position first{ i , from.getJ() };
			m_items.at(first.getIndex(m_row, m_col))->generateNewType();
		}
	}
}

void SimpleBoard::initialize()
{
	for (auto i = 0; i < m_row; ++i) {
		for (auto j = 0; j < m_col; ++j) {
			ItemPtr currentItem = new OrdinaryItems(i, j,m_figuresCount);
			m_items.push_back(currentItem);
		}
	}
}

void SimpleBoard::initializeWithEmptyValues()
{
	for (auto i = 0; i < m_row; ++i) {
		for (auto j = 0; j < m_col; ++j) {
			ItemPtr currentItem = new OrdinaryItems(i, j, m_figuresCount);
			currentItem->setType(ItemType::eUnknownType);
			m_items.push_back(currentItem);
		}
	}
}


void SimpleBoard::clearVertical(const Position & position, Positions & outputPositions, QueueOfPosition & bonusPositions)
{
	for (auto i = 0; i < m_row; ++i) {
		Position pos{i, position.getJ() };
		int currentIndex = pos.getIndex(m_row, m_col);
		if (m_items.at(currentIndex)->getType() <5) {
			outputPositions.push_back(pos);
		}
		else if (m_items.at(currentIndex)->getType() != 8) {
			outputPositions.push_back(pos);
			bonusPositions.push(pos);
		}
	}
}

void SimpleBoard::clearHorizontal(const Position & position, Positions &outputPositions, QueueOfPosition & bonusPositions)
{
	for (auto j = 0; j < m_col; ++j) {
		Position pos{ position.getI(),j };
		int currentIndex = pos.getIndex(m_row, m_col);
		if (m_items.at(currentIndex)->getType() <5) {
			outputPositions.push_back(pos);
		}
		else if (m_items.at(currentIndex)->getType() != 8) {
			outputPositions.push_back(pos);
			bonusPositions.push(pos);
		}
	}
}

void SimpleBoard::clearBonusMatchingsHelper(const Position & position, Positions &outputPositions, QueueOfPosition & bonusPositions)
{
	auto type = m_items.at(position.getIndex(m_row, m_col))->getType();
	if (type < 5 || type == 8) {
		return;
	}
	m_items.at(position.getIndex(m_row, m_col))->setType(eUnknownType);
	switch (type) {
	case eVerticalBomb:
		clearVertical(position, outputPositions, bonusPositions);
		break;
	case eHoriziontalBomb:
		clearHorizontal(position, outputPositions, bonusPositions);
		break;
	case eBomb:
		clearVertical(position, outputPositions, bonusPositions);
		clearHorizontal(position, outputPositions, bonusPositions);
		break;
	}
}

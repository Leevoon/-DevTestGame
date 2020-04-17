#include "Objectives.h"
#include "GeneralInformation.h"

Objectives::Objectives()
{
}

void Objectives::setMoveCount(int i)
{
	m_moveCount = i;
}

void Objectives::decreaseMoveCount()
{
	m_moveCount--;
}

int Objectives::getMoveCount() const
{
	return m_moveCount;
}

void Objectives::setObjectives(const ItemType & itemType, int count)
{
	auto currentFigures = GeneralInformation::getInstance()->getCurrentOrdinaryItems();
	if (std::find(currentFigures.begin(), currentFigures.end(), itemType) != currentFigures.end() && count >0) {
		m_itemTypeToCountMapping[itemType] = count;
	}
}

void Objectives::decreaseObjectiveCount(const ItemType & itemType, int count)
{
	if (m_itemTypeToCountMapping.find(itemType) != m_itemTypeToCountMapping.end()) {
		m_itemTypeToCountMapping[itemType] -= count;
	}
	if (m_itemTypeToCountMapping[itemType] <= 0) {
		m_itemTypeToCountMapping.erase(itemType);
	}
}

int Objectives::getCountByType(const ItemType & itemType) 
{
	int count = m_itemTypeToCountMapping[itemType];
	return count;
}

ItemTypes Objectives::getObjectives()
{
	ItemTypes result;
	for (auto const & m : m_itemTypeToCountMapping) {
		result.push_back(m.first);
	}
	return result;
}

GameStatus Objectives::getGameStatus()
{
	if (m_itemTypeToCountMapping.size() == 0) {
		return GameStatus::Won;
	}
	else if (m_moveCount <= 0) {
		return GameStatus::Failed;
	}
	return GameStatus::Started;
}

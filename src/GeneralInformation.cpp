#include "GeneralInformation.h"

GeneralInformationPtr GeneralInformation::s_instance = nullptr;


GeneralInformation::GeneralInformation()
{
	m_bonusItems = ItemTypes{ eBomb,eHoriziontalBomb,eVerticalBomb };
	m_ordinaryItems = ItemTypes{ eBlue,eOrange,eViolet,eRed,eGreen };
	m_matchings= Matchings{ { Mat{ { 1,1,1 },{ 0,1,0 },{ 0,1,0 } } ,ItemTypes{}, 4, 16 }
		,{ Mat{ { 1,1,1 } }, ItemTypes{}, 4, 4 }
		,{ Mat{ { 1,1,1,1 } }, ItemTypes{ ItemType::eHoriziontalBomb,ItemType::eVerticalBomb }, 4, 8 }
		,{ Mat{ { 1,1 },{ 1,1 } },  ItemTypes{ ItemType::eBomb }, 2, 6 } };
	m_initialPathOfResources = "../../";
}
GeneralInformationPtr GeneralInformation::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new GeneralInformation();
	}
	return s_instance;
}

void GeneralInformation::initialize(int countOfItems)
{
	GeneralInformation::getInstance()->getOrdinaryItems(countOfItems);
}

std::string GeneralInformation::getInitialPathOfResources()
{
	return m_initialPathOfResources;
}

ItemTypes GeneralInformation::getOrdinaryItems(int countOfItems)
{
	if (countOfItems >= m_ordinaryItems.size()) {
		return m_ordinaryItems;
	}
	else if(countOfItems <=0){
		return ItemTypes();
	}
	else {
		if (m_currentOrginaryItems.size() == 0) {
			int pos = std::rand() % m_ordinaryItems.size();
			for (auto i = 0; i < countOfItems; ++i) {
				//TODO
				m_currentOrginaryItems.push_back(m_ordinaryItems.at(pos++%m_ordinaryItems.size()));
			}
		}
		return m_currentOrginaryItems;
	}
	return ItemTypes();
}

ItemTypes GeneralInformation::getCurrentOrdinaryItems()
{
	if (m_currentOrginaryItems.size() == 0) {
		return m_ordinaryItems;
	}
	else {
		return m_currentOrginaryItems;
	}
}

ItemTypes GeneralInformation::getBonusItems()
{
	return m_bonusItems;
}

Matchings GeneralInformation::getMatchings()
{
	return m_matchings;
}

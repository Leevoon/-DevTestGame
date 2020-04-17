#ifndef GENERALINFORMATION_H
#define GENERALINFORMATION_H

#include "Item.h"
#include "IMatchingAlgorithm.h"
struct Matching
{
	Mat m_initialMatchingMat;
	ItemTypes m_bonusItemTypes;
	int m_variationsCount;
	int m_proirity;
};
using Matchings = std::vector<Matching>;
class GeneralInformation;
using GeneralInformationPtr = GeneralInformation * ;
class GeneralInformation
{
public:

	static GeneralInformationPtr getInstance();

	static void initialize(int countOfItems);
	std::string getInitialPathOfResources();
	ItemTypes getOrdinaryItems(int countOfItems =5);
	ItemTypes getCurrentOrdinaryItems();
	ItemTypes getBonusItems();
	Matchings getMatchings();
private:
	GeneralInformation();
private:
	static GeneralInformationPtr s_instance;
	std::string m_initialPathOfResources;
	Matchings m_matchings;
	ItemTypes m_ordinaryItems;
	ItemTypes m_currentOrginaryItems;
	ItemTypes m_bonusItems;
};
#endif //GENERALINFORMATION_H
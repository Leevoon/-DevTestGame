#include "OrdinaryItem.h"
#include "GeneralInformation.h"

OrdinaryItems::OrdinaryItems(int i,int j,int countOfFigures)
	:Item(i,j, GeneralInformation::getInstance()->getOrdinaryItems(countOfFigures))
{
}

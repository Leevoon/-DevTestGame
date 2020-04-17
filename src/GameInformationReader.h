#ifndef GAMEINFORMATIONREADER_H
#define GAMEINFORMATIONREADER_H

#include "Item.h"
#include <map>
struct GameInfo
{
	int m_windowWidth;
	int m_windowHeight;
	int m_row;
	int m_col;
	int m_movesCount;
	std::map<ItemType, int> m_objectives;
	int m_figureCounts;
};
class GameInformationReader
{
public:
	GameInformationReader(const std::string & path);
	std::string getErrorMessage(bool &ok);
	GameInfo getInfo();
private:
	GameInfo m_info;
};
#endif // !GAMEINFORMATIONREADER_H

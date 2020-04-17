#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Observer.h"


class MainWindow :public sf::RenderWindow, public Observer
{

public:
	MainWindow(int width, int height , const std::string & title, int style , int framerateLimit);
	void setItemsRow(int row);
	void setItemsCol(int col);
	void run();
	void updateItems(const ItemPtrs & itemPtrs);
	void updateMessage(const std::string& message);
	void updateObjectives(Objectives* objectives);
	int getPositionOfClick(int x, int y, bool &isInRange);
private://functions
	void setInitialView();
	void loadItems();
	void updateWindow();
	void setItems(const ItemPtrs & itemPtrs);
	void setObjectives(Objectives* objectives);
private://members
	int m_itemsRow;
	int m_itemsCol;

	int m_score;

	std::vector<sf::Sprite> m_headerSprites;
	std::vector<sf::Sprite> m_objectiveSprites;
	std::vector<sf::Text> m_objectiveTexts;
	std::vector<sf::Sprite> m_itemSprites;
	std::vector<sf::Sprite> m_itemBackgroundSprites;
	std::vector<std::string> m_itemColors;
	sf::Texture m_firstTexture;
	sf::Texture m_secondTexture;
	std::map<ItemType, sf::Texture> m_itemTextures;
	sf::Text m_scoreLabel;
	sf::Font m_font;
	sf::Texture m_blueTexture;
	sf::Texture m_greenTexture;
	sf::Texture m_orangeTexture;
	sf::Texture m_redTexture;
	sf::Texture m_violetTexture;
	sf::Texture m_bombTexture;
	sf::Texture m_horizontalBombTexture;
	sf::Texture m_verticalBombTexture;
	std::vector<int> m_selectedSprites;
	int m_initialWidth;
	int m_initialHeight;
	int m_height;
	int m_width;
};
#endif // !MAINWINDOW_H
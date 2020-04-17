#include "MainWindow.h"
#include "GeneralInformation.h"

MainWindow::MainWindow(int width, int height,const std::string & title,int style, int framerateLimit)
	:sf::RenderWindow(sf::VideoMode(width,height),title,style)
	,m_score(0)
	,m_height(height)
	,m_width(width)
{
	setFramerateLimit(framerateLimit);
	loadItems();
}

void MainWindow::setItemsRow(int row)
{
	m_itemsRow = row;
}

void MainWindow::setItemsCol(int col)
{
	m_itemsCol = col;
}

void MainWindow::run()
{
	setInitialView();
	updateWindow();
}

void MainWindow::updateItems(const ItemPtrs & itemPtrs)
{
	setItems(itemPtrs);
	updateWindow();
}

void MainWindow::updateMessage(const std::string & message)
{
	sf::Text currentText;
	currentText.setCharacterSize(30);
	currentText.setFont(m_font);
	currentText.setString(message);
	sf::Color color(18, 128, 34);
	currentText.setFillColor(color);
	currentText.setStyle(sf::Text::Regular);
	currentText.setPosition(m_width / 2 - currentText.getLocalBounds().width / 2, m_height / 2 - currentText.getLocalBounds().height / 2);
	if (isOpen()) {
		clear(sf::Color(150, 150, 150, 255));
		draw(currentText);
		display();
	}

}

void MainWindow::updateObjectives(Objectives * objectives)
{
	setObjectives(objectives);
	updateWindow();
}

int MainWindow::getPositionOfClick(int x, int y, bool & isInRange)
{
	int w = m_itemBackgroundSprites.front().getTextureRect().width;
	int h = m_itemBackgroundSprites.front().getTextureRect().height;
	int j = (x - m_initialWidth) / w;
	int i = (y - m_initialHeight) / h;
	if (i <0 || i >= m_itemsRow) {
		isInRange = false;
		return -1;
	}
	if (j <0 || j >= m_itemsCol) {
		isInRange = false;
		return -1;
	}
	auto pos = i * m_itemsCol + j;
	isInRange = true;
	return pos;
}

void MainWindow::setInitialView()
{
	
	
	std::vector<sf::Sprite> sprites;
	sf::Sprite firstHeader(m_secondTexture);
	sf::Sprite secondHeader(m_firstTexture);
	sf::Sprite thirdHeader(m_secondTexture);
	sf::Sprite spr(m_firstTexture);
	
	m_scoreLabel.setCharacterSize(30);
	m_scoreLabel.setFont(m_font);
	m_scoreLabel.setString(std::to_string(m_score));
	m_scoreLabel.setPosition(m_width / 2- m_scoreLabel.getLocalBounds().width/2 , 30);
	sf::Color color(18, 128, 34);
	m_scoreLabel.setFillColor(color);
	m_scoreLabel.setStyle(sf::Text::Regular);
	auto width = spr.getTextureRect().width;
	auto height = spr.getTextureRect().height;
	firstHeader.setScale(m_width / float(2.5 * width), 1.5);
	firstHeader.setPosition(0, 0);
	secondHeader.setScale(m_width / float(5 * width), 1.5);
	secondHeader.setPosition(m_width / 2.5f, 0);
	thirdHeader.setScale(m_width / float(2.5 * width), 1.5);
	thirdHeader.setPosition(3* m_width / 5.f, 0);
	m_initialWidth = (m_width - m_itemsCol * width) / 2;
	m_initialHeight = (m_height - m_itemsRow * height) / 2 + height/2;
	for (auto i = 0; i < m_itemsRow; ++i) {
		for (auto j = 0; j < m_itemsCol; ++j) {
			Item *currentItem = new Item(i, j);
			sf::Sprite currentSprite;
			if (currentItem != nullptr) {
				switch (currentItem->getType()) {
				case eBlue:
					currentSprite.setTexture(m_blueTexture);
					break;
				case eGreen:
					currentSprite.setTexture(m_greenTexture);
					break;
				case eOrange:
					currentSprite.setTexture(m_orangeTexture);
					break;
				case eRed:
					currentSprite.setTexture(m_redTexture);
					break;
				case eViolet:
					currentSprite.setTexture(m_violetTexture);
					break;
				}
			}
			sf::Sprite sprite;
			if ((i + j) % 2 == 0) {
				sprite.setTexture(m_firstTexture);
			}
			else {
				sprite.setTexture(m_secondTexture);
			}
			sprite.setPosition(float(m_initialWidth + j* sprite.getTextureRect().width), float(m_initialHeight + i * sprite.getTextureRect().height));
			currentSprite.setPosition(float(m_initialWidth + j * sprite.getTextureRect().width)+ sprite.getTextureRect().width/2- currentSprite.getTextureRect().width / 2, float(m_initialHeight +i * sprite.getTextureRect().height) + sprite.getTextureRect().height / 2 - currentSprite.getTextureRect().height / 2);
			m_itemBackgroundSprites.push_back(sprite);
			m_itemSprites.push_back(currentSprite);
		}
	}

	m_headerSprites.push_back(firstHeader);
	m_headerSprites.push_back(secondHeader);
	m_headerSprites.push_back(thirdHeader);
}

void MainWindow::loadItems()
{	
	m_font.loadFromFile(GeneralInformation::getInstance()->getInitialPathOfResources()+"Resources/Roboto-Medium.ttf");
	m_firstTexture.loadFromFile(GeneralInformation::getInstance()->getInitialPathOfResources() + "Resources/tile_1.png");
	m_secondTexture.loadFromFile(GeneralInformation::getInstance()->getInitialPathOfResources() + "Resources/tile_2.png");
	m_blueTexture.loadFromFile(GeneralInformation::getInstance()->getInitialPathOfResources() + "Resources/blue.png");
	m_greenTexture.loadFromFile(GeneralInformation::getInstance()->getInitialPathOfResources() + "Resources/green.png");
	m_orangeTexture.loadFromFile(GeneralInformation::getInstance()->getInitialPathOfResources() + "Resources/orange.png");
	m_redTexture.loadFromFile(GeneralInformation::getInstance()->getInitialPathOfResources() + "Resources/red.png");
	m_violetTexture.loadFromFile(GeneralInformation::getInstance()->getInitialPathOfResources() + "Resources/violet.png");
	m_bombTexture.loadFromFile(GeneralInformation::getInstance()->getInitialPathOfResources() + "Resources/bomb.png");
	m_horizontalBombTexture.loadFromFile(GeneralInformation::getInstance()->getInitialPathOfResources() + "Resources/h_bomb.png");
	m_verticalBombTexture.loadFromFile(GeneralInformation::getInstance()->getInitialPathOfResources() + "Resources/v_bomb.png");
}

void MainWindow::updateWindow()
{
	if(isOpen()) {
		clear(sf::Color(150, 150, 150, 255));
		for (auto const & s : m_headerSprites) {
			draw(s);
		}
		for (auto const & s : m_itemBackgroundSprites) {
			draw(s);
		}
		for (auto const & s : m_itemSprites) {
			draw(s);
		}
		for (auto const & s : m_objectiveSprites) {
			draw(s);
		}
		for (auto const & s : m_objectiveTexts) {
			draw(s);
		}
		draw(m_scoreLabel);
		display();
	}
}

void MainWindow::setItems(const ItemPtrs & itemPtrs)
{
	m_itemSprites.clear();
	for (auto i = 0; i < m_itemsRow; ++i) {
		for (auto j = 0; j < m_itemsCol; ++j) {
			auto currentItem = itemPtrs.at(i * m_itemsCol + j);
			sf::Sprite currentSprite;
			if (currentItem != nullptr) {
				switch (currentItem->getType()) {
				case eBlue:
					currentSprite.setTexture(m_blueTexture);
					break;
				case eGreen:
					currentSprite.setTexture(m_greenTexture);
					break;
				case eOrange:
					currentSprite.setTexture(m_orangeTexture);
					break;
				case eRed:
					currentSprite.setTexture(m_redTexture);
					break;
				case eViolet:
					currentSprite.setTexture(m_violetTexture);
					break;
				case eBomb:
					currentSprite.setTexture(m_bombTexture);
					break;
				case eHoriziontalBomb:
					currentSprite.setTexture(m_horizontalBombTexture);
					break;
				case eVerticalBomb:
					currentSprite.setTexture(m_verticalBombTexture);
					break;
				}
			}
			currentSprite.setPosition(float(m_initialWidth + j * m_itemBackgroundSprites.front().getTextureRect().width) + m_itemBackgroundSprites.front().getTextureRect().width / 2 - currentSprite.getTextureRect().width / 2, float(m_initialHeight + i * m_itemBackgroundSprites.front().getTextureRect().height) + m_itemBackgroundSprites.front().getTextureRect().height / 2 - currentSprite.getTextureRect().height / 2);
			m_itemSprites.push_back(currentSprite);
		}
	}
}

void MainWindow::setObjectives(Objectives * objectives)
{
	m_objectiveSprites.clear();
	m_objectiveTexts.clear();
	auto objs = objectives->getObjectives();
	for (auto i = 0; i < objs.size();++i ) {
		auto type = objs.at(i);
		Item *currentItem = new Item(-i, -i);
		currentItem->setType(type);
		sf::Sprite currentSprite;
		if (currentItem != nullptr) {
			switch (currentItem->getType()) {
			case eBlue:
				currentSprite.setTexture(m_blueTexture);
				break;
			case eGreen:
				currentSprite.setTexture(m_greenTexture);
				break;
			case eOrange:
				currentSprite.setTexture(m_orangeTexture);
				break;
			case eRed:
				currentSprite.setTexture(m_redTexture);
				break;
			case eViolet:
				currentSprite.setTexture(m_violetTexture);
				break;
			case eBomb:
				currentSprite.setTexture(m_bombTexture);
				break;
			case eHoriziontalBomb:
				currentSprite.setTexture(m_horizontalBombTexture);
				break;
			case eVerticalBomb:
				currentSprite.setTexture(m_verticalBombTexture);
				break;
			}
		}
		sf::Text currentText;
		currentText.setCharacterSize(30);
		currentText.setFont(m_font);
		currentText.setString(std::to_string(objectives->getCountByType(type)));
		sf::Color color(18, 128, 34);
		currentText.setFillColor(color);
		currentText.setStyle(sf::Text::Regular);
		currentSprite.setPosition(20+float(0+ i * m_itemBackgroundSprites.front().getTextureRect().width) + m_itemBackgroundSprites.front().getTextureRect().width / 2 - currentSprite.getTextureRect().width / 2, 10);
		currentText.setPosition(20 + float(0 + i * m_itemBackgroundSprites.front().getTextureRect().width) + m_itemBackgroundSprites.front().getTextureRect().width / 2 - currentText.getLocalBounds().width / 2, float(m_itemBackgroundSprites.front().getTextureRect().height));
		m_objectiveSprites.push_back(currentSprite);
		m_objectiveTexts.push_back(currentText);
	}
	m_scoreLabel.setString(std::to_string(objectives->getMoveCount()));
	m_scoreLabel.setPosition(m_width / 2 - m_scoreLabel.getLocalBounds().width / 2, 30);
}

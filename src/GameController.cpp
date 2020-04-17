#include <SFML/Graphics.hpp>
#include "GameController.hpp"
#include <iostream>
#include "GeneralInformation.h"


GameController::GameController() {
}

void GameController::updateGameStatus(const GameStatus &status) {
	m_gameStatus = status;
}

void GameController::startGame() {
	m_reader= new GameInformationReader(GeneralInformation::getInstance()->getInitialPathOfResources() + "info.json");
	bool isOk;
	auto errorMessage = m_reader->getErrorMessage(isOk);
	auto info = m_reader->getInfo();
    m_mainWindow = new MainWindow(info.m_windowWidth, info.m_windowHeight, "Game", 4,60);
	if (!isOk) {
		m_mainWindow->updateMessage(errorMessage);
		run();
		return;
	}
	GeneralInformation::initialize(info.m_figureCounts);
	m_mainWindow->setItemsRow(info.m_row);
	m_mainWindow->setItemsCol(info.m_col);
	m_mainWindow->run();
	m_boardController = new BoardController(info.m_row,info.m_col, info.m_figureCounts);
	m_boardController->registerObs(m_mainWindow);
	m_boardController->setMoves(info.m_movesCount);
	for (auto const & obj : info.m_objectives) {
		m_boardController->setObjectives(obj.first, obj.second);
	}
	m_boardController->initializeStepByStep();

	updateGameStatus(GameStatus::Started);
    run();
}

void GameController::run() {
	while (m_mainWindow->isOpen()) {
		
		sf::Event event;
		while (m_mainWindow->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				m_mainWindow->close();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (m_gameStatus != Started) {
					exit(0);
				}
				bool isOk =false;
				int val = m_mainWindow->getPositionOfClick(event.mouseButton.x, event.mouseButton.y, isOk);
				if (isOk) {
					m_boardController->update(val);
				}
				updateGameStatus(m_boardController->getGameStatus());
				checkGameStatus();
			}
		}
	}
}

void GameController::checkGameStatus()
{
	switch (m_gameStatus)
	{
	case Won:
		m_mainWindow->updateMessage("Game Complete");
		break;
	case Failed:
		m_mainWindow->updateMessage("Game Failed");
		break;
	default:
		break;
	}
}

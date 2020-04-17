
#ifndef GameController_hpp
#define GameController_hpp

#include <stdio.h>
#include "MainWindow.h"
#include "GameInformationReader.h"
#include "BoardController.h"
#include "GameStatus.h"

#endif /* GameController_hpp */


class GameController {

public :
    GameController();
    void startGame();
    void updateGameStatus(const GameStatus &status);
private:
    void run();
	void checkGameStatus();
private:
    GameStatus m_gameStatus = NotStarted;
    MainWindow *m_mainWindow;
	BoardController* m_boardController;
	GameInformationReader* m_reader;


};
#include "BoardController.h"
#include "SimpleBoard.h"
#include "SimpleMatching.h"
#include "GeneralInformation.h"

#include <chrono>
#include <thread>

BoardController::BoardController(int row, int col , int figuresCount)
	:m_row(row)
	,m_col(col)
{
	//TODO
	m_board = new SimpleBoard(row, col , figuresCount);
	m_matchingDispatcher = new MatchingDispatcher();// (currentMat, row, col);
	auto matchings =GeneralInformation::getInstance()->getMatchings();
	for (auto const & matching : matchings) {
		IMatchingAlgorithm* ptr = new SimpleMatching(matching.m_initialMatchingMat, row, col, matching.m_bonusItemTypes, matching.m_variationsCount, matching.m_proirity);
		m_matchingDispatcher->addAlgorithm(ptr);
	}
	//IMatchingAlgorithm* ptr1 = new SimpleMatching(Mat{ { 1,1,1 },{ 0,1,0 },{ 0,1,0 } }, row, col, ItemTypes{}, 4, 16);
	//IMatchingAlgorithm* ptr2 = new SimpleMatching(Mat{ { 1,1,1 } }, row, col, ItemTypes{}, 4, 4);
	//IMatchingAlgorithm* ptr3 = new SimpleMatching(Mat{ { 1,1,1,1 } }, row, col, ItemTypes{ ItemType::eHoriziontalBomb,ItemType::eVerticalBomb }, 4, 8);
	//IMatchingAlgorithm* ptr4 = new SimpleMatching(Mat{ { 1,1 },{ 1,1 } }, row, col, ItemTypes{ ItemType::eBomb }, 2, 6);
	//m_matchingDispatcher->addAlgorithm(ptr1);
	//m_matchingDispatcher->addAlgorithm(ptr2);
	//m_matchingDispatcher->addAlgorithm(ptr3);
	//m_matchingDispatcher->addAlgorithm(ptr4);
	m_matchingDispatcher->initialize();
	m_objectives = new Objectives;
}

void BoardController::setMoves(int count)
{
	m_objectives->setMoveCount(count);
}

void BoardController::setObjectives(const ItemType & type, int count)
{
	m_objectives->setObjectives(type, count);
	notifyObjectives(m_objectives);
}

void BoardController::update(int pos)
{
	if (m_selectedIds.size() == 1) {
		if (m_selectedIds.size() != pos) {
			Position firstPosition = getPositionFromIndex(pos);
			Position secondPosition = getPositionFromIndex(m_selectedIds.front());
			if (areTheyNeighbours(firstPosition, secondPosition)) {
				auto isOrdinaryTypeFirst = isOrdinaryType(firstPosition);
				auto isOrdinaryTypeSecond = isOrdinaryType(secondPosition);
				if (isOrdinaryTypeFirst && isOrdinaryTypeSecond) {
					cultivateActionForTwoOrdinaryFigures(firstPosition, secondPosition);
				}
				else if (!isOrdinaryTypeFirst && isOrdinaryTypeSecond) {
					cultivateActionForSpecificFigureAndForOrdinaryFigure(firstPosition, secondPosition);
				}
				else if (isOrdinaryTypeFirst && !isOrdinaryTypeSecond) {
					cultivateActionForSpecificFigureAndForOrdinaryFigure(secondPosition, firstPosition);
				}
				else if (!isOrdinaryTypeFirst && !isOrdinaryTypeSecond) {

				}
			}
		}
		m_selectedIds.clear();
	}
	else {
		m_selectedIds.push_back(pos);
	}
}

void BoardController::shuffle()
{
	if (!m_board->isSpecificItem() && !m_matchingDispatcher->isPossibilityToMakeMatching(m_board)) {
		m_board->update();
		initialize();
	}
}

void BoardController::initialize()
{
	while (m_matchingDispatcher->isMatching(m_board))
	{
		m_board->update();
		notifyObs(m_board->getItems());
	}
	auto items = m_board->getItems();
	notifyObs(m_board->getItems());
}

void BoardController::initializeStepByStep()
{
	for (auto i = 0; i < m_row; ++i) {
		for (auto j = 0; j < m_col; ++j) {
			Position currentPosition{ i,j };
			do
			{
				m_board->updateItemByPosition(currentPosition);
			} while (m_matchingDispatcher->isMatchingForGivenPosition(m_board,currentPosition));
		}
	}
	auto items = m_board->getItems();
	notifyObs(m_board->getItems());
}

GameStatus BoardController::getGameStatus()
{
	return m_objectives->getGameStatus();;
}

void BoardController::clearAndNotify(const Positions & positions,  const ItemPtrs & bonusItems, bool updateMoveCount)
{
	updateObjectives(positions);
	if (updateMoveCount) {
		m_objectives->decreaseMoveCount();
	}
	notifyObjectives(m_objectives);
	m_board->clearMatchings(positions);
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	notifyObs(m_board->getItems());
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	m_board->regulate(positions);
	for (auto const & bI : bonusItems) {
		m_board->setItem(bI);
	}
	notifyObs(m_board->getItems());
	auto positionPair = getMinAndMaxPositions(positions);
	automaticlyDetectMatchings(positionPair.first, positionPair.second);
}

void BoardController::cultivateActionForTwoOrdinaryFigures(const Position & firstPosition, const Position & secondPosition)
{
	int firstPositionIndex = firstPosition.getIndex(m_row, m_col);
	int secondPositionIndex = secondPosition.getIndex(m_row, m_col);
	m_board->swap(firstPositionIndex, secondPositionIndex);
	ItemPtrs firstBonusItems;
	ItemPtrs secondBonusItems;
	auto firstPositions = m_matchingDispatcher->getPositionsOfItemsWhereIsMatchingsForGivenPosition(m_board, firstPosition, firstBonusItems);
	auto secondPositions = m_matchingDispatcher->getPositionsOfItemsWhereIsMatchingsForGivenPosition(m_board, secondPosition, secondBonusItems);
	firstBonusItems.insert(firstBonusItems.end(), secondBonusItems.begin(), secondBonusItems.end());
	firstPositions.insert(firstPositions.end(), secondPositions.begin(), secondPositions.end());
	if (firstPositions.size() == 0) {
		m_board->swap(firstPositionIndex, secondPositionIndex);
		shuffle();
		return;
	}
	clearAndNotify(firstPositions, firstBonusItems, true);
}

void BoardController::cultivateActionForSpecificFigureAndForOrdinaryFigure(const Position & specificFigurePosition, const Position & ordinaryFigurePosition)
{
	int specificFigurePositionIndex = specificFigurePosition.getIndex(m_row, m_col);
	int ordinaryFigurePositionIndex = ordinaryFigurePosition.getIndex(m_row, m_col);
	m_board->swap(specificFigurePositionIndex, ordinaryFigurePositionIndex);
	ItemPtrs firstBonusItems;
	auto firstPositions = m_matchingDispatcher->getPositionsOfItemsWhereIsMatchingsForGivenPosition(m_board, specificFigurePosition, firstBonusItems);
	auto positionsOfDeletedItemsFromBooster = m_board->clearBonusMatchings(ordinaryFigurePosition);
	if (positionsOfDeletedItemsFromBooster.size() != 1) {
		firstPositions.insert(firstPositions.end(), positionsOfDeletedItemsFromBooster.begin(), positionsOfDeletedItemsFromBooster.end());
	}
	clearAndNotify(firstPositions, firstBonusItems, true);
}


BoardController::~BoardController()
{
	delete m_board;
	delete m_matchingDispatcher;
	delete m_objectives;
}

PairOfPositions BoardController::getMinAndMaxPositions(const Positions & positions)
{
	int minI = std::numeric_limits<int>::max();
	int maxI = std::numeric_limits<int>::min();
	int minJ = std::numeric_limits<int>::max();
	int maxJ = std::numeric_limits<int>::min();
	for (auto const &pos : positions) {
		if (pos.getI() > maxI) {
			maxI = pos.getI();
		}
		if (pos.getI() < minI) {
			minI = pos.getI();
		}if (pos.getJ() > maxJ) {
			maxJ = pos.getJ();
		}if (pos.getJ() < minJ) {
			minJ = pos.getJ();
		}
	}
	minI = 0;
	Position minPos{ minI,minJ };
	Position maxPos{ maxI,maxJ };
	return PairOfPositions{minPos,maxPos};
}

Position BoardController::getPositionFromIndex(int index)
{
	Position res;
	res.setI(index / m_col);
	res.setJ(index % m_col);
	return res;
}

void BoardController::updateObjectives(const Positions & positions)
{
	for (auto const & pos : positions) {
		m_objectives->decreaseObjectiveCount(m_board->getItems().at(pos.getIndex(m_row, m_col))->getType(),1);
	}
}

bool BoardController::isOrdinaryType(const Position & position)
{
	auto type =m_board->getItemTypeByPosition(position);
	return type < 5;
}

int BoardController::getIndexFromPosition(Position position)
{
	return position.getI() *m_col + position.getJ();
}

bool BoardController::areTheyNeighbours(const Position & firstPosition, const Position & secondPosition)
{
	if ((firstPosition.getI() == secondPosition.getI() && firstPosition.getJ() == secondPosition.getJ() - 1)
		|| (firstPosition.getI() == secondPosition.getI() && firstPosition.getJ() == secondPosition.getJ() + 1)
		|| (firstPosition.getI() == secondPosition.getI() - 1 && firstPosition.getJ() == secondPosition.getJ())
		|| (firstPosition.getI() == secondPosition.getI() + 1 && firstPosition.getJ() == secondPosition.getJ()))
	{
		return true;
	}
	return false;
}

void BoardController::automaticlyDetectMatchings(const Position & min, const Position & max)
{
	ItemPtrs bonusItems;
	auto positions = m_matchingDispatcher->isMatchingInPart(m_board, min, max, bonusItems);
	if (positions.size() == 0) {
		return;
	}
	clearAndNotify(positions,bonusItems,false);
}

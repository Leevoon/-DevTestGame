#ifndef BOARDCONTOROLLER_H
#define BOARDCONTOROLLER_H

#include <SFML/Graphics.hpp>
#include "Item.h"
#include "subject.h"

#include "Board.h"
#include "MatchingDispatcher.h"
#include "Objectives.h"
#include "GameStatus.h"

class BoardController : public Subject
{
public:
	BoardController(int row , int col, int figuresCount);

	/*setMovies, The function setting moves count
	*
	* @count -count of moves
	*
	*/
	void setMoves(int count);
	/*setObjectives, The function setting objectives
	*
	* @ItemType -type of objective
	* @count -count of objective
	*
	*/
	void setObjectives(const ItemType & type, int count);

	/*update, The function is calling when client taping on figures
	*
	* @pos - position of taped figure
	*
	*/
	void update(int pos);

	/*initialize, The function is initializing the whole board randomly 
	*
	*/
	void initialize();
	/*initializeStepByStep, The function is initializing the whole board randomly checking matches for each position
	*
	*/
	void initializeStepByStep();
	GameStatus getGameStatus();
	~BoardController();

private: //functions

	PairOfPositions getMinAndMaxPositions(const Positions & positions);
	Position getPositionFromIndex(int index);
	void updateObjectives(const Positions & positions);
	bool isOrdinaryType(const Position & position);
	int getIndexFromPosition(Position);
	bool areTheyNeighbours(const Position & firstPosition, const Position & secondPosition);

	/*automaticlyDetectMatchings, the function automatically detects matches, erases them, 
	* justifies the board ( pieces fall down from the top) lets the interface and objectives know about the erased figures 
	* and performs this action until there are no matches at all
	*
	* @min - min position of range
	* @max - max position of range
	*
	*/
	void automaticlyDetectMatchings(const Position & min , const Position & max);

	/*clearAndNotify, the function is clearing all matches from the board, notifying about matches to the interface and objectives
	*
	* @positions - positions of items that should be deleted
	* @bonusItems - positions of bonus items that should be deleted
	* @updateMoveCount - if this argument is true, the number of moves will be decresed
	*
	*/
	void clearAndNotify(const Positions & positions,const ItemPtrs & bonusItems, bool updateMoveCount);

	/*cultivateActionForTwoOrdinaryFigures, the function is cultivating action for two ordinary figures
	*
	* @firtPosition - position of first ordinary figure
	* @secondPosition - position of second ordinary figure
	*
	*/
	void cultivateActionForTwoOrdinaryFigures(const Position  & firstPosition, const Position  & secondPosition);

	/*cultivateActionForSpecificFigureAndForOrdinaryFigure, the function is cultivating action for specific and ordinary figures
	*
	* @specificFigurePosition - position of specific figure
	* @ordinaryFigurePosition - position of ordinary figure
	*
	*/
	void cultivateActionForSpecificFigureAndForOrdinaryFigure(const Position  & specificFigurePosition, const Position  & ordinaryFigurePosition);

	/*shuffle, If there is a situation that no match can be made.
	* The board will be shuffled as many times as it is necessary to create a possibility to match.
	*/
	void shuffle();
private: //members
	Objectives* m_objectives;
	IBoard * m_board;
	MatchingDispatcher* m_matchingDispatcher;
	int m_row;
	int m_col;
	std::vector<int> m_selectedIds;
};

#endif // !BOARDCONTOROLLER_H

#ifndef MATCHINGDISPATCHER_H
#define MATCHINGDISPATCHER_H

#include "IMatchingAlgorithm.h"
#include <set>

class MatchingDispatcher
{
public:
	MatchingDispatcher();
	~MatchingDispatcher();
	/*addAlgorithm, 
	* The function adds algorithms that are sorted with a predefined priority.
	*
	* @algorithm - matching algorithm
	*
	*/
	void addAlgorithm(IMatchingAlgorithmPtr algorithm);

	/*getPositionsOfItemsWhereIsMatchingsForGivenPosition, The function will find matchings giving importance to algorithms with high priority
	*
	* @board -board of game
	* @position - position of item
	* @bonusItems - item positions that is specific figures
	*
	*/
	Positions getPositionsOfItemsWhereIsMatchingsForGivenPosition(IBoard * board, const Position & position,ItemPtrs & bonusItems);

	/*isMatching, The function will find a matchings. If they are available on board, it will return true, otherwise false.
	* The function will find matchings giving importance to algorithms with high priority
	*
	* @board -board of game
	*
	*/
	bool isMatching(IBoard * board);

	/*isMatchingForGivenPosition, The function will find a matching in given position. If it is available on board, it will return true, otherwise false.
	*
	* @board -board of game
	* @position - position of item
	*
	*/
	bool isMatchingForGivenPosition(IBoard * board, const Position & position);

	/*isPossibilityToMakeMatching, The function will find a possible matchings.
	* If after one move matches appear on the board function will return true, otherwise false.
	*
	* @board -board of game
	*
	*/
	bool isPossibilityToMakeMatching(IBoard * board);

	/*isMatchingInPart, The function will find a matchings in given range.
	* The function will return positions of matchings  for each position
	* The function will find matchings giving importance to algorithms with high priority
	*
	* @board - board of game
	* @startPosition - start position
	* @endPosition - end position
	* @bonusItems - item positions that is specific figures
	*
	*/
	Positions isMatchingInPart(IBoard * board, Position startPosition, Position endPosition, ItemPtrs & bonusItems);

	/*initialize,
	*
	* The function is initializing all parameters that are used for other methods.
	*
	*/
	void initialize();

private:

	//The function will find a matchings beetwen two algorithms,and will set values.
	void computePossibleMatchings(IMatchingAlgorithmPtr bigPriority, IMatchingAlgorithmPtr smallPriority);
	//Getting aa matches between matrix and positions
	Positions2D getMatchings(const Mat & first, const Positions2D & positions);

	//is matching beetwenn matrix and positions
	bool isMatching(const Mat & first, const Positions & positions);

	//the function finds the positions from where can appear cruches
	Positions getPointsWhereCanBeCrush(const Positions2D & position2D);

	//the function finds the intersection of positions
	Positions intersectPositions(Positions first , Positions  second);
private:
	MatchingAlgorithmsSet m_algorithms;
};
#endif //MATCHINGDISPATCHER_H
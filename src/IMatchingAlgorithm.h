#ifndef MATCHINGALGORITHNINTERFACE_H
#define MATCHINGALGORITHNINTERFACE_H

#include "Board.h"
#include "Item.h"
#include "Position.h"

#include <set>
#include <map>

class IMatchingAlgorithm;
//Matrix
using MatRow = std::vector<int>;
using Mat = std::vector < MatRow>;
using MatVector = std::vector<Mat>;

//Pointer of IMatchingAlgorithm
using IMatchingAlgorithmPtr = IMatchingAlgorithm * ;


/*IMatchingAlgorithmComparator, 
*
*compares the importance of the matching algorithm
*
*/
struct IMatchingAlgorithmComparator
{
	bool operator()(IMatchingAlgorithm* first, IMatchingAlgorithm* second);
};

//Matching Algorithms Set
using MatchingAlgorithmsSet = std::set<IMatchingAlgorithmPtr, IMatchingAlgorithmComparator>;



class IMatchingAlgorithm
{
public:

	IMatchingAlgorithm();
	virtual ~IMatchingAlgorithm() = 0;
	bool operator <(const IMatchingAlgorithm & other);

	/*isMatching, The function will find a matchings. If they are available on board, it will return true, otherwise false. 
	*
	* @board -board of game
	*
	*/
	virtual bool isMatching(IBoard * board) = 0;

	/*isPossibilityToMakeMatching, The function will find a possible matchings. 
	* If after one move matches appear on the board function will return true, otherwise false.
	*
	* @board -board of game
	*
	*/
	virtual bool isPossibilityToMakeMatching(IBoard * board) = 0;

	/*isMatchingForGivenPosition, The function will find a matching in given position. If it is available on board, it will return true, otherwise false.
	*
	* @board -board of game
	* @position - position of item
	*
	*/
	virtual bool isMatchingForGivenPosition(IBoard * board , const Position & position) = 0;

	/*isPossibilityToMakeMatchingForGivenPosition, The function will find a possible matching in given position.
	* If it is available on board, it will return true, otherwise false.
	*
	* @board -board of game
	* @position - position of item
	*
	*/
	virtual bool isPossibilityToMakeMatchingForGivenPosition(IBoard * board ,const Position & position) = 0;


	/*isMatchingInPart, The function will find a matchings in given range.
	* The function will return positions of matchings  for each position
	*
	* @board -board of game
	* @startPosition - start position
	* @endPosition - end position 
	* @alreadyDeletedPositions - item positions that have already been deleted
	*
	*/
	virtual std::map<Position, Positions>  isMatchingInPart(IBoard * board, Position startPosition, Position endPosition,  Positions & alreadyDeletedPositions) = 0;

	/*getPositionsOfItemsWhereIsMatchingsForGivenPosition, The function will find a matchings for given position.
	* The function will return positions of matchings
	*
	* @board -board of game
	* @position - position of item
	* @alreadyDeletedPositions - item positions that have already been deleted
	*
	*/
	virtual Positions getPositionsOfItemsWhereIsMatchingsForGivenPosition(IBoard * board, const Position & position, const Positions & alreadyDeletedPositions) = 0;
	/*getMatrixes,
	* The function will return all variations of predefined matching
	*
	*/
	virtual MatVector getMatirxes() =0;

	/*getAllPossibleMatchingsInRange,
	* The function will return all possible matchings in range
	*
	* @row
	* @col
	*
	*/
	virtual Positions2D getAllPossibleMatchingsInRange(int row , int col) =0;

	/*appendCrushPositions,
	* The function will append positions, from where it is an opportunity to get matching
	*
	* @positions  
	* @index - index of variation
	*
	*/
	virtual void appendCrushPositions(const Positions & positions, int index) =0;

	/*initialize,
	*
	* The function is initializing all parameters that are used for other methods.
	*
	*/
	virtual void initialize() =0;
protected:
	int m_priority;
};


#endif // !MATCHINGALGORITHNINTERFACE_H

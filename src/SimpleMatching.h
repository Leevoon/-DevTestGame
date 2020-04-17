#ifndef SimpleMATCHING_H
#define SimpleMATCHING_H

#include "IMatchingAlgorithm.h"
#include <map>

class SimpleMatching : public IMatchingAlgorithm
{
public:
	SimpleMatching(const Mat & matrix, int row , int col,  const ItemTypes & bonusItemType,int variationsCount=2, int proirity=4);
	bool isMatching(IBoard * board);
	bool isPossibilityToMakeMatching(IBoard * board);
	bool isMatchingForGivenPosition(IBoard * board, const Position & position);
	bool isPossibilityToMakeMatchingForGivenPosition(IBoard * board, const Position & position);
	Positions getPositionsOfItemsWhereIsMatchingsForGivenPosition(IBoard * board, const Position & position, const Positions & alreadyDeletedPositions);
	std::map<Position, Positions>  isMatchingInPart(IBoard * board, Position startPosition, Position endPosition, Positions & alreadyDeletedPositions);
	ItemPtrs getItemsForCrush(IBoard* board);
	Positions2D getAllPossibleMatchingsInRange(int col, int row);
	ItemType getBonusItemType(const Positions & positions);
	~SimpleMatching();
	void initialize();
	MatVector getMatirxes();
	void appendCrushPositions(const Positions & positions ,int index);

private:

	MatVector getPossibleMatchingMatrixes(const Mat & mat);
	MatVector createMats(const Position & position, const Positions & positions, const Positions & appendedPositions, int row, int col);
	void computePossibleMatchingPossitionsForEachPoint();
	void computeMatchingPossitionsForEachPoint();

	Positions2D getInterestingPositionsForCurrentPosition(const Mat & matrix , const Position & pos);
	std::vector<Mat> getAllVariationsOfMatrix(const Mat & matrix,int variationsCount);
	Mat rotateMatrixWith90Celsius(const Mat & matrix);
	Mat getMirrorOfMatrix(const Mat & matrix);
	void appendInResult(Positions2D & positions, const Positions2D & forAdding);
	bool isEqualPositions(const Positions & first, const Positions & second);
	Positions2D getInterestingPositionsForCurrentPosition(int indexOfVariation, const Position & pos);
	Positions2D getInterestingPositionsForCurrentPosition(int indexOfVariation, const Position & pos,int row ,int col);
	void initializeInterestingPositions(const Mat & mat);

private:
	Mat m_matrix;
	MatVector m_matVariations;
	ItemTypes m_boinusItems;
	std::map<Position, Positions2D> m_interestingPositionMapping;
	std::map<Position, Positions2D> m_interestingPositionToMakeMatchingMapping;
	Positions2D m_positionsWhereCanAppearCrush;
	Positions m_initialPositionsWhereCanAppearCrush;
	int m_lengthOfCombination;
	int m_row;
	int m_col;
	bool m_withMirror;
};
#endif // !SimpleMATCHING_H

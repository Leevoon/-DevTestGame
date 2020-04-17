#include "SimpleMatching.h"



SimpleMatching::SimpleMatching(const Mat & matrix, int row, int col ,const ItemTypes & bonusItemTypes,int variationsCount , int proirity)
	:m_row(row)
	,m_col(col)
	,m_matrix(matrix)
	,m_lengthOfCombination(0)
{
	m_priority = proirity;
	for (auto i = 0; i < m_matrix.size(); ++i) {
		for (auto j = 0; j < m_matrix.at(i).size(); ++j) {
			m_lengthOfCombination += m_matrix[i][j];
		}
	}	
	m_matVariations = getAllVariationsOfMatrix(m_matrix, variationsCount);
}

bool SimpleMatching::isMatching(IBoard * board)
{
	for (auto i = 0; i < m_row; ++i) {
		for (auto j = 0; j < m_col; ++j) {
			if (isMatchingForGivenPosition(board, Position{ i,j }))
			{
				return true;
			}
		}
	}
	return false;
}

bool SimpleMatching::isPossibilityToMakeMatching(IBoard * board)
{
	for (auto i = 0; i < m_row; ++i) {
		for (auto j = 0; j < m_col; ++j) {
			if (isPossibilityToMakeMatchingForGivenPosition(board, Position{ i,j }))
			{
				return true;
			}
		}
	}
	return false;
}

bool SimpleMatching::isMatchingForGivenPosition(IBoard * board, const Position & position)
{
	bool isMatching = false;
	auto items = board->getItems();
	auto type = items.at(position.getIndex(m_row,m_col))->getType();
	for (auto const &p2D : m_interestingPositionMapping[position]) {
		isMatching = true;
		for (auto const & p : p2D) {
			if (type != items.at(p.getIndex(m_row, m_col))->getType()) {
				isMatching = false;
				break;
			}
		}
		if (isMatching) {
			return true;
		}
	}
	return false;
}

bool SimpleMatching::isPossibilityToMakeMatchingForGivenPosition(IBoard * board, const Position & position)
{
	bool isMatching = false;
	auto items = board->getItems();
	auto type = items.at(position.getIndex(m_row, m_col))->getType();
	for (auto const &p2D : m_interestingPositionToMakeMatchingMapping[position]) {
		isMatching = true;
		for (auto const & p : p2D) {
			if (type != items.at(p.getIndex(m_row, m_col))->getType()) {
				isMatching = false;
				break;
			}
		}
		if (isMatching) {
			return true;
		}
	}
	return false;
}

Positions SimpleMatching::getPositionsOfItemsWhereIsMatchingsForGivenPosition(IBoard * board, const Position & position, const Positions & alreadyDeletedPositions)
{
	Positions result;
	bool isMatching = false;
	auto items = board->getItems();
	auto type = items.at(position.getIndex(m_row, m_col))->getType();
	for (auto const &p2D : m_interestingPositionMapping[position]) {
		isMatching = true;
		for (auto const & p : p2D) {
			auto it = std::find(alreadyDeletedPositions.begin(), alreadyDeletedPositions.end(), p);
			if (it != alreadyDeletedPositions.end()) {
				isMatching = false;
				result.clear();
				break;
			}
			if (type != items.at(p.getIndex(m_row, m_col))->getType()) {
				isMatching = false;
				result.clear();
				break;
			}
			else {
				result.push_back(p);
			}
		}
		if (isMatching) {
			return result;
		}
	}
	return result;
}

std::map<Position,Positions> SimpleMatching::isMatchingInPart(IBoard * board, Position startPosition, Position endPosition, Positions & alreadyDeletedPositions)
{
	std::map<Position,Positions> result;
	for (auto i = startPosition.getI(); i <= endPosition.getI(); ++i) {
		for (auto j = startPosition.getJ(); j <= endPosition.getJ(); ++j) {
			Position currentPosition{ i,j };
			auto currentPositions = getPositionsOfItemsWhereIsMatchingsForGivenPosition(board,currentPosition, alreadyDeletedPositions);
			alreadyDeletedPositions.insert(alreadyDeletedPositions.end(), currentPositions.begin(), currentPositions.end());
			result[currentPosition] = currentPositions;
		}
	}
	return result;
}

ItemPtrs SimpleMatching::getItemsForCrush(IBoard * board)
{
	return ItemPtrs();
}

Positions2D SimpleMatching::getAllPossibleMatchingsInRange(int row, int col)
{
	Positions2D result;
	for (auto k = 0; k < m_matVariations.size();++k) {
		for (auto i = 0; i < row; ++i) {
			for (auto j = 0; j < col; ++j) {
				Position currentPosition{ i,j };
				auto currentPositions = getInterestingPositionsForCurrentPosition(k, currentPosition,row,col);
				appendInResult(result, currentPositions);
			}
		}
	}
	return result;
}

ItemType SimpleMatching::getBonusItemType(const Positions & positions)
{

	return ItemType();
}

SimpleMatching::~SimpleMatching()
{
}

void SimpleMatching::initialize()
{
	computeMatchingPossitionsForEachPoint();
	computePossibleMatchingPossitionsForEachPoint();
}

void SimpleMatching::computeMatchingPossitionsForEachPoint()
{
	for (auto k = 0; k < m_matVariations.size(); ++k) {
		for (auto i = 0; i < m_row; ++i) {
			for (auto j = 0; j < m_col; ++j) {
				Position currentPosition{ i,j };
				auto currentPositions = getInterestingPositionsForCurrentPosition(k, currentPosition);
				m_interestingPositionMapping[currentPosition].insert(m_interestingPositionMapping[currentPosition].end(),currentPositions.begin(),currentPositions.end());
			}
		}
	}
}

void SimpleMatching::appendInResult(Positions2D & positions, const Positions2D & forAdding)
{
	Positions2D result;
	bool contains;
	for (auto const & add : forAdding) {
		contains = false;
		for (auto const & pos : positions) {
			if (isEqualPositions(pos, add)) {
				contains = true;
				break;
			}
		}
		if (!contains) {
			result.push_back(add);
		}
	}
	positions.insert(positions.end(), result.begin(), result.end());
}

bool SimpleMatching::isEqualPositions(const Positions & first, const Positions & second)
{
	if (first.size() != second.size()) {
		return false;
	}
	for (auto i = 0; i < first.size(); ++i) {
		if (!(first.at(i)== second.at(i))) {
			return false;
		}
	}
	return true;
}

Positions2D SimpleMatching::getInterestingPositionsForCurrentPosition(int indexOfVariation, const Position & pos)
{
	return getInterestingPositionsForCurrentPosition(indexOfVariation,pos,m_row,m_col);
}

Positions2D SimpleMatching::getInterestingPositionsForCurrentPosition(int indexOfVariation, const Position & position, int row, int col)
{
	Positions2D result;

	Mat mat = m_matVariations.at(indexOfVariation);
	Positions firstPositions, secondPositions;
	for (auto i = 0; i < mat.size(); ++i) {
		for (auto j = 0; j < mat.at(i).size(); ++j) {
			if (mat.at(i).at(j) == 1) {
				secondPositions.push_back({ i,j });
			}
		}
	}
	if (m_positionsWhereCanAppearCrush.at(indexOfVariation).size()==0) {
		firstPositions = secondPositions;
	}
	else {
		firstPositions = m_positionsWhereCanAppearCrush.at(indexOfVariation);
	}

	for (auto const& first : firstPositions) {
		Positions currentPositions;
		for (auto const& second : secondPositions) {
			auto iCurr = position.getI() + first.getI() - second.getI();
			auto jCurr = position.getJ() + first.getJ() - second.getJ();
			if (iCurr < 0 || iCurr >= row) {
				break;
			}
			if (jCurr < 0 || jCurr >= col) {
				break;
			}
			currentPositions.push_back({ iCurr,jCurr });
		}
		if (currentPositions.size() == m_lengthOfCombination) {
			result.push_back(currentPositions);
		}
	}

	return result;
}

void SimpleMatching::initializeInterestingPositions(const Mat & matrix)
{
	for (auto i = 0; i < matrix.size(); ++i) {
		for (auto j = 0; j < matrix.at(i).size(); ++j) {
			if (matrix.at(i).at(j) == 1) {
				m_initialPositionsWhereCanAppearCrush.push_back({ i,j });
			}
		}
	}
}



MatVector SimpleMatching::getMatirxes()
{
	return m_matVariations;
}

void SimpleMatching::appendCrushPositions(const Positions & positions , int index)
{
	m_positionsWhereCanAppearCrush.at(index).insert(m_positionsWhereCanAppearCrush.at(index).end(), positions.begin(), positions.end());
}

MatVector SimpleMatching::getPossibleMatchingMatrixes(const Mat & mat)
{
	MatVector result;
	Mat nv;
	int row = int(mat.size()) + 2;
	int col = int(mat.front().size()) + 2;
	nv.resize(row);
	for (auto i = 0; i < nv.size(); ++i) {
		nv.at(i).resize(col);
		for (auto j = 0; j < col; ++j) {
			nv.at(i).at(j) = 0;
		}
	}
	Positions ones;
	for (auto i = 0; i < mat.size(); ++i) {
		for (auto j = 0; j < mat.at(i).size(); ++j) {
			if (mat.at(i).at(j) == 1) {
				ones.push_back(Position{ i + 1,j + 1 });
			}
		}
	}

	for (auto const &pos : ones) {
		Positions poses;

		auto up = Position(pos.getI() + 1, pos.getJ());
		auto down = Position(pos.getI() - 1, pos.getJ());
		auto left = Position(pos.getI(), pos.getJ() - 1);
		auto right = Position(pos.getI(), pos.getJ() + 1);
		if (std::find(ones.begin(), ones.end(), up) == ones.end()) {
			poses.push_back(up);
		}
		if (std::find(ones.begin(), ones.end(), down) == ones.end()) {
			poses.push_back(down);
		}
		if (std::find(ones.begin(), ones.end(), left) == ones.end()) {
			poses.push_back(left);
		}
		if (std::find(ones.begin(), ones.end(), right) == ones.end()) {
			poses.push_back(right);
		}
		auto currentMats = createMats(pos, ones, poses, row, col);
		result.insert(result.end(), currentMats.begin(), currentMats.end());
	}
	return result;
}
MatVector SimpleMatching::createMats(const Position & position, const Positions & positions, const Positions & appendedPositions, int row, int col)
{
	MatVector result;
	for (auto const & appendedPosition : appendedPositions) {
		Mat currentMat;
		currentMat.resize(row);
		for (auto i = 0; i < row; ++i) {
			currentMat.at(i).resize(col);
			for (auto j = 0; j < col; ++j) {
				currentMat.at(i).at(j) = 0;
			}
		}
		for (auto const & pos : positions) {
			if (!(pos == position)) {
				currentMat.at(pos.getI()).at(pos.getJ()) = 1;
			}
		}
		currentMat.at(appendedPosition.getI()).at(appendedPosition.getJ()) = 1;
		result.push_back(currentMat);
	}
	return result;
}
void SimpleMatching::computePossibleMatchingPossitionsForEachPoint()
{
	MatVector possibleMatrixes;
	for (auto const & m : m_matVariations) {
		auto currentMatrixes = getPossibleMatchingMatrixes(m);
		possibleMatrixes.insert(possibleMatrixes.end(), currentMatrixes.begin(), currentMatrixes.end());
	}
	for (auto const & mat : possibleMatrixes) {
		for (auto i = 0; i < m_row; ++i) {
			for (auto j = 0; j < m_col; ++j) {
				Position currentPosition{ i,j };
				auto currentPositions = getInterestingPositionsForCurrentPosition(mat, currentPosition);
				m_interestingPositionToMakeMatchingMapping[currentPosition].insert(m_interestingPositionToMakeMatchingMapping[currentPosition].end(), currentPositions.begin(), currentPositions.end());
			}
		}
	}
}
Positions2D SimpleMatching::getInterestingPositionsForCurrentPosition(const Mat & matrix, const Position & position)
{
	Positions2D result;
	Positions positions;
	for (auto i = 0; i < matrix.size(); ++i) {
		for (auto j = 0; j < matrix.at(i).size(); ++j) {
			if (matrix.at(i).at(j) == 1) {
				positions.push_back({ i,j });
			}
		}
	}
	for (auto const& first : positions) {
		Positions currentPositions;
		for (auto const& second : positions) {
			auto iCurr = position.getI() + first.getI() - second.getI();
			auto jCurr = position.getJ() + first.getJ() - second.getJ();
			if (iCurr < 0 || iCurr >= m_row) {
				break;
			}
			if (jCurr < 0 || jCurr >= m_col) {
				break;
			}
			currentPositions.push_back({ iCurr,jCurr });
		}
		if (currentPositions.size() == positions.size()) {
			result.push_back(currentPositions);
		}
	}
	return result;
}
std::vector<Mat> SimpleMatching::getAllVariationsOfMatrix(const Mat & matrix, int variationsCount)
{
	std::vector<Mat> result;
	auto currMatrix = matrix;
	for (auto i = 0; i < variationsCount/2; ++i) {
		auto mat = rotateMatrixWith90Celsius(currMatrix);
		auto matMirror = getMirrorOfMatrix(mat);
		if (matMirror != Mat()) {
			result.push_back(matMirror);
		}
		currMatrix = mat;
		result.push_back(mat);
	}
	m_positionsWhereCanAppearCrush.resize(result.size());
	return result;
}

Mat SimpleMatching::rotateMatrixWith90Celsius(const Mat & mat)
{
	Mat result;
	result.resize(mat.front().size());

	for (auto i = 0; i < result.size(); ++i) {
		result.at(i).resize(mat.size());
	}
	for (auto i = 0; i < mat.size(); ++i) {
		for (auto j = 0; j < mat.at(i).size(); ++j) {
			result.at(j).at(i) = mat.at(i).at(j);
		}
	}
	return result;
}

Mat SimpleMatching::getMirrorOfMatrix(const Mat & mat)
{
	Mat result = mat;
	int count = 0;
	for (auto i = 0; i < mat.size(); ++i) {
		for (auto j = 0; j < mat.at(i).size(); ++j) {
			int tmp = result.at(i).at(j);
			result.at(i).at(j) = mat.at(mat.size()-1-i).at(j);
			if (tmp == result.at(i).at(j)) {
				count++;
			}
		}
	}
	if (count == mat.size() *mat.front().size()) {
		count = 0;
		for (auto i = 0; i < mat.size(); ++i) {
			for (auto j = 0; j < mat.at(i).size(); ++j) {
				int tmp = result.at(i).at(j);
				result.at(i).at(j) = mat.at(i).at(mat.at(i).size()-1-j);
				if (tmp == result.at(i).at(j)) {
					count++;
				}
			}
		}
	}
	if (count == mat.size() *mat.front().size()) {
		return Mat();
	}
	return result;
}

#include "MatchingDispatcher.h"
#include <algorithm>
#include "BonusItem.h"

MatchingDispatcher::MatchingDispatcher()
{
}

MatchingDispatcher::~MatchingDispatcher()
{
	for (auto alg : m_algorithms) {
		delete alg;
	}
}

void MatchingDispatcher::addAlgorithm(IMatchingAlgorithmPtr algorithm)
{
	m_algorithms.insert(algorithm);
}

void MatchingDispatcher::initialize()
{
	for (auto itFirst = m_algorithms.begin(); itFirst != m_algorithms.end(); ++itFirst) {
		for (auto itSecond = m_algorithms.cbegin(); itSecond != m_algorithms.cend() && itFirst!= itSecond; --itSecond) {
			computePossibleMatchings(*itFirst, *itSecond);
		}
	}
	for (auto alg : m_algorithms) {
		alg->initialize();
	}
}

void MatchingDispatcher::computePossibleMatchings(IMatchingAlgorithmPtr bigPriority, IMatchingAlgorithmPtr smallPriority)
{
	auto matrixes = bigPriority->getMatirxes();
	for (auto i = 0; i < matrixes.size(); ++i) {
		auto posiblePositionsOfSmallPriority = smallPriority->getAllPossibleMatchingsInRange(int(matrixes.at(i).size()), int(matrixes.at(i).front().size()));
		auto pos2D = getMatchings(matrixes.at(i), posiblePositionsOfSmallPriority);
		auto posForCrush = getPointsWhereCanBeCrush(pos2D);
		bigPriority->appendCrushPositions(posForCrush,i);
	}
}

Positions2D MatchingDispatcher::getMatchings(const Mat & first, const Positions2D & positions)
{
	Positions2D result;
	for (auto const & p2D : positions) {
		if (isMatching(first, p2D)) {
			result.push_back(p2D);
		}
	}
	return result;
}

Positions MatchingDispatcher::getPositionsOfItemsWhereIsMatchingsForGivenPosition(IBoard * board, const Position & position, ItemPtrs & bonusItems)
{
	Positions result;
	for (auto alg : m_algorithms) {
		auto currentMatchings =alg->getPositionsOfItemsWhereIsMatchingsForGivenPosition(board,position,result);
		auto bonusItem = BonusItem::getBonusItem(currentMatchings);
		if (bonusItem->getType() != ItemType::eUnknownType) {
			bonusItem->setRow(position.getI());
			bonusItem->setCol(position.getJ());
			bonusItems.push_back(bonusItem);
		}
		result.insert(result.end(), currentMatchings.begin(), currentMatchings.end());
	}
	return result;
}

bool MatchingDispatcher::isMatching(IBoard * board)
{

	for (auto alg : m_algorithms) {
		if (alg->isMatching(board)) {
			return true;
		}
	}
	return false;
}

bool MatchingDispatcher::isMatchingForGivenPosition(IBoard * board, const Position & position)
{
	for (auto alg : m_algorithms) {
		if (alg->isMatchingForGivenPosition(board,position)) {
			return true;
		}
	}
	return false;
}

bool MatchingDispatcher::isPossibilityToMakeMatching(IBoard * board)
{
	for (auto alg : m_algorithms) {
		if (alg->isPossibilityToMakeMatching(board)) {
			return true;
		}
	}
	return false;
}

Positions MatchingDispatcher::isMatchingInPart(IBoard * board, Position startPosition, Position endPosition, ItemPtrs & bonusItems)
{
	Positions result;
	for (auto alg : m_algorithms) {
		auto currentMatchings = alg->isMatchingInPart(board, startPosition,endPosition, result);
		for (auto cM : currentMatchings) {
			result.insert(result.end(), cM.second.begin(), cM.second.end());
			auto bonusItem = BonusItem::getBonusItem(cM.second);
			if (bonusItem->getType() != ItemType::eUnknownType) {
				bonusItem->setRow(cM.first.getI());
				bonusItem->setCol(cM.first.getJ());
				bonusItems.push_back(bonusItem);
			}
		}
	}
	return result;
}

bool MatchingDispatcher::isMatching(const Mat & first, const Positions & positions)
{
	for (auto const &pos : positions) {
		if(first.size() <=pos.getI() || first.front().size()<=pos.getJ()) {
			return false;
		}
		if (first.at(pos.getI()).at(pos.getJ()) != 1) {
			return false;
		}
	}
	return true;
}

Positions MatchingDispatcher::getPointsWhereCanBeCrush(const Positions2D & position2D)
{
	if (position2D.size() == 0) {
		return Positions();
	}
	Positions result = position2D.front();
	for (auto const &pos : position2D) {
		result = intersectPositions(result, pos);
	}
	return result;
}

Positions MatchingDispatcher::intersectPositions(Positions  first, Positions  second)
{
	Positions result;
	std::sort(first.begin(), first.end());
	std::sort(second.begin(), second.end());
	std::set_intersection(first.begin(), first.end(),
		second.begin(), second.end(),
		back_inserter(result));
	return result;
}

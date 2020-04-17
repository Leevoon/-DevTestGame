#ifndef SIMPLEBOARD_H
#define SIMPLEBOARD_H
#include "Item.h"
#include "Board.h"
class SimpleBoard : public IBoard
{
public:
	SimpleBoard(int row, int col , int figuresCount);
	void setItems(const ItemPtrs & items);
	void setItem(const ItemPtr & item);
	ItemPtrs getItems() const;
	ItemType getItemTypeByPosition(const Position & position);
	void swap(int firstPos, int secondPos);
	void update();
	void updateItemByPosition(const Position & position);
	void clearMatchings(const Positions & positions);
	Positions clearBonusMatchings(const Position & position);
	void regulate(const Positions & positions);
	bool isSpecificItem();
	~SimpleBoard();
private:
	Position getNearestPosition(const Position & pos);
	void replaceItems(const Position & from, const Position & to);
	void initialize();
	void initializeWithEmptyValues();

	void clearVertical(const Position & position, Positions & outputPositions , QueueOfPosition & bonusPositions);
	void clearHorizontal(const Position & position, Positions & outputPositions, QueueOfPosition & bonusPositions);
	void clearBonusMatchingsHelper(const Position & positionPositions,Positions &outputPositions, QueueOfPosition & bonusPositions);

private:
	int m_row;
	int m_col;
	int m_figuresCount;
	ItemPtrs m_items;
};

#endif // !SIMPLEBOARD_H

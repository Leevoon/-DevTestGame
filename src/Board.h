#ifndef BOARD_H
#define BOARD_H
#include "Item.h"

class IBoard
{
public:

	/*setItems, The function setting items 
	*
	* @items -the vector of items pointers
	*
	*/
	virtual void setItems(const ItemPtrs & items) =0;
	/*setItem, The function setting single item
	*
	* @item - item pointer
	*
	*/
	virtual void setItem(const ItemPtr & item) =0;

	/*getItems, The function geting all items from board*/
	virtual ItemPtrs getItems() const = 0;

	/*setItems, The function seting single item
	*
	* @position - position of item
	*
	*/
	virtual ItemType getItemTypeByPosition(const Position & position) = 0;
	/*swap, The function swaps to items
	*
	* @firstPos - position of the first item
	* @secondPos - position of the second item
	*
	*/
	virtual void swap(int firstPos, int secondPos) =0;

	/*updateItemByPosition, The function will update item for given position
	*
	* @position - position of item
	*
	*/
	virtual void updateItemByPosition(const Position & position)=0;

	/*update, The function will update whole board items
	*
	*/
	virtual void update() = 0;

	/*clearMatchings, The function will clear all items (by given  positions)
	*
	* @positions - positions of items
	*
	*/
	virtual void clearMatchings(const Positions & positions) =0;
	/*clearBonusMatchings, The function will clear all bonus items (by given  positions)
	*
	* @positions - positions of items
	*
	*/
	virtual Positions clearBonusMatchings(const Position & position) =0;

	/*regulate, The function will regulate board by given positions
	* After clearing matched items from board top items are dropping into free cells.
	*
	* @positions - positions of items
	*
	*/
	virtual void regulate(const Positions & positions) = 0;

	/*isSpecificItem,If board have specific item, the function will return true otherwise false.
	*
	*/
	virtual bool isSpecificItem()= 0;
	virtual ~IBoard() = 0;
};
#endif // !BOARD_H


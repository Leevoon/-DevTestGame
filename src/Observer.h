#ifndef OBSERVER_H
#define OBSERVER_H

#include "Item.h"
#include "Objectives.h"
#include <string>
class Observer {
public:
    Observer() {}
    virtual void updateItems(const ItemPtrs & itemPtrs) = 0;
    virtual void updateMessage(const std::string& message) = 0;
    virtual void updateObjectives(Objectives* objectrives) = 0;

};

#endif // OBSERVER_H


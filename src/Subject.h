#ifndef SUBJECT
#define SUBJECT
#include <vector>
#include "Item.h"
#include "Objectives.h"
class Observer;

class Subject {
public:
    Subject();

	void notifyObjectives(Objectives *objectives);
	void notifyMessages(const std::string & messages);
    void notifyObs(const ItemPtrs & itemPtrs);
    void registerObs(Observer *observers);
private:
    std::vector<Observer*> m_observers;
};

#endif // SUBJECT


#include "Subject.h"
#include "Observer.h"

Subject::Subject() {

}

void Subject::notifyObs(const ItemPtrs &itemPtrs) 
{
	for (Observer* obs : m_observers) {
		obs->updateItems(itemPtrs);
	}
}
void Subject::notifyObjectives(Objectives *objectives) 
{
	for (Observer* obs : m_observers) {
		obs->updateObjectives(objectives);
	}
}

void Subject::notifyMessages(const std::string & message)
{
	for (Observer* obs : m_observers) {
		obs->updateMessage(message);
	}
}

void Subject::registerObs(Observer* obs) {
	m_observers.push_back(obs);
}

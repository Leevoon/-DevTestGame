#include "IMatchingAlgorithm.h"

IMatchingAlgorithm::IMatchingAlgorithm()
{

}

IMatchingAlgorithm::~IMatchingAlgorithm()
{

}

bool IMatchingAlgorithm::operator<(const IMatchingAlgorithm & other)
{
	return m_priority > other.m_priority;
}



bool IMatchingAlgorithmComparator::operator()(IMatchingAlgorithm * first, IMatchingAlgorithm * second)
{
	return *first < *second;
}

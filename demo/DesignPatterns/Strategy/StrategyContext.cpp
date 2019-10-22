#include <iostream>

#include "StrategyContext.hpp"
#include "Strategy.hpp"

using namespace std;

StrategyContext::StrategyContext(Strategy_4* stg)
{
	_stg = stg;
}

StrategyContext::~StrategyContext()
{
	if (!_stg)
		delete _stg;
}

void StrategyContext::DoAction()
{
	_stg->AlgrithmInterface();
}

#include "Manager.h"
#include "../Common/ConfigurationManager.h"

using namespace Common;

namespace Common{
	Manager::Manager(Behavior *startBehavior) : _currBehavior(startBehavior) {
//		_robot = ConfigurationManager::Instance()->GetRobot();
	}

	Manager::~Manager(){

	}

	void Manager::addNext(Behavior *beh) {
		_nextBehaviors.push_back(beh);
	}

	Behavior* Manager::selectNext() {
		for (unsigned int i = 0; i < _nextBehaviors.size(); i++)
		{
			if (_nextBehaviors[i]->startCond())
				return _nextBehaviors[i];
		}
		return NULL;
	}

	void Manager::run()
	{
		Robot* robot = ConfigurationManager::Instance()->GetRobot();
		robot->Read();
		if (!_currBehavior->startCond()) {
			cout << "Cannot start the first behavior" << endl;
			return;
		}

		while (_currBehavior != NULL) {
			_currBehavior->action();
			robot->Read();

			// Update particles...

			if (_currBehavior->stopCond()) {
				_currBehavior = selectNext();
			}
		}
		cout << "Manager stopped" << endl;
	}

}

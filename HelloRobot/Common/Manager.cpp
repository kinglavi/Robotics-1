#include "Manager.h"

namespace Common{

	Manager::Manager(Robot *robot, Behavior *startBehavior) : _currBehavior(startBehavior) {
		_robot = ConfigurationManager::Instance()->GetRobot();
	}

	void Manager::run()
	{
		_robot->Read();
		if (!_currBehavior->startCond()) {
			cout << "Cannot start the first behavior" << endl;
			return;
		}

		while (_currBehavior != NULL) {
			_currBehavior->action();
			_robot->Read();

			// Update particles...

			if (_currBehavior->stopCond()) {
				_currBehavior = _currBehavior->selectNext();
			}
		}
		cout << "Manager stopped" << endl;
	}

}

#include "Manager.h"
#include "../Common/ConfigurationManager.h"

using namespace Common;

namespace Common{
	Manager::Manager(PathManager *pathManager) {
		_pathManager = pathManager;
		_moveBehavior = new MoveForward(pathManager);
		_rotateBehavior = new TurnLeftBehavior(pathManager);
	}

	Manager::~Manager(){

	}

	void Manager::run()
	{
		Robot* robot = ConfigurationManager::Instance()->GetRobot();
		robot->Read();

		while (_pathManager->MoveToNextCoordinate()) {
			if (_rotateBehavior->startCond())
			{
				while (!_rotateBehavior->stopCond())
				{
					robot->Read();
					_rotateBehavior->action();
				}
			}

			Coordinates* currentPosition = robot->GetRobotsPosition();

			// Update particles...

			if (_moveBehavior->startCond())
			{
				while (!_moveBehavior->stopCond())
				{
					robot->Read();
					_moveBehavior->action();
				}
			}
		}
		cout << "Manager stopped" << endl;
	}

}

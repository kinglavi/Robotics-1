#pragma once

#include "../Robot.h"
#include "../Common/PathManager.h"
#include <vector> 

using namespace std;
using namespace Common;

namespace Behaviors {
	class Behavior {
	protected:
		Robot *_robot;
		PathManager* _pathManager;
		const double MaxYawChangeSpeed = 25.0;

	public:
		virtual bool startCond() = 0;
		virtual bool stopCond() = 0;
		virtual void action() = 0;

		Behavior(PathManager* pathManager);
		virtual ~Behavior();
	};
}

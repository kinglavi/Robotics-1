#include "../Robot.h"
#include "../Behaviors/Behavior.h"
#include "ConfigurationManager.h"

using namespace Behaviors;

namespace Common{
	class Manager {
	private:
		Robot* _robot;
		Behavior *_currBehavior;
	public:
		Manager(Robot *robot, Behavior *startBehavior);
		void run();
		virtual ~Manager();
	};
}

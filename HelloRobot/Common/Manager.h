#include "../Robot.h"
#include "../Behaviors/Behavior.h"
#include "ConfigurationManager.h"

using namespace Behaviors;

namespace Common{
	class Manager {



	private:
		vector<Behavior *> _nextBehaviors;
		Behavior *_currBehavior;
	public:
		Manager(Behavior *startBehavior);
		void run();
		void addNext(Behavior *beh);
		Behavior *selectNext();
		virtual ~Manager();
	};
}

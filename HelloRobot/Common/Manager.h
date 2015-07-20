#include "../Robot.h"
#include "../Behaviors/Behavior.h"
#include "../Behaviors/MoveForward.h"
#include "../Behaviors/TurnLeftBehavior.h"
#include "ConfigurationManager.h"

using namespace Behaviors;

namespace Common{
	class Manager {



	private:
		PathManager* _pathManager;
		MoveForward* _moveBehavior;
		TurnLeftBehavior* _rotateBehavior;
	public:
		Manager(PathManager *pathManager);
		void run();
		virtual ~Manager();
	};
}

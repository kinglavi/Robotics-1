/*
 * MoveForward.h
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#ifndef MOVEFORWARD_H_
#define MOVEFORWARD_H_

#include "Behavior.h"
namespace Behaviors {
	class MoveForward : public Behavior {
	private:
		bool checkObstacleInFront();
		bool checkIfReachedTarget();

	public:
		MoveForward(PathManager* pathManager);
		virtual ~MoveForward();

		virtual bool startCond();
		virtual bool stopCond();
		virtual void action();
	};
}

#endif /* MOVEFORWARD_H_ */

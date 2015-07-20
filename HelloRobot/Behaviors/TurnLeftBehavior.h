/*
 * TurnLeftBehavior.h
 *
 *  Created on: Jul 19, 2015
 *      Author: colman
 */

#ifndef TURNLEFTBEHAVIOR_H_
#define TURNLEFTBEHAVIOR_H_
#include "Behavior.h"
#include "../Mapping/Coordinates.h"

namespace Behaviors {
	class TurnLeftBehavior : public Behavior {
	public:
		TurnLeftBehavior(PathManager* pathManager);
		virtual ~TurnLeftBehavior();
		virtual bool startCond();
		virtual bool stopCond();
		virtual void action();
	private:
		bool ShouldTurnLeft	();
		double CalcAngle(Coordinates* first, Coordinates* second);
	};

} /* namespace Path */

#endif /* TURNLEFTBEHAVIOR_H_ */

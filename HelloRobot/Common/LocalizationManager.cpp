#include "LocalizationManager.h"

namespace Common {

	LocalizationManager::LocalizationManager() {

	}

	void LocalizationManager::update(double deltaX, double deltaY, double deltaYaw){

	}
	void LocalizationManager::resampleParticles(){

	}

	Particle* LocalizationManager::getBestParticle(){
		return new Particle(0,0,0);
	}

	LocalizationManager::~LocalizationManager() {

	}

}

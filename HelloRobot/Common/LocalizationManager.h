#include "../Particle.h"
#include <vector>

using namespace Model;
using namespace std;

namespace Common {

	class LocalizationManager {
	private:
	    vector<Particle *> _particles;

	public:
		LocalizationManager();
		void update(double deltaX, double deltaY, double deltaYaw);
		void resampleParticles();
		Particle* getBestParticle();

		virtual ~LocalizationManager();
	};

}

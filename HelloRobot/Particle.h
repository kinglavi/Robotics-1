namespace Model {

	class Particle {
	private:
		double _xPos, _yPos, _yaw;
		double _belief;

	public:
		Particle(double xPos, double yPos, double yaw);

		double getBelief();
		void update(double deltaX, double deltaY, double deltaYaw);
		void printPosition();

		virtual ~Particle();
	};
}

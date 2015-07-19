namespace model {

	class Location {
	public:
		Location();
		Location(double x, double y, double yaw);
		virtual ~Location();
		double position_X;
		double position_Y;
		double position_Yaw;
	};
}

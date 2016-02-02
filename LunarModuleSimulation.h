void welcome_msg();
void print_header();
void start_game();
void print_stats(int t, double altitude, double velocity, double fuel, double& percentBurn);
void calculate_thrust(int& t, double& altitude, double& velocity, double& acceleration, double& mass, double& fuel, double& percentBurn);
void victory_msg(double& altitude, double& velocity);
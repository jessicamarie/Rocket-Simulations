/*
	Program Name:			Lunar Module Simulation													
	File Name:				LunarModuleSimulation.cpp												
	Author:					Jessie Nelson															
	Original:				02/19/15																
	Updated:				02/02/16																

	Purpose:																						
		The user will input a percent burn (0-99) to control the throttle of the engine of a lunar lander	
		as it descends to the moon's surface. The program will output the lander's velocity,		
		altitude, and remaining fuel at 1 second intervals. The program will also output the final	
		velocity of the lander at touchdown.
*/


// Include Section
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "LunarModuleSimulation.h"
using namespace std;

//Global Variables
const double gravity = -1.62;		// The acceleration due to gravity on the moon in m/s/s
const int deltaT = 1;				// The change in time in seconds

// Main Program
int main( )
{
	welcome_msg();
	start_game();

	cout << "\nEnd Simulation.\n";
	return 0;
}

void welcome_msg(){
	system("CLS");

	cout << "Welcome to the Lunar Lander simulation!\n\n";
	cout << "You are in control of a Lunar Lander on its descent to the moon's surface.\n";
	cout << "You will adjust the thrust to the main engine every second by entering\na percent burn (from 0-99).";
	cout << " Your mission is to land the spacecraft at a velocity of less than 1 meter/second\n";
	cout << "Type 'h' for hints and how-to-play\n\nGOOD LUCK!\n";

	cout << fixed << setprecision(2);
};

void victory_msg(double& altitude, double& velocity){
	char playAgain;
	
	cout << "\nTouchdown velocity was " << -1 * velocity << " meters/second.\n";
	
	if (velocity > -1)
		cout << "Congratulations!! You have executed a perfect landing.";
	else if (velocity > -3)
		cout << "Rough Landing. Phew, that was a close one.";
	else if (velocity < -3)
		cout << "Can you hear me Major Tom? Can you hear me Major Tom...";

	cout << "\n\nWould you like to repeat the simulation? <Y or N> : ";
	cin >> playAgain;
	playAgain = tolower(playAgain);
	
	if (playAgain == 'y'){
		welcome_msg();
		start_game();
	}
};

void print_header(){
	cout << endl << right << setw(5) << "Sec" << setw(10) << "Alt";
	cout << setw(10) << "Speed" << setw(10) << "Fuel\n";
};

void start_game(){
	// Variable Declarations
	double percentBurn;			// Entered by user
	int t = 0;				// Initial time in seconds
	double velocity = 0;		// Initial velocity in m/s before descent
	double altitude = 2300;		// Initial altitude in meteres before descent
	double acceleration = 0;	// Initial acceleration	in m/s/s before descent
	double mass = 6831;			// Initial mass of lander including fuel in kg
	double fuel = 300;			// Initial fuel amount before descent in kg

	while (altitude > 0){
		print_stats(t, altitude, velocity, fuel, percentBurn);
		calculate_thrust(t, altitude, velocity, acceleration, mass, fuel, percentBurn);
	}
	victory_msg(altitude, velocity);
	};

void print_stats(int t, double altitude, double velocity, double fuel, double& percentBurn){
	print_header();
	cout << right << setw(5) << t << setw(10) << altitude;
	cout << setw(10) << velocity << setw(10) << fuel << "    ";

	if (fuel > 0){
		cout << left << setw(29) << "Enter percent burn (0-100) :";
		cin >> percentBurn;
	}
	else{
		cout << endl;
		percentBurn = 0;
	}
};

void calculate_thrust(int& t, double& altitude, double& velocity, double& acceleration, double& mass, double& fuel, double &percentBurn) {
	if (percentBurn == 0 || (percentBurn >= 10.637 && percentBurn <= 100)){
		double weight;			// The weight of the lander in Newtons
		double thrust; 			// The total upward thrust of the engine
		double force;			// The total force acting on the lander
		double spentFuel;		// The amount of fuel used at a given time 
		
		weight = mass * gravity;
		thrust = (percentBurn / 100) * 43900;
		force = thrust + weight;
		acceleration = force / mass;			// The lander's acceleration at a given time
		fuel = fuel - ((percentBurn / 100) * 13.6);	// The amount of fuel at a given time
		spentFuel = 300 - fuel;				
		mass = 6831 - spentFuel;					// The mass of the lunar given less fuel

		altitude = altitude + velocity * deltaT + 0.5 * acceleration * deltaT * deltaT;
		velocity = velocity + acceleration * deltaT;
		t = t + deltaT;
	}
	else if (percentBurn > 100){
		cout << "    " << "Please enter a number between 0 and 100";
	}
	else if (percentBurn < 10.637){
		cout << "    " << "You'll need more fuel than that to throttle the engine.";
	}
};
#include "robot.hpp"
#include <numeric>
#include <vector>
using namespace std;

/*	sets the speed of the motors depending on the passed arguments		
 * 	issue: since the camera is asymmetric and default is 4 white pixels on the right, hard to make it so that when robot is on line it should not move.
 *  Instead what happens is that if the white line is on the robot's right it thinks that everything's fine.
 */
int speed(int left, int right, vector<int> vector){
	double straight = 20.0;				//default speed
    double error;
    
    if(right == 4){						//for when left and right is equal
		error = 0;
	}
	else if(left > right){				//need != 2 condition since left is initalized with 2
		error = left;					//left being the left half of the cam (from robot POV)
	}
	else if(right > left){
		error = right;					//right being the left half of the cam (from robot POV)
	}
	//everything from here onwards is from Lecture 15 notes (kp gained via trial and error)
	double dv = 0.8 * error;
	double vRight = straight + dv;
	double vLeft = straight - dv;
	
	if(left > right){
		setMotors(vLeft, vRight);
	}
	else if(right > left){
		setMotors(vRight, vLeft);
	}
	return 0; 
}

int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
    while(1){
		takePicture();
		std::vector<int> yVect;
		for ( int column =0 ; column < cameraView.width ; column++){	
			double white = get_pixel(cameraView,99,column,3);				//gets luminosity of basically the bottom of the camera vs column
			if(white==255){
				yVect.push_back(1);						//adds 1 to vector if there is a white pixel
			}
			else{
				yVect.push_back(0);						//adds 0 to vector if there isn't
			}
	    }
	    int left = 0;
	    int right = 0;
	    for(double i = 0; i < yVect.size(); i++){			//summing of values. Top half goes into left, etc
			if (i < (yVect.size()/2)){
				left += yVect[i];
			}
			else{
				right += yVect[i];
			}
		}
		//cout of vector halves and each element in vector
	    std::cout<<"left"<<left<<endl;
	    std::cout<<"right"<<right<<endl;
	    
	    for (int i = 0; i < yVect.size(); i++){
			std::cout<<yVect.at(i)<<' ';
		}
		
		speed(left, right, yVect);				//setting speed
		usleep(10000);					//deletion of this could remove the shaking problem
  } //while
	
} // main



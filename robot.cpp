#include "robot.hpp"
#include <numeric>
#include <vector>
using namespace std;

//sets the speed of the motors depending on the passed arguments		issue: shaking robot due to oscillation-like change in left and right. Fix could be smoother turns and implementation of 'error'
int speed(int left, int right){
	double vLeft = 20.0;
    double vRight = 20.0;
    double toTurn = 15.0;
    double sharpTurn = 10.0;
    
	if(left > right){
		setMotors(toTurn,vLeft); 
	}
	else if(right > left){
		setMotors(vRight,toTurn); 
	}
	else if(left > right*2){
		setMotors(sharpTurn,vLeft);
	}
	else if(right > left*2){
		setMotors(vRight,sharpTurn); 
	}
	else{
		setMotors(vLeft,vRight);
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
			double white = get_pixel(cameraView, (cameraView.height/2),column,3);			//gets luminosity of cameraView.height/2 vs column
			if(white==255){
				yVect.push_back(1);						//adds 1 to vector if there is a white pixel
			}
			else{
				yVect.push_back(0);						//adds 0 to vector if there isn't
			}
	    }
	    int left = std::accumulate(yVect.begin(), yVect.begin()+int(yVect.size()/2), 0);				//finds sum of first half
	    int right = std::accumulate(yVect.begin()+int(yVect.size()/2), yVect.end(), 0);					//finds sum of last half
	    
	    //std::cout<<"left"<<left<<endl;
	    //std::cout<<"right"<<right<<endl;
	    
	    //for (int i = 0; i < yVect.size(); i++){
			//std::cout<<yVect.at(i)<<' ';
		//}
		
		speed(left, right);				//setting speed
		usleep(10000);					//deletion of this could remove the shaking problem
  } //while
	
} // main



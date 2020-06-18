#include "robot.hpp"

/**
 * Horizontal pixel Function
 * Takes data from camera image and builds a 1D array of pixel values on a line
 * Uses that array to tell the robot where to move
 */

int horizontalPixel(){
	int redCount = 0;
	
	int* pixelArray = new int[50]; //Creates pixel array
	
	for(int i = 0; i < 50; i++){ //Runs through a line of pixels
		pixelArray[i] = get_pixel(cameraView, 10, 50 + i, 0); //Builds an array of pixels on a line
		if(pixelArray[i] == 255){
			pixelArray[i] = 1; //Sets all white pixels to 1
			redCount = redCount + 1;
		}
		else{
			pixelArray[i] = 0; //Sets all other pixels to 0
		}
	}
	std::cout<<redCount<<std::endl;
	if(redCount >= 20){ 
		return(1);
	}
	
	return(0);
}

/**
 * Right side pixel function 
 * Takes data from camera image and builds a 1D array of the pixel values on a line
 * The line is on the right side of the image, used to tell the robot when to turn right when there is a sharp turn
 */

int rightSidePixel(){
	int redCount = 0;
	
	int* pixelArray = new int[70]; //Creates pixel array
	
	for(int i = 0; i < 70; i++){ //Runs through a line of pixels
		pixelArray[i] = get_pixel(cameraView, i, (cameraView.width - 10), 0); //Builds an array of pixels on a line
		if(pixelArray[i] == 255){
			pixelArray[i] = 1; //Sets all white pixels to 1
			redCount = redCount + 1;
		}
		else{
			pixelArray[i] = 0; //Sets all other pixels to 0
		}
	}
	//std::cout<<redCount<<std::endl;
	if(redCount == 0){ 
		return(1); 
	}
	
	return(0);
}

int leftSidePixel(){
	int redCount = 0;
	
	int* pixelArray = new int[cameraView.height]; //Creates pixel array
	
	for(int i = 0; i < cameraView.height; i++){ //Runs through a line of pixels
		pixelArray[i] = get_pixel(cameraView, i, 10, 0); //Builds an array of pixels on a line
		if(pixelArray[i] == 255){
			pixelArray[i] = 1; //Sets all white pixels to 1
			redCount = redCount + 1;
		}
		else{
			pixelArray[i] = 0; //Sets all other pixels to 0
		}
	}
	
	if(redCount >= 1){
		return(1);
	}
	
	return(0); 
}

int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
    double vLeft = 10.0;
    double vRight = 10.0;
    int leftCount = 0;
    int testCount = 5;
    while(1){
		takePicture();
		/*if(rightSidePixel() == 1){
			vLeft = 10.0;
			vRight = 15.0;
		}*/
		if(leftSidePixel() == 1){
			vLeft = 19.0;
			vRight = 12.0;
			leftCount = 0;
		}
		/*else if(horizontalPixel() == 1){
			vLeft = 20.0;
			vRight = -20.0;
			std::cout<<"Right turn"<<std::endl;
		}*/
		/*else if(rightSidePixel() == 1){
			vLeft = -40.0;
			vRight = 40.0;
		}*/
		else if(leftSidePixel() == 0){
			vLeft = 11;
			vRight = 15;
			leftCount += 1;
			if(leftCount > testCount && testCount > 1){
				for(int i = 0; i < 120; i++){
						vLeft = 10;
						vRight = 15;
						setMotors(vLeft,vRight);
				}
				for(int i = 0; i < 30; i++){
						vLeft = 15;
						vRight = 10;
						setMotors(vLeft,vRight);
				}
				leftCount = 0;
				testCount = 0;
			}
		}
		/*else{
			vLeft = 10.0;
			vRight = 11.0;
		}*/
		setMotors(vLeft,vRight);
		//std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
		usleep(10000);
  } //while

} // main


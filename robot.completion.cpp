#include "robot.hpp"

/**
 * Horizontal pixel Function
 * Takes data from camera image and builds a 1D array of pixel values on a line
 * Uses that array to tell the robot where to move
 */

int horizontalPixel(){
	int whiteCount = 0;
	int whitePositions = 0;
	float whiteAverage = 0;
	
	int* pixelArray = new int[cameraView.width]; //Creates pixel array
	
	for(int i = 0; i < cameraView.width; i++){ //Runs through a line of pixels
		pixelArray[i] = get_pixel(cameraView, (cameraView.height/4), i, 3); //Builds an array of pixels on a line
		if(pixelArray[i] == 255){
			pixelArray[i] = 1; //Sets all white pixels to 1
			whiteCount = whiteCount + 1;
		}
		else{
			pixelArray[i] = 0; //Sets all other pixels to 0
		}
		if(pixelArray[i] == 1){ //Add up the positions of all white pixels
			whitePositions = whitePositions + i;
		}
	}
	
	if(!(whiteCount == 0)){ //If the line contains white pixels
		whiteAverage = (whitePositions / whiteCount); //Get the middle position of the white pixels
	}
	if(whiteCount == 0){ //If there are no white pixels on the line, do a 180 degree turn
		return(5);
	}
		
	if(whiteAverage > (cameraView.width/3 * 2)){
		return(3); //If the white line is to the right of the center more, turn left more
	}
	if(whiteAverage < (cameraView.width/3)){
		return(4); //If the white line is to the left of the center more, turn right more
	}		
	if(whiteAverage > (cameraView.width/2)){
		return(1); //If the white line is to the right of the center, turn left
	}
	if(whiteAverage < (cameraView.width/2)){
		return(2); //If the white line is to the left of the center, turn right
	}
	
	return(0); //If the white line is in the center, move straight
}

/**
 * Right side pixel function
 * Takes data from camera image and builds a 1D array of the pixel values on a line
 * The line is on the right side of the image, used to tell the robot when to turn right when there is a sharp turn
 */

int rightSidePixel(){
	int whiteCount = 0;
	
	int* pixelArray = new int[cameraView.height]; //Creates pixel array
	
	for(int i = 0; i < cameraView.height; i++){ //Runs through a line of pixels
		pixelArray[i] = get_pixel(cameraView, i, (cameraView.width - 10), 3); //Builds an array of pixels on a line
		if(pixelArray[i] == 255){
			pixelArray[i] = 1; //Sets all white pixels to 1
			whiteCount = whiteCount + 1;
		}
		else{
			pixelArray[i] = 0; //Sets all other pixels to 0
		}
	}
	
	if(whiteCount > 2){ //If there are white pixels in the array
		return(1); //Turn the robot right sharply
	}
	
	return(0); //Otherwise move straight
}

int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
    double vLeft = 10.0;
    double vRight = 10.0;
    while(1){
		takePicture();
		if(rightSidePixel() == 1){
			vLeft = 60.0;
			vRight = 10.0;
		}
		else if(horizontalPixel() == 1){
			vLeft = 12.0;
			vRight = 10.0;
		}
		else if(horizontalPixel() == 2){
			vLeft = 10.0;
			vRight = 12.0;
		}
		else if(horizontalPixel() == 3){
			vLeft = 20.0;
			vRight = 10.0;
		}
		else if(horizontalPixel() == 4){
			vLeft = 10.0;
			vRight = 20.0;
		}
		else if(horizontalPixel() == 5){
			vLeft = -40.0;
			vRight = 40.0;
		}
		else if(horizontalPixel() == 0){
			vLeft = 10.0;
			vRight = 10.0;
		}
		setMotors(vLeft,vRight);
		//std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
		usleep(10000);
  } //while

} // main


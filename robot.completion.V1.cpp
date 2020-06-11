#include "robot.hpp"

/**
 * pixel Function
 * Takes data from camera image and builds a 1D array of pixel values on a line
 * Uses that array to tell the robot where to move
 */

int pixel(){
	int whiteCount = 0;
	int whitePositions = 0;
	float whiteAverage = 0;
	
	int* pixelArray = new int[cameraView.width];
	
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
			std::cout<<whitePositions<<std::endl;
		}
	}
	
	if(!(whitePositions == 0 || whiteCount == 0)){ //If the line contains white pixels
		whiteAverage = (whitePositions / whiteCount); //Get the middle position of the white pixels
	}
	if(whitePositions == 0 || whiteCount == 0){ //If there are no white pixels on the line, do a 180 degree turn
		return(5);
	}
	
	if(whiteCount > 10){ //If there are alot of white pixels (indicating a sudden turn), turn right sharply
		return(3);
	}
			
	if(whiteAverage > (cameraView.width/2)){
		return(1); //If the white line is to the right of the center, turn left
	}
	if(whiteAverage < (cameraView.width/2)){
		return(2); //If the white line is to the left of the center, turn right
	}
	if(whiteAverage > (cameraView.width/3 * 2)){
		return(3); //If the white line is to the right of the center more, turn left more
	}
	if(whiteAverage < (cameraView.width/3)){
		return(4); //If the white line is to the left of the center more, turn right more
	}
	
	return(0); //If the white line is in the center, move straight
}

int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
    double vLeft = 10.0;
    double vRight = 10.0;
    while(1){
		takePicture();
		//SavePPMFile("i0.ppm",cameraView);
		//pixel();
		if(pixel() == 1){
			vLeft = 12.0;
			vRight = 10.0;
		}
		if(pixel() == 2){
			vLeft = 10.0;
			vRight = 12.0;
		}
		if(pixel() == 3){
			vLeft = 20.0;
			vRight = 10.0;
		}
		if(pixel() == 4){
			vLeft = 10.0;
			vRight = 20.0;
		}
		if(pixel() == 5){
			vLeft = 0.0;
			vRight = 180.0;
		}
		if(pixel() == 0){
			vLeft = 10.0;
			vRight = 10.0;
		}
		setMotors(vLeft,vRight);
		//std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
		usleep(10000);
  } //while

} // main




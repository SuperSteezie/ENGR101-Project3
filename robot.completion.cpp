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
	
	int* pixelArray = new int[cameraView.width];
	
	for(int i = 0; i < cameraView.width; i++){ //Runs through a line of pixels
		pixelArray[i] = get_pixel(cameraView, (30), i, 3); //Builds an array of pixels on a line
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

int cornerPixel(){
	int whiteCount = 0;
	
	int* pixelArray = new int[cameraView.height];
	
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
	
	if(whiteCount > 2){
		return(1);
	}
	
	return(0);
}

int challengeMaze(){
	int redCount1 = 0;
	int redCount2 = 0;
	int isRed = 0;
	double vLeft = 0;
	double vRight = 0;
	takePicture();
	for(int i = 0; i < cameraView.height; i++){ 
		isRed = get_pixel(cameraView, i, 60, 0); 
		if(isRed == 255){
			redCount1 = 1;
		}
		isRed = get_pixel(cameraView, i, 90, 0); 
		if(isRed == 255){
			redCount2 = 1;
		}
	}
	if(redCount1 == 1 && redCount2 == 1){
		for(int i = 0; i < 10; i++){
			vLeft = 16.7;
			vRight = -16.7;
			setMotors(vLeft,vRight);
		}
	}else if(redCount1 == 0 && redCount2 == 0){
		vLeft = 400;
		vRight = 400;
		setMotors(vLeft,vRight);
		for(int i = 0; i < 10; i++){
			vLeft = -16.7;
			vRight = 16.7;
			setMotors(vLeft,vRight);
		}
	}else if(redCount1 == 0 && redCount2 == 1){
		for(int i = 0; i < 10; i++){
			vLeft = -19;
			vRight = 19;
			setMotors(vLeft,vRight);
		}
		vLeft = 200;
		vRight = 200;
		setMotors(vLeft,vRight);
	}else if(redCount1 == 1 && redCount2 == 0){
		for(int i = 0; i < 10; i++){
			vLeft = 17;
			vRight = -17;
			setMotors(vLeft,vRight);
		}
		vLeft = 200;
		vRight = 200;
		setMotors(vLeft,vRight);
		for(int i = 0; i < 10; i++){
			vLeft = -16;
			vRight = 16;
			setMotors(vLeft,vRight);
		}
	}
	
}

int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
    double vLeft = 10.0;
    double vRight = 10.0;
    int challenge = 0;
    takePicture();
    int* pixelArray = new int[cameraView.height];
    for(int i = 0; i < cameraView.height; i++){ //Runs through a line of pixels
	pixelArray[i] = get_pixel(cameraView, i, (cameraView.width), 0); //Builds an array of pixels on a line
	if(pixelArray[i] == 255){
			challenge = 1;
		}
	}
	vLeft = 1200;
	vRight = 1200;
	setMotors(vLeft,vRight);
    while(1){
		if(challenge == 0){
			takePicture();
			//SavePPMFile("i0.ppm",cameraView);
			if(cornerPixel() == 1){
				vLeft = 40.0;
				vRight = 10.0;
				std::cout<<"hello"<<std::endl;
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
		}else if(challenge == 1){
			challengeMaze();
		}
		//std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
		usleep(10000);
  } //while

} // main

#include "robot.hpp"

int pixel(){
	int whiteCount = 0;
	int whitePositions = 0;
	float whiteAverage = 0;
	
	int leftCount = 0;
	int rightCount = 0;
	
	int* pixelArray = new int[cameraView.width];
	int* lostLeft = new int[cameraView.height];
	int* lostRight = new int[cameraView.height];
	
	for(int i = 0; i < cameraView.width; i++){
		pixelArray[i] = get_pixel(cameraView, (cameraView.height/4), i, 3);
		if(pixelArray[i] == 255){
			pixelArray[i] = 1;
			whiteCount = whiteCount + 1;
		}
		else{
			pixelArray[i] = 0;
		}
		
		
		if(pixelArray[i] == 1){
			whitePositions = whitePositions + i;
			std::cout<<whitePositions<<std::endl;
		}
	}
	
	for(int i = 0; i < cameraView.height; i++){
		lostLeft[i] = get_pixel(cameraView, i, (cameraView.width/4), 3);
		lostRight[i] = get_pixel(cameraView, i, ((cameraView.width/4) * 3), 3);
		if(lostLeft[i] == 255){
			leftCount = leftCount + 1;
		}
		if(lostRight[i] == 255){
			rightCount = rightCount + 1;
		}
	}
	
	if(!(whitePositions == 0 || whiteCount == 0)){
		whiteAverage = (whitePositions / whiteCount);
	}
	if(whitePositions == 0 || whiteCount == 0){
		if(leftCount >= rightCount){
			return(4);
		}
		else{
			return(3);
		}
	}
			
	if(whiteAverage > (cameraView.width/2)){
		return(1);
	}
	if(whiteAverage < (cameraView.width/2)){
		return(2);
	}
	if(whiteAverage > (cameraView.width/3)){
		return(3);
	}
	if(whiteAverage < (cameraView.width/3)){
		return(4);
	}
	
	return(0);
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
		pixel();
		if(pixel() == 1){
			vLeft = 12.0;
			vRight = 10.0;
		}
		if(pixel() == 2){
			vLeft = 10.0;
			vRight = 12.0;
		}
		if(pixel() == 3){
			vLeft = 14.0;
			vRight = 10.0;
		}
		if(pixel() == 4){
			vLeft = 10.0;
			vRight = 14.0;
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




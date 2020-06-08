
#include "robot.hpp"
int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
    double vLeft = 10.0;
    double vRight = 10.0;
    int whiteAt = 0;
    //takePicture();
    //SavePPMFile("i0.ppm",cameraView);
    while(1){
		takePicture();
		for (int i = 0; i < 150; i++){
			int pix = get_pixel(cameraView, 50, i , 3);
			int isWhite;
			if (pix > 250){
					isWhite = 1;
					whiteAt = i;
					std::cout<<isWhite<<" ";
			}else{
					isWhite = 0;
			}	
			
		}
		if(whiteAt < 100){
			vLeft = 15.0;
			vRight = 10.0;
		}else if(whiteAt > 100){
			vLeft = 10.0;
			vRight = 15.0;
		}else{
			vLeft = 10.0;
			vRight = 10.0;
		}
		std::cout<<std::endl;
		setMotors(vLeft,vRight);   
		std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
		usleep(10000);
		
	} //while
	
} // main


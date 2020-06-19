#include "robot.hpp"

/*
 * Core code function
 * Function used for the core maze, robot successfully reaches the flag
 */
int coreCodeFunction(){
	int whiteCount = 0;
	int whitePositions = 0;
	float whiteAverage = 0;

	int leftCount = 0;
	int rightCount = 0;

	int* pixelArray = new int[cameraView.width];
	int* lostLeft = new int[cameraView.height];
	int* lostRight = new int[cameraView.height];

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

	for(int i = 0; i < cameraView.height; i++){ //Loop to identify wether line to the left or line to the right of the image has more pixels
		lostLeft[i] = get_pixel(cameraView, i, (cameraView.width/4), 3); //Count up pixels on left side line of image
		lostRight[i] = get_pixel(cameraView, i, ((cameraView.width/4) * 3), 3); //Count up pixels on right side line of image
		if(lostLeft[i] == 255){
			leftCount = leftCount + 1; //Count up white pixels on left side line of image
		}
		if(lostRight[i] == 255){
			rightCount = rightCount + 1; //Count up white pixels on right side line of image
		}
	}

	if(!(whitePositions == 0 || whiteCount == 0)){ //If the line contains white pixels
		whiteAverage = (whitePositions / whiteCount); //Get the middle position of the white pixels
	}
	if(whitePositions == 0 || whiteCount == 0){ //If there are no white pixels in the line (robot has lost the line)
		if(leftCount >= rightCount){ //If there was / were more pixels in the left side of the image
			return(4); //Turn right
		}
		else{
			return(3); //Otherwise turn left
		}
	}

	if(whiteAverage > (cameraView.width/2)){
		return(1); //If the white line is to the right of the center, turn left
	}
	if(whiteAverage < (cameraView.width/2)){
		return(2); //If the white line is to the left of the center, turn right
	}
	if(whiteAverage > (cameraView.width/3)){
		return(3); //If the white line is to the right of the center more, turn left more
	}
	if(whiteAverage < (cameraView.width/3)){
		return(4); //If the white line is to the left of the center more, turn right more
	}

	return(0); //If the white line is in the center, move straight
}

/*
 * Completion code function #1
 * Function used for the completion maze, robot successfully reaches the flag
 */
int completionCodeFunction(){
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

/*
 * Completion code function #2
 * Second function used for the completion maze, robot successfully reaches the flag
 */
int completionCodeFunction2(){
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

/*
 * Challenge code function 
 * Function used for the challenge maze, robot successfully reaches the flag
 */
int challengeCodeFunction(){
	int redCount = 0;

	int* pixelArray = new int[cameraView.height]; //Creates pixel array

	for(int i = 0; i < cameraView.height; i++){ //Runs through a line of pixels
		pixelArray[i] = get_pixel(cameraView, i, 10, 0); //Builds an array of pixels on a line
		if(pixelArray[i] == 255){
			pixelArray[i] = 1; //Sets all red pixels to 1
			redCount = redCount + 1;
		}
		else{
			pixelArray[i] = 0; //Sets all other pixels to 0
		}
	}

	if(redCount >= 1){
		return(1); //If there are red pixels in the array, turn left
	}

	return(0); //Otherwise turn right
}

int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
	bool inputCheck = true;
	std::string mazeInput;

	while(inputCheck){
		std::cout<<"What maze (core, completion, challenge): "<<std::endl; //AAsks for user input on what maze is being run
		std::cin >> mazeInput;
		if(mazeInput == "core" || mazeInput == "completion" || mazeInput == "challenge"){ //If input is valid, exit loop
			inputCheck = false;
		}
		else{ //Otherwise print error message and ask again
			std::cout<<"Invalid input, please enter 'core', 'completion', or 'challenge'"<<std::endl;
		}
	}

    double vLeft = 10.0;
    double vRight = 10.0;
    int leftCount = 0;
    int testCount = 5;
    while(1){ //Run loop forever
		takePicture();
		if(mazeInput == "core"){
			if(coreCodeFunction() == 1){
				vLeft = 12.0;
				vRight = 10.0;
			}
			if(coreCodeFunction() == 2){
				vLeft = 10.0;
				vRight = 12.0;
			}
			if(coreCodeFunction() == 3){
				vLeft = 14.0;
				vRight = 10.0;
			}
			if(coreCodeFunction() == 4){
				vLeft = 10.0;
				vRight = 14.0;
			}
			if(coreCodeFunction() == 0){
				vLeft = 10.0;
				vRight = 10.0;
			}
		}

		if(mazeInput == "completion"){
			if(completionCodeFunction2() == 1){
				vLeft = 60.0;
				vRight = 10.0;
			}
			else if(completionCodeFunction() == 1){
				vLeft = 12.0;
				vRight = 10.0;
			}
			else if(completionCodeFunction() == 2){
				vLeft = 10.0;
				vRight = 12.0;
			}
			else if(completionCodeFunction() == 3){
				vLeft = 20.0;
				vRight = 10.0;
			}
			else if(completionCodeFunction() == 4){
				vLeft = 10.0;
				vRight = 20.0;
			}
			else if(completionCodeFunction() == 5){
				vLeft = -40.0;
				vRight = 40.0;
			}
			else if(completionCodeFunction() == 0){
				vLeft = 10.0;
				vRight = 10.0;
			}
		}

		if(mazeInput == "challenge"){
			if(challengeCodeFunction() == 1){
				vLeft = 19.0;
				vRight = 12.0;
				leftCount = 0;
			}
			else if(challengeCodeFunction() == 0){
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
		}
		setMotors(vLeft,vRight);
		usleep(10000);
  } //while

} // main

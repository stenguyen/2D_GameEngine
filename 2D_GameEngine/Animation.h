#pragma once

//class but everything is public instead of private
struct Animation {

	//corresponds to the position of the animation in the tilesheet (0 for start)
	int index;
	//the number of frames in the animation (0 by default bc animated is false)
	int frames;
	//speed represents the delay between frames in milliseconds 
	int speed;

	//default constructor (not going to be used)
	Animation(){}
	//constructor given index, frames, and speed
	Animation(int i, int f, int s) {
		index = i;
		frames = f;
		speed = s;
	}

};
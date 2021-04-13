#include<iostream>
#include"opencv.h"

using namespace std;

int main()
{
	cout << "start picture" << endl;
	take_picture("cam01.jpg");
	
	cout << "start video" << endl;
	take_video("video.avi");
	
	cout << "start face" << endl;
	face_detection();
	
	cout << "start eyes" << endl;
	eyes_detection();
	
	cout << "start image" << endl;
	iamge_save();
}

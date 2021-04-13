#include<opencv2/opencv.hpp>
#include"opencv.h"

using namespace std;
using namespace cv;

void take_picture(string file_name)
{
	VideoCapture camera(0);
	if(!camera.isOpened())
	{
		cout <<"Can't Open Camera" << endl;
	}
	
	namedWindow("CAM", WINDOW_AUTOSIZE);
	Mat frame;
	camera >> frame;
	
	imwrite(file_name, frame);
	while(1)
	{
		imshow("CAM", frame);
		if(waitKey(10) >= 0) break;
	}
}

// file_name이 .avi여야 한다. 
void take_video(string file_name)
{
	VideoCapture camera(0);
	if(!camera.isOpened())
	{
		cout << "Can't Open Camera" << endl;
	}
	
	int frame_width = camera.get(cv::CAP_PROP_FRAME_WIDTH);
	int frame_height = camera.get(cv::CAP_PROP_FRAME_HEIGHT);

	VideoWriter video(file_name, VideoWriter::fourcc('M','J','P','G'), 10, Size(frame_width, frame_height));
	
	while(1)
	{
		Mat frame;
		camera >> frame;
		if(frame.empty()) break;
		
		video.write(frame);
		imshow("Video", frame);
		
		if(waitKey(10) >= 0) break;
	}
	video.release();
}

void face_detection()
{	
	VideoCapture camera(0);
	if(!camera.isOpened())
	{
		cout << "Can't Open Camera" << endl;
	}
	
	CascadeClassifier face_classifier;
	face_classifier.load( "/home/pi/opencv/data/haarcascades/haarcascade_frontalface_default.xml" );
	Mat frame;
	
	while(1)
	{
		
		camera >> frame;
		
		if(frame.empty()) break;
	
		Mat grayFrame;
		cvtColor( frame, grayFrame, COLOR_BGR2GRAY );
		equalizeHist( grayFrame, grayFrame );
			
		vector<Rect> faces;
			
		face_classifier.detectMultiScale( grayFrame, faces );
			
		for(int i = 0; i < faces.size(); i++)
		{
			Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
			Point tr(faces[i].x, faces[i].y);
				
			rectangle(frame, lb, tr, Scalar(0, 255, 0));
		}
		imshow("Face_Detection", frame);
		if(waitKey(1) == 27) break;
	}
	
}


void eyes_detection()
{
	VideoCapture camera(0);
	if(!camera.isOpened())
	{
		cout << "Can't Open Camera" << endl;
	}
	
	CascadeClassifier face_classifier;
	face_classifier.load( "/home/pi/opencv/data/haarcascades/haarcascade_eye.xml" );
	Mat frame;
	
	while(1)
	{
		camera >> frame;	
		if(frame.empty()) break;
	
		Mat grayFrame;
		cvtColor( frame, grayFrame, COLOR_BGR2GRAY );
		equalizeHist( grayFrame, grayFrame );
			
		vector<Rect> eyes;
			
		face_classifier.detectMultiScale( grayFrame, eyes );
			
		for(int i = 0; i < eyes.size(); i++)
		{
			Point lb(eyes[i].x + eyes[i].width, eyes[i].y + eyes[i].height);
			Point tr(eyes[i].x, eyes[i].y);
				
			rectangle(frame, lb, tr, Scalar(0, 255, 0));
		}
		imshow("Eyes_Detection", frame);
		if(waitKey(1) == 27) break;
	}
}

void iamge_save()
{
	const string img_file{"image.jpg"};
	
	Mat img = imread(img_file, 1);
	if(!img.data)
	{
		cout << "Can't Open File " << img_file << endl;
	}
	
	Mat grayImg;
	cvtColor(img, grayImg, COLOR_BGR2GRAY);
	
	imwrite("GrayImage.jpg", grayImg);
}

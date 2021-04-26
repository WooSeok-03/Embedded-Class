import cv2
import timeit

def videoDetector(cam,cascade_video):   # Video Face Detecting
	cascade = cv2.CascadeClassifier(cascade_video)
	
	while True:
		ret,img = cam.read()
		img = cv2.resize(img,dsize=None,fx=0.75,fy=0.75)
		gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
		results = cascade.detectMultiScale(gray, 1.2, 5)        
        
		for box in results:
			x, y, w, h = box
			cv2.rectangle(img, (x,y), (x+w, y+h), (255,0,0), 2)
			
		terminate_t = timeit.default_timer()
		
		cv2.imshow('facenet',img)
		if cv2.waitKey(1) > 0:
		   break
        
def imgDetector(img,cascade_image):     # Image Face Detecting
	cascade = cv2.CascadeClassifier(cascade_image)
	img = cv2.resize(img,dsize=None,fx=0.5,fy=0.5)
	gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	results = cascade.detectMultiScale(gray, 1.2, 5)

	for box in results:
		x, y, w, h = box
		cv2.rectangle(img, (x,y), (x+w, y+h), (255,0,0), 2)
		
	cv2.imshow('facenet',img)  
	cv2.waitKey(10000)
	
cascade_video = 'haarcascade_profileface.xml'
cascade_image = 'haarcascade_frontalface_default.xml'

cam = cv2.VideoCapture('sample.mp4')
img = cv2.imread('sample.jpg')

# Video Face Detecting
#videoDetector(cam,cascade_video)

# Image Face Detecting
imgDetector(img,cascade_image)

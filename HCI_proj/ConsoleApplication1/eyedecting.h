#pragma once
#include <opencv2\opencv.hpp>
#include<opencv\cv.h>
#include<opencv\cxcore.h>
#include<opencv\cvaux.h>
#include<opencv\highgui.h>
using namespace std;
using namespace cv;


class VIDEO {	// VIDEO 클래스
	private:		// 구현시 변경되면 안되는 것들
		String face_cascade_name = "haarcascade_frontalface_alt.xml";		// 정면얼굴 인식 관련 .xml파일
		String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";	// 양쪽 눈 인식 관련 .xml파일
		CascadeClassifier face_cascade;	// 종속분류사클래스 face_cascade 지정
		CascadeClassifier eyes_cascade; // 종속분류사클래스 eyes_cascade 지정
		string window_name = "Face detection";	// window창 이름
	public:
		int videoPlay();	// cam화면 window로 영상처리 함수
		void detectAndDisplay(Mat frame);	// face와 eyes인식 관련 함수
};
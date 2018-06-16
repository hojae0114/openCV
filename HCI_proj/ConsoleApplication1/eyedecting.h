#pragma once
#include <opencv2\opencv.hpp>
#include<opencv\cv.h>
#include<opencv\cxcore.h>
#include<opencv\cvaux.h>
#include<opencv\highgui.h>
using namespace std;
using namespace cv;


class VIDEO {	// VIDEO Ŭ����
	private:		// ������ ����Ǹ� �ȵǴ� �͵�
		String face_cascade_name = "haarcascade_frontalface_alt.xml";		// ����� �ν� ���� .xml����
		String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";	// ���� �� �ν� ���� .xml����
		CascadeClassifier face_cascade;	// ���Ӻз���Ŭ���� face_cascade ����
		CascadeClassifier eyes_cascade; // ���Ӻз���Ŭ���� eyes_cascade ����
		string window_name = "Face detection";	// windowâ �̸�
	public:
		int videoPlay();	// camȭ�� window�� ����ó�� �Լ�
		void detectAndDisplay(Mat frame);	// face�� eyes�ν� ���� �Լ�
};
#include"eyedecting.h"
#include"time.h"
#define norm_rand() (rand()/(RAND_MAX + 1.0))

int check = 0;

int VIDEO::videoPlay() {
	VideoCapture vc(0);	// 기본 backend를 사용하여 기본 카메라를 열기위하여, 인자로 0을 전달.
	Mat frame;
	Mat img;
	


//	srand((unsigned)time(NULL));
	if (!vc.isOpened()) {	// video(즉, 기본카메라) 열기 실패시
		printf("failed\n");
	}

	//-- 1. Load the cascades
	if (!face_cascade.load(face_cascade_name)){	// face_cascade_name 로드 실패시
		printf("--(!)Error loading\n");
		return -1;
	};

	if (!eyes_cascade.load(eyes_cascade_name)){ // eyes_cascade_name 로드 실패시
		printf("--(!)Error loading\n");
		return -1;
	};

	if (vc.isOpened())	// video(즉, 기본카메라) 열기 성공시
	{
		while (1) {
			vc >> img;

			vc.read(frame);

			//3. Apply the classifier to the frame
			if (!frame.empty())		// 불러온 frame에 데이터(row,col을 보면서)가 비어있는지 조사.
			{
				detectAndDisplay(frame);	//'frame'을 인자로 전달받아 detectAndDisplay함수 실행
			}
			else    // 실패시
			{
				printf(" --(!) No captured frame -- Break!");
				break;
			}

			if (waitKey(10) == 27) { // key number for 'ESC'
				break; 
			}
			check = check + 1000;
		}
		destroyAllWindows();	// 모든 Windows창 종료
	}
	
	return 0;
}

void VIDEO::detectAndDisplay(Mat frame) {
	vector<Rect> faces;
	Mat frame_gray;
	int arr[10] = { 0, };
	int count = 0;
	//	int current_time = 0;

	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	//-- Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

	for (size_t i = 0; i < faces.size(); i++)
	{
		int tmp = 0;
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		ellipse(frame, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);

		Mat faceROI = frame_gray(faces[i]);
		std::vector<Rect> eyes;

		//-- In each face, detect eyes
		eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
		int k = 0;
		for (size_t j = 0; j < eyes.size(); j++)
		{
			tmp = 1;
			Point center(faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5);
			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);

			circle(frame, center, radius, Scalar(255, 0, 0), 4, 8, 0);
			arr[k++]=1;
		}

	}
	count = 0;
	for (int l = 0; l < 10; l++) {
		count = count + arr[l];
	}
	if (count == 0) {
		printf("언제졸았니? : %d\n", check);
	}
	
	//-- Show what you got
	imshow(window_name, frame);
}



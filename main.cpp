#include <opencv2/opencv.hpp>
#include <sstream>
#include <time.h>

const std::string windowName = "Window";

//960x720->640x480 1920x1080->854x480
const int INPUT_IMAGE_WIDTH = 960;
const int INPUT_IMAGE_HEIGHT = 720;

const int RESIZED_IMAGE_WIDTH = 640;
const int RESIZED_IMAGE_HEIGHT = 480;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

const int N = 30; //FPS ��������� ��� ������� �� N �������

int main(int argc, char **argv) {
	//������
	cv::VideoCapture camera(0);
	camera.set(CV_CAP_PROP_FRAME_WIDTH, INPUT_IMAGE_WIDTH);
	camera.set(CV_CAP_PROP_FRAME_HEIGHT, INPUT_IMAGE_HEIGHT);
	if (!camera.isOpened()) return 1; //���� ������ ������� ������

	//������
	cv::CascadeClassifier face_cascade("C:\\123\\C++\\Libraries\\OpenCV\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml");
	if (face_cascade.empty()) return 1;

	//����
	cv::namedWindow(windowName);

	//������ ��� FPS
	clock_t time = clock();

	int counter = 0; //������� ��� FPS
	std::string FPS ="";

	for(;;) {

		cv::Mat frame;
		camera >> frame;
		if (frame.empty()) continue; //���� ����� �� ��������

		//��������� �����������
		cv::resize(frame, frame, cv::Size(RESIZED_IMAGE_WIDTH,
				RESIZED_IMAGE_HEIGHT));
		cv::Mat grayFrame;
		cv::cvtColor(frame, grayFrame, CV_BGR2GRAY);
		cv::equalizeHist(grayFrame, grayFrame);

		//����� ���
		std::vector<cv::Rect> faces;
		face_cascade.detectMultiScale(grayFrame, faces, 1.3, 4, 0, cv::Size(80, 80));

		//���������
		for (unsigned int i = 0; i < faces.size(); i++) {
			cv::Point center(faces[i].x + faces[i].width * 0.5,
					faces[i].y + faces[i].height * 0.5);
			cv::ellipse(frame, center,
					cv::Size(faces[i].width * 0.5, faces[i].height * 0.5),
					0, 0, 360, cv::Scalar(255, 0, 255 ), 4, 8, 0);
		}

		//������ ����������� ��� ������ ����
		cv::resize(frame, frame, cv::Size(WINDOW_WIDTH, WINDOW_HEIGHT));

		//������� � ��������� FPS
		counter = (counter + 1) % N;
		if (counter == 0) {
			time = clock() - time;
			int iFPS = ((double)N * CLOCKS_PER_SEC) / (time);
			std::stringstream sstr;
			sstr << iFPS;
			FPS = sstr.str();
			time = clock();
		}
		cv::Point p(10, WINDOW_HEIGHT - 10);
		cv::Scalar color(0, 255, 0);
		cv::putText(frame, FPS, p, cv::FONT_HERSHEY_DUPLEX, 1, color);

		imshow(windowName, frame);
		if(cv::waitKey(30) >= 0) break;
	}

}

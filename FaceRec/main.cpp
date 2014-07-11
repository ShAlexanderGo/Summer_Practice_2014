#include <opencv2/opencv.hpp>
#include <sstream>
#include <time.h>

const std::string windowName = "Window";
const std::string cascadePath = "haarcascade_frontalface_alt.xml";

const int INPUT_IMAGE_WIDTH = 864;
const int INPUT_IMAGE_HEIGHT = 480;

const int RESIZED_IMAGE_WIDTH = 800;
const int RESIZED_IMAGE_HEIGHT = 450;

const int WINDOW_WIDTH = 533;
const int WINDOW_HEIGHT = 300;

const int SIZE = 80;

const int N = 30; //FPS ��������� ��� ������� �� N �������

int main(int argc, char **argv) {
	//������
	cv::VideoCapture camera(0);
	camera.set(CV_CAP_PROP_FRAME_WIDTH, INPUT_IMAGE_WIDTH);
	camera.set(CV_CAP_PROP_FRAME_HEIGHT, INPUT_IMAGE_HEIGHT);
	if (!camera.isOpened()) return 1; //���� ������ ������� ������

	//������
	cv::CascadeClassifier face_cascade(cascadePath);
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
		cv::Mat originalFrame = frame;
		cv::resize(frame, frame, cv::Size(RESIZED_IMAGE_WIDTH,
				RESIZED_IMAGE_HEIGHT));
		cv::Mat grayFrame;
		cv::cvtColor(frame, grayFrame, CV_BGR2GRAY);
		cv::equalizeHist(grayFrame, grayFrame);

		//����� ���
		std::vector<cv::Rect> faces;
		face_cascade.detectMultiScale(grayFrame, faces, 1.3, 4, 0, cv::Size(SIZE, SIZE));

		//����� ��� ������ ������
		cv::resize(originalFrame, originalFrame, cv::Size(WINDOW_WIDTH, WINDOW_HEIGHT));

		//���������
		double scale = (double)WINDOW_WIDTH / (double)RESIZED_IMAGE_WIDTH;
		for (unsigned int i = 0; i < faces.size(); i++) {
			faces[i].x = (int)(scale * (double)faces[i].x);
			faces[i].y = (int)(scale * (double)faces[i].y);
			faces[i].width = (int)(scale * (double)faces[i].width);
			faces[i].height = (int)(scale * (double)faces[i].height);
			cv::rectangle(originalFrame, faces[i], cv::Scalar(0, 255, 0), 2);
		}

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
		cv::Point p(10, 200);
		cv::Scalar color(0, 255, 0);
		cv::putText(originalFrame, FPS, p, cv::FONT_HERSHEY_DUPLEX, 1, color);

		imshow(windowName, originalFrame);
		if(cv::waitKey(30) >= 0) break;
	}

}

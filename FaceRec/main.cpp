#include <opencv2/opencv.hpp>
#include <sstream>
#include <time.h>

const std::string windowName = "Window";
const std::string PathCascadeFrontalFace = "cascades\\haarcascade_frontalface_alt_tree.xml";

const int INPUT_IMAGE_WIDTH = 640;
const int INPUT_IMAGE_HEIGHT = 480;

const double scaleFactor = 1.35;
const int minNeighbors = 2;
const int flags = 0;
const int minSize = 40;

const int N = 30; //FPS считается как среднее за N фреймов

int main(int argc, char **argv) {
	//Камера
	cv::VideoCapture camera(0);
	camera.set(CV_CAP_PROP_FRAME_WIDTH, INPUT_IMAGE_WIDTH);
	camera.set(CV_CAP_PROP_FRAME_HEIGHT, INPUT_IMAGE_HEIGHT);
	if (!camera.isOpened()) return 1; //Если нельзя открыть камеру

	//Каскад
	cv::CascadeClassifier cascadeFrontalFace(PathCascadeFrontalFace);
	if (cascadeFrontalFace.empty()) return 1;

	//Окно
	cv::namedWindow(windowName);

	//Таймер для FPS
	clock_t time = clock();

	int counter = 0; //счётчик для FPS
	std::string FPS ="";
	std::string cleanFPS ="";

	for(int i = 0; i < N; i++) {
		cv::Mat frame;
		camera >> frame;
	}
	{
		time = clock() - time;
		int iFPS = ((double)N * CLOCKS_PER_SEC) / (time);
		std::stringstream sstr;
		sstr << iFPS;
		cleanFPS = sstr.str();
		time = clock();
	}

	for(;;) {

		cv::Mat frame;
		camera >> frame;
		if (frame.empty()) continue; //если фрейм не считался

		//обработка изображения
		cv::Mat grayFrame;
		cv::cvtColor(frame, grayFrame, CV_BGR2GRAY);
		cv::equalizeHist(grayFrame, grayFrame);

		//поиск лиц
		std::vector<cv::Rect> faces;
		cascadeFrontalFace.detectMultiScale(grayFrame, faces, scaleFactor, minNeighbors, flags, cv::Size(minSize, minSize));

		//рисование
		for(unsigned int i = 0; i < faces.size(); i++) {
			cv::rectangle(frame, faces[i], cv::Scalar(0, 255, 0), 2);
		}

		//подсчёт и рисование FPS
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
		cv::putText(frame, cleanFPS + " " + FPS, p, cv::FONT_HERSHEY_DUPLEX, 1, color);

		imshow(windowName, frame);

		if(cv::waitKey(1) >= 0) break;
	}

	cv::destroyAllWindows();
	camera.release();

}

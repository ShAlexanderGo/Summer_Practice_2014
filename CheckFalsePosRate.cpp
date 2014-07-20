#include <opencv2/opencv.hpp>
#include <sstream>
#include <time.h>

const std::string windowName = "Window";
std::vector<std::string> 			names;
std::vector<cv::CascadeClassifier> 	cascades;
std::vector<cv::Scalar> 			colors;
std::vector< std::vector<int> >		workTimes;
std::vector<int> 					counterErrors;

const int INPUT_IMAGE_WIDTH = 640;
const int INPUT_IMAGE_HEIGHT = 480;

const double scaleFactor = 1.4;
const int minNeighbors = 5;
const int flags = 0;
const int minSize = 0;

const int N = 30; //FPS считается как среднее за N фреймов

int main(int argc, char **argv) {
	//Камера
	cv::VideoCapture camera("480.mp4");
	//camera.set(CV_CAP_PROP_FRAME_WIDTH, INPUT_IMAGE_WIDTH);
	//camera.set(CV_CAP_PROP_FRAME_HEIGHT, INPUT_IMAGE_HEIGHT);
	if (!camera.isOpened()) return 1; //Если нельзя открыть камеру

	names.push_back("cascades\\haarcascade_eye.xml");
	colors.push_back(cv::Scalar(255, 0, 0));
	names.push_back("cascades\\haarcascade_eye_tree_eyeglasses.xml");
	colors.push_back(cv::Scalar(0, 255, 0));
	names.push_back("cascades\\haarcascade_lefteye_2splits.xml");
	colors.push_back(cv::Scalar(0, 0, 255));
	names.push_back("cascades\\haarcascade_righteye_2splits.xml");
	colors.push_back(cv::Scalar(255, 255, 0));
	names.push_back("cascades\\haarcascade_mcs_lefteye.xml");
	colors.push_back(cv::Scalar(255, 0, 255));
	names.push_back("cascades\\haarcascade_mcs_righteye.xml");
	colors.push_back(cv::Scalar(0, 255, 255));
	names.push_back("cascades\\haarcascade_mcs_eyepair_big.xml");
	colors.push_back(cv::Scalar(0, 0, 0));
	names.push_back("cascades\\haarcascade_mcs_eyepair_small.xml");
	colors.push_back(cv::Scalar(255, 255, 255));
	names.push_back("cascades\\haarcascade_mcs_mouth.xml");
	colors.push_back(cv::Scalar(255, 125, 0));//оранжевый
	names.push_back("cascades\\haarcascade_mcs_nose.xml");
	colors.push_back(cv::Scalar(255, 125, 255));//розовый
	for(unsigned int i = 0; i < names.size(); i++) {
		cascades.push_back(cv::CascadeClassifier(names[i]));
		counterErrors.push_back(0);
		workTimes.push_back(*new std::vector<int>);
	}

	//Окно
	cv::namedWindow(windowName);

	//Таймер для FPS
	clock_t time = clock();

	int counter = 0; //счётчик для FPS
	std::string FPS ="";
	int imageCounter = 0;

	for(;;) {

		cv::Mat frame;
		camera >> frame;
		if (frame.empty()) continue; //если фрейм не считался
		//обработка изображения
		cv::Mat grayFrame;
		cv::cvtColor(frame, grayFrame, CV_BGR2GRAY);
		cv::equalizeHist(grayFrame, grayFrame);

		//поиск лиц

		for(unsigned int i = 0; i < cascades.size(); i++) {
			clock_t interval = clock();
			std::vector<cv::Rect> buffer;
			cascades[i].detectMultiScale(grayFrame, buffer, scaleFactor, minNeighbors, flags, cv::Size(minSize, minSize));
			interval = clock() - interval;
			workTimes[i].push_back(interval);
			if(buffer.size() > 0) {
				counterErrors[i] += buffer.size();
				std::cout << names[i] << " " << counterErrors[i] << std::endl;
				for(unsigned int j = 0; j < buffer.size(); j++) {
					std::cout << buffer[j].x << " " << buffer[j].y << " " << buffer[j].width << " " << buffer[j].height << std::endl;
					cv::rectangle(frame, buffer[j], colors[i], 2);
				}
			}
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
		cv::putText(frame, FPS, p, cv::FONT_HERSHEY_DUPLEX, 1, color);

		imageCounter++;
		std::cout << "new image " << imageCounter << "/" <<
				camera.get(CV_CAP_PROP_FRAME_COUNT) << std::endl;
		imshow(windowName, frame);

		if(imageCounter == 1000) break;
		if(cv::waitKey(1) >= 0) break;
	}

	cv::destroyAllWindows();
	camera.release();

	std::cout << "---------------" << std::endl;
	for(unsigned int i = 0; i < names.size(); i++) {
		int avInterval = 0;
		for (unsigned int j = 0; j < workTimes[i].size(); j++) {
			avInterval += workTimes[i][j];
		}
		avInterval = avInterval / workTimes[i].size();
		std::cout << names[i] << " " << avInterval << " " << counterErrors[i] << std::endl;
	}
}

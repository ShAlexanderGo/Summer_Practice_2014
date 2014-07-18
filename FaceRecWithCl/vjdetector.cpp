#include "vjdetector.hpp"

const int VJDetector::N = 30;

const int VJDetector::INPUT_IMAGE_WIDTH = 640;
const int VJDetector::INPUT_IMAGE_HEIGHT = 480;

const std::string VJDetector::WINDOW_NAME = "VJDetector window";

VJDetector::VJDetector() {
	stopFlag = false;
	camera.open(0);
	//if (!camera.isOpened()) return 1;
	camera.set(CV_CAP_PROP_FRAME_WIDTH, INPUT_IMAGE_WIDTH);
	camera.set(CV_CAP_PROP_FRAME_HEIGHT, INPUT_IMAGE_HEIGHT);
	cascadeFrontalFace.load("cascades\\haarcascade_frontalface_alt_tree.xml");
}

void VJDetector::detect() {
	cv::namedWindow(WINDOW_NAME);
	std::thread thW(&VJDetector::threadWindow, this);
	std::thread thC(&VJDetector::threadCompute, this);
	for(;;) {
		if (cv::waitKey(50) >= 0) {
			stopFlag = true;
			break;
		}
	}
	thC.join();
	thW.join();
	cv::destroyAllWindows();
	camera.release();
	return;
}

void VJDetector::threadCompute() {
	clock_t time = clock();
	int counter = 0;
	for(;;) {
		cv::Mat grayFrame;
		mutexFrame.lock();
		if (frame.empty()) {
			mutexFrame.unlock();
			cv::waitKey(10);
			continue;
		}
		cv::cvtColor(frame, grayFrame, CV_BGR2GRAY);
		mutexFrame.unlock();
		cv::equalizeHist(grayFrame, grayFrame);
		std::vector<cv::Rect> preFaces;
		cascadeFrontalFace.detectMultiScale(grayFrame, preFaces, 1.2, 3, 0, cv::Size(40, 40));
		counter++;
		if (counter == N) {
			counter = 0;
			time = clock() - time;
			mutexFPS.lock();
			FPS = std::to_string(CLOCKS_PER_SEC * N / time);
			mutexFPS.unlock();
			time = clock();
		}
		mutexFaces.lock();
		faces.clear();
		faces = preFaces;
		mutexFaces.unlock();
		if (stopFlag) return;
	}
}

void VJDetector::threadWindow() {
	for(;;) {
		mutexFrame.lock();
		camera >> frame;
		if (frame.empty()) {
			mutexFrame.unlock();
			continue;
		}
		cv::Mat frameToWindow = frame;
		mutexFrame.unlock();
		mutexFaces.lock();
		for(unsigned int i = 0; i < faces.size(); i++) {
			cv::rectangle(frameToWindow, faces[i], cv::Scalar(0, 255, 0), 2);
		}
		mutexFaces.unlock();
		mutexFPS.lock();
		cv::putText(frameToWindow, FPS, cv::Point(10, 50),
				cv::FONT_HERSHEY_PLAIN, 3, cv::Scalar(0, 255, 0));
		mutexFPS.unlock();
		cv::imshow(WINDOW_NAME, frameToWindow);
		if (stopFlag) return;
	}
}

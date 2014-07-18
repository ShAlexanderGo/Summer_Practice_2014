#ifndef VJDETECTOR_HPP_
#define VJDETECTOR_HPP_

#include <opencv2/opencv.hpp>
#include <thread>
#include <mutex>
#include <time.h>

class VJDetector {

private:

	static const int N;

	static const int INPUT_IMAGE_WIDTH;
	static const int INPUT_IMAGE_HEIGHT;
	static const std::string WINDOW_NAME;

	void threadCompute();
	void threadWindow();

	bool stopFlag;

	cv::CascadeClassifier cascadeFrontalFace;
	cv::Mat frame;
	cv::VideoCapture camera;

	std::mutex mutexFaces;
	std::mutex mutexFrame;
	std::mutex mutexFPS;
	std::string FPS;
	std::vector<cv::Rect> faces;

public:

	VJDetector();

	void detect();

};

#endif /* VJDETECTOR_HPP_ */

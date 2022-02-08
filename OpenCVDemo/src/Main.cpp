#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/tracking/tracking_legacy.hpp>

void ResizeBoxes(cv::Rect &box)
{
	box.x += cvRound(box.width * 0.1);
	box.width = cvRound(box.width * 0.8);
	box.y += cvRound(box.height * 0.06);
	box.height = cvRound(box.height * 0.8);
}

int main(int argc, char *argv[])
{
	cv::VideoCapture video("test.mp4");
	if (!video.isOpened())
		return -1;

	cv::Mat frame;
	int32_t frameWidth = (int32_t)video.get(cv::CAP_PROP_FRAME_WIDTH);
	int32_t frameHeigth = (int32_t)video.get(cv::CAP_PROP_FRAME_HEIGHT);
	cv::VideoWriter output("output.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(frameWidth, frameHeigth));
	cv::Ptr<cv::legacy::MultiTracker> multiTracker = cv::legacy::MultiTracker::create();
	cv::HOGDescriptor hog;
	std::vector<cv::Rect> detections;
	int32_t frameNumber = 1;
	
	video.read(frame);

	// Initialize HOG descriptor and use human detection classifier coefficients
	hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());

	// Detect people and save them to detections and initialize multi tracker based on these
	hog.detectMultiScale(frame, detections, 0, cv::Size(8, 8), cv::Size(32, 32), 1.2, 2);

	for (auto &detection : detections)
	{
		ResizeBoxes(detection);
		cv::Ptr<cv::legacy::TrackerKCF> tracker = cv::legacy::TrackerKCF::create();
		tracker->init(frame, detection);
		multiTracker->add(tracker, frame, detection);
	}

	while (video.read(frame))
	{
		frameNumber++;

		// Every 15 frames add new set of detections and clear old ones
		if (frameNumber % 15 == 0)
		{
			detections.clear();
			hog.detectMultiScale(frame, detections, 0, cv::Size(8, 8), cv::Size(32, 32), 1.2, 2);
			multiTracker->clear();

			for (auto &detection : detections)
			{
				ResizeBoxes(detection);
				
				cv::Ptr<cv::legacy::TrackerKCF> tracker = cv::legacy::TrackerKCF::create();
				tracker->init(frame, detection);
				multiTracker->add(tracker, frame, detection);
			}
		}
		else
		{
			bool found = multiTracker->update(frame);
		}

		// draw rectangles around objects
		for (const auto &object : multiTracker->getObjects())
		{
			cv::rectangle(frame, object, cv::Scalar(255, 0, 0), 2, 8);
		}

		// Display the frame
		cv::imshow("Video feed", frame);

		output.write(frame);

		// Break if ESC was hit
		if (cv::waitKey(1) == 27)
			break;
	}

	output.release();
	video.release();

	cv::destroyAllWindows();
	
	return 0;
}


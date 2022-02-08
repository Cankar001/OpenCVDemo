#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <opencv2/tracking/tracking_legacy.hpp>

namespace utils
{
	static cv::Ptr<cv::legacy::tracking::Tracker> CreateTrackerByName(const std::string &name)
	{
		if (name == "KCF")
			return cv::legacy::tracking::TrackerKCF::create();
		else if (name == "MIL")
			return cv::legacy::tracking::TrackerMIL::create();
		else if (name == "TLD")
			return cv::legacy::tracking::TrackerTLD::create();
		else if (name == "CSRT")
			return cv::legacy::tracking::TrackerCSRT::create();
		else if (name == "MOSSE")
			return cv::legacy::tracking::TrackerMOSSE::create();

		// default tracker
		return cv::legacy::tracking::TrackerKCF::create();
	}
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "Error: Please provide the path to a test video file as the first command line argument!" << std::endl;
		return -1;
	}

	std::string trackerName = "KCF";
	if (argc >= 3)
	{
		std::cout << "Selected custom tracker: " << argv[2] << std::endl;
		trackerName = argv[2];
	}

	char *videoPath = argv[1];
	cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT); // Disable log output, otherwise the erros are really bad to read
	cv::VideoCapture video(videoPath);

	if (!video.isOpened())
	{
		std::cout << "Error: Video file could not be opened!" << std::endl;
		return -1;
	}

	cv::Mat frame;
	cv::Ptr<cv::legacy::MultiTracker> multiTracker = cv::legacy::MultiTracker::create();
	std::vector<cv::Rect> rois;
	std::vector<cv::Rect2d> detections;
	std::vector<cv::Ptr<cv::legacy::tracking::Tracker>> algorithms;

	// Get the first frame
	video >> frame;
	
	// Let the user select the objects he wishes to track
	cv::selectROIs("Select objects to track", frame, rois);
	if (!rois.size())
	{
		std::cout << "Error: no selection has been made!" << std::endl;
		return -1;
	}

	// Close the window, it is not needed anymore
	cv::destroyWindow("Select objects to track");

	// now the program will not break with any error exceptions, so set the loglevel
#ifdef OPENCVDEMO_DEBUG
	cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_DEBUG);
#else
	cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_ERROR);
#endif // OPENCVDEMO_DEBUG

	// copy all selected results and add the requested tracker type
	for (uint64_t i = 0; i < rois.size(); ++i)
	{
		algorithms.push_back(utils::CreateTrackerByName(trackerName));
		detections.push_back(rois[i]);
	}

	// Add the detections and the algorithms to the multitracker
	multiTracker->add(algorithms, frame, detections);

	std::cout << "Starting the tracking process, press esc to quit!" << std::endl;
	for (;;)
	{
		// Get the next frame
		video >> frame;

		// If the video was finished, close the window and shut down the program!
		if (frame.rows == 0 || frame.cols == 0)
			break;

		// Update the multitracker, the result determines whether a human has been tracked
		bool found = multiTracker->update(frame);
		if (found)
		{
			std::cout << "Found an instance of the object!" << std::endl;

			// draw rectangles around tracked objects
			for (const auto &object : multiTracker->getObjects())
			{
				cv::rectangle(frame, object, cv::Scalar(255, 0, 0), 2, 8);
			}
		}
		else
		{
			std::cout << "Found no instance of the object!" << std::endl;
		}

		// Display the frame
		cv::imshow("Video feed", frame);

		// Break if ESC was pressed
		if (cv::waitKey(1) == 27)
			break;
	}

	// free the video resources
	video.release();

	// close all remaining windows
	cv::destroyAllWindows();
	
	return 0;
}


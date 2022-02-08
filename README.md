# OpenCVDemo

This program is a highly customizable OpenCV demo application, to test some of the OpenCV features.

The source is based on the official OpenCV documentation.

# Getting started

To build the program in windows, double click the `GenerateSolution.bat` file and open the resulting Visual Studio Solution.

In Visual Studio you can select to build either the `Debug` or `Release` build.

**Keep in mind, that the program needs command line arguments as well, you need to provide them by inserting them into the "Settings > Debugging > Command line arguments" setting if you wish to start the application from within visual studio.**

# Commandline arguments

The application needs at least the **filepath** to the test video, you can use any test video you would like.

The second commandline argument is the tracking type, there are only a few Trackers supported by this program, here is a list of the available tracker types:

- **KCF (default if no options is provided):** KCF is a novel tracking framework that utilizes properties of circulant matrix to enhance the processing speed.
- **MIL:** The MIL algorithm trains a classifier in an online manner to separate the object from the
background.
- **TLD:** TLD is a novel tracking framework that explicitly decomposes the long-term tracking task into
tracking, learning and detection.
- **CSRT:** Discriminative Correlation Filter with Channel and Spatial Reliability.
- **MOSSE:**  Visual Object Tracking using Adaptive Correlation Filters (this tracker works with grayscale images, if passed bgr ones, they will get converted internally.)

**Note: (The descriptions are taken from the brief descriptions of the respective classes.)**


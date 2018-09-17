#ifndef ASVideoCapture_h
#define ASVideoCapture_h

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

#include "ASVideoConfig.h"
#include "rx.hpp"
#include <windows.h>
#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")

using namespace Gdiplus;
namespace Rx {
	using namespace rxcpp;
	using namespace rxcpp::subjects;
	using namespace rxcpp::operators;
	using namespace rxcpp::util;
}

using namespace cv;

typedef signed char sbyte;
typedef unsigned char byte;

class ASVideoCapture
{
public:
	ASVideoCapture(ASVideoConfig* config);
	~ASVideoCapture();
	void processVideo();
	byte* getBytesFromMat(Mat frame);	
	Bitmap* getBitmapFromMat(Mat frame);
	Rx::subject<Mat> frameImage;
	Rx::observable<Mat> observableImage = frameImage.get_observable();
private:	
	Rx::subscriber<Mat> frameout = frameImage.get_subscriber();
	ASVideoConfig _config;
	void sendFrame(Mat inputImg);
	Mat _frame; 
	bool flagCapture = true;
	int _deviceId = -1;
	int fps_camera = 0;
	ASVideoConfig* _asvideoConfig;
	bool buildPathVideo();
	bool isPositiveInteger(string &device);
	bool searchProtocol(string &device);
	string buildUrl(string device);
	string _urlVideo;
};


#endif
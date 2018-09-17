#include "ASVideoCapture.h"

ASVideoCapture::ASVideoCapture(ASVideoConfig* config)
{	
	_asvideoConfig = config;
}

ASVideoCapture::~ASVideoCapture()
{
}

void ASVideoCapture::processVideo() {
	
	if (buildPathVideo()) {
		VideoCapture capture;
		if (_deviceId != -1) {
			capture.open(_deviceId);
		}
		else {
			capture.open(_urlVideo);
		}

		if (!capture.isOpened()) {			
			cout << "Unable to open video file: " << _urlVideo << endl;
			return;
		}
		fps_camera = (int)(capture.get(CAP_PROP_FPS));
		while (flagCapture) {
			if (!capture.read(_frame)) {
				cout << "Unable to read next frame." << endl;
				cout << "Exiting..." << endl;
				return;
			}
			else {
				sendFrame(_frame);
				if (waitKey(1000 / fps_camera) >= 0) {
					flagCapture = false;
				}
			}
		}
		capture.release();
	}

}

byte* ASVideoCapture::getBytesFromMat(Mat frame) {
	return frame.data;
}

Bitmap* ASVideoCapture::getBitmapFromMat(Mat inputImg) {
	cv::Size size = inputImg.size();
	Bitmap* bitmap = new Bitmap(size.width, size.height, inputImg.step1(),
	PixelFormat24bppRGB, inputImg.data);
	return bitmap;
}

void ASVideoCapture::sendFrame(Mat inputImg) {
	
	frameout.on_next(inputImg);
}

bool ASVideoCapture::buildPathVideo() {
	string path = _asvideoConfig->getPath();
	if (!path.empty()) {
		if (isPositiveInteger(path)) {
			_deviceId = stoi(path);
		}
		else if(searchProtocol(path)) {
			_urlVideo = buildUrl(path);
		}
		else {
			_urlVideo = path;
		}
		return true;
	}
	else {
		return false;
	}
}

bool ASVideoCapture::isPositiveInteger(string &device) {
	return !device.empty() &&
		(std::count_if(device.begin(), device.end(), std::isdigit) == device.size());
}

bool ASVideoCapture::searchProtocol(string &device) {
	string word = "http://";
	if (device.find(word) == string::npos) {
		return false;
	}
	else {
		return true;
	}
}

string ASVideoCapture::buildUrl(string device) {
	device.replace(0, 7, "");
	string url = "http://" + _asvideoConfig->getUser() + ":" +
		_asvideoConfig->getPassword() + "@" +
		device + "/axis-cgi/mjpg/video.cgi?resolution=" +
		_asvideoConfig->getResolution() + "&req_fps=30&.mjpg";
	return url;
}

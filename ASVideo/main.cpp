#include <windows.h>
#include <gdiplus.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "ASVideoConfig.h"
#include "ASVideoCapture.h"

#include <stdlib.h> 
#include "rx.hpp"

using namespace Gdiplus;
namespace Rx {
	using namespace rxcpp;
	using namespace rxcpp::subjects;
	using namespace rxcpp::operators;
	using namespace rxcpp::util;
}

void testConfig() {
	ASVideoConfig asvideoConfig;

	asvideoConfig.Path("http://192.168.1.0");
	asvideoConfig.Password("123qwe");
	asvideoConfig.User("admin");
	asvideoConfig.Resolution("1280x860");

	string json = asvideoConfig.getJsonConfig();
	cout << json << endl;
	asvideoConfig.setJsonConfig(json);
	json = asvideoConfig.getJsonConfig();
	cout << json << endl;
}

void testReactive() {
	ASVideoConfig* asvideoConfig = new ASVideoConfig();
	asvideoConfig->Path("video.mp4");
	ASVideoCapture asvideoCapture(asvideoConfig);
	auto frame_input
		= asvideoCapture.observableImage.map([](Mat p) {
		return p;
	});

	auto subscription = frame_input.subscribe([](Mat p) {
		cv::imshow("window image", p);
		
	});
	asvideoCapture.processVideo();
	subscription.unsubscribe();
}

void testUrl() {
	ASVideoConfig* asvideoConfig = new ASVideoConfig();
	asvideoConfig->Path("http://192.168.1.0");
	asvideoConfig->User("admin");
	asvideoConfig->Password("123qwe");
	asvideoConfig->Resolution("1280x860");
	ASVideoCapture asvideoCapture(asvideoConfig);
	auto frame_input
		= asvideoCapture.observableImage.map([](Mat p) {
		return p;
	});

	auto subscription = frame_input.subscribe([](Mat p) {
		cv::imshow("window image", p);

	});
	asvideoCapture.processVideo();
	subscription.unsubscribe();
}

int main() {
	testUrl();
	
}
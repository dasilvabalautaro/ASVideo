#include "ASVideoConfig.h"

#include <iostream>
#include <map>
#include <json\json.h>
using namespace std;

ASVideoConfig::ASVideoConfig() {

}

ASVideoConfig::~ASVideoConfig() {

}

void ASVideoConfig::Password(string password) {
	_password = password;
}

void ASVideoConfig::Path(string path) {
	_path = path;
}

void ASVideoConfig::User(string user) {
	_user = user;
}

void ASVideoConfig::Resolution(string resolution) {
	_resolution = resolution;
}

string ASVideoConfig::getPassword() {
	return _password;
}

string ASVideoConfig::getPath() {
	return _path;
}

string ASVideoConfig::getUser() {
	return _user;
}

string ASVideoConfig::getResolution() {
	return _resolution;
}

string ASVideoConfig::getJsonConfig() {
	Json::Value jsonMap;
	std::map<std::string, std::string> params;
	params.insert(std::pair<std::string, std::string>(PATH, _path));
	params.insert(std::pair<std::string, std::string>(PASSWORD, _password));
	params.insert(std::pair<std::string, std::string>(USER, _user));
	params.insert(std::pair<std::string, std::string>(RESOLUTION, _resolution));
	std::map<std::string, std::string>::const_iterator it = params.begin(),
		end = params.end();
	for (; it != end; ++it) {
		jsonMap[it->first] = it->second;
		
	}
	Json::Value root;
	root["config"] = "video_config";
	root["params"] = jsonMap; 

	Json::StyledWriter writer;
	string output = writer.write(root);
	return output;
}

void ASVideoConfig::setJsonConfig(string jsonString) {	
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(jsonString, root);
	if (!parsingSuccessful)
	{
		cout << "Error parsing the string" << endl;
		return;
	}

	const Json::Value params = root["config"];
	for (Json::Value::const_iterator it = params.begin();
		it != params.end(); ++it) {
		cout << it.key().asString() << ':' << it->asString() << '\n';
		if (it.key().asString() == PATH) {
			_path = it->asString();
		}
		else if (it.key().asString() == PASSWORD) {
			_password = it->asString();
		}
		else if (it.key().asString() == USER) {
			_user = it->asString();
		}
		else if (it.key().asString() == RESOLUTION) {
			_resolution = it->asString();
		}
		
	}
		
}
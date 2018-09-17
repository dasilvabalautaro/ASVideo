#ifndef ASVideoConfig_h
#define ASVideoConfig_h

#include <iostream>

using namespace std;

class ASVideoConfig
{
public:
	ASVideoConfig();
	~ASVideoConfig();
	void Path(string path);
	void User(string user);
	void Password(string password);
	void Resolution(string resolution);
	string getPath();
	string getUser();
	string getPassword();
	string getResolution();
	string getJsonConfig();
	void setJsonConfig(string jsonString);
private:
	string _path;
	string _user;
	string _password;
	string _resolution;
	const string PATH = "path";
	const string PASSWORD = "password";
	const string USER = "user";
	const string RESOLUTION = "resolution";
};

#endif // !ASVideoConfig_h


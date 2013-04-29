#pragma once

#include <Poco/Mutex.h>
#include <Poco/Util/ServerApplication.h>

using namespace Poco;
using namespace Poco::Util;
using namespace std;

class MyServerApp : public ServerApplication
{
public:
	static string getText();
	static void setText(string newText);

protected:
	int main(const vector<string> &);
	static string text;
	static Mutex textLock;
};
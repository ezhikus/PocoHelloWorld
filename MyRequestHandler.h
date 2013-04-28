#pragma once

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Util/ServerApplication.h>

using namespace Poco::Net;
using namespace Poco::Util;
using namespace Poco;
using namespace std;

class CMyRequestHandler : public HTTPRequestHandler
{
public:
	void handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp);
};

class MyServerApp : public ServerApplication
{
public:
	static void setText(string newText);
	static string getText() { return text; }

protected:
	int main(const vector<string> &);
	static string text;
};
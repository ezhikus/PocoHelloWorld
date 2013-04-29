#include <iostream>
#include <conio.h>
#include <string>

#include "MyRequestHandler.h"
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/ScopedLock.h>
#include <Poco/URI.h>
#include <Poco/StringTokenizer.h>

using namespace Poco::Net;

string MyServerApp::text = "Hello world!";
Mutex MyServerApp::textLock;

class CMyRequestHandler : public HTTPRequestHandler
{
public:
	void handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp)
	{
		resp.setStatus(HTTPResponse::HTTP_OK);
		resp.setContentType("text/html");
		ostream& out = resp.send();

		URI uri(req.getURI());
		if (uri.toString().find("/setText") == 0)
		{
			StringTokenizer str(uri.getQuery(), "=");
			if (str.count() == 2 && str[0] == "text")
			{
				MyServerApp::setText(str[1]);
				out << "ok";
				out.flush();
				return;
			}
		}

		out << "error";
		out.flush();
	}
};

class MyRequestHandlerFactory : public HTTPRequestHandlerFactory
{
public:
	virtual HTTPRequestHandler* createRequestHandler(const HTTPServerRequest &)
	{
		return new CMyRequestHandler;
	}
};

void MyServerApp::setText(string newText)
{
	ScopedLock<Mutex> lock(textLock);
	text = newText;
}

string MyServerApp::getText() 
{ 
	ScopedLock<Mutex> lock(textLock);
	return text; 
}

int MyServerApp::main(const vector<string> &)
{
	HTTPServer s(new MyRequestHandlerFactory, ServerSocket(8000), new HTTPServerParams);
	s.start();
	for(;;)
	{
		cout << MyServerApp::getText() << endl;
		_getch();
	}
	s.stop();
	return Application::EXIT_OK;
}

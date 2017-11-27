#include "WebViewWrapper.h"

#include <iostream>
#include <thread>

extern "C" void init_webview(void(*cbPtr)(const char*));
extern "C" void execute_js(const char* js);

static std::function<void(const char*)> instanceCallback;

using namespace std::placeholders;

WebViewWrapper::WebViewWrapper()
{
	instanceCallback = std::bind(&WebViewWrapper::ReceiveMidiMsg, this, _1);

	this->mThread = std::thread([this]() {
		init_webview([](const char* args) {
			instanceCallback(args);
		});
	});
	this->mThread.detach();
}


WebViewWrapper::~WebViewWrapper()
{
}

void WebViewWrapper::SetReceiveMidiMsgCallback(std::function<void(int,int,int)> cb)
{
	this->receiveMidiMsgCallback = cb;
}

void WebViewWrapper::ReceiveMidiMsg(const char* arg)
{
	// TODO - Send & parse JSON or something instead
	char buffer[255];
	int noteNumber = 0;
	int velocity = 0;
	int status = 0;

	sprintf(buffer, "%s", arg);
	char* pch = strtok(buffer, ",");
	noteNumber = atoi(pch);
	pch = strtok(NULL, ",");
	status = atoi(pch);
	pch = strtok(NULL, ",");
	velocity = atoi(pch);
	this->receiveMidiMsgCallback(noteNumber, status, velocity);
}

void WebViewWrapper::SendMidiMsg(IMidiMsg note)
{
	// window.external.invoke_('hello world');
	int status = note.StatusMsg();
	int velocity = note.Velocity();
	int noteNumber = note.NoteNumber();
	int channel = note.Channel();
	char buffer[512];
	sprintf(buffer, "window.sendNote(%i, %i, %i, %i);", channel, noteNumber, status, velocity);
	execute_js(buffer);
}

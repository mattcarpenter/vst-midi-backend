#include "WebViewWrapper.h"

#include <iostream>
#include <thread>

extern "C" void init_webview();
extern "C" void execute_js(const char* js);

WebViewWrapper::WebViewWrapper()
{
	this->mThread = std::thread(init_webview);
	this->mThread.detach();
}


WebViewWrapper::~WebViewWrapper()
{
}

void WebViewWrapper::SendMidiMsg(IMidiMsg note)
{
	// window.external.invoke_('hello world');
	int status = note.StatusMsg();
	int velocity = note.Velocity();
	int noteNumber = note.NoteNumber();
	char buffer[512];
	sprintf(buffer, "window.sendNote(%i, %i, %i);", noteNumber, status, velocity);
	execute_js(buffer);
}

#pragma once
#include <iostream>
#include <thread>
#include "IPlug_include_in_plug_hdr.h"

extern "C" {
#include <windows.h>

#include <commctrl.h>
#include <exdisp.h>
#include <mshtmhst.h>
#include <mshtml.h>
#include <shobjidl.h>

#include <stdio.h>

	struct webview_priv {
		HWND hwnd;
		IOleObject **browser;
	};

	struct webview;

	typedef void(*webview_external_invoke_cb_t)(struct webview *w,
		const char *arg);

	struct webview {
		const char *url;
		const char *title;
		int width;
		int height;
		int resizable;
		webview_external_invoke_cb_t external_invoke_cb;
		struct webview_priv priv;
		void *userdata;
	};
}

class WebViewWrapper
{
public:
	WebViewWrapper();
	~WebViewWrapper();
	void SendMidiMsg(IMidiMsg msg);
private:
	std::thread mThread;
	webview mWebview;
};


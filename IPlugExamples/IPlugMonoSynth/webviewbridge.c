#define WEBVIEW_WINAPI 1
#include "webviewbridge.h"
#include "webview.h"

void callback(struct webview *w, const char *arg);

struct webview wv = {
	.title = "Webview",
	.url = "http://localhost:8000/",
	.width = 800,
	.height = 600,
	.resizable = 0,
	.external_invoke_cb = callback,
};

void init_webview()
{
	webview_init(&wv);
	while (webview_loop(&wv, 1) == 0);
	webview_exit(&wv);
}

void eval(struct webview w, const char* js)
{
	char buffer[1024];
	sprintf(buffer, "try { %s } catch (e) { alert(e); }", js);
	webview_eval(&w, buffer);
}

void execute_js(const char* js)
{
	char* buffer = malloc(512);
	memcpy(buffer, js, 512);
	webview_dispatch(&wv, eval, buffer);
}

void callback(struct webview *w, const char *arg) {

}

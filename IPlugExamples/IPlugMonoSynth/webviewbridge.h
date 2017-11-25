#pragma once

void init_webview(void(*cbPtr)(const char*));
void execute_js(const char* js);

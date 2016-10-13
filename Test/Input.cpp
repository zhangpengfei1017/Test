#include "Input.h"
#include <windows.h> 
HWND curHandle;
Input::Input()
{
}
void Input::Init() {
	for (int i = 0; i < 256; i++) {
		Input::IsKeyUp[i] = true;
	}
	curHandle = GetConsoleWindow();
}
Input::~Input()
{
}
bool Input::GetKey(int vKey) {
	if (curHandle != GetForegroundWindow()) {
		return false;
	}
	return (GetAsyncKeyState(vKey) && 0x8000);
}

bool Input::GetKeyDown(int vKey) {
	if (curHandle != GetForegroundWindow()) {
		return false;
	}
	bool IsKeyDown = (GetAsyncKeyState(vKey) && 0x8000);
	if (IsKeyDown&&IsKeyUp[vKey]) {
		IsKeyUp[vKey] = false;
		return(true);
	}
	else if (IsKeyDown&&!IsKeyUp[vKey]) {
		return(false);
	}
	else if (!IsKeyDown) {
		IsKeyUp[vKey] = true;
		return(false);
	}
	return(false);
}
bool Input::IsKeyUp[256];

//
// Created by Yu on 1/17/2021.
//

#ifndef ROGUELIKE_ENGINE_GAMEWINDOW_H
#define ROGUELIKE_ENGINE_GAMEWINDOW_H

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>


class GameWindow {
public:
	void setupWindow(HINSTANCE);
	HWND getWindowHandler();

private:
	HWND windowHandler;
};


#endif //ROGUELIKE_ENGINE_GAMEWINDOW_H

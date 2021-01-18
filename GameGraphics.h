//
// Created by Yu on 1/18/2021.
//

#ifndef ROGUELIKE_ENGINE_GAMEGRAPHICS_H
#define ROGUELIKE_ENGINE_GAMEGRAPHICS_H


#include <dxgi.h>

class GameGraphics {
public:
	void setupGraphics(const HWND& hwnd);
private:
	void _setupD3DDeviceAndContext();
	void _setupD3DSwapChain(const HWND& pHwnd);
};


#endif //ROGUELIKE_ENGINE_GAMEGRAPHICS_H

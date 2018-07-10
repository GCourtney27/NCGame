#pragma once


#define DLL_EXPORT __declspec(dllexport)
#define DLL_IMPORT __declspec(dllimport)

#ifdef ENGINE_EXPORTS  
#define ENGINE_API __declspec(dllexport)   
#else  
#define ENGINE_API __declspec(dllimport)   
#endif 

#include "sdl.h"

class ENGINE_API Engine
{
public:
	Engine() {}
	~Engine() {}

	bool Initialize();
	void Update();
	void Shutdown();

	SDL_Window * GetWindow() { return m_window; }

	bool IsQuit() { return m_isQuit; }

protected:
	bool m_isQuit = false;
	SDL_Window* m_window = nullptr;
	 
};

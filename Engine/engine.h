#pragma once


#define DLL_EXPORT __declspec(dllexport)
#define DLL_IMPORT __declspec(dllimport)

#ifdef ENGINE_EXPORTS  
#define ENGINE_API __declspec(dllexport)   
#else  
#define ENGINE_API __declspec(dllimport)   
#endif 

#pragma warning(disable:4251)

#include <sdl.h>
#include <sdl_ttf.h>

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
	bool IsDebug() { return m_isDebug; }

protected:
	bool m_isQuit = false;
	bool m_isDebug = false;
	SDL_Window* m_window = nullptr;
	 
};

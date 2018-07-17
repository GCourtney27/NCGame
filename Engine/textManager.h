#pragma once
#include "singleton.h"
#include "engine.h"
#include "text.h"
#include <string>
#include <vector>


class ENGINE_API TextManager : public Singleton<TextManager>
{
public:
	bool Initialize(Engine * engine);
	void Shutdown();

	Text* CreateText(const std::string& text, const std::string& fontname, int size, const Color& color);
	void DestroyText(Text* text);

	friend Singleton<TextManager>;

protected:
	TextManager() {}

private:
	Engine * m_engine;
	std::vector<Text*> m_texts;
};
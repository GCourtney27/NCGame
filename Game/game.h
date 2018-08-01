#pragma once

class Engine;
class Scene;

class Game
{
public:
	Game(Engine* engine) : m_engine(engine) {}
	~Game() {}

	bool Initialize();
	void Shutdown();
	void Update();

	bool Run() { return m_running; }
	Scene* GetScene() { return m_scene; }

protected:
	bool m_running = false;
	Engine * m_engine = nullptr;
	Scene* m_scene = nullptr;
};
#pragma once
#include "singleton.h"
#include "engine.h"
#include "event.h"
#include "eventReceiver.h"

#define COLLISION_EVENT "collision"

enum eEventType
{
	COLLISION,
	PLAYER_DEATH
};

class ENGINE_API EventManager : public Singleton<EventManager>
{
public:
	bool Initialize(Engine* engine);
	void Shutdown();
	void Update();

	void SendMessage(const Event& event);
	void SendGameMessage(const Event& event);

	void SetGameEventReceiver(EventReceiver* eventReceiver) { m_gameEventReceiver = eventReceiver; }

protected:
	friend Singleton<EventManager>;

protected:
	Engine * m_engine = nullptr;
	EventReceiver * m_gameEventReceiver = nullptr;
};
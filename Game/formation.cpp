#include "formation.h"
#include "timer.h"

//std::vector<Vector2D> Enemy::m_enterPath = { Vector2D(200.0f, 400.0f), Vector2D(300.0f, 300.0f), Vector2D(200.0f, 200.0f), Vector2D(100.0f, 300.0f), Vector2D(200.0f, 400.0f) };

void Formation::Create(ID& type)
{
	
	if (type == "begin_phase")
	{
		m_attackPaths.push_back({ Vector2D(400.0f, 300.0f), Vector2D(500.0f, 500.0f), Vector2D(600.0f, 600.0f), Vector2D(550.0f, 650.0f) });
		m_enterPaths[0] = { Vector2D(500.0f, -64.0f), Vector2D(100.0f, 300.0f), Vector2D(200.0f, 400.0f), Vector2D(300.0f, 300.0f) };
		m_enterPaths[1] = { Vector2D(300.0f, -64.0f), Vector2D(700.0f, 300.0f), Vector2D(600.0f, 400.0f), Vector2D(500.0f, 300.0f) };

		m_formation =
		{ { { Enemy::BEE, Enemy::LEFT, 300.0f, Vector2D(100.0f, 160.0f), this }, 0.0f, false },
		{ { Enemy::BEE, Enemy::LEFT, 300.0f, Vector2D(140.0f, 160.0f), this }, 0.35f, false },
		{ { Enemy::BEE, Enemy::LEFT, 300.0f, Vector2D(100.0f, 200.0f), this }, 0.7f, false },
		{ { Enemy::BEE, Enemy::LEFT, 300.0f, Vector2D(140.0f, 200.0f), this }, 1.05f, false },
		{ { Enemy::BUG, Enemy::RIGHT, 300.0f, Vector2D(100.0f, 80.0f), this }, 0.0f, false },
		{ { Enemy::BUG, Enemy::RIGHT, 300.0f, Vector2D(140.0f, 80.0f), this }, 0.35f, false },
		{ { Enemy::BUG, Enemy::RIGHT, 300.0f, Vector2D(100.0f, 120.0f), this }, 0.7f, false },
		{ { Enemy::BUG, Enemy::RIGHT, 300.0f, Vector2D(140.0f, 120.0f), this }, 1.05f, false },
		{ { Enemy::BOSS, Enemy::LEFT, 300.0f, Vector2D(180.0f, 100.0f), this }, 0.7f, false }
		};
	}

	if (type == "middle_phase")
	{
		m_attackPaths.push_back({ Vector2D(400.0f, 300.0f), Vector2D(500.0f, 500.0f), Vector2D(600.0f, 600.0f), Vector2D(550.0f, 650.0f) });
		m_enterPaths[0] = { Vector2D(200.0f, 400.0f), Vector2D(300.0f, 300.0f), Vector2D(200.0f, 200.0f), Vector2D(100.0f, 300.0f), Vector2D(200.0f, 400.0f) };
		m_enterPaths[1] = { Vector2D(600.0f, 400.0f), Vector2D(500.0f, 300.0f), Vector2D(600.0f, 200.0f), Vector2D(700.0f, 300.0f), Vector2D(600.0f, 400.0f) };

		m_formation =
		{ { { Enemy::BEE, Enemy::LEFT, 300.0f, Vector2D(100.0f, 100.0f), this }, 0.0f, false },
		{ { Enemy::BEE, Enemy::LEFT, 300.0f, Vector2D(140.0f, 100.0f), this }, 0.35f, false },
		{ { Enemy::BOSS, Enemy::LEFT, 300.0f, Vector2D(180.0f, 100.0f), this }, 0.7f, false },
		{ { Enemy::BEE, Enemy::RIGHT, 300.0f, Vector2D(700.0f, 100.0f), this }, 3.0f, false },
		{ { Enemy::BUG, Enemy::RIGHT, 300.0f, Vector2D(660.0f, 100.0f), this }, 3.35f, false },
		{ { Enemy::BEE, Enemy::RIGHT, 300.0f, Vector2D(600.0f, 100.0f), this }, 2.0f, false },
		};
	}

	//m_enterPaths[0] = { Vector2D(200.0f, 400.0f), Vector2D(300.0f, 300.0f), Vector2D(200.0f, 200.0f), Vector2D(100.0f, 300.0f), Vector2D(200.0f, 400.0f) };
	//m_enterPaths[1] = { Vector2D(600.0f, 400.0f), Vector2D(500.0f, 300.0f), Vector2D(600.0f, 200.0f), Vector2D(700.0f, 300.0f), Vector2D(600.0f, 400.0f) };

	/*m_attackPaths.push_back({ Vector2D(400.0f, 300.0f), Vector2D(500.0f, 500.0f), Vector2D(600.0f, 600.0f), Vector2D(550.0f, 650.0f) });

	m_enterPaths[0] = { Vector2D(500.0f, -64.0f), Vector2D(100.0f, 300.0f), Vector2D(200.0f, 400.0f), Vector2D(300.0f, 300.0f) };
	m_enterPaths[1] = { Vector2D(300.0f, -64.0f), Vector2D(700.0f, 300.0f), Vector2D(600.0f, 400.0f), Vector2D(500.0f, 300.0f) };*/

	// Enemies to be in the scene
	// Formation type 1
	/*m_formation =
	{ { { Enemy::BEE, Enemy::LEFT, 300.0f, Vector2D(100.0f, 160.0f), this }, 0.0f, false },
	{ { Enemy::BEE, Enemy::LEFT, 300.0f, Vector2D(140.0f, 160.0f), this }, 0.35f, false },
	{ { Enemy::BEE, Enemy::LEFT, 300.0f, Vector2D(100.0f, 200.0f), this }, 0.7f, false },
	{ { Enemy::BEE, Enemy::LEFT, 300.0f, Vector2D(140.0f, 200.0f), this }, 1.05f, false },
	{ { Enemy::BUG, Enemy::RIGHT, 300.0f, Vector2D(100.0f, 80.0f), this }, 0.0f, false },
	{ { Enemy::BUG, Enemy::RIGHT, 300.0f, Vector2D(140.0f, 80.0f), this }, 0.35f, false },
	{ { Enemy::BUG, Enemy::RIGHT, 300.0f, Vector2D(100.0f, 120.0f), this }, 0.7f, false },
	{ { Enemy::BUG, Enemy::RIGHT, 300.0f, Vector2D(140.0f, 120.0f), this }, 1.05f, false },
	{ { Enemy::BOSS, Enemy::LEFT, 300.0f, Vector2D(180.0f, 100.0f), this }, 0.7f, false }
	};*/

	// Formation type 2
	/*m_formation =
	{ { { Enemy::BEE, Enemy::LEFT, 300.0f, Vector2D(100.0f, 100.0f), this }, 0.0f, false },
	{ { Enemy::BEE, Enemy::LEFT, 300.0f, Vector2D(140.0f, 100.0f), this }, 0.35f, false },
	{ { Enemy::BOSS, Enemy::LEFT, 300.0f, Vector2D(180.0f, 100.0f), this }, 0.7f, false },
	{ { Enemy::BEE, Enemy::RIGHT, 300.0f, Vector2D(700.0f, 100.0f), this }, 3.0f, false },
	{ { Enemy::BOSS, Enemy::RIGHT, 300.0f, Vector2D(660.0f, 100.0f), this }, 3.35f, false },
	};*/

	m_timer = 0.0f;
}

void Formation::Update()
{
	m_timer = m_timer + Timer::Instance()->DeltaTime();
	for (Info& info : m_formation)
	{
		if (info.isActive == false && m_timer > info.enterTime)
		{
			info.isActive = true;
			Enemy* enemy = m_scene->AddEntity<Enemy>();
			enemy->Create(info.enemyInfo);
		}
	}
}

void Formation::Destroy()
{

}

const Formation::Path& Formation::GetRandomAttackPath()
{
	size_t index = rand() % m_attackPaths.size();
	return m_attackPaths[index];
}

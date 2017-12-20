#include <Siv3D.hpp>
#include "Enemy.hpp"

void Main()
{
	Enemy enemy(Window::Center(), 100);
	
	while (System::Update())
	{
		enemy.Update();
		enemy.Draw();
	}
}

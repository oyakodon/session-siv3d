#include <Siv3D.hpp>
#include "wm4s3d.hpp"

void Main()
{
	const Font font(30);

	Wii wii;

	while (System::Update())
	{
		if (Wiimote::waitConnect(1))
		{
			// 待っている間の処理
			font(L"接続待機中...").draw();
			continue;
		}

		if (wii.hasConnected())
		{
			System::Sleep(60);
			wii.setLED(0, true);
			wii.rumble(150);
		}

		// 接続していたらここから下を実行
		font(L"Aボタン: ", wii.buttonA.pressed).draw();
		
		Circle(wii.getPointerInWindow(), 15).draw(Palette::Orange);
		
		wii.update();

	}

}

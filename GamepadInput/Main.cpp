# include <Siv3D.hpp>

void Main()
{
	const Font font(18);

	const Circle stickL(400, 150, 90);

	while (System::Update())
	{
		font(L"Gamepad 0: ", Gamepad(0).isConnected()).draw();
		font(L"Button 0 :", Gamepad(0).button(0).pressed).draw({ 0, 50 });
		font(L"X Axis :", Gamepad(0).x).draw({ 0, 100 });
		font(L"Y Axis :", Gamepad(0).y).draw({ 0, 150 });
		font(L"Z Axis :", Gamepad(0).z).draw({ 0, 200 });

		stickL.draw(Color(127));
		Circle(stickL.center + Vec2(Gamepad(0).u, Gamepad(0).r) * 25, 70).draw();

	}

}
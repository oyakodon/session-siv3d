
# include <Siv3D.hpp>

void Main()
{
	const Font font(30);

	String text;

	while (System::Update())
	{
		Input::GetCharsHelper(text);

		font(L"KeyA.pressed: ", Input::KeyA.pressed).draw();
		font(L"MouseL.pressed: ", Input::MouseL.pressed).draw({0, 40});

		Circle(Mouse::Pos(), 50).draw({ 255, 0, 0, 127 });
	}
}

# include <Siv3D.hpp>
# include <HamFramework.hpp>

struct CommonData
{
	int counter = 0;
	Font font{ 50 };
};

using MyApp = SceneManager<String, CommonData>;

class Title : public MyApp::Scene
{
public:

	void update() override
	{
		if (Input::MouseL.clicked)
		{
			++m_data->counter;
			changeScene(L"Game");
		}
	}

	void draw() const override
	{
		Window::ClientRect().draw(Palette::Blue);
		m_data->font(L"TITLE:", m_data->counter).drawCenter(Window::Center());
	}
};

class Game : public MyApp::Scene
{
public:

	void update() override
	{
		if (Input::MouseL.clicked)
		{
			++m_data->counter;
			changeScene(L"Result");
		}
	}

	void draw() const override
	{
		Window::ClientRect().draw(Palette::Red);
		m_data->font(L"GAME:", m_data->counter).drawCenter(Window::Center());
	}
};

class Result : public MyApp::Scene
{
public:

	void update() override
	{
		if (Input::MouseL.clicked)
		{
			++m_data->counter;
			changeScene(L"Title");
		}
	}

	void draw() const override
	{
		Window::ClientRect().draw(Palette::Green);
		m_data->font(L"RESULT:", m_data->counter).drawCenter(Window::Center());
	}
};

void Main()
{
	MyApp manager;

	manager.add<Title>(L"Title");
	manager.add<Game>(L"Game");
	manager.add<Result>(L"Result");

	while (System::Update())
	{
		manager.updateAndDraw();
	}
}
# include <Siv3D.hpp>
# include "wm4s3d.hpp"

class Block
{
public:

	Block() {}

	Block(const RectF& region) :
		m_region(region),
		m_texture(L"Example/Brick.jpg") {}

	// プレイヤーの現在位置を更新する関数
	void setPlayerPos(const Vec2& pos)
	{
		m_playerPosition = pos;
	}

	// 描画以外の操作をする関数
	void update() {}

	// 点との当たり判定を取る関数
	bool intersects(const Vec2 &shape) const
	{
		return m_region.intersects(shape);
	}

	// 描画をする関数（描画操作以外行わないこと.）
	void draw()
	{
		m_region.movedBy(-m_playerPosition + Window::Center())(m_texture).draw();
	}


private:

	// ブロックの領域
	RectF m_region;

	// ブロックのテキスチャ（画像）
	Texture m_texture;

	// プレイヤーの現在の位置
	Vec2 m_playerPosition;
};


class Player
{
public:

	Player() :
		m_position(100, 200),
		m_texture(L"Example/Siv3D-kun.png"),
		m_isGrounded(false),
		m_isFaceRight(true),
		m_isCreativeMode(false),
		m_jumpFrame(0) {}

	// 位置を取得する関数
	Vec2 getPos()
	{
		return m_position;
	}

	// 地面に接しているかを更新する関数
	void checkGround(const Array<Block>& blocks)
	{
		m_isGrounded = false;

		for (size_t i = 0; i < blocks.size(); i++)
		{
			if (blocks[i].intersects(m_position))
			{
				m_isGrounded = true;
			}
		}
	}

	// 描画以外の操作をする関数
	void update(const Wii& wii)
	{
		if (!m_isCreativeMode)
		{
			if (m_isGrounded)
			{
				if ((Input::KeySpace.clicked || wii.buttonTwo.clicked) && m_jumpFrame <= 0)
				{
					m_jumpFrame = 30;
				}
			}
			else
			{
				m_position.y += 10.0;
			}

			if (m_jumpFrame > 0)
			{
				m_position.y -= 20.0;
				m_jumpFrame--;
			}
		}

		if (Input::KeyRight.pressed || wii.buttonDown.pressed)
		{
			m_position.x += m_isCreativeMode ? 10.0 : 5.0;
			m_isFaceRight = true;
		}

		if (Input::KeyLeft.pressed || wii.buttonUp.pressed)
		{
			m_position.x -= m_isCreativeMode ? 10.0 : 5.0;
			m_isFaceRight = false;
		}

		if (m_isCreativeMode)
		{
			if (Input::KeySpace.pressed || wii.buttonTwo.pressed)
			{
				m_position.y -= 10.0;
			}

			if (Input::KeyLShift.pressed || wii.buttonOne.pressed)
			{
				m_position.y += 10.0;
			}
		}

		if (Input::KeyC.clicked || wii.buttonHome.clicked)
		{
			m_isCreativeMode = !m_isCreativeMode;
		}

		if (!m_isCreativeMode && m_position.y > 1000)
		{
			m_position = { 100, 200 };
		}

	}

	// 描画をする関数（描画操作以外行わないこと.）
	void draw()
	{
		RectF(Vec2(-72.5, -200) + Window::Center(), 145, 200)(m_isFaceRight ? m_texture.mirror() : m_texture).draw();
	}

private:

	// プレイヤーの座標
	Vec2 m_position;

	// プレイヤーのテクスチャ（画像）
	Texture m_texture;

	// 地面に接しているか否か
	bool m_isGrounded;

	// 残りのジャンプ時間
	int m_jumpFrame;

	// 右向いてるか否か
	bool m_isFaceRight;

	// クリエイティブ！
	bool m_isCreativeMode;

};


void Main()
{
	const Font font(30);
	Window::Resize(1280, 720);

	Texture background(L"Example/Windmill.png");
	Player player;
	Array<Block> blocks;

	CSVReader csv(L"stage.csv");
	if (!csv) return;

	for (int i = 0; i < csv.rows; i++)
	{
		blocks.push_back(Block({ csv.get<double>(i, 0), csv.get<double>(i, 1), csv.get<double>(i, 2), csv.get<double>(i, 3) }));
	}

	Wii wii;

	while (System::Update())
	{
		if (Wiimote::waitConnect(1))
		{
			font(L"接続待機中").drawCenter(Window::Center(), Palette::Orange);
			continue;
		}

		if (wii.hasConnected())
		{
			System::Sleep(60);
			wii.setLED(0, true);
		}

		if (csv.hasChanged())
		{
			csv.reload();

			blocks.clear();
			for (int i = 0; i < csv.rows; i++)
			{
				blocks.push_back(Block({ csv.get<double>(i, 0), csv.get<double>(i, 1), csv.get<double>(i, 2), csv.get<double>(i, 3) }));
			}
		}

		wii.update();

		for (size_t i = 0; i < blocks.size(); i++)
		{
			blocks[i].setPlayerPos(player.getPos());
			blocks[i].update();
		}

		player.checkGround(blocks);
		player.update(wii);

		// 実際には縦横比を合わせるように.
		Rect(Window::Size())(background).draw();

		for (size_t i = 0; i < blocks.size(); i++)
		{
			blocks[i].draw();
		}

		player.draw();

		// Line({ player.getPos().x - Window::Width() / 2, 1000 }, {player.getPos().x + Window::Width() / 2, 1000}).movedBy(-player.getPos() + Window::Center()).draw(3.0, Palette::Red);
	}
}

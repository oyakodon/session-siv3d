#include <Siv3D.hpp>

// 実際にファイルに分ける

class Enemy
{
public:
	// コンストラクタ
	Enemy(const Point& p, int hp_)
	{
		pos = p;
		hp = hp_;
	}

	void Update()
	{
		// 右にspped分動かす
		pos.x += speed;

		// 右端まで来たら左端に戻ってくる
		if (pos.x > Window::Width())
		{
			pos.x = 0;
		}

		// 当たり判定, 弾の処理...
	}

	void Draw()
	{
		// 敵機の描画
		Circle(pos, 12).draw(col);

		for (const auto& b : bullets)
		{
			// 弾の描画
			Circle(b, 5).draw(Palette::Yellow);
		}
	}

private:
	Point pos;				// 座標
	int hp;					// HP
	Array<Point> bullets;	// 弾
	
	const Color col = Palette::Orange;
	const int speed = 2;
};


void Main()
{
	Enemy enemy(Window::Center(), 100);
	
	while (System::Update())
	{
		enemy.Draw();
		enemy.Update();
	}
}

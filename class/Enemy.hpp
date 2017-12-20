#pragma once
#include <Siv3D.hpp>

class Enemy
{
public:
	// �R���X�g���N�^
	Enemy(const Point& p, int hp_)
	{
		pos = p;
		hp = hp_;
	}

	void Update()
	{
		// �E��spped��������
		pos.x += speed;

		// �E�[�܂ŗ����獶�[�ɖ߂��Ă���
		if (pos.x > Window::Width())
		{
			pos.x = 0;
		}

		// �����蔻��, �e�̏���...
	}

	void Draw()
	{
		// �G�@�̕`��
		Circle(pos, 12).draw(col);

		for (const auto& b : bullets)
		{
			// �e�̕`��
			Circle(b, 5).draw(Palette::Yellow);
		}
	}

private:
	Point pos;				// ���W
	int hp;					// HP
	Array<Point> bullets;	// �e

	const Color col = Palette::Orange;
	const int speed = 2;
};

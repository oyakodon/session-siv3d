#include <iostream>
#include <string>
using namespace std;

class Cat
{
public:
	
	Cat(string name)
	{
		m_name = name;
	}

	// ���������܂�
	void Greet()
	{
		cout << "�˂��ł�" << endl;
		cout << "�Ȃ܂���" << m_name << "�ł�" << endl;
		cout << "��낵�����˂������܂�" << endl;
	}

private:
	string m_name;

};

int main()
{
	Cat neko("�܂��Ȃ�");

	neko.Greet();

	return 0;
}
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

	// あいさつします
	void Greet()
	{
		cout << "ねこです" << endl;
		cout << "なまえは" << m_name << "です" << endl;
		cout << "よろしくおねがいします" << endl;
	}

private:
	string m_name;

};

int main()
{
	Cat neko("まだない");

	neko.Greet();

	return 0;
}
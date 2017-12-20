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

	// ‚ ‚¢‚³‚Â‚µ‚Ü‚·
	void Greet()
	{
		cout << "‚Ë‚±‚Å‚·" << endl;
		cout << "‚È‚Ü‚¦‚Í" << m_name << "‚Å‚·" << endl;
		cout << "‚æ‚ë‚µ‚­‚¨‚Ë‚ª‚¢‚µ‚Ü‚·" << endl;
	}

private:
	string m_name;

};

int main()
{
	Cat neko("‚Ü‚¾‚È‚¢");

	neko.Greet();

	return 0;
}
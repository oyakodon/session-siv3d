#include <iostream>
using namespace std;

int f(int a, int b)
{
	int ans;
	ans = 2 * a + b;
	return ans;
}

void g(int x, int a)
{
	long z = 1;

	for (int i = 0; i < a; i++)
	{
		z *= x;
	}

	cout << x << "^" << a << "= " << z << endl;
}

void g(int x)
{
	cout << "x‚Ì3æ‚ğŒvZ‚µ‚Ü‚·B" << endl;
	g(x, 3);
}

int main()
{
	int y = f(1, 2);

	cout << "y = " << y << endl;

	g(5);

	g(2, 6);

    return 0;
}


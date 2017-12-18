
# include <Siv3D.hpp>

void Main()
{
	Array<int> v1 = { 10, 20, 30, 40 };
	Array<int> v2(8, 10);
	Array<String> v3 = { L"apple", L"banana" };
	Array<double> v4;
	
	Println(L"v1 = ", v1);
	Println(L"v2 = ", v2);
	Println(L"v3 = ", v3);
	Println(L"v4 = ", v4);

	Println(L"v1.size() = ", v1.size());
	Println(L"v2.size() = ", v2.size());
	Println(L"v3.size() = ", v3.size());
	Println(L"v4.size() = ", v4.size());

	Println(L"v1[2] = ", v1[2]);
	Println(L"v2[0] = ", v2[0]);
	Println(L"v3[1] = ", v3[1]);

	Println(L"キーを押して続行...");

	WaitKey();

	ClearPrint();

	Println(L"v1.empty() = ", v1.empty());
	Println(L"v2.empty() = ", v2.empty());
	Println(L"v3.empty() = ", v3.empty());
	Println(L"v4.empty() = ", v4.empty());

	v1.push_back(50);
	v1.push_back(60);

	Println(L"v1(50, 60をpush_back) = ", v1);

	v3.pop_back();

	Println(L"v3(一回pop_back) = ", v3);

	Erase_if(v1, [](int n) { return n < 30; });
	Println(L"v1(Erase_ifで30未満の要素を削除) = ", v1);

	Println(L"range-based forでv1の要素を出力");
	for (const auto& item : v1)
	{
		Println(item);
	}

	Println(L"キーを押して終了...");

	WaitKey();

}

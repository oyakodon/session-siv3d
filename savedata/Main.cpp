
# include <Siv3D.hpp>

void Main()
{
	/* INI */
	// 書き込み
	INIWriter ini_w(L"save.ini");
	ini_w.write(L"Circle", L"center", Vec2(200, 200));
	ini_w.close();

	Println(L"INIファイル書き出し完了");

	// 読み込み
	INIReader ini_r(L"save.ini");
	Circle circle;
	circle.center = ini_r.get<Vec2>(L"Circle.center");
	ini_r.close();

	Println(L"INIファイル読み込み完了");
	Println(L"circle.center = ", circle.center);

	Println();
	Println(L"何かキーを押して次に進む...");
	WaitKey();
	Println();

	/* Binary */
	// 書き込み
	const String s = L"Siv3D Engine";
	Serializer<BinaryWriter> bin_w(L"save.bin");
	bin_w(s);
	bin_w.getWriter().close();

	Println(L"バイナリファイル書き出し完了");

	// 読み込み
	Deserializer<BinaryReader> bin_r(L"save.bin");
	String s2;
	bin_r(s2);
	bin_r.getReader().close();

	Println(L"バイナリファイル読み込み完了");
	Println(L"読み込まれたString: ", s2);

	Println();
	Println(L"何かキーを押すと終了");
	WaitKey();

}

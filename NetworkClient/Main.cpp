#include <Siv3D.hpp>
#include "asc\TCPString.hpp"

void Main()
{
	const Font font(18);

	asc::TCPStringClient client;
	client.connect(IPv4::localhost(), 30304);

	String input, rcv;

	while (System::Update())
	{
		font(L"received: ", rcv).draw({ 0, 40 });
		font(L"input: ", input).draw({ 0, 80 });

		if (client.isConnected())
		{
			font(L"isConnected").draw();

			if (input.length > 0 && Input::KeyBackspace.clicked)
			{
				input.pop_back();
			}
			else if (Input::KeyEnter.clicked)
			{
				client.sendString(Format(input, L'\n'));
				input = L"";
			}
			else
			{
				input += Input::GetChars();
			}

			while (client.readLine(rcv));
		}

		if (client.hasError())
		{
			font(L"hasError").draw();
			client.disconnect();
			client.connect(IPv4::localhost(), 30304);
		}

	}
}
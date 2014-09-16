#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

int main()
{
	char buffer[100] = {0};
	string caption("");
	HWND old_hand = NULL;
	HWND now_hand = NULL;

	while(true)
	{
		now_hand = ::GetForegroundWindow();
		if(GetWindowTextLength(now_hand) != GetWindowTextLength(old_hand))
		{
			::GetWindowText(now_hand, buffer,::GetWindowTextLength(now_hand));
			caption.append(buffer);
			cout<<now_hand<<"  "<<caption.c_str()<<endl;
			old_hand = now_hand;
			caption = "";
		}
		Sleep(100);
	
	}
	return 0;
}
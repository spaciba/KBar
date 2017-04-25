// KBar.cpp : Defines the entry point for the console application.
//

#include "Commands.h"



int wmain()
{
	String^ input = "";
	int dir_ret;
	String^ com_dir = "dir";
	array<String^>^ tok_input;
	int err;

	do {
		Console::WriteLine("Please enter a command");
		input = Console::ReadLine();

		String^ delim = " ";
		array<Char>^ delimin = delim->ToCharArray();

		tok_input = input->Split(delimin);



		if (String::Equals(tok_input[0], "dir"))
		{
			if (tok_input->Length < 2)
			{

				TCHAR cdBuff[MAX_PATH];
				GetCurrentDirectory(MAX_PATH, cdBuff);


				err = dir(gcnew System::String(cdBuff));
			}
			else
				err = dir(tok_input[1]);
		}

		if (String::Equals(tok_input[0], "help"))
		{
			_tprintf(TEXT("Commands are: \n dir -- dir [path to dir]\ncd\nscreenshot\nget\nput\ntimestomp\nwinlist\nservlist\nproclist\n"));
		}

		if (String::Equals(tok_input[0], "cd"))
		{
			if (tok_input->Length < 2)
				Console::WriteLine("Please give cd an argument\n");
			err = cd(tok_input[1]);
			Console::WriteLine("Directory moved to {0}", tok_input[1]);
		}


		printf("Error: %d\n", dir_ret);
	} while (!String::Equals(tok_input[0], "exit"));

}


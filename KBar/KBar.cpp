// KBar.cpp : Defines the entry point for the console application.
//

#include "Commands.h"



int wmain()
{
	String^ input = "";
	int dir_ret;
	String^ com_dir = "dir";

	do {
		Console::WriteLine("Please enter a command");
		input = Console::ReadLine();
		
		String^ delim = " ";
		array<Char>^ delimin = delim->ToCharArray();
		array<String^>^ tok_input;
		tok_input = input->Split(delimin);

		

		if (String::Equals(tok_input[0], "dir"))
		{
			int dirn = dir(tok_input[1]);
		}

		if (String::Equals(tok_input[0], "help"))
		{
			_tprintf(TEXT("Commands are: \n dir\ncd\nscreenshot\nget\nput\ntimestomp\nwinlist\nservlist\nproclist\n"));
		}


		printf("Error: %d", dir_ret);
	} while(!String::Compare(input, "exit"));
	
}


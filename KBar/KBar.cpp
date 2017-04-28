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
			try
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
			catch (Exception^ e)
			{
				Console::WriteLine("Error code: {0}/n", e);
			}
		}

		if (String::Equals(tok_input[0], "help"))
		{
			_tprintf(TEXT("Commands are: \n dir -- dir [path to dir]\ncd\nscreenshot\nget\nput\ntimestomp\nwinlist\nservlist\nproclist\n"));
		}

		if (String::Equals(tok_input[0], "cd"))
		{
			try
			{
				if (tok_input->Length < 2)
					Console::WriteLine("Please give cd an argument\n");
				else
				{
					err = cd(tok_input[1]);
					if(err == 0)
						Console::WriteLine("Directory moved to {0}", tok_input[1]);
				}
			}
			catch (Exception^ e)
			{
				Console::WriteLine("Error code: {0}/n", e);
			}
		}

		if (String::Equals(tok_input[0], "screenshot"))
		{
			try
			{
				Console::WriteLine("Please enter the destination of the screenshot\n");
				String^ uin = (Console::ReadLine());
				

				screenshot(uin);
			}
			catch (Exception^ e)
			{
				Console::WriteLine("Error code: {0}/n", e);
			}
		}

		if (String::Equals(tok_input[0], "timestomp"))
		{
			try
			{
				Console::WriteLine("Please enter the files to match\t[good] [bad]\n");
				String^ uin = (Console::ReadLine());
				String^ good;
				String^ bad;

				good = uin->Split(delimin)[0];
				bad = uin->Split(delimin)[1];


				timestomp(good, bad);
			}
			catch (Exception^ e)
			{
				Console::WriteLine("Error code: {0}/n", e);
			}
		}

		if (String::Equals(tok_input[0], "winlist"))
		{
			try
			{
				winlist();
			}
			catch (Exception^ e)
			{
				Console::WriteLine("Couldn't get windows: {0}/n", e);
			}
		}

	} while (!String::Equals(tok_input[0], "exit"));

}


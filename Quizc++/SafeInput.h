#pragma once
#include <string>
#include <iostream>

static class SafeInput
{
public:
	SafeInput() = delete;
	//SafeInput(int a) : a(a){}		
	//do some flag bullshit for what you want 
	//prolly needs to be polymorphic 
	//would narrow down the public interface to a constructor and a general Get(); which will return whatever is needed
	//I think that would be pretty neat
	//or is that some Pythonlevel bullshit? i mean "auto" works that way too, no?

	static int GetInt(std::string q)
	{
		std::string s;
		int x;
		while (true)
		{
			std::cout << q << std::endl;
			std::getline(std::cin, s);
			std::cout << "\n";
			if (s >= "0" && s <= "9")
				return x = stoi(s);
			else
				std::cout << "Wrong input.\n\n";
		}
	}

	static std::string GetString(std::string q)
	{
		std::string s;
		std::cout << q << std::endl;
		std::getline(std::cin, s);
		std::cout << "\n";
		return s;
	}

	static std::string GetPath(std::string q, int flag = 0)
	{
		if (flag == 0)
		{
			std::string s;
			std::cout << q << std::endl;
			std::getline(std::cin, s);
			std::cout << "\n";
			ReplaceAll(s, "/", "\\\\");
			ReplaceAll(s, "\\", "\\\\");
			std::ifstream test(s);
			if (!test)
			{
				std::cout << "The file doesn't exist" << std::endl;
				s = "";
			}
			return s;
		}
		else if (flag == 1)
		{
			std::ifstream path("rememberpath.txt");
			std::string s;
			std::getline(path, s);
			ReplaceAll(s, "\\", "\\\\");
			std::ifstream test(s);
			if (!test)
			{
				return GetPath("Pfad setzen: ", 0);
			}
			return s;
		}
		else if (flag == 2)
			return "C:\\Users\\User\\source\\repos\\Quizc++\\Resources\\Quiz.txt";
		else
			return "";
	}

private:
	static std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) //thanks StackOverflow
	{
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) 
		{
			str.replace(start_pos, from.length(), to);
			start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
		}
		return str;
	}
};
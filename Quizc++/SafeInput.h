#pragma once
#include <string>
#include <iostream>

#define M_NUMBERS 1

class SafeInput
{
public:
	SafeInput() = default;
	//SafeInput(int a) : a(a){}		
	//do some flag bullshit for what you want 
	//prolly needs to be polymorphic 
	//would narrow down the public interface to a constructor and a general Get(); which will return whatever is needed
	//I think that would be pretty neat

	int GetInt(std::string q = "")
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

	std::string GetString(std::string q = "")
	{
		std::string s;
		std::cout << q << std::endl;
		std::getline(std::cin, s);
		std::cout << "\n";
		return s;
	}
};
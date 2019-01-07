#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <random>

class Quiz
{
public:
	Quiz(std::string filename) : filename(filename) 
	{ 
		readfile();
	};

	void Start(std::mt19937& rng)
	{
		std::uniform_int_distribution<int> Dist(0, Questions.size() - 1);
		for(int i = 0; i < rounds; i++)
		{
			int rndnumber = Dist(rng);
			std::cout << "Frage Nummer " << i+1 << ": ";
			if (askquestion(rndnumber))
			{
				//correct answer given
				std::cout << "Korrekt!\n";
			}
			else
			{
				//wrong answer given
				std::cout << "Leider Falsch. Richtige Antwort ist: " << Answers[rndnumber][0] << "\n\n";
			}
		}
	}
	void SetRounds(int r)
	{
		rounds = r;
	}
	void SetChance(int c)
	{
		chance = c;
	}

private:
	void readfile()
	{
		std::ifstream in(filename);
		int endqi = 0;
		{
			std::string startq;
			std::string endq;
			std::getline(in, startq, '#');
			std::getline(in, endq, '#');
			int startqi = stoi(startq) - 1;
			endqi = stoi(endq) - startqi;
			Questions.resize(endqi);
			Correct.resize(endqi);
			Wrong.resize(endqi);

			in.ignore(1, '\n');
			for (int i = 0; i < startqi; i++)
			{
				in.ignore(1000, '\n');
			}
		}
		int i = 0;
		while (in.good() && i < endqi)
		{
			std::getline(in, Questions[i], ';');
			std::vector<std::string> temp;
			temp.resize(10);
			int j = 0;
			while (!(in.peek() >= '0' && in.peek() <= '9'))
			{
				std::getline(in, temp[j], ';'); j++;
			}
			temp.resize(j);
			Answers.push_back(temp);
			std::getline(in, Correct[i], ';');
			std::getline(in, Wrong[i], ';');
			i++;
			in.ignore(1, '\n');
		}
	}
	int askquestion(int i)
	{
		std::cout << Questions[i];
		std::string answer;
		std::cin >> answer;
		bool correct = false;
		for (unsigned int j = 0; j < Answers[i].size(); j++)
		{
			correct = correct || (Answers[i][j] == answer);
		}
		correct ? Correct[i] = std::to_string(stoi(Correct[i]) + 1) : Wrong[i] = std::to_string(stoi(Wrong[i]) + 1);
		return correct;
	}
	void savetofile()
	{
		std::ofstream out(filename);
		if (out.is_open())
		{
			out << "1#20#\n";
			for (unsigned int i = 0; i < Answers.size(); i++)
			{
				out << Questions[i] << ";";
				for (unsigned int j = 0; j < Answers[i].size(); j++)
				{
					out << Answers[i][j] << ";";
				}
				out << Correct[i] << ";";
				out << Wrong[i] << ";\n";
			}
		}
		else
		{
			throw;
		}
	}

private:
	std::string filename;
	std::vector<std::string> Questions;
	std::vector<std::vector<std::string>> Answers;
	std::vector<std::string> Correct;
	std::vector<std::string> Wrong;

	int rounds = 10;
	int chance = 60;
};
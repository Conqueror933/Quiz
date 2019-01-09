#pragma once

#include <fstream>
#include <iostream>
#include <random>
#include "QuestionObject.h"

class Quiz
{
public:
	Quiz(std::string filename) : filename(filename) 
	{ 
		readfile();
	};

	void Start(std::mt19937& rng)
	{
		//std::uniform_int_distribution<int> Dist(0, Questions.size() - 1);
		std::uniform_int_distribution<int> diceDist(1, 100);
		for(int i = 0; i < rounds; i++)
		{
			std::sort(Questions.begin(), Questions.end());
			int index = 0;
			std::cout << "Frage Nummer " << i+1 << ": ";
			//make chance happen
			//pick a q, do wrongs > rights ? pick 60 : pick 40
			//int rolls = 0;

			//sorted list
			//take first, roll dice
			//go on or 
			//take second, roll dice
			bool whilecondition = true;
			do {
				int dice = diceDist(rng);
				if (dice < chance)
				{
					whilecondition = false;
				}
				else
				{
					index++;
				}
			} while (whilecondition);
			//do
			//{
			//	//roll a dice
			//	int dice = diceDist(rng);
			//	if (dice < chance)
			//	{
			//		if(Questions[index].wrong >= Questions[index].correct)
			//			rolls = 10;	//logic, logic, do stuff, leaving, fuck
			//	}
			//	else
			//	{
			//		index = Dist(rng);
			//	}
			//	rolls++;
			//} while (Questions[index].wrong >= Questions[index].correct || rolls == 10);	//magic number, but fuck it

			if (askquestion(index))
			{
				//correct answer given
				std::cout << "Korrekt!\n";
			}
			else
			{
				//wrong answer given
				std::cout << "Leider Falsch. Richtige Antwort ist: " << Questions[index].answers[0] << "\n\n";
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
		//Scan(filename);	//trash shit fuck for saving
		std::ifstream in(filename);
		int endqi = 0;
		{
			std::getline(in, startq, '#');
			std::getline(in, endq, '#');
			int startqi = stoi(startq) - 1;
			endqi = stoi(endq) - startqi;
			in.ignore(1, '\n');

			for (int i = 0; i < startqi; i++)
			{
				in.ignore(1000, '\n');
			}
		}
		for (int i = 0; in.good() && i < endqi; i++)
		{
			std::string q;
			std::string as;
			std::vector<std::string> av;
			int c;
			int w;
			std::getline(in, q, ';');
			int j = 0;
			while (!(in.peek() >= '0' && in.peek() <= '9'))
			{
				std::getline(in, as, ';'); j++; av.emplace_back(as);
			}
			std::string temp;
			std::getline(in, temp, ';');
			c = std::stoi(temp);
			std::getline(in, temp, ';');
			w = std::stoi(temp);
			Questions.emplace_back(q, av, c, w);
			in.ignore(1, '\n');
		}
	}
	int askquestion(int i)
	{
		std::cout << Questions[i].question;
		std::string answer;
		std::cin >> answer;
		bool correct = false;
		for (unsigned int j = 0; j < Questions[i].answers.size(); j++)
		{
			correct = correct || (Questions[i].answers[j] == answer);
		}
		correct ? Questions[i].correct = Questions[i].correct + 1 : Questions[i].wrong = Questions[i].wrong + 1;
		return correct;
	}


	//broken
	void Scan(std::string filename)	//trash for saving
	{
		std::ifstream in(filename);
		while (in.good())
		{
			if (in.peek() == '\n')
			{
				numberofquestions++;
			}
		}
	}
	void savetofile()	//bugged, dont use
	{
		if (startq == "1" && endq == std::to_string(Questions.size()))
		{

		}
		std::ofstream out(filename);
		if (out.is_open())
		{
			out << startq + "#" + endq + "#\n";
			for (unsigned int i = 0; i < Questions.size(); i++)
			{
				out << Questions[i].question << ";";
				for (unsigned int j = 0; j < Questions[i].answers.size(); j++)
				{
					out << Questions[i].answers[j] << ";";
				}
				out << Questions[i].correct << ";";
				out << Questions[i].wrong << ";\n";
			}
		}
		else
		{
			throw;
		}
	}
	
private:
	std::string startq;
	std::string endq;
	int numberofquestions;
	std::string filename;
	std::vector<QuestionObject> Questions;
	int rounds = 10;
	int chance = 60;
};
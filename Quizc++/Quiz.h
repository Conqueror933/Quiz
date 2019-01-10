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
		scan();
		readfile();
	};
	~Quiz()
	{
		savetofile();
	}

	void Start(std::mt19937& rng)
	{
		std::uniform_int_distribution<int> diceDist(1, 100);
		for(int i = 0; i < rounds; i++)
		{
			std::sort(Questions.begin(), Questions.end());
			int index = 0;
			std::cout << "Frage Nummer " << i+1 << ": ";
			//desperatly try to make chance happen
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
	void GetStatistics()
	{
		int c = 0;
		int w = 0;
		for (unsigned int i = 0; i < Questions.size(); i++)
		{
			c += Questions[i].correct;
			w += Questions[i].wrong;
		}
		std::cout << "Total number of correct Answers: " << c << "\n";
		std::cout << "Total number of wrong Answers: " << w << "\n\n";
	}
	void GetPQStatistics()
	{
		for (unsigned int i = 0; i < Questions.size(); i++)
		{
			std::cout << i+1 << " # " << Questions[i].question 
				<< "Correct: " << Questions[i].correct 
				<< " Wrong: " << Questions[i].wrong << std::endl;
		}
		std::cout << std::endl;
	}
	void SetPath(std::string fn)
	{
		filename = fn;
		scan();
		readfile();
	}
	void AddQuestion()
	{
		//ask for question, repeatedly ask for answers until a certain code is entered, Question[i].emplace_back(temp, temp2);
		std::cout << "Geben Sie die Frage ein die Sie hinzufuegen moechten.\n";
		std::string tempq;
		std::getline(std::cin, tempq);
		//check for question mark at the end, if there is none add "? "
		std::string temp;
		std::vector<std::string> tempa;
		bool b = true;
		while (b)
		{
			std::cout << "Fuegen Sie eine Antwortmoeglichkeit hinzu. Tippen Sie \"fertig\" wenn Sie fertig sind.\n";
			std::getline(std::cin, temp);
			if (temp == "fertig")
				b = false;
			else
				tempa.push_back(temp);
		}
		Questions.emplace_back(tempq, tempa, 0, 0);
	}

private:
	void readfile()
	{
		//Scan(filename);	//trash shit fuck for saving
		std::ifstream in(filename);
		for (int i = 0; in.good() && i < numberofquestions; i++)
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
		std::getline(std::cin, answer);
		bool correct = false;
		for (unsigned int j = 0; j < Questions[i].answers.size(); j++)
		{
			correct = correct || (Questions[i].answers[j] == answer);
		}
		correct ? Questions[i].correct = Questions[i].correct + 1 : Questions[i].wrong = Questions[i].wrong + 1;
		return correct;
	}
	void scan()	//trash for saving
	{
		std::string line;
		std::ifstream in(filename);
		if (in.peek() == std::ifstream::traits_type::eof())
			std::cout << "FILE IS EMPTY\n\n\n\n\n\n";	//make exception
		while (std::getline(in, line))
			++numberofquestions;
	}
	void savetofile()
	{
		std::ofstream out(filename);
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
	
private:
	int numberofquestions;
	std::string filename;
	std::vector<QuestionObject> Questions;
	int rounds = 10;
	int chance = 60;
};
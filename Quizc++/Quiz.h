#pragma once

#include <fstream>
#include <iostream>
#include <random>
#include <algorithm>
#include "QuestionObject.h"

struct QaP //Question and Position
{
	std::string question;
	unsigned int line;
	unsigned int line2;
};

class Quiz
{
public:
	Quiz(std::string f)
	{
		filename = f;
		if (scan())
			readfile();
		if (duplicate_questions())
		{
			QaP t = find_duplicate_question();
			std::cout << "FRAGE: " << t.question << " IN ZEILEN: " << t.line << ", " << t.line2 << " IST DOPPELT!.\n\n";
			//do i want to disable the quiz because of this?
		}
	}
	virtual ~Quiz(){}

	void Start(std::mt19937& rng)
	{
		if (allgood)
		{
			std::uniform_int_distribution<int> diceDist(1, 100);
			unsigned int size = Questions.size(); //used so many times, might be worth
			for (int i = 0; i < rounds; i++)
			{
				//sort list: unanswered, mostly wrongs, mostly rights
				std::sort(Questions.begin(), Questions.end());
				//get the index where mostly wrong switches to mostly right
				int wcount = 0;
				for (unsigned int i = 0; i < size; i++)
				{
					if (Questions[i].wrong >= Questions[i].correct)
						wcount++;
				}
				//roll a dice (considering the set chance) if we ask a mostly wrong or mostly right question
				int index = 0;
				int dice;
				//manipulate rng as long as the number of wrong questions is really low (because unanswered is considered wrong)
				if (size > 10) //magic numbers! wuhu!
					if (wcount > size - 5) //magic numbers! wuhu!
						dice = 0;
					else
						dice = diceDist(rng);
				else
					dice = diceDist(rng);
				if (wcount == size)
				{
					//std::cout << "Alle Fragen falsch beantwortet...\nWaehle zufaellige Frage aus.\n\n";
					std::uniform_int_distribution<int> rollq(0, size - 1);
					index = rollq(rng);
				}
				else if (wcount == 0)
				{
					std::cout << "Alle Fragen richtig beantwortet!\nWaehle zufaellige Frage aus.\n\n";
					std::uniform_int_distribution<int> rollq(0, size - 1);
					index = rollq(rng);
				}
				else
				{
					if (dice <= chance)
					{
						std::uniform_int_distribution<int> rollq(0, wcount - 1);
						index = rollq(rng);
					}
					else
					{
						std::uniform_int_distribution<int> rollq(wcount, size - 1);
						index = rollq(rng);
					}
				}
				//ask the question
				std::cout << "Frage Nummer " << i + 1 << ": ";
				int t = askquestion(index);
				//checking errorcodes
				if (t < 0) break;	//-1 "abbrechen"-command //-2 'error with construction'
				//handling normal flow
				if (t == 1)
				{
					//correct answer given
					Questions[i].correct = Questions[i].correct + 1;
					std::cout << "Korrekt!\n";
				}
				else
				{
					//wrong answer given
					Questions[i].wrong = Questions[i].wrong + 1;
					std::cout << "Leider Falsch. Richtige Antwort ist: " << Questions[index].answers[0] << "\n\n";
				}
			}
		}
		else
		{
			std::cout << "Quiz-initialisierung fehlgeschlagen.\n" << std::endl;
		}
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
			std::cout << i + 1 << " # " << Questions[i].question
				<< "Correct: " << Questions[i].correct
				<< " Wrong: " << Questions[i].wrong << std::endl;
		}
		std::cout << std::endl;
	}

	void SetRounds(int r)
	{
		rounds = r;
	}
	void SetChance(int c)
	{
		chance = c;
	}
	void SetPath(std::string fn)
	{
		if (fn != "")
		{
			filename = fn;
			if (scan())
				readfile();
		}
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

	void Safe()
	{
		savetofile();
		std::ofstream out("rememberpath.txt");
		out << filename;
	}
	void HardReset()
	{
		for (unsigned int i = 0; i < Questions.size(); i++)
		{
			Questions[i].correct = 0;
			Questions[i].wrong = 0;
		}
		Safe();
	}

protected:
	bool duplicate_questions() //true for duplicates
	{
		unsigned int size = Questions.size();
		for (unsigned int j = 0u; j < size; j++)
		{
			for (unsigned int k = j+1u; k < size; k++)
			{
				bool b = false;
				b = b || Questions[j].question == Questions[k].question;
				if (b) return true;
			}
		}
		return false;
	}
	QaP find_duplicate_question() //only gets the first question and the first 2 occurences, but i think that should suffice (for now)
	{ //make sure to call duplicate_questions() first!
		unsigned int size = Questions.size();
		for (unsigned int j = 0u; j < size; j++)
		{
			for (unsigned int k = j + 1u; k < size; k++)
			{
				bool b = false;
				b = b || Questions[j].question == Questions[k].question;
				if (b) return { Questions[j].question, j+1u, k+1u };
			}
		}
	}
	void readfile()
	{
		std::ifstream in(filename);
		for (int i = 0; in.good() && i < numberofquestions; i++)
		{
			std::string q;
			std::string as;
			std::vector<std::string> av;
			int c;
			int w;
			std::getline(in, q, delimiter);
			int j = 0;
			while (!(in.peek() >= '0' && in.peek() <= '9'))
				/*
				this in.peek() for a number works, but disabled numbers to be used in answers,
				which really sucks to be honest,
				way around that: count number of ";" per line first and then
				reserve first for question
				and last 2 for the correct and wrong
				and go from 2nd ";" to 3rd to last ";"

				might this fix (or help with fixing) the issue of total annihilation crash when the .txt isnt in the right format?
				*/
			{
				std::getline(in, as, delimiter); j++; av.emplace_back(as);
			}
			std::string temp;
			std::getline(in, temp, delimiter);
			c = std::stoi(temp);
			std::getline(in, temp, delimiter);
			w = std::stoi(temp);
			Questions.emplace_back(q, av, c, w);
			in.ignore(1, '\n');
		}
	}
	virtual int askquestion(int i) = 0;
	bool scan()	//trash for saving
	{
		std::string line;
		std::ifstream in(filename);
		if (in.peek() == std::ifstream::traits_type::eof())
		{
			std::cout << "FILE IS EMPTY\n\n\n\n\n\n";	//possibly make exception?
			return false;
		}
		while (std::getline(in, line))
			++numberofquestions;
		return true;
	}
	void savetofile()
	{
		std::ofstream out(filename);
		for (unsigned int i = 0; i < Questions.size(); i++)
		{
			out << Questions[i].question << delimiter;
			for (unsigned int j = 0; j < Questions[i].answers.size(); j++)
			{
				out << Questions[i].answers[j] << delimiter;
			}
			out << Questions[i].correct << delimiter;
			out << Questions[i].wrong << delimiter << "\n";
		}
	}
	
protected:
	int numberofquestions;
	std::string filename;
	char delimiter = ';';
	std::vector<QuestionObject> Questions;
	int rounds = 10;
	int chance = 75;
	bool allgood = false;
};
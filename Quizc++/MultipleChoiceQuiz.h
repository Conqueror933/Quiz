#pragma once
#include "Quiz.h"
#include "SafeInput.h"
#include <random>

class MultipleChoiceQuiz : public Quiz
{
public:
	MultipleChoiceQuiz(std::string f) : Quiz(f) {}

protected:
	int askquestion(int i) override
	{
		//init
		unsigned int size = Questions.size();
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<unsigned int> dice(0u, size-1u);
		std::uniform_int_distribution<unsigned int> vdice(0u, 3u);
		std::vector<std::string> v(4);
		bool allgood = false;

		//it ain't pretty, but it'll keep double answers from showin up...

		//checking if there are at least 4 unique questions
		if (numberofquestions > 3)
		{
			//checking if there are at least 4 unique answers
			int temp = 0;
			for (unsigned int j = 0u; j < size; j++)
			{
				for (unsigned int k = j; k < size; k++)
				{
					bool b = false;
					b = b || Questions[j].answers[0] != Questions[k].answers[0];
					if (b)
					{
						temp++;
						break;
					}
				}
				if (temp == 4)
				{
					allgood = true;
					break;
				}
			}
		}
		else
		{
			std::cout << "Quiz muss mindestens 4 Fragen haben." << std::endl;
			return -3;
		}

		//making sure there are enough answers
		unsigned int i2, i3, i4; 
		if (allgood)
		{//picking out the answer choices
			do { i2 = dice(rng); } while (i2 == i || Questions[i2].answers[0] == Questions[i].answers[0]);
			do { i3 = dice(rng); } while (i3 == i2 || i3 == i
				|| Questions[i3].answers[0] == Questions[i].answers[0] || Questions[i3].answers[0] == Questions[i2].answers[0]);
			do { i4 = dice(rng); } while (i4 == i3 || i4 == i2 || i4 == i
				|| Questions[i4].answers[0] == Questions[i].answers[0] || Questions[i4].answers[0] == Questions[i2].answers[0]
				|| Questions[i4].answers[0] == Questions[i3].answers[0]);
		}
		else
		{
			std::cout << "Quiz muss mindestens 4 unterschiedliche Antworten haben." << std::endl;
			return -2;
		}

		//randomly distributing for the 4 slots
		unsigned int r1, r2, r3, r4;
		r1 = vdice(rng);
		do { r2 = vdice(rng); } while (r2 == r1);
		do { r3 = vdice(rng); } while (r3 == r2 || r3 == r1);
		r4 = 6; r4 -= r3; r4 -= r2; r4 -= r1;

		//putting the answers in order
		v[r1] = Questions[i].answers[0];
		v[r2] = Questions[i2].answers[0];
		v[r3] = Questions[i3].answers[0];
		v[r4] = Questions[i4].answers[0];

		//output
		std::cout << "Frage Nummer " << i + 1 << ": ";
		std::cout << Questions[i].question << "\n"
			<< "1: " << v[0] << " 2: " << v[1] << " 3: " << v[2] << " 4: " << v[3];

		//check and return
		std::string s = SafeInput::GetString("");
		if (s == "abbrechen")
			return -1;
		if (s >= "1" && s <= "4")
			return stoi(s) - 1 == r1;
		return s == v[r1];
	}
};
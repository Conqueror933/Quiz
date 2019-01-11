#pragma once
#include "Quiz.h"
#include "SafeInput.h"

class InputBasedQuiz : public Quiz
{
public:
	InputBasedQuiz(std::string f) : Quiz(f) {}

protected:
	bool askquestion(int i) override
	{
		std::string answer;
		std::cout << Questions[i].question;
		std::getline(std::cin, answer);
		bool correct = false;
		for (unsigned int j = 0; j < Questions[i].answers.size(); j++)
		{
			correct = correct || (Questions[i].answers[j] == answer);
		}
		correct ? Questions[i].correct = Questions[i].correct + 1 : Questions[i].wrong = Questions[i].wrong + 1;
		return correct;
	}
};
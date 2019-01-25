#pragma once
#include "Quiz.h"
#include "SafeInput.h"

class InputBasedQuiz : public Quiz
{
public:
	InputBasedQuiz(std::string f) : Quiz(f) { allgood = true; }

protected:
	int askquestion(int i) override
	{
		std::string answer = SafeInput::GetString(Questions[i].question);
		if (answer == "abbrechen") return -1;
		bool correct = false;
		for (unsigned int j = 0; j < Questions[i].answers.size(); j++)
		{
			correct = correct || (Questions[i].answers[j] == answer);
		}
		return correct;
	}
};
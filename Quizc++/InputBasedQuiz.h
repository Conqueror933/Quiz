#pragma once
#include "Quiz.h"
#include "SafeInput.h"

class InputBasedQuiz : public Quiz
{
public:
	InputBasedQuiz(std::string f) : Quiz(f) {}

protected:
	int askquestion(int i) override
	{
		std::cout << "Frage Nummer " << i + 1 << ": ";
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
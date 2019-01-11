#pragma once
#include <string>
#include <vector>

struct QuestionObject
{
public:
	QuestionObject(std::string question, std::vector<std::string> answers, int correct, int wrong)
		:
		question(question),
		answers(answers),
		correct(correct),
		wrong(wrong)
	{}

	bool operator < (const QuestionObject& rhs)
	{
		if (correct + wrong == 0)
			if (rhs.correct + rhs.wrong == 0)
				return question < rhs.question;
			else
				return true;
		else
			if (rhs.correct + rhs.wrong == 0)
				return false;
			else
				return wrong * 100 / (correct + wrong) > rhs.wrong * 100 / (rhs.correct + rhs.wrong);
	}

public:
	std::string question;
	std::vector<std::string> answers;
	int correct;
	int wrong;
};
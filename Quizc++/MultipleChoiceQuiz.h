#pragma once
#include "Quiz.h"
#include "SafeInput.h"
#include <random>

class MultipleChoiceQuiz : public Quiz
{
public:
	MultipleChoiceQuiz(std::string f) : Quiz(f) {}

protected:
	bool askquestion(int i) override
	{
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<unsigned int> dice(0u, Questions.size()-1u);
		std::uniform_int_distribution<unsigned int> vdice(0u, 3u);
		std::vector<std::string> v(4);

		unsigned int i2, i3, i4;
		do { i2 = dice(rng); } while (i2 == i);
		do { i3 = dice(rng); } while (i3 == i2 || i3 == i);
		do { i4 = dice(rng); } while (i4 == i3 || i4 == i2 || i4 == i);

		unsigned int r1, r2, r3, r4;
		r1 = vdice(rng);
		do { r2 = vdice(rng); } while (r2 == r1);
		do { r3 = vdice(rng); } while (r3 == r2 || r3 == r1);
		r4 = 6; r4 -= r3; r4 -= r2; r4 -= r1;

		v[r1] = Questions[i].answers[0];
		v[r2] = Questions[i2].answers[0];
		v[r3] = Questions[i3].answers[0];
		v[r4] = Questions[i4].answers[0];

		std::cout << Questions[i].question << "\n"
			<< "1: " << v[0] << " 2: " << v[1] << " 3: " << v[2] << " 4: " << v[3];

		std::string s = SafeInput::GetString("");
		if (s >= "1" && s <= "4")
			return stoi(s) - 1 == r1;
		return s == v[r1];
	}
};
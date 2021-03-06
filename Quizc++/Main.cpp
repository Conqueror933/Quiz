#include <Windows.h>
#include "InputBasedQuiz.h"
#include "MultipleChoiceQuiz.h"
#include "SafeInput.h"
#include <memory>

int main()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 800, 640, TRUE); // 800 width, 640 height

	std::random_device rd;
	std::mt19937 rng(rd());

	std::unique_ptr<Quiz> quiz;
	std::string quiztype = SafeInput::GetString("Willkommen zum Quiz!\n"
		"Lernformat oder 'Wer wird Millionaer'-format?\n"
		"1 Lernformat, 2 'Wer wird Millionaer'");
	if (quiztype == "1")
	{
		std::string temp;
		do
		{
			temp = SafeInput::GetPath("Pfad setzen: ", 1);
		} while (temp == "");
		quiz = std::make_unique<InputBasedQuiz>(temp);
	}
	else
	{
		std::string temp;
		do
		{
			temp = SafeInput::GetPath("Pfad setzen: ", 1);
		} while (temp == "");
		quiz = std::make_unique<MultipleChoiceQuiz>(temp);
	}

	//main loop here
	while (true)
	{
		int choice;
		choice = SafeInput::GetInt("Hauptmenu:\n"
			"01: Quiz starten\n"
			"02: Statistiken abrufen\n"
			"03: Pro Frage Statistiken abrufen\n"
			"04: Chance fuer falsch beantwortete Fragen anpassen\n"
			"05: Anzahl der Fragen pro Runde setzen\n"
			"06: Waehle andere Quizdatei aus\n"
			"07: Neue Frage hinzufuegen\n"
			"08: Art des Quizes aendern\n"
			"09: Zwischenspeichern\n"
			"00: Speichern und Beenden\n"
			"10: Beenden ohne Speichern\n"
			"99: Statistiken zuruecksetzen");

		switch (choice)
		{
		case 0:	//Beenden
			quiz->Safe();
		case 10: //NoSafe Quit
			return 0;
		case 1:	//Quiz starten
			quiz->Start(rng);
			break;
		case 2:	//Statistiken abrufen
			quiz->GetStatistics();
			break;
		case 3:	//Pro Frage Statistiken abrufen
			quiz->GetPQStatistics();
			break;
		case 4:	//Chance f�r falsch beantwortete Fragen anpassen
			quiz->SetChance(SafeInput::GetInt("Wie hoch soll die Chance fuer zuvor falsch beantwortete Fragen sein? (in %): "));
			break;
		case 5:	//Anzahl der Fragen pro Runde setzen
			quiz->SetRounds(SafeInput::GetInt("Wie viele Runden moechten Sie spielen? "));
			break;
		case 6:	//W�hle andere Quizdatei aus
			quiz->SetPath(SafeInput::GetPath("Geben Sie den vollst�ndigen Pfad an. "));
			break;
		case 7:	//Neue Frage hinzuf�gen
			quiz->AddQuestion();
			break;
		case 8:	//Art des Quizes �ndern
			if (quiztype == "1")
			{
				quiz = std::make_unique<MultipleChoiceQuiz>(SafeInput::GetPath("Pfad setzen: ", 1));
				quiztype = "2";
			}
			else
			{
				quiz = std::make_unique<InputBasedQuiz>(SafeInput::GetPath("Pfad setzen: ", 1));
				quiztype = "1";
			}
			break;
		case 9:
			quiz->Safe();
		case 99: //HardReset
			quiz->HardReset();
			break;
		default://wrong input
			//happens when a number is entered that is not assigned, like 23242525
			std::cout << "Wrong input.\n\n";
			break;
		}
	}
}
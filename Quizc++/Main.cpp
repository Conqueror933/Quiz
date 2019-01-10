#include "Quiz.h"
#include "SafeInput.h"

int main()
{
	std::random_device rd;
	std::mt19937 rng(rd());
	Quiz quiz("C:\\Users\\User\\source\\repos\\Quizc++\\Resources\\Quiz.txt");
	//main loop here
	std::cout << "Willkommen zum kleinen Quiz der Baustoffkunde!\n";
	while (true)
	{
		int choice;
		choice = SafeInput::GetInt("Hauptmenu:\n"
			"Quiz starten: 1\n"
			"Statistiken abrufen: 2\n"
			"Pro Frage Statistiken abrufen: 3\n"
			"Chance fuer falsch beantwortete Fragen anpassen: 4\n"
			"Anzahl der Fragen pro Runde setzen: 5\n"
			"Waehle andere Quizdatei aus: 6\n"
			"Neue Frage hinzufuegen: 7\n"
			//"Hard Reset: 8\n"
			"Beenden: 0");

		switch (choice)
		{
		case 0:	//Beenden
			return 0;
		case 1:	//Quiz starten
			quiz.Start(rng);
			break;
		case 2:	//Statistiken abrufen
			quiz.GetStatistics();
			break;
		case 3:	//Pro Frage Statistiken abrufen
			quiz.GetPQStatistics();
			break;
		case 4:	//Chance für falsch beantwortete Fragen anpassen
			quiz.SetChance(SafeInput::GetInt("Wie hoch soll die Chance fuer zuvor falsch beantwortete Fragen sein? (in %): "));
			break;
		case 5:	//Anzahl der Fragen pro Runde setzen
			quiz.SetRounds(SafeInput::GetInt("Wie viele Runden moechten Sie spielen? "));
			break;
		case 6:	//Wähle andere Quizdatei aus
			quiz.SetPath(SafeInput::GetPath("Geben Sie den vollständigen Pfad an. "));
			break;
		case 7:	//Neue Frage hinzufügen
			quiz.AddQuestion();
			break;
		//case 8:	//Hard Reset
		//	//not even sure what i had in mind when laying this out
		//	break;
		default://wrong input
			//should never happen
			std::cout << "Wrong input.\n\n";
			break;
		}
	}
}
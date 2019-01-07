#include "Quiz.h"
#include <iostream>

int main()
{
	Quiz quiz("C:\\Users\\User\\PycharmProjects\\Python Quiz\\Quizc.txt");
	//main loop here
	std::cout << "Willkommen zum kleinen Quiz der Baustoffkunde!\n";
	while (true)
	{
		int choice;
		std::cout << "Hauptmenu:\n"
			<< "Quiz starten: 1\n"
			<< "Statistiken abrufen: 2\n"
			<< "Pro Frage Statistiken abrufen: 3\n"
			<< "Chance f�r falsch beantwortete Fragen anpassen: 4\n"
			<< "Anzahl der Fragen pro Runde setzen: 5\n"
			<< "W�hle andere Quizdatei aus: 6\n"
			<< "Neue Frage hinzuf�gen: 7\n"
			<< "Hard Reset: 8\n"
			<< "Beenden: 0\n";
		std::cin >> choice;
		switch (choice)
		{
		case 0:	//Beenden
			return 0;
		case 1:	//Quiz starten
			quiz.Start();
			break;
		case 2:	//Statistiken abrufen
			break;
		case 3:	//Pro Frage Statistiken abrufen
			break;
		case 4:	//Chance f�r falsch beantwortete Fragen anpassen
			break;
		case 5:	//Anzahl der Fragen pro Runde setzen
			break;
		case 6:	//W�hle andere Quizdatei aus
			break;
		case 7:	//Neue Frage hinzuf�gen
			break;
		case 8:	//Hard Reset
			break;
		default://wrong input
			throw;
			break;
		}
	}
	//main loop here
	std::cout << "Press the 'Enter' key to close...";
	std::cin.get();
	return 0;
}
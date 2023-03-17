#include <iostream>
#include "Car.h"
#include "Buyer.h"

using namespace std;

int main()
{
	// створення об'єкту авто з початковою ціною 100_000 $
	Car* bmw = new Car("bmw X9", 100000);

	// створення об'єктів потенційних покупців
	UkrainianBuyer* firstBuyer = new UkrainianBuyer("Petro Mikolaenko");
	UkrainianBuyer* secondBuyer = new UkrainianBuyer("Oleg Kononenko");

	// покупці цікавляться конкретним авто
	bmw->Attach(firstBuyer);
	bmw->Attach(secondBuyer);
	// others...

	// зменшення ціни авто, зацікавлені покупці відразу про це дізнаються
	bmw->SetPrice(80000);
	bmw->SetPrice(70000);

	bmw->Detach(secondBuyer);

	bmw->SetPrice(65000);
	bmw->SetPrice(60000);

	delete firstBuyer;
	delete secondBuyer;
	delete bmw;

	system("pause");
	return 0;
}
#include "Functions.h"
#include "List.h"
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char* argv[])
{
    srand(time(NULL));

   vector<string>inputs = Inputs(argc, argv);
  
if (inputs.size())
{

       

       List<Diver> divers;
       Diver Wojtek("Wojtek", "Dranka", "XR", 20, 300, 130429);
       Diver Piotr("Piotr", "Dranka", "DEEP", 53, 150, 123321);
       Diver Iwona("Iwona", "Dranka", "DEEP", 50, 132, 2009988);
       Diver Ostatni("Ostatni", "Nurek", "OWD_W_Jackecie", 0, 10, 99999999);

       List <Flight> flights;
       Flight KatBar("Katowice", "Barcelona", "12.02.2021", "23.02.2021", "AirSpain", 2300, true);
       Flight KraAms("Krakow", "Amsterdam", "30.12.2021", "02.01.2022", "Lot", 450, true);
       Flight WarPhu("Warszawa", "Phuket", "11.08.2022", "08.09.2022", "AirKorea", 3000, false);
       Flight FraMex("Frankfurt", "Mexico_City", "11.07.2022", "08.08.2022", "UsaFly", 6300, true);
       Flight ParMau("Paryz", "Mauritius", "00.00.0000", "99.99.9999", "AirFrance", 9999, false);



       divers.Read(inputs[0]);
       flights.Read(inputs[1]);

       List<string> words;
       words.Read(inputs[2]);

       divers.Write("outnurkowie.bin");
       flights.Write("outloty.bin");
       words.Write("outstring.bin"); 

       divers.Sort(false, cmpDiverDives);
       divers.Display();

       cout<<"Szukany element na pozycji: "<<divers.Find(Wojtek)<<endl<<endl;

       flights.Sort(true, cmpFlightFrom);
       flights.Display();
       cout <<"Szukany element na pozycji: " << flights.Find(KatBar) << endl;


       List<int> numbers;
       for (int i = 0; i < 10; i++) {
           numbers.Append(rand() % 10);
       }

       List<int> numbers2 = numbers;
       List <int> numbers3;
       numbers3 = numbers;
       
       cout << "Liczby: ";
       numbers.Display();
       cout << endl<<"Liczby po Sortowaniu: ";
       numbers.Sort(false);
       numbers.Display();
       numbers.Delete(numbers.Size()-1);
       cout << "Liczby po usunieciu: ";
       numbers.Display();
       cout << endl<<"Liczby 2: ";
       numbers2.Display();
       cout << endl<<"Liczby 3: ";
       numbers3.Display();
    
       List <int> numbers4 = move(numbers);
       cout << endl << "Liczby 4: ";
       numbers4.Display();
       cout << endl << "Liczby: ";
       numbers.Display();

       numbers = move(numbers4);
       cout << endl << "Liczby 4: ";
       numbers4.Display();
       cout << endl << "Liczby: ";
       numbers.Display();


       words.Display();
       words.Append("KONIEC");
       words.Prepend("POCZATEK");
       cout << endl;
       words.Display();
       cout<<"Szukany element (bardzo) na pozycji: "<<words.Find("bardzo")<<endl;
 
       
       
}
}

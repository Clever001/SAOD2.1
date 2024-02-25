/*
    17.	Одна запись счета за ремонтные работы содержит поля: название фирмы, вид работ, единица измерения, 
    стоимость единицы выполненных работ, дата исполнения, количество выполненных работ. Поиск и сортировка 
    — по названию фирмы, виду работ, дате исполнения.
*/

#include <windows.h>
#include "Controller.h"

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    SetConsoleTitle(TEXT("Никончук В.И. КЭ-243"));
    
    Controller cont;
    
    int act;
    Controller::InputValue(act, "Как вы хотите ввести данные?\n0 - с консоли\n1 - из файла");
    if (!act)
        cont.InitListFromConsole();
    else {
        bool fileReadSuccess = cont.InitListFromTxt("C:\\Users\\cakev\\OneDrive\\Рабочий стол\\структуры и алгоритмы обработки данных\\2\\SAOD2(1)\\Input.txt");
        if (!fileReadSuccess) {
            Controller::Print("Не удалось открыть файл на чтение.");
            return 1;
        }
    }
    Controller::Print();
    cont.SortData();
    Controller::Print();
    cont.PrintList();
    Controller::Print();
    cont.SearchDataFromConsole();
}

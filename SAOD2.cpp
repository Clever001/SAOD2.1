/*
    17.	Одна запись счета за ремонтные работы содержит поля: название фирмы, вид работ, единица измерения, 
    стоимость единицы выполненных работ, дата исполнения, количество выполненных работ. Поиск и сортировка 
    — по названию фирмы, виду работ, дате исполнения.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <windows.h>
#include <stdlib.h>
#include <vector> // Нужен для более простого вывода списка в консоль
#include "LinkedList.h"
#define READ_DATA(dataField, width) \
    if ((in >> setw(width) >> dataField).fail()) exitWithFailure();

using namespace std;

static void exitWithFailure() {
    cout << "Неправильно составлен файл с входными данными.\n";
    exit(EXIT_FAILURE);
}

template <typename T>
static void inputValue(T& value, const string& message) {
    std::cout << message << '\n';
    std::cin >> value;
}

static void printData(const Data& data) {
    cout << "Название фирмы: " << data.firmName << '\n';
    cout << "Вид работ: " << data.workType << '\n';
    cout << "Единица измерений: " << data.measure << '\n';
    cout << "Стоимость единицы выполненных работ: " << data.cost << '\n';
    cout << "Дата исполнения: " << data.date << '\n';
    cout << "Количество выполненных работ: " << data.workCnt << '\n';
}

static void printList(const LinkedList& list) {
    vector<Data> vec = list.getAllData();
    for (const auto& data : vec) {
        printData(data);
        cout << '\n';
    }
    cout << '\n';
}

static void PrintOptionalData(const optional<pair<Data, int>>& data) {
    if (data.has_value()) {
        cout << "Было найдено значение с индексом " << data.value().second << ".\n";
        printData(data.value().first);
    }
    else {
        cout << "Значение не было найдено.\n";
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    SetConsoleTitle(TEXT("Никончук В.И. КЭ-243"));
    
    LinkedList list;
    string inputFile = "D:\\study\\Структуры и алгоритмы обработки данных\\2\\SAOD2.1\\Input1.txt";
    ifstream in(inputFile);
    if (!in.is_open()) {
        cout << "Не удалось открыть файл с входными данными.\n";
        exit(EXIT_FAILURE);
    }
    cout << "Происходит ввод данных с файла.\n";
    int cnt, act; // cnt - количество элементов в списке; при act = 1 - добавление в конец, иначе (при 0) в начало.
    if ((in >> cnt >> act).fail()) exitWithFailure();
    for (; cnt > 0; --cnt) {
        Data data;
        READ_DATA(data.firmName, 17)
        READ_DATA(data.workType, 21)
        READ_DATA(data.measure, 19)
        READ_DATA(data.cost, 9)
        READ_DATA(data.date, 14)
        READ_DATA(data.workCnt, 10)
        if (!act)
            list.push_front(data);
        else
            list.push_back(data);
    }
    cout << "Файл прочитан. Информация была введена.\n\n";
    
    printList(list);

    // ----- Сортировка данных
    inputValue(act, "По какому ключу вы хотите сортировать данные?\n0 - по названию фирмы\n1 - по виду работ\n2 - по дате исполнения");
    switch (act) {
    case 0:
    {
        list.sort([](const Data& l, const Data& r) {
            return l.firmName > r.firmName;
            });
    }
    break;
    case 1:
    {
        list.sort([](const Data& l, const Data& r) {
            return l.workType > r.workType;
            });
    }
    break;
    default:
    {
        list.sort([](const Data& l, const Data& r) {
            return l.date > r.date;
            });
    }
    break;
    }

    printList(list);

    // ----- Поиск значения в списке
    inputValue(act, "По какому ключу вы хотите искать значения в списке?\n0 - по названию фирмы\n1 - по виду работ\n2 - по дате исполнения");
    switch (act) {
    case 0:
    {
        string firmName;
        inputValue(firmName, "Введите название фирмы.");
        auto pair = list.search([&firmName](const Data& item) {
            return item.firmName == firmName;
            });
        PrintOptionalData(pair);
    }
    break;
    case 1:
    {
        string workType;
        inputValue(workType, "Введите вид работ.");
        auto pair = list.search([&workType](const Data& item) {
            return item.workType == workType;
            });
        PrintOptionalData(pair);
    }
    break;
    default:
    {
        string date;
        inputValue(date, "Введите дату исполнения.");
        auto pair = list.search([&date](const Data& item) {
            return item.date == date;
            });
        PrintOptionalData(pair);
    }
    break;
    }
}

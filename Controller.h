#pragma once
#include <iostream>
#include <fstream>
#include "LinkedList.h"
using namespace std;

/*
    17.	Одна запись счета за ремонтные работы содержит поля: название фирмы, вид работ, единица измерения,
    стоимость единицы выполненных работ, дата исполнения, количество выполненных работ. Поиск и сортировка
    — по названию фирмы, виду работ, дате исполнения.
*/

class Controller {
private:
    LinkedList list;
    void PrintOptionalData(const optional<pair<Data, int>>& data) {
        if (data.has_value()) {
            cout << "Было найдено значение с индексом " << data.value().second << ".\n";
            PrintData(data.value().first);
        }
        else {
            Print("Значение не было найдено.");
        }
    }
public:
    template <typename T>
    static void InputValue(T& value, const string& message) {
        std::cout << message << '\n';
        std::cin >> value;
    }
    static void Print(const string& str = "") {
        std::cout << str << '\n';
    }
    bool InitListFromTxt(const string& path) {
        ifstream in(path);
        if (!in.is_open())
            return false;
        int cnt, act;
        in >> cnt >> act;
        for (; cnt > 0; --cnt) {
            Data data;
            in >> data.firmName;
            in >> data.workType;
            in >> data.measure;
            in >> data.cost;
            in >> data.date;
            in >> data.workCnt;
            if (!act)
                list.PushFront(data);
            else
                list.PushBack(data);
        }
        return true;
    }
    void InitListFromConsole() {
        int cnt;
        InputValue(cnt, "Сколько элементов вы хотите добавить в список?");
        int act;
        InputValue(act, "Куда вы хотите добавлять новые значения?\n0 - в начало списка\n1 - в конец списка");
        
        for (; cnt > 0; --cnt) {
            Print();
            Data data;
            InputValue(data.firmName, "Введите название фирмы");
            InputValue(data.workType, "Введите вид работ");
            InputValue(data.measure, "Введите единицы измерений");
            InputValue(data.cost, "Введите стоимость единицы выполненных работ");
            InputValue(data.date, "Введите дату исполнения");
            InputValue(data.workCnt, "Введите количество выполненных работ");

            if (act == 0)
                list.PushFront(data);
            else
                list.PushBack(data);
        }
    }
    void SortData() {
        int act;
        InputValue(act, "По какому ключу вы хотите сортировать данные?\n0 - по названию фирмы\n1 - по виду работ\n2 - по дате исполнения");
        switch (act) {
        case 0:
            {
                list.Sort([](const Data& l, const Data& r) {
                        return l.firmName > r.firmName;
                    });
            }
            break;
        case 1:
            {
                list.Sort([](const Data& l, const Data& r) {
                        return l.workType > r.workType;
                    });
            }
            break;
        default:
            {
                list.Sort([](const Data& l, const Data& r) {
                        return l.date > r.date;
                    });
            }
            break;
        }
    }
    static void PrintData(const Data& data) {
        cout << "Название фирмы: " << data.firmName << '\n';
        cout << "Вид работ: " << data.workType << '\n';
        cout << "Единица измерений: " << data.measure << '\n';
        cout << "Стоимость единицы выполненных работ: " << data.cost << '\n';
        cout << "Дата исполнения: " << data.date << '\n';
        cout << "Количество выполненных работ: " << data.workCnt << '\n';
    }
    void PrintList() {
        Print("Вывод информации из списка.");
        list.BeginRead();
        do {
            Print();
            PrintData(list.GetCurData());
        } while (list.NextData());
        Print();
    }
    void SearchDataFromConsole() {
        Print("Введите данные для поиска значения в списке.");

        int act;
        InputValue(act, "По какому ключу вы хотите искать значения в списке?\n0 - по названию фирмы\n1 - по виду работ\n2 - по дате исполнения");
        switch (act) {
        case 0:
        {
            string firmName;
            InputValue(firmName, "Введите название фирмы.");
            auto pair = list.Search([&firmName](const Data& item){
                    return item.firmName == firmName;
                });
            PrintOptionalData(pair);
        }
        break;
        case 1:
        {
            string workType;
            InputValue(workType, "Введите вид работ.");
            auto pair = list.Search([&workType](const Data& item) {
                return item.workType == workType;
                });
            PrintOptionalData(pair);
        }
        break;
        default:
        {
            string date;
            InputValue(date, "Введите дату исполнения.");
            auto pair = list.Search([&date](const Data& item) {
                return item.date == date;
                });
            PrintOptionalData(pair);
        }
        break;
        }
    }
};
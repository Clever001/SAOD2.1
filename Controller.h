#pragma once
#include <iostream>
#include <fstream>
#include "LinkedList.h"
using namespace std;

/*
    17.	���� ������ ����� �� ��������� ������ �������� ����: �������� �����, ��� �����, ������� ���������,
    ��������� ������� ����������� �����, ���� ����������, ���������� ����������� �����. ����� � ����������
    � �� �������� �����, ���� �����, ���� ����������.
*/

class Controller {
private:
    LinkedList list;
    void PrintOptionalData(const optional<pair<Data, int>>& data) {
        if (data.has_value()) {
            cout << "���� ������� �������� � �������� " << data.value().second << ".\n";
            PrintData(data.value().first);
        }
        else {
            Print("�������� �� ���� �������.");
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
        InputValue(cnt, "������� ��������� �� ������ �������� � ������?");
        int act;
        InputValue(act, "���� �� ������ ��������� ����� ��������?\n0 - � ������ ������\n1 - � ����� ������");
        
        for (; cnt > 0; --cnt) {
            Print();
            Data data;
            InputValue(data.firmName, "������� �������� �����");
            InputValue(data.workType, "������� ��� �����");
            InputValue(data.measure, "������� ������� ���������");
            InputValue(data.cost, "������� ��������� ������� ����������� �����");
            InputValue(data.date, "������� ���� ����������");
            InputValue(data.workCnt, "������� ���������� ����������� �����");

            if (act == 0)
                list.PushFront(data);
            else
                list.PushBack(data);
        }
    }
    void SortData() {
        int act;
        InputValue(act, "�� ������ ����� �� ������ ����������� ������?\n0 - �� �������� �����\n1 - �� ���� �����\n2 - �� ���� ����������");
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
        cout << "�������� �����: " << data.firmName << '\n';
        cout << "��� �����: " << data.workType << '\n';
        cout << "������� ���������: " << data.measure << '\n';
        cout << "��������� ������� ����������� �����: " << data.cost << '\n';
        cout << "���� ����������: " << data.date << '\n';
        cout << "���������� ����������� �����: " << data.workCnt << '\n';
    }
    void PrintList() {
        Print("����� ���������� �� ������.");
        list.BeginRead();
        do {
            Print();
            PrintData(list.GetCurData());
        } while (list.NextData());
        Print();
    }
    void SearchDataFromConsole() {
        Print("������� ������ ��� ������ �������� � ������.");

        int act;
        InputValue(act, "�� ������ ����� �� ������ ������ �������� � ������?\n0 - �� �������� �����\n1 - �� ���� �����\n2 - �� ���� ����������");
        switch (act) {
        case 0:
        {
            string firmName;
            InputValue(firmName, "������� �������� �����.");
            auto pair = list.Search([&firmName](const Data& item){
                    return item.firmName == firmName;
                });
            PrintOptionalData(pair);
        }
        break;
        case 1:
        {
            string workType;
            InputValue(workType, "������� ��� �����.");
            auto pair = list.Search([&workType](const Data& item) {
                return item.workType == workType;
                });
            PrintOptionalData(pair);
        }
        break;
        default:
        {
            string date;
            InputValue(date, "������� ���� ����������.");
            auto pair = list.Search([&date](const Data& item) {
                return item.date == date;
                });
            PrintOptionalData(pair);
        }
        break;
        }
    }
};
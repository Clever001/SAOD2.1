#pragma once
#include <functional>
#include <optional>
using namespace std;

struct Data {
    string firmName, workType, measure, date;
    int cost = -1, workCnt = -1;
};

struct Node {
    Data data;
    Node* next;

    Node(const Data& data, Node* next = nullptr) {
        this->data = data;
        this->next = next;
    }
};

class LinkedList {
private:
    Node* head;
    int size;
    Node* _cur;
public:
    LinkedList() {
        head = nullptr;
        size = 0;
        _cur = nullptr;
    }
    int Size() const {
        return size;
    }
    bool Empty() const {
        return head == nullptr;
    }
    optional<pair<Data, size_t>> Search(std::function<bool(const Data&)> cmp) const {
        if (Empty()) return {};
        size_t index = 0;
        for (Node* cur = head; cur != nullptr; cur = cur->next) {
            if (cmp(cur->data))
                return pair<Data, size_t>({ cur->data, index });
            ++index;
        }
        return {};
    }
    void Sort(bool (*cmp)(const Data& left, const Data& right)) {
        for (int i = 0; i < size - 1; ++i) {
            Node* cur = head;
            for (int j = 0; j < size - i - 1; ++j) {
                if (cmp(cur->data, cur->next->data))
                    std::swap(cur->data, cur->next->data);
                cur = cur->next;
            }
        }
    }
    void PushBack(const Data& data) {
        if (head == nullptr)
            head = new Node(data);
        else {
            Node* cur = head;
            for (; cur->next != nullptr; cur = cur->next);
            cur->next = new Node(data);
        }
        ++size;
    }
    void PushFront(const Data& data) {
        if (head == nullptr)
            head = new Node(data);
        else {
            Node* newNode = new Node(data, head);
            head = newNode;
        }
        ++size;
    }
    Data& operator [] (size_t index) {
        if (index >= size)
            throw exception("Wrong index!");
        Node* cur = head;
        for (; index != 0; --index)
            cur = cur->next;
        return cur->data;
    }
    void PopFront() {
        if (head != nullptr) {
            Node* tmp = head->next;
            delete head;
            head = tmp;
            --size;
        }
    }
    void BeginRead() {
        _cur = head;
    }
    bool NextData() {
        if (head == nullptr) 
            return false;
        if (_cur->next == nullptr) {
            return false;
        }
        else {
            _cur = _cur->next;
            return true;
        }
    }
    Data GetCurData() const {
        return _cur->data;
    }
    ~LinkedList() {
        for (; head != nullptr; PopFront());
    }
};
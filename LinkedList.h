#pragma once
#include <functional>
#include <optional>
#include <vector>
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
    int _size;
    Node* _cur;
public:
    LinkedList() {
        head = nullptr;
        _size = 0;
        _cur = nullptr;
    }
    int size() const {
        return _size;
    }
    bool empty() const {
        return head == nullptr;
    }
    optional<pair<Data, size_t>> search(std::function<bool(const Data&)> cmp) const {
        if (empty()) return {};
        size_t index = 0;
        for (Node* cur = head; cur != nullptr; cur = cur->next) {
            if (cmp(cur->data))
                return pair<Data, size_t>({ cur->data, index });
            ++index;
        }
        return {};
    }
    void sort(bool (*cmp)(const Data& left, const Data& right)) {
        for (int i = 0; i < _size - 1; ++i) {
            Node* cur = head;
            for (int j = 0; j < _size - i - 1; ++j) {
                if (cmp(cur->data, cur->next->data))
                    std::swap(cur->data, cur->next->data);
                cur = cur->next;
            }
        }
    }
    void push_back(const Data& data) {
        if (empty())
            head = new Node(data);
        else {
            Node* cur = head;
            for (; cur->next != nullptr; cur = cur->next);
            cur->next = new Node(data);
        }
        ++_size;
    }
    void push_front(const Data& data) {
        if (empty())
            head = new Node(data);
        else {
            Node* newNode = new Node(data, head);
            head = newNode;
        }
        ++_size;
    }
    /*
    Data& operator [] (size_t index) {
        if (index >= _size)
            throw exception("Wrong index!");
        Node* cur = head;
        for (; index != 0; --index)
            cur = cur->next;
        return cur->data;
    }
    */
    void pop_front() {
        if (!empty()) {
            Node* tmp = head->next;
            delete head;
            head = tmp;
            --_size;
        }
    }
    vector<Data> getAllData() const {
        // »спользуетс€ только при выводе списка в консоль.
        vector<Data> vec;
        Node* cur = head;
        for (; cur != nullptr; cur = cur->next)
            vec.push_back(cur->data);
        return vec;
    }
    void beginRead() {
        _cur = head;
    }
    bool nextData() {
        if (empty()) 
            return false;
        if (_cur->next == nullptr) {
            return false;
        }
        else {
            _cur = _cur->next;
            return true;
        }
    }
    Data getCurData() const {
        return _cur->data;
    }
    ~LinkedList() {
        for (; head != nullptr; pop_front());
    }
};
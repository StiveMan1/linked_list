#ifndef _s_list_h
#define _s_list_h

#include <iostream>
#include <cstring>

/**
Структура как элемент списка и хранения данных.
*/
template<class T>
struct node {
    T data;            // Данные
    node<T> *next;    // Адрес следующего элемента списка
    node() : next(nullptr) {}
};

/**
Реализация класса итератора для организации доступа
к элементам контейнера.
*/
template<class T>
class s_iterator {
    node<T> *ptr;
public:
    s_iterator() : ptr(nullptr) {}

    s_iterator(node<T> *ptr) : ptr(ptr) {}

    s_iterator &operator++() {
        ptr = ptr->next;
        return *this;
    }

    T &operator*() const { return ptr->data; }

    node<T> operator->() { return ptr; }

    bool operator!=(const s_iterator &obj) const { return ptr != obj.ptr; }

    ~s_iterator() { ptr = nullptr; }
};



/**
Описание класса списка.
*/
template<class T>
class s_list {
    node<T> *first;                                    // адрес первого элемента списка
    node<T> *last;                                    // адрес последнего элемента списка
    size_t _size;
public:
    friend class s_iterator<T>;                        // включение класса итератора
    s_list() {                                       // конструктор по умолчанию
        first = nullptr;
        last = nullptr;
        _size = 0;
    }

    s_list(const s_list<T> &obj) {                   // конструктор копирования
        this = obj;
    }

    s_list(s_list<T> &&obj) {                        // конструктор перемещения
        this = obj;
    }

    s_list<T> &operator=(const s_list<T> &obj);        // оператор равно копированием
    s_list<T> &operator=(s_list<T> &&obj);            // оператор равно перемещением
    T &operator[](size_t pos) const{
        node<T> *now = this->first;
        for (size_t i = 0; i < pos; i++)
            if(now != nullptr)
                now = now->next;
        return now->data;
    }                // оператор индексирования

    void add_to_head(const T &data) {               // добавление элемента в начало
        auto *new_elm = (node<T>*)malloc(sizeof(node<T>));
        new_elm->data = data;
        add_to_head(new_elm);
    }

    void add_to_tail(const T &data) {               // добавление элемента в конец
        auto *new_elm = (node<T>*)malloc(sizeof(node<T>));
        new_elm->data = data;
        add_to_tail(new_elm);
    }

    T front() const {
        return this->first->data;
    }                                // возвращает первое значение
    T back() const {
        return this->last->data;
    }                                    // возвращает последнее значение
    T delete_from_head() {
        if (_size == 0) return T();
        if (_size == 1){
            T res = this->first->data;
            delete_all();
            return res;
        }
        _size--;

        node<T> *del_elm = this->first;
        this->first = this->first->next;
        T res = del_elm->data;
        free(del_elm);
        return res;
    }                            // удаление первого элемента
    T delete_from_tail() {
        if (_size == 0) return T();
        if (_size == 1){
            T res = this->first->data;
            delete_all();
            return res;
        }
        _size--;

        node<T> *elm = this->first;
        for (size_t i = 0; i < _size-1; i++) elm = elm->next;
        node<T> *del_elm = this->last;
        this->last = elm;
        elm->next = nullptr;
        T res = del_elm->data;
        free(del_elm);
        return res;
    }                            // удаление последнего элемента
    void delete_all() {
        node<T> *now = this->first;
        node<T> *next;
        for (size_t i = 0; i < _size; i++) {
            next = now->next;
            free(now);
            now = next;
        }


        _size = 0;
        this->first = nullptr;
        this->last = nullptr;
    }                                // удаление всех элементов
    void show() const;                            // отображение всех элементов
    size_t size() const{
        return _size;
    }                            // количество элементов

    s_iterator<T> begin() const{
        return s_iterator<T>(first);
    }                    // возвращает итератор на первый элемент
    s_iterator<T> end() const{
        return s_iterator<T>(last->next);
    }                        // возвращает итератор на элемент, следующий за последним

    void insert_at(size_t pos, const T &data){
        auto *new_elm = (node<T> *)malloc(sizeof(node<T>));
        new_elm->data = data;
        if(pos == 0) return add_to_head(new_elm);
        node<T> *now = this->first;
        for (size_t i = 0; i < pos-1; i++)
            if(now != nullptr)
                now = now->next;
        if(now != nullptr) {
            new_elm->next = now->next;
            now->next = new_elm;
            _size++;
        }else return add_to_tail(new_elm);
    }        // вставка в указанную позицию
    void delete_at(size_t pos){
        if(pos == 0){
            delete_from_head();
            return;
        }
        if(pos == _size-1){
            delete_from_tail();
            return;
        }
        node<T> *now = this->first;
        for (size_t i = 0; i < pos-1; i++)
            if(now != nullptr)
                now = now->next;

        node<T> *elm = now->next;
        now->next = elm->next;
        free(elm);
    }                       // удаление по указанной позиции
    size_t find(const T &data) const{
        node<T> *now = this->first;
        for (size_t i = 0; i < _size; i++) {
            if(data == now->data){
                return i+1;
            }
            now = now->next;
        }
        return NULL;
    }                // поиск элемента (NULL в случае неудачи)
    size_t find_and_replace(const T &data, const T &repl_data){
        node<T> *now = this->first;
        size_t _s = 0;
        for (size_t i = 0; i < _size; i++) {
            if(data == now->data){
                _s ++;
                now->data = repl_data;
            }
            now = now->next;
        }
        return _s;
    }    // поиск и замена всех элементов (возвращаем кол-во замен)
    void reverse(){
        node<T> *now = this->first;
        node<T> *priv = nullptr;
        node<T> *next;
        for(size_t i=0; i <_size;i++){
            next = now->next;
            now->next = priv;
            priv = now;
            now = next;
        }
        printf("\n");
        this->first = (node<int>*)((unsigned long long)first ^ (unsigned long long)last);
        this->last = (node<int>*)((unsigned long long)first ^ (unsigned long long)last);
        this->first = (node<int>*)((unsigned long long)first ^ (unsigned long long)last);
    }                                    // переворот списка

    void sort();                                    // сортирует элементы (вставками)
    void splice(s_list<T> &obj);                    // перемещает элементы из другого list

    ~s_list(){
        this->delete_all();
    }                                        // деструктор
private:
    void add_to_head(node<T> *ptr){
        if (_size > 0) {
            ptr->next = this->first;
            this->first = ptr;
        } else {
            this->first = this->last = ptr;
        }
        _size++;
    }                    // добавляет ноду в голову списка
    void add_to_tail(node<T> *ptr){
        if (_size > 0) {
            this->last->next = ptr;
            this->last = ptr;
        } else {
            this->first = this->last = ptr;
        }
        _size++;
    }                    // добавляет ноду в конец списка
};

#endif
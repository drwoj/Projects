#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<memory>


using namespace std;

template<class T>
class List {

private:


    struct node {
        T data;
        shared_ptr<node> prev;
        shared_ptr<node> next;

    };

    shared_ptr<node> head;
    shared_ptr<node> tail;
    int counter;

    template<class C>
    auto Partition(shared_ptr<node> f, shared_ptr<node> l, bool up, C cmp);

    auto Partition(shared_ptr<node> f, shared_ptr<node> l, bool up);

    template<class C>
    void QuickSort(shared_ptr<node> f, shared_ptr<node> l, bool up, C cmp);

    void QuickSort(shared_ptr<node> f, shared_ptr<node> l, bool up);


    void swap(T& data1, T& data2);

public:
    List();

    ~List();

    List(const List<T>& new_list);

    List(List&& new_list)noexcept;

    List<T>& operator = (const List<T>& new_list);

    List<T>& operator = (List&& new_list);

    void Prepend(const T& new_data);

    void Append(const T& new_data);

    void Delete(int n);

    void Display();

    template<class C>
    void Sort(bool up, C cmp);
    
    void Sort(bool up);


    int Size();

    int Find(T key);

    void Write(string s);

    void Read(string s);

};

template<class T>
template<class C>
auto List<T>::Partition(shared_ptr<node> f, shared_ptr<node> l, bool up, C cmp) {

    T x = l->data; // pivot na koñcu
    shared_ptr<node> p = f->prev;

    if (up)
    {
        for (shared_ptr<node> q = f; q != l; q = q->next) {
            if (cmp(q->data, x)) {
                if (p == nullptr)  
                    p = f;
                else               
                    p = p->next;

                swap(p->data, q->data);

            }
        }


        if (p == nullptr)    
            p = f;
        else                 
            p = p->next;

        swap(p->data, l->data);
        return p;
    }

    for (shared_ptr<node> q = f; q != l; q = q->next) {
        if (!cmp(q->data, x)) {
            if (p == nullptr)  
                p = f;
            else               
                p = p->next;

            swap(p->data, q->data);

        }
    }


    if (p == nullptr)    
        p = f;
    else                 
        p = p->next;

    swap(p->data, l->data);
    return p;
}

template<class T>
auto List<T>::Partition(shared_ptr<node> f, shared_ptr<node> l, bool up) {

    T x = l->data; // pivot na koñcu
    shared_ptr<node> p = f->prev; //tymczasowy pivot

    if (up)
    {
        for (shared_ptr<node> q = f; q != l; q = q->next) {
            if (q->data < x) { // jesli obecny element jest mniejszy od pivotu
                if (p == nullptr) // sytuacja wyjatkowa
                    p = f;
                else               
                    p = p->next; // przesun tymczasowy pivot o jeden dalej

                swap(p->data, q->data); //zamien obecny element z tymczasowym pivotem

            }
        }


        if (p == nullptr)   // sytuacja wyjatkowa
            p = f;
        else                 
            p = p->next;    // ustaw pivot na dobra pozycja (pomiedzy mniejszymi a wiekszymi elementami)

        swap(p->data, l->data);
        return p;           // pivot index
    }

    for (shared_ptr<node> q = f; q != l; q = q->next) {
        if (q->data > x) {
            if (p == nullptr)  
                p = f;
            else               
                p = p->next;

            swap(p->data, q->data);

        }
    }


    if (p == nullptr)    
        p = f;
    else                 
        p = p->next;

    swap(p->data, l->data);
    return p;
}

template <class T>
template<class C>
void List<T>::QuickSort(shared_ptr<node> f, shared_ptr<node> l, bool up, C cmp) {
    if (l != nullptr && f != l && f != l->next) {

        shared_ptr<node> p = Partition(f, l, up, cmp); //Zwykly Quick Sort
        QuickSort(f, p->prev, up, cmp); // lewa strona pivotu
        QuickSort(p->next, l, up, cmp); // prawa strona pivotu


    }
}

template <class T>
void List<T>::QuickSort(shared_ptr<node> f, shared_ptr<node> l, bool up) {
    if (l != nullptr && f != l && f != l->next) {

        shared_ptr<node> p = Partition(f, l, up);
        QuickSort(f, p->prev, up);
        QuickSort(p->next, l, up);


    }
}

template<class T>
template<class C>
void List<T>::Sort(bool up, C cmp) { //funkcja pomocnicza - poniewaz QuickSort bedzie wywolywany rekurencyjnie
    QuickSort(head, tail, up, cmp); // Ta funkcja ogranicza wymagane argumenty (bez head i tail)
}

template<class T>
void List<T>::Sort(bool up) {
    QuickSort(head, tail, up);
}

template<class T>
void List<T>::swap(T& data1, T& data2) {

    T tmp = data1; //wystarczy zmienic tylko dane, wskazniki moga zostac
    data1 = data2;
    data2 = tmp;
}

template<class T>
List<T>::List() {
    head = nullptr;
    tail = nullptr;
    counter = 0;
    cout << "Konstruktor domyslny" << endl;
}

template<class T>
List<T>::~List() {
    cout << "Destruktor" << endl;
}

template<class T>
List<T>::List(const List<T>& new_list) {
    head = nullptr;;
    tail = nullptr;
    counter = 0;

    shared_ptr<node> tmp = make_shared<node>();
    tmp = new_list.head;

    while (tmp != nullptr) {
        Append(tmp->data);
        tmp = tmp->next;
    }
    cout << "Konstruktor kopiujacy" << endl;
}

template<class T>
List<T>::List(List&& new_list)noexcept {
    head = nullptr;
    tail = nullptr;
    counter = 0;
    std::swap(head, new_list.head);
    std::swap(tail, new_list.tail);
    std::swap(counter, new_list.counter);
    cout << "Konsturktor przenoszacy" << endl;
}

template<class T>
List<T>& List<T>:: operator = (const List<T>& new_list) {
    counter = 0;
    head = nullptr;
    tail = nullptr;

    shared_ptr<node> tmp = make_shared<node>();
    tmp = new_list.head;

    while (tmp != nullptr) {
        Append(tmp->data);
        tmp = tmp->next;
    }
    return *this;
}

template<class T>
List<T>& List<T>:: operator = (List&& new_list) {
    head = nullptr;
    tail = nullptr;
    counter = 0;
    std::swap(head, new_list.head);
    std::swap(tail, new_list.tail);
    std::swap(counter, new_list.counter);

    return *this;
}

template<class T>
void List<T>::Prepend(const T& new_data) {

    shared_ptr<node> new_node = make_shared<node>();

    new_node->data = new_data;
    new_node->prev = NULL;        //Element bedzie glowa wiec przed nim jest null
    new_node->next = head;        //laczymy pierwszy z drugim elementem

    if (head != nullptr)            // jesli lista nie jest pusta to dodajemy element przed obecna g³owê
        head->prev = new_node;
    else
        tail = new_node;            // jesli lista jest pusta to ogon = glowa

    head = new_node;                //przenosimy g³owê
    counter++;
}

template<class T>
void List<T>::Append(const T& new_data) {

    shared_ptr<node> new_node = make_shared<node>();

    new_node->data = new_data;
    new_node->prev = tail;
    new_node->next = NULL;

    if (tail != nullptr)
        tail->next = new_node;
    else
        head = new_node;

    tail = new_node;
    counter++;
}

template<class T>
void List<T>::Delete(int n) {

    if (n > counter - 1 || n < 0) { //jesli element ktory chcemy usunac nie znajduje sie w liscie (indeks)
        cout << "Podany element nie istnieje!" << endl;
        return;
    }

    if (n == 0) {
        head = head->next;
        head->prev = NULL;
        counter--;
        return;
    }

    if (n == counter - 1) {
        tail = tail->prev;
        tail->next = NULL;
        counter--;
        return;
    }

    shared_ptr<node> tmp = make_shared<node>();
    shared_ptr<node> tmp2 = make_shared<node>();

    if (n <= (counter / 2)) { // szukamy albo z przodu albo z tylu, zeby bylo szybciej
        tmp = head;

        for (int i = 0; i < n; i++)
            tmp = tmp->next;
    }

    else {
        tmp = tail;

        for (int i = counter; i > n+1; i--)
            tmp = tmp->prev;
    }


    tmp2 = tmp->prev; //laczymy poprzedni element z nastepnym (pomijamy obecny)
    tmp->prev->next = tmp->next; 
    tmp->next->prev = tmp2;
    counter--;
}

template<class T>
void List<T>::Display() {

    shared_ptr<node> tmp = head;;

    if (tmp != NULL) {
        while (tmp != NULL) {
            cout << tmp->data <<endl;
            tmp = tmp->next;
        }

        cout << endl;
    }
    else
        cout << "List is empty!" << endl;

}

void List<int>::Display() {
    shared_ptr<node> tmp = head;;

    if (tmp != NULL) {
        while (tmp != NULL) {
            cout << tmp->data << " ";
            tmp = tmp->next;
        }

        cout << endl;
    }
    else
        cout << "List is empty!" << endl;
}

void List<string>::Display() {
    shared_ptr<node> tmp = head;;

    if (tmp != NULL) {
        while (tmp != NULL) {
            cout << tmp->data << " ";
            tmp = tmp->next;
        }

        cout << endl;
    }
    else
        cout << "List is empty!" << endl;
}


template<class T>
int List<T>::Size() { 
    return counter; 
}

template<class T>
int List<T>::Find(T key) {

    shared_ptr<node> tmp = head;
    int i = 0;

    while (tmp != tail)
        if (tmp->data == key) //sprawdzamy czy dane zgadzaja sie z kluczem (potrzebne przeciazenie ==)
            return i;
        else {                // jesli sie nie zgadza to szukamy dalej
            i++;
            tmp = tmp->next;
        }


    cout << "Nie znaleziono szukanego elementu!" << endl;
    return -1; //zwracamy -1 informacyjnie poniewaz nie moze istniec taki indeks 

}

template<class T>
void List<T>::Write(string s) {
    ofstream file;
    file.open(s, ios::binary);

    shared_ptr<node> tmp = head;

    if (!file.good()) {
        cout << "Nie mozna Utworzyc pliku!";
        return;
    }

    while (tmp != nullptr) {
        file << tmp->data << endl;
        tmp = tmp->next;
    }

    file.close();

}

template<class T>
void List<T>::Read(string s) {
    ifstream file;
    file.open(s, ios::binary);

    if (!file.good()) {
        cout << "Nie mozna otworzyc pliku!";
        return;
    }

    T data;

    while(true){

        file >> data;

        if (file.eof()) //if musi byc przed Append, zeby nie dublowalo ostatniego elementu 
            break;

        Append(data); // dodajemy element do listy 

   
    }

    file.close();
}

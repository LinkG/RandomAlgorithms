#ifndef OHP
#define OHP

template <typename T>
class sortArray {
    struct node {
        T t;
        node* link;
    };
    node* top;
    bool (*comparer)(T, T);
    bool (*searcher) (T, T);
public:
    int len;
    sortArray(bool (*compPtr)(T, T), bool (*searchPtr)(T, T));    
    void insert(T);
    T* pop();
    bool find(T);
    bool find_check(T);
    ~sortArray();
};


//Pass the comparing function, followed by equality function
template <typename T>
sortArray<T>::sortArray(bool (*compPtr)(T, T), bool (*searchPtr)(T, T)) {
    top = nullptr;
    comparer = compPtr;
    searcher = searchPtr;
    len = 0;
}

template <typename T>
void sortArray<T>::insert(T t){
    len++;
    node *new_node = new node;
    new_node->t = t; 

    if(top == nullptr) {
        new_node->link = top;
        top = new_node;
        return;
    }

    node *comp = top;
    node *prev = nullptr;
    while(!comparer(new_node->t, comp->t)) {
        prev = comp;
        comp = comp->link;
        if(comp == nullptr) {
            break;
        }
    }
    if(prev == nullptr) {
        new_node->link = top;
        top = new_node;
    } else {
        prev->link = new_node;
        new_node->link = comp;
    }
}

template <typename T>
T* sortArray<T>::pop() {
    if(top != nullptr) {
        node *temp = top;
        T* return_val = new T(top->t);
        top = top->link;
        delete temp;
        len--;
        return return_val;        
    }
    return nullptr;
}

template <typename T>
bool sortArray<T>::find(T t1) {
    bool ret = false;
    node *cur = top;
    
    while(cur) {
        if(searcher(t1, cur->t)) {
            ret = true;
            break;
        }
        cur = cur->link;
    }

    return ret;
}

//returns true if a smaller one is found
template <typename T>
bool sortArray<T>::find_check(T t1) {
    node *cur = top;
    bool found = false;
    while(cur) {
        if(searcher(t1, cur->t)) {
            if(comparer(cur->t, t1)) {
                found = true;
                break;
            }
        }
        cur = cur->link;
    }
    return found;
}

template <typename T>
sortArray<T>::~sortArray() {
    node* current = top;
    while(current != nullptr) {
        top = top->link;
        delete current;
        current = top;
    }
}
#endif


namespace vlnk {

//Specific Node Constructor
template<typename Data>
List<Data>::Node::Node(const Data& val) {

    value=val;

}

//Copy Node Constructor
template<typename Data>
List<Data>::Node::Node(const Node& cpynode) {

    value = cpynode.value;
    nextptr = cpynode.nextptr;

}

//Move Node Constructor
template<typename Data>
List<Data>::Node::Node(Node&& mvnode) noexcept {

    std::swap(value, mvnode.value);
    std::swap(nextptr, mvnode.nextptr);

}

//Specific List Constructor
template<typename Data>
List<Data>::List(const LinearContainer<Data>& container) {

    for(ulong i=0;i<container.Size();++i) {

        InsertAtBack(container[i]);

    }

}

//List Copy Constructor
template<typename Data>
List<Data>::List(const List& list) {

    if(list.head==nullptr) return;

    Node* tmp = list.head;

    while(tmp!=nullptr) {

        InsertAtBack(tmp->value);
        tmp = tmp->nextptr;
        
    }

}

//List Move Constructor
template<typename Data>
List<Data>::List(List&& list) noexcept {

    std::swap(head, list.head);
    std::swap(tail, list.tail);
    std::swap(size, list.size);

}

//List Copy Assignment
template<typename Data>
List<Data>& List<Data>::operator=(const List<Data>& list) {

    List<Data>* tmplist = new List<Data>(list);
    std::swap(*tmplist, *this);
    delete tmplist;

    return *this;

}

//List Move Assigment
template<typename Data>
List<Data>& List<Data>::operator=(List<Data>&& list) noexcept {

    std::swap(head, list.head);
    std::swap(tail, list.tail);
    std::swap(size, list.size);

    return *this;

}

//List Clear
template<typename Data>
void List<Data>::Clear() {

    Node* tmp = head;

    while(head!=nullptr) {

        head = head->nextptr;
        delete tmp;
        tmp = head;

    }

    tail = nullptr;
    size = 0;

}

//List Destructor
template<typename Data>
List<Data>::~List() {

    Node* tmp = head;

    while(head!=nullptr) {

        head = head->nextptr;
        delete tmp;
        tmp = head;

    }

}

//Insert At Back Function
template<typename Data>
void List<Data>::InsertAtBack(const Data& data) {

    Node* tmp = new Node(data);

    if(head == nullptr) {

        head = tmp;
        tail = tmp;

    }else {

        tail->nextptr = tmp;
        tail = tmp;

    }

    ++size;

}

//Insert At Back Function
template<typename Data>
void List<Data>::InsertAtBack(Data&& data) noexcept {

    Node* tmp = new Node(std::move(data)) ;

    if(head == nullptr) {

        head = tmp;
        tail = tmp;

    }else {

        tail->nextptr = tmp;
        tail = tmp;

    }

    ++size;

}

//Insert At Front Function
template<typename Data>
void List<Data>::InsertAtFront(const Data& data) {

    Node* tmp = new Node(data);

    if(head == nullptr) {

        head = tmp;
        tail = tmp;

    } else {

        tmp->nextptr = head;
        head = tmp;

    }

    ++size;

}

//Insert At Front Function
template<typename Data>
void List<Data>::InsertAtFront(Data&& data) noexcept {

    Node* tmp = new Node(std::move(data));
    // std::swap(tmp->data, data);

    if(head == nullptr) {

        head = tmp;
        tail = tmp;

    } else {

        tmp->nextptr = head;
        head = tmp;

    }

    ++size;

}

//Remove From Front Function
template<typename Data>
void List<Data>::RemoveFromFront() {

    if(head!=nullptr) {

        Node* tmp=head;
        head=head->nextptr;
        
        delete tmp;

        size--;

    } else {

        throw std::length_error("Access to an empty list.");

    }


}

//Remove From Front Function 
template<typename Data>
Data List<Data>::FrontNRemove() {

    if(head!=nullptr) {

        Data value = head->value;
        RemoveFromFront();

        return value;

    } else {

        throw std::length_error("Access to an empty list.");

    }

}

//Front Function
template<typename Data>
Data& List<Data>::Front() const {

    if(head!=nullptr) {

        return head->value;

    } else {

        throw std::length_error("Access to an empty list.");

    }

}

//Back Function
template<typename Data>
Data& List<Data>::Back() const {

    if(head!=nullptr) {

        return tail->value;

    } else {

        throw std::length_error("Access to an empty list.");

    }

}

//List Comparison Operator==
template<typename Data>
bool List<Data>::operator==(const List<Data>& list) const noexcept {

    if(size!=list.size) return false;

    if(head==nullptr) return true;

    Node* ptr = head;
    Node* listptr = list.head;

    while(ptr!=nullptr) {

        if(ptr->value!=listptr->value) return false;

        ptr = ptr->nextptr;
        listptr = listptr->nextptr;

    }

    return true;


}

//List Comparison Operator!=
template<typename Data>
inline bool List<Data>::operator!=(const List<Data>& list) const noexcept {

    return !(*this==list);

}

//List Operator[]
template<typename Data>
Data& List<Data>::operator[](const ulong index) const {

    if(index<size) {

        Node* tmp = head;

        for(ulong i=0;i<index;i++) {

            tmp = tmp->nextptr;

        }

        return tmp->value;

    }else {

        throw std::out_of_range("Access at index " + std::to_string(index) + "; list size " + std::to_string(size) + ".");

    }

}

//MapPreOrder Function
template<typename Data>
void List<Data>::MapPreOrder(const MapFunctor fun, void* par) {

    for(ulong i=0;i<size;++i) {

        fun((*this)[i], par);

    }

}

//MapPostOrder Function
template<typename Data>
void List<Data>::MapPostOrder(const MapFunctor fun, void* par) {

        ulong i = size;
        while(i>0) {

            fun((*this)[--i], par);

        }

}

//FoldPreOrder Function
template<typename Data>
void List<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const {

    for(ulong i=0;i<size;++i) {

        fun((*this)[i], par, acc);

    }

}

//FoldPostOrder Function
template<typename Data>
void List<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const {

        ulong i = size;
        while(i>0) {

            fun((*this)[--i], par, acc);

        }
        

}

}

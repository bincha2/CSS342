/*
David Kim - Dimpsey 342 Spring - List342
*/

#ifndef LIST342_H_
#define LIST342_H_
#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>
using namespace std;

template <class T>
struct Node
{
    T *data;
    Node *next;
};

template <class T>
class List342
{
public:
    // constructors
    List342();
    List342(const List342 &list);
    ~List342();

    // actions
    bool BuildList(string file_name);
    bool Insert(T *obj);
    bool Remove(T target, T &result);
    bool Peek(T target, T &result) const;
    int Size() const;
    void DeleteList();
    bool Merge(List342 &list1);

    // overloads
    List342 operator+(const List342 &list) const;
    List342 &operator+=(const List342 &list);
    List342 &operator=(const List342 &list);

    bool operator==(const List342 &list) const;
    bool operator!=(const List342 &list) const;

    friend ostream &operator<<(ostream &stream, const List342<T> &list)
    {
        Node<T> *current = list.head_;
        while (current != nullptr)
        {
            stream << *(current->data);
            current = current->next;
        }
        return stream;
    }

private:
    int size_;
    Node<T> *head_ = nullptr;
};

template <class T>
List342<T>::List342()
{
}

template <class T>
List342<T>::List342(const List342 &list)
{
    head_ = nullptr;
    *this = list;
}

template <class T>
List342<T>::~List342()
{
    DeleteList();
}

template <class T>
bool List342<T>::BuildList(string file_name)
{
    ifstream file(file_name);

    while (!file.eof())
    {
        T *object = new T();
        file >> *object;
        Insert(object);
        delete object;
    }
    file.close();
    return true;
}

template <class T>
bool List342<T>::Insert(T *obj)
{
    if (obj == nullptr)
    {
        return false;
    }

    Node<T> *new_node = new Node<T>();
    T *object = new T(*obj);
    new_node->data = object;

    // if list is empty or new_node is the smallest, make new_node the head
    if (head_ == nullptr || (*obj < *(head_->data)))
    {
        new_node->next = head_;
        head_ = new_node;
        return true;
    }

    if (*obj == *(head_->data))
    {
        delete new_node;
        delete object;
        return false;
    }

    Node<T> *current = head_;
    // end loop when correct position for insertion is found
    while (current->next != nullptr && *obj > *(current->next->data))
    {
        current = current->next;
    }
    // make sure a duplicate is not being added
    if (current->next == nullptr || *obj != *(current->next->data))
    {
        new_node->next = current->next;
        current->next = new_node;
        return true;
    }
    delete new_node;
    delete object;
    return false;
}

template <class T>
bool List342<T>::Remove(T target, T &result)
{
    // If the list is empty
    if (head_ == nullptr)
        return false;

    // If the target is at the head of the list
    if (*(head_->data) == target)
    {
        Node<T> *current = head_;
        head_ = head_->next;
        result = *(current->data);
        delete current->data;
        delete current;
        return true;
    }

    // Search for the target node
    Node<T> *current = head_;
    Node<T> *prev = nullptr;

    while (current != nullptr && *(current->data) != target)
    {
        prev = current;
        current = current->next;
    }

    // If the target item was not found and reach end list
    if (current == nullptr)
    {
        return false;
    }
    else
    {
        // Found the target item, remove it
        prev->next = current->next;
        result = *(current->data);
        delete current->data;
        delete current;
        return true;
    }
}

template <class T>
bool List342<T>::Peek(T target, T &result) const
{
    // If the list is empty
    if (head_ == nullptr)
        return false;

    // Search for the target node
    Node<T> *current = head_;

    while (current != nullptr && *(current->data) < target)
    {
        current = current->next;
    }

    if (current == nullptr)
    {
        return false;
    }
    if (*(current->data) > target)
    {
        return false;
    }
    if (*(current->data) == target)
    {
        result = *(current->data);
        return true;
    }

    return false; // Target not found
}

template <class T>
int List342<T>::Size() const
{
    int count = 0;
    Node<T> *current = head_;
    while (current != nullptr)
    {
        count++;
        current = current->next;
    }
    return count;
}

template <class T>
void List342<T>::DeleteList()
{
    while (head_ != nullptr)
    {
        Node<T> *current = head_;
        head_ = head_->next;
        delete current->data;
        delete current;
    }
}

template <class T>
bool List342<T>::Merge(List342 &list1)
{
    if (list1.head_ == nullptr) // If list1 is empty, nothing to merge
        return false;

    if (head_ == nullptr)
    { // If the calling list is empty, simply take ownership of list1
        head_ = list1.head_;
        list1.head_ = nullptr;
        return false;
    }

    if (&list1 == this) // Prevent self-merge
        return false;

    Node<T> *current = head_;
    Node<T> *list1_ptr = list1.head_;

    while (list1_ptr != nullptr)
    {
        // Check for duplicates in the calling list
        bool duplicate = false;
        Node<T> *ptr_node = head_;
        while (ptr_node != nullptr)
        {
            if (*(ptr_node->data) == *(list1_ptr->data))
            {
                duplicate = true;
                break;
            }
            ptr_node = ptr_node->next;
        }

        if (duplicate)
        {
            // Skip duplicate
            Node<T> *temp = list1_ptr;
            list1_ptr = list1_ptr->next;
            delete temp->data;
            delete temp;
            continue;
        }

        // Find correct position to insert
        Node<T> *prev = nullptr;
        while (current != nullptr && *(current->data) < *(list1_ptr->data))
        {
            prev = current;
            current = current->next;
        }

        // Insert at correct position
        Node<T> *insert_node = new Node<T>;
        insert_node->data = new T(*(list1_ptr->data));
        if (prev == nullptr)
        {
            insert_node->next = head_;
            head_ = insert_node;
        }
        else
        {
            insert_node->next = current;
            prev->next = insert_node;
        }

        // Move to the next node in list1
        Node<T> *temp = list1_ptr;
        list1_ptr = list1_ptr->next;

        // Delete node from list1
        delete temp;
    }

    list1.head_ = nullptr; // Empty list1
    return true;
}

template <class T>
List342<T> List342<T>::operator+(const List342 &list) const
{
    List342<T> result;
    Node<T> *current1 = head_;
    Node<T> *current2 = list.head_;
    Node<T> *track_tail = nullptr;

    // Merge two sorted lists into a new sorted list
    while (current1 != nullptr && current2 != nullptr)
    {
        if (*(current1->data) < *(current2->data))
        {
            if (result.head_ == nullptr)
            {
                result.head_ = current1;
            }
            else
            {
                track_tail->next = current1;
            }
            track_tail = current1;
            current1 = current1->next;
        }
        else if (*(current1->data) > *(current2->data))
        {
            if (result.head_ == nullptr)
            {
                result.head_ = current2;
            }
            else
            {
                track_tail->next = current2;
            }
            track_tail = current2;
            current2 = current2->next;
        }
        else
        {
            // duplicates are not allowed, skip duplicate elements
            current1 = current1->next;
            current2 = current2->next;
        }
    }

    // Add remaining elements from the first list
    if (current1 != nullptr)
    {
        if (result.head_ == nullptr)
        {
            result.head_ = current1;
        }
        else
        {
            track_tail->next = current1;
        }
        while (current1->next != nullptr)
        {
            current1 = current1->next;
        }
        track_tail = current1;
    }

    // Add remaining elements from the second list
    if (current2 != nullptr)
    {
        if (result.head_ == nullptr)
        {
            result.head_ = current2;
        }
        else
        {
            track_tail->next = current2;
        }
        while (current2->next != nullptr)
        {
            current2 = current2->next;
        }
        track_tail = current2;
    }

    return result;
}

template <class T>
List342<T> &List342<T>::operator+=(const List342 &list)
{
    Node<T> *current = list.head_;

    // Insert elements from the second list into the calling list
    while (current != nullptr)
    {
        this->Insert(current->data);
        current = current->next;
    }

    return *this;
}

template <class T>
bool List342<T>::operator==(const List342 &list) const
{
    if (this->Size() != list.Size())
        return false;

    Node<T> *current1 = this->head_;
    Node<T> *current2 = list.head_;

    // Check if each corresponding element is equal
    while (current1 != nullptr && current2 != nullptr)
    {
        if (*(current1->data) != *(current2->data))
            return false;
        current1 = current1->next;
        current2 = current2->next;
    }

    return true;
}

template <class T>
bool List342<T>::operator!=(const List342 &list) const
{
    return !(*this == list);
}

template <class T>
List342<T> &List342<T>::operator=(const List342 &source)
{
    Node<T> *source_node;      // source Node
    Node<T> *destination_node; // destination Node

    // Check to see if assigning to ourselves and return if so
    if (this == &source)
    {
        return *this;
    }

    // Empty destination stack of elements
    this->DeleteList();

    // If souce stack is empty return
    if (source.head_ == nullptr)
    {
        return *this;
    }

    // copy over first node
    destination_node = new Node<T>;
    destination_node->data = new T(*(source.head_)->data);
    head_ = destination_node;
    source_node = (source.head_)->next;

    // loop and copy over all other nodes
    while (source_node != nullptr)
    {
        destination_node->next = new Node<T>;
        destination_node = destination_node->next;
        destination_node->data = new T(*(source_node->data));
        source_node = source_node->next;
    }
    return *this;
}

#endif
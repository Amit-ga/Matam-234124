#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cassert>
#include "node.h"

namespace mtm
{
    /** Generic class for defining a linked list */
    template <class T>
    class List
    {
        Node<T>* list_head;
        int list_size;

    public:
        /*constructor- builds an empty list*/
        List();
        /*copy constructor*/
        List(const List<T>& list);
        /*destructor*/
        ~List();
        /*assignment operator*/
        List& operator=(const List& orig_list);

        /**
        * addNode: adds a new node to the list.
        *
        * @param value -new node's value.
        */
        void addNode(const T value);

        /**
        * getHead: returns list's head data member
        *
        */
        Node<T>* getHead() const;

        void setHead(Node<T>* head);

        /**
        * getSize: returns list's size data member
        *
        */
        int getSize() const;

        /**
        * contains: returns whether a node with a certin value exists in the list.
        *
        * @param value - Target value.
        * @return
        * 	true - if the value was found in the list.
        * 	false -otherwise
        */
        bool contains(T value);

        /**
        * deleteNode: Removes a node from the list.
        *   If there are multiple nodes with the same value the first one will be removed.
        *
        * @param value - Target value to be removed from the list.
        * @return
        * 	true if node was successfully removed .
        * 	false if the value was not in the list
        */
        bool deleteNode(T value);

        //operator [] - returns the value of the node in mt_index
        T operator[](int my_index);

        /**
        * getLastValue: returns the value of the last node
        * @return
        * 	the value of the last node of a given list
        */
        T getLastValue() const;

        /**
        * swap: swaps a node with its next node
        *
        * @param to_swap - pointer to the target node that needs to be swaped with its next node
        *
        */
        void swap(mtm::Node<T>* to_swap);
    };

    /*constructor*/
    template<class T>
    List<T>::List():
        list_head(nullptr),
        list_size(0)
    {
    }

    template<class T>
    List<T>::List(const List<T>& list)
    {
        Node<T>* current_node = nullptr;//current
        Node<T>* next_node = nullptr;//next
        this->list_size = list.getSize();
        if (!(list.getHead()))
        {
            this->list_head = nullptr;
        }
        else
        {
            this->list_head = new Node<T>;
            this->list_head->setNext(list.getHead()->next());
            this->list_head->setValue(list.getHead()->value());
            current_node = this->list_head;
            next_node = list.getHead()->next();
            while (next_node)
            {
                current_node->setNext(new Node<T>());
                current_node = current_node->next();
                current_node->setNext(next_node->next());
                current_node->setValue(next_node->value());
                next_node = next_node->next();
            }
            current_node->setNext(nullptr);
        }
    }

    template <class T>
    mtm::List<T>& mtm::List<T>::operator=(const List<T>& orig_list)
    {
        if (this == &orig_list || this->list_head == nullptr)
        {
            return *this;
        }
        mtm::Node<T>* temp = this->list_head;

        while (temp != nullptr)
        {
            this->list_head = this->list_head->next();
            delete temp;
            temp = this->list_head;
        }
        this->list_size = 0;
        temp = orig_list.list_head;
        while (temp != nullptr)
        {
            this->addNode(temp->value());
            temp = temp->next();
        }
        return *this;
    }

    template <class T>
    Node<T>* List<T>::getHead() const
    {
        return this->list_head;
    }

    template <class T>
    void mtm::List<T>::setHead(mtm::Node<T>* node)
    {
        this->list_head = node;
    }

    template <class T>
    int List<T>::getSize() const
    {
        return this->list_size;
    }

    template <class T>
    void List<T>::addNode(const T value)
    {
        Node<T>* to_add = new Node<T>(value);

        if (this->list_head == nullptr)
        {
            // The list is empty
            this->list_head = to_add;
        }
        else {
            mtm::Node<T>* temp = this->list_head;
            // The list isn't empty
            while (temp->next() != nullptr)
            {
                temp = temp->next();
            }
            temp->setNext(to_add);
        }
        this->list_size++;
    }

    template <class T>
    mtm::List<T>::~List()
    {
        if(!(this->getSize()==0))
        {
            mtm::Node<T>* head = this->list_head;
            while (head != nullptr)
            {
                mtm::Node<T>* to_delete = head;
                head = head->next();
                delete to_delete;
            }
        }
    }

    template <class T>
    bool List<T>::contains(T value)
    {
        mtm::Node<T>* head = this->list_head;
        while (head != nullptr)
        {
            if (head->value() == value)
            {
                return true;
            }

            head = head->next();
        }
        return false;
    }

    template <class T>
    bool List<T>::deleteNode(T value)
    {
        if (!(contains(value)))
        {
            //no such object, we return false because we failed to delete
            return false;
        }

        Node<T>* to_delete = this->list_head;
        Node<T>* prev = nullptr;
        while (to_delete != nullptr)
        {
            if (to_delete->value() == value)
            {
                break;
            }
            prev = to_delete;
            to_delete = to_delete->next();
        }
        if (prev == nullptr)
        {
            this->list_head = this->list_head->next();
        }
        else
        {
            prev->setNext(prev->next()->next());
        }

        delete to_delete;
        this->list_size--;

        if (list_size == 0)
        {
            this->list_head = nullptr;
        }

        return true;
    }


    template <class T>
    T mtm::List<T>::operator[](int my_index)
    {
        if (my_index == 0) {
            // Get the first element
            return this->getHead()->value();

        }
        else {
            Node<T>* temp = this->getHead();
            for (int i = 0; i < my_index; ++i) {
                temp = temp->next();
            }
            return temp->value();
        }
    }

    template <class T>
    T mtm::List<T>::getLastValue() const
    {
        assert(this->getHead() != nullptr);

        Node<T>* tmp = this->getHead();
        while (tmp->next())
        {
            tmp = tmp->next();
        }
        return tmp->value();
    }

    template <class T>
    void mtm::List<T>::swap(mtm::Node<T>* to_swap)
    {

        mtm::Node<T>* prev = this->getHead();

        if (prev == to_swap)
        {
            prev = to_swap->next()->next();
            to_swap->next()->setNext(to_swap);
            this->setHead(to_swap->next());
            to_swap->setNext(prev);
        }

        else
        {
            while (prev)
            {
                if (prev->next() == to_swap)
                {
                    prev->setNext(to_swap->next());
                    to_swap->setNext(to_swap->next()->next());
                    prev->next()->setNext(to_swap);
                    break;
                }

                prev = prev->next();
            }
        }
    }
}

#endif //LIST_H

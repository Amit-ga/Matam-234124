#ifndef Node_H
#define Node_H

#include <iostream>

namespace mtm
{
    /** Generic class for defining a Node */
    template <class T>
    class Node
    {
        T node_value;
        Node<T>* node_next;

    public:
        /* constructor - builds a new node
        * node will be with a difault value and a Null next node by default
        */
        explicit Node(T value = T(), Node<T>* next = nullptr);

        /*copy constructor*/
        Node(const Node& node);
        
        /*assignment operator*/
        Node& operator=(const Node& node)=delete;

        /* destructor*/
        ~Node() = default;

        /**
        * value: returns node's value data member
        *
        */
        T value() const;

        /**
        * value: returns node's next data member
        *
        */
        Node<T>* next() const;
        
        /**
        * setNext: set node's next node
        *
        *@param node - Target node
        */
        void setNext(Node<T>* node);
        
        /**
        * setValue: set node's value
        *
        *@param value - Target value
        */
        void setValue(const T& value);

    };

    template<class T>
    Node<T>::Node(T value, Node<T>* next):
        node_value(value),
        node_next(next)
    {
    }

    template <class T>
    Node<T>::Node(const Node& node) :
        node_value(node.node_value),
        node_next(nullptr)
    {
    }

    template <class T>
    T Node<T>::value() const
    {
        return this->node_value;
    }

    template <class T>
    Node<T>* Node<T>::next() const
    {
        return this->node_next;
    }

    template <class T>
    void mtm::Node<T>::setNext(Node<T>* node)
    {
       this->node_next = node;
    }

    template <class T>
    void mtm::Node<T>::setValue(const T& value)
    {
        this->node_value = value;
    }
}


#endif //Node_H

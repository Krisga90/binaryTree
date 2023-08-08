
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <algorithm>
#include <iostream>
#include <vector>

// #define PRINT_DEBUG
#define VAL int

class Node
{
public:
    Node(VAL value): m_data{value}, m_lower{nullptr}, m_higher{nullptr} 
    {
        #ifdef PRINT_DEBUG
        std::cout << "Node::Node(VAL value)" << std::endl;
        #endif //PRINT_DEBUG
    };

    Node() = delete;
    Node(const Node& ) = delete;
    Node(Node&&) = delete;
    Node& operator=(const Node&) = delete;
    Node& operator=(Node&&) = delete;


    ~Node()
    {
        #ifdef PRINT_DEBUG
        std::cout << "Node::~Node()" << std::endl;
        #endif //PRINT_DEBUG
        if (m_lower)
        {
            delete m_lower;
            m_lower = nullptr;
        }
        if(m_higher)
        {
            delete m_higher;
            m_higher =  nullptr;
        }
    }

    inline const bool operator<(const Node& other)const {return m_data < other.m_data;}
    inline const bool operator<(const Node* other)const {return this->operator<(*other);}
    inline const bool operator>(const Node& other)const {return other < *this;}
    inline const bool operator>(const Node* other)const {return other->operator<(this);}

    inline const bool operator<(const VAL& other)const {return m_data < other;}
    inline const bool operator<(const VAL* other)const {return this->operator<(*other);}
    inline const bool operator>(const VAL& other)const {return m_data > other;}
    inline const bool operator>(const VAL* other)const {return this->operator>(*other);}

    
    Node* m_lower;
    Node* m_higher;
    VAL m_data;
private:
};

class BinaryTree
{
public:
    BinaryTree();
    BinaryTree(VAL value);
    BinaryTree(std::initializer_list<VAL> elements);
    BinaryTree(BinaryTree&& other);
    BinaryTree(const BinaryTree& other);
    BinaryTree& operator=(const BinaryTree& other);
    BinaryTree& operator=(BinaryTree&& other);

    /**
     * @brief add value to binary tree
     * 
     * @param value argument to add to tree
     * @return true when value has not been in tree
     * @return false when value has been in tree
     */
    bool addElement(VAL value);

    /**
     * @brief remove element from binary tree
     * 
     * @param value argument to remove
     * @return true when value is removed
     * @return false when value is not removed
     */
    bool removeElement(VAL value);

    /**
     * @brief 
     * 
     * @param value argument to search
     * @return true if value is in binary tree
     * @return false if value is not in binary tree
     */
    bool elementExists(VAL value);

private:
    bool addNode(Node*& parent, Node *new_node);
    void copyTree(Node* current_trunk, Node *copy_trunk);
    Node* findNode(Node* parent, const VAL& value)const;
    bool removeNode(Node*& parent, const VAL& value);
    Node* findMinNode(Node* parent);
/**
 * @brief return median value from initializer_list
 * 
 * @param elements 
 * @return VAL 
 */
    VAL median(std::initializer_list<VAL>& elements);

    bool pushToTree(Node*& current_node, VAL & value);

public:
    Node* m_trunk;
};

BinaryTree::BinaryTree(): m_trunk{nullptr}
{
    #ifdef PRINT_DEBUG
        std::cout << "BinaryTree::BinaryTree()" << std::endl;
    #endif //PRINT_DEBUG
}

BinaryTree::BinaryTree(VAL value)
{
    #ifdef PRINT_DEBUG
        std::cout << "BinaryTree::BinaryTree(VAL value)" << std::endl;
    #endif //PRINT_DEBUG
    m_trunk = new Node(value);
}

BinaryTree::BinaryTree(std::initializer_list<VAL> elements)
{
    #ifdef PRINT_DEBUG
        std::cout << "BinaryTree::BinaryTree(std::initializer_list<VAL> elements)" << std::endl;
    #endif //PRINT_DEBUG
    auto trunk_value = median(elements);
    m_trunk = new Node(trunk_value);
    for(auto value: elements)
    {
        Node * new_node = new Node(value);
        addNode(m_trunk, new_node);
    }
}

BinaryTree::BinaryTree(BinaryTree&& other)
{
    #ifdef PRINT_DEBUG
        std::cout << "BinaryTree::BinaryTree(BinaryTree&& other)" << std::endl;
    #endif //PRINT_DEBUG
    operator=(std::move(other));
}

BinaryTree::BinaryTree(const BinaryTree& other): m_trunk{nullptr}
{
    #ifdef PRINT_DEBUG
        std::cout << "BinaryTree::BinaryTree(const BinaryTree& other): BinaryTree()" << std::endl;
    #endif //PRINT_DEBUG
    if (other.m_trunk)
    {
        operator=(other);
        
    }
}

BinaryTree& BinaryTree::operator=(const BinaryTree& other)
{
    #ifdef PRINT_DEBUG
        std::cout << "BinaryTree& BinaryTree::operator=(const BinaryTree& other)" << std::endl;
    #endif //PRINT_DEBUG
    if (this != &other)
    {
        delete m_trunk;
        copyTree(m_trunk, other.m_trunk);
    }
    return *this;
}

BinaryTree& BinaryTree::operator=(BinaryTree&& other)
{
    #ifdef PRINT_DEBUG
        std::cout << "BinaryTree& BinaryTree::operator=(BinaryTree&& other)" << std::endl;
    #endif //PRINT_DEBUG
    if (this != &other)
    {
        delete m_trunk;
        m_trunk = other.m_trunk;
        other.m_trunk =  nullptr;
    }
    return *this;
}

    bool BinaryTree::addNode(Node*& parent, Node *new_node)
    {
        #ifdef PRINT_DEBUG
        std::cout << "bool BinaryTree::addNode(Node* parent, Node *new_node)" << std::endl;
        #endif //PRINT_DEBUG
        if(!parent)
        {
            parent = new_node;
            #ifdef PRINT_DEBUG
            std::cout << new_node->m_data << std::endl;
            #endif //PRINT_DEBUG
            return true;
        }
        if (*parent > new_node)
        {
            return addNode(parent->m_lower, new_node);
        }
        else if(*parent < new_node)
        {
            return addNode(parent->m_higher, new_node);
        }
        return false;
    }

    bool BinaryTree::addElement(VAL value)
    {
            #ifdef PRINT_DEBUG
        std::cout << "bool BinaryTree::addElement(VAL value)" << std::endl;
    #endif //PRINT_DEBUG
        return pushToTree(m_trunk, value);
    }

    bool BinaryTree::removeElement(VAL value)
    {
            #ifdef PRINT_DEBUG
        std::cout << "bool BinaryTree::removeElement(VAL value)" << std::endl;
    #endif //PRINT_DEBUG
        return removeNode(m_trunk, value);
    }

    bool BinaryTree::elementExists(VAL value)
    {
        #ifdef PRINT_DEBUG
        std::cout << "bool BinaryTree::elementExists(VAL value)" << std::endl;
        #endif //PRINT_DEBUG
        return findNode(m_trunk, value) != nullptr;
    }

    void BinaryTree::copyTree(Node* current_trunk, Node *copy_trunk)
    {
            #ifdef PRINT_DEBUG
        std::cout << "void BinaryTree::copyTree(Node* current_trunk, Node *copy_trunk)" << std::endl;
    #endif //PRINT_DEBUG
        if(copy_trunk)
        {
            current_trunk = new Node(copy_trunk->m_data);
            copyTree(current_trunk->m_lower, copy_trunk->m_lower);
            copyTree(current_trunk->m_higher, copy_trunk->m_higher);
        }
    }

    VAL BinaryTree::median(std::initializer_list<VAL>& elements)
    {
        #ifdef PRINT_DEBUG
        std::cout << "VAL BinaryTree::median(std::initializer_list<VAL>& elements)" << std::endl;
        #endif //PRINT_DEBUG
        std::vector<VAL> values(elements.begin(), elements.end());
        std::sort(values.begin(), values.end());
        return *(values.begin() + values.size()/2); 
    }

    bool BinaryTree::pushToTree(Node*& current_node, VAL & value)
    {
        #ifdef PRINT_DEBUG
        std::cout << "void BinaryTree::pushToTree(Node* current_node, VAL & value)" << std::endl;
        #endif //PRINT_DEBUG

        if(!current_node)
        {
            current_node = new Node(value);
            return true;
        }
        if(*current_node > value)
        {
            return pushToTree(current_node->m_lower, value);
        }
        else if(*current_node < value)
        {
            return pushToTree(current_node->m_higher, value);
        }
        return false;
    }

    Node* BinaryTree::findMinNode(Node* parent)
    {
            #ifdef PRINT_DEBUG
        std::cout << "Node* BinaryTree::findMinNode(Node* parent)" << std::endl;
    #endif //PRINT_DEBUG
        if(!parent)
        {
            return nullptr;
        }
        while(parent->m_lower)
        {
            parent= parent->m_lower;
        }
        return parent;
    }

    Node* BinaryTree::findNode(Node* parent, const VAL& value)const
    {
            #ifdef PRINT_DEBUG
        std::cout << "Node* BinaryTree::findNode(Node* parent, const VAL& value)const" << std::endl;
    #endif //PRINT_DEBUG
        if(!parent)
        {
            return nullptr;
        }

        if(*parent < value)
        {
            return findNode(parent->m_higher, value);
        }
        else if(*parent > value)
        {
            return findNode(parent->m_lower, value);
        }
        return parent;
    }

    bool BinaryTree::removeNode(Node*& parent, const VAL& value)
    {
        #ifdef PRINT_DEBUG
        std::cout << "bool BinaryTree::removeNode(Node*& parent, const VAL& value)" << std::endl;
        #endif //PRINT_DEBUG
        if(!parent)
        {
            return false;
        }

        if(*parent < value)
        {
            return removeNode(parent->m_higher, value);
        }
        if (*parent > value)
        {
            return removeNode(parent->m_lower, value);
        }

        if (!parent->m_lower)
        {
            auto temp = parent;
            parent = temp->m_higher;
            temp->m_higher =  nullptr;
            delete temp;
            return true;
        }
        else if (!parent->m_higher)
        {
            auto temp = parent;
            parent = temp->m_lower;
            temp->m_lower =  nullptr;
            delete temp;
            return true;
        }
        else
        {
            auto temp = parent->m_lower;
            auto successor = findMinNode(parent->m_higher);
            parent->m_data = successor->m_data;
            removeNode(parent->m_higher, successor->m_data);
            return true;
        }
    return false;
    }

    



#endif //BINARY_TREE_H
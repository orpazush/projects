//
// Created by orpaz on 24/12/2020.
//


template <typename T>
class BST
{
public:
    enum child_t
    {
        LEFT,
        RIGHT,
        NUM_OF_CHILDREN
    };

    struct Node
    {
        T data;
        Node child[2];
    };

    BST();
    ~BST();

    void Insert(T newData);
    void Remove(Node *toRemove);
    void Find(T toFind);

private:
    Node m_root;
};

template<typename T>
void BST<T>::Insert(T newData)
{

}



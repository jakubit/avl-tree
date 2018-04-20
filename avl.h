#ifndef AVL_H
#define AVL_H

#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
#include <vector>

#include"matrix.h"



///Klasa wezla
template <class T>
class avlNode
{
    public:
    T data;
    avlNode<T> *left;
    avlNode<T> *right;
    avlNode(T key): data(key), left(NULL), right(NULL) {}
};

///Klasa drzewa
template <class T>
class avlTree
{
    private:
        avlNode<T> *RR_rotation(avlNode<T> *);
        avlNode<T> *LL_rotation(avlNode<T> *);
        avlNode<T> *LR_rotation(avlNode<T> *);
        avlNode<T> *RL_rotation(avlNode<T> *);
        avlNode<T> *balance(avlNode<T> *);
        avlNode<T> *root;

    public:

        avlTree(const avlTree &);                ///konstruktor kopiujacy
        avlTree& operator=(avlTree&);            ///operator przypisania

        std::vector<T> valuesInOrder;            ///wektor z wartosciami drzewa, ustawionymi w kolejnosci dodawnia ich do drzewa - potrzebne do kopiowania obiektu

        int height(avlNode<T> *);                ///zwarca wysokosc drzewa
        int height();

        int balanceFactor(avlNode<T> *);         ///zwraca wspolczynnik wywazenia

        avlNode<T> *insert_(avlNode<T> *, T );   ///wstawianie elementu
        int insertValue(T);

        avlNode<T> *remove_(avlNode<T> *, T );   ///usuwanie wezla z zadanym kluczem
        int removeValue(T);

        void display(avlNode<T> *, int);         ///wyswietlanie drzewa
        void display();

        avlNode<T> *findMin(avlNode<T> *);       ///zwraca wezlem z najmniejsza wartoscia
        avlNode<T> *extractMin(avlNode<T> *);    ///pomocnicza do usuwania

        int checkValue(avlNode<T> *, T);         ///sprawdza czy wartosc nalezy do drzewa
        int checkValue(T);

        T getValue(avlNode<T> *, T);             ///pobiera zadana wartosc z drzewa
        T getValue(T);

        avlTree<T> operator+(const avlTree &);   ///laczenie drzew

        avlTree<T> operator-(const avlTree &);   ///Odejmowanie drzew


        ///porownywanie drzew
        bool treeCmp(avlTree<T> &);
        int operator==(avlTree&);
        int operator!=(avlTree&);

        avlTree(): root(NULL) {}

};



/**< ++++++++ METODY ++++++++++++++*/


///Konstruktor kopiujacy
template <class T>
avlTree<T>::avlTree(const avlTree & cop): root(NULL)
{
    for(int i=0; i<cop.valuesInOrder.size(); i++)
        this->insertValue(cop.valuesInOrder[i]);
}


///Operator +
template <class T>
avlTree<T> avlTree<T>::operator+(const avlTree &element)
{
    avlTree<T> temp(*this);
    for(int i=0; i<element.valuesInOrder.size(); i++)
        temp.insertValue(element.valuesInOrder[i]);

    return temp;

}

///Operator -
template <class T>
avlTree<T> avlTree<T>::operator-(const avlTree &element)
{
    avlTree<T> temp(*this);
    for(int i=0; i<element.valuesInOrder.size(); i++)
        temp.removeValue(element.valuesInOrder[i]);

    return temp;

}

///Operator =
template <class T>
avlTree<T>& avlTree<T>::operator=(avlTree & cop)
{
    for(int i=0; i<cop.valuesInOrder.size(); i++)
        this->insertValue(cop.valuesInOrder[i]);

    return this;
}


///Porownanie drzew
template <class T>
bool avlTree<T>::treeCmp(avlTree<T> &other)
{
    int control_sum=0;

    for(int i=0; i<this->valuesInOrder.size(); i++)
        for(int j=0; j<other.valuesInOrder.size(); j++)
            if( this->valuesInOrder[i] == other.valuesInOrder[j] ) control_sum++;

    if( control_sum == valuesInOrder.size() ) return 1;
    else return 0;

}

///Operator porownaia ==
template <class T>
int avlTree<T>::operator==(avlTree<T> &temp)
{
    if( (this->valuesInOrder.size()) != (temp.valuesInOrder.size()) ) return 0;

    return treeCmp(temp);
}

///Operator porownaia !=
template <class T>
int avlTree<T>::operator!=(avlTree<T> &temp)
{
    if( (this->valuesInOrder.size()) != (temp.valuesInOrder.size()) ) return 1;

    return treeCmp(temp);
}

///
template <class T>
int avlTree<T>::checkValue(avlNode<T> *temp, T value)
{
    while (temp)
    {
        if(temp->data == value)
            return 1;
        else if(value > temp->data)
                temp = temp->right;
             else
                temp = temp->left;

    }

    return 0;
}

///
template <class T>
int avlTree<T>::checkValue(T value)
{
    return this->checkValue(this->root, value);
}

///
template <class T>
T avlTree<T>::getValue(avlNode<T> *temp, T value)
{

    if(checkValue(temp, value) == 0); // return;
    else
    {
        while(temp)
        {
            if(temp->data == value) return temp->data;
            else if(value > temp->data)
                    temp = temp->right;
                else
                    temp = temp->left;
        }
    }

}

///
template <class T>
T avlTree<T>::getValue(T value)
{
    return this->getValue(this->root, value);
}

///
template <class T>
avlNode<T> *avlTree<T>::findMin(avlNode<T> *temp)
{
    if( !temp || !temp->left ) return temp;
    else return findMin( temp->left );
}



///
template <class T>
avlNode<T> *avlTree<T>::extractMin(avlNode<T> *temp)
{
    if ( !temp->left ) return temp->right;
    temp->left = extractMin(temp->left);
    return balance(temp);
}

///
template <class T>
int avlTree<T>::height(avlNode<T>  *temp)
{
    int h = 0;
    if (temp != NULL)
    {
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = std::max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

///
template <class T>
int avlTree<T>::height()
{
    return height(this->root);
}

///
template <class T>
int avlTree<T>::balanceFactor(avlNode<T> *temp)
{
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;

    return b_factor;
}

///RR rotacja
template <class T>
avlNode<T> *avlTree<T>::RR_rotation(avlNode<T> *parent)
{
    avlNode<T> *temp;
    temp = parent->right;

    parent->right = temp->left;

    temp->left = parent;
    return temp;
}

///LL rotacja
template <class T>
avlNode<T> *avlTree<T>::LL_rotation(avlNode<T> *parent)
{
    avlNode<T> *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

///LR rotacja
template <class T>
avlNode<T> *avlTree<T>::LR_rotation(avlNode<T> *parent)
{
    avlNode<T> *temp;
    temp = parent->left;
    parent->left = RR_rotation (temp);
    return LL_rotation (parent);
}

///RL rotacja
template <class T>
avlNode<T> *avlTree<T>::RL_rotation(avlNode<T> *parent)
{
    avlNode<T> *temp;
    temp = parent->right;
    parent->right = LL_rotation (temp);
    return RR_rotation (parent);
}

///Wywazanie
template <class T>
avlNode<T> *avlTree<T>::balance(avlNode<T> *temp)
{
    int bal_factor = balanceFactor (temp);

    if (bal_factor > 1)
    {
        if (balanceFactor (temp->left) > 0)
            temp = LL_rotation (temp);
        else
            temp = LR_rotation (temp);
    }
    else if (bal_factor < -1)
    {
        if (balanceFactor (temp->right) > 0)
            temp = RL_rotation (temp);
        else
            temp = RR_rotation (temp);
    }
    return temp;
}

///Wstawianie
template <class T>
avlNode<T> *avlTree<T>::insert_(avlNode<T> *root, T value)
{
    if (root == NULL)
    {
        root = new avlNode<T>(value);
        root->data = value;
        root->left = NULL;
        root->right = NULL;
        this->valuesInOrder.push_back(value);
        return root;
    }
    else if ((value) < (root->data))
    {
        root->left = insert_(root->left, value);
        root = balance (root);
    }
    else if ((value) > (root->data))
    {
        root->right = insert_(root->right, value);
        root = balance (root);
    }
    return root;

}

///
template <class T>
int avlTree<T>::insertValue(T value)
{
    this->root = this->insert_(this->root, value);
    return 0;
}


///Usuwanie
template <class T>
avlNode<T> *avlTree<T>::remove_(avlNode<T> *temp, T value)
{
    if(!temp) return temp;

    if(value < temp->data)
        temp->left = remove_(temp->left, value);
    else if(value > temp->data)
        temp->right = remove_(temp->right, value);
    else
    {
        int i=0;

        while(1)
        {
            if(this->valuesInOrder[i] == value) break;
            else i++;
        }
        this->valuesInOrder.erase(valuesInOrder.begin()+i);


        avlNode<T>* left = temp->left;
        avlNode<T>* right = temp->right;

        delete temp;

        if(!right) return left;

        avlNode<T>* mini = findMin(right);
        mini->right = extractMin(right);
        mini->left = left;
        return balance(mini);
    }
    return balance(temp);
}

///
template <class T>
int avlTree<T>::removeValue(T value)
{
    this->root = remove_(this->root, value);
    return 0;
}


///Wyswietlanie
template <class T>
void avlTree<T>::display(avlNode<T> *temp, int level)
{
    if (temp!=NULL)
    {
        display((temp->right), level + 1);

        std::cout<<"\n";

        if (temp == root)
        std::cout<<"Root -> ";

        for (int i=0; i<level && temp != root; i++)
            std::cout<<"\t";

        std::cout<<(temp->data);

        display((temp->left), level + 1);
    }

}

///
template <class T>
void avlTree<T>::display()
{
    this->display(this->root, 1);
}


#endif // AVL_H

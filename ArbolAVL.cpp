/*
 *	Código modificado por Daniel Roa
 *	A01021960
 *	Fecha de entrega: 23/septiembre/2019
 *
 * 	Obtenido de https://rosettacode.org/wiki/AVL_tree#C.2B.2B
 *
 */

#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <chrono>
#include <bits/stdc++.h>
#include <queue>

using namespace std::chrono;
using namespace std;

template <class T>
class AVLnode {
public:
    T key;
    int balance;
    AVLnode *left, *right, *parent;

    AVLnode(T k, AVLnode* p)
        : key(k)
        , balance(0)
        , parent(p)
        , left(NULL)
        , right(NULL)
    {
    }

    ~AVLnode()
    {
        delete left;
        delete right;
    }
};

/* AVL tree */
template <class T>
class AVLtree {
public:
    AVLtree(void);
    ~AVLtree(void);
    bool insert(T key);
    void deleteKey(const T key);
    void printBalance();

private:
    AVLnode<T>* root;

    AVLnode<T>* rotateLeft(AVLnode<T>* a);
    AVLnode<T>* rotateRight(AVLnode<T>* a);
    AVLnode<T>* rotateLeftThenRight(AVLnode<T>* n);
    AVLnode<T>* rotateRightThenLeft(AVLnode<T>* n);
    void rebalance(AVLnode<T>* n);
    int height(AVLnode<T>* n);
    void setBalance(AVLnode<T>* n);
    void printBalance(AVLnode<T>* n);
    void clearNode(AVLnode<T>* n);
};

/* AVL class definition */
template <class T>
void AVLtree<T>::rebalance(AVLnode<T>* n)
{
    setBalance(n);

    if (n->balance == -2) {
        if (height(n->left->left) >= height(n->left->right))
            n = rotateRight(n);
        else
            n = rotateLeftThenRight(n);
    }
    else if (n->balance == 2) {
        if (height(n->right->right) >= height(n->right->left))
            n = rotateLeft(n);
        else
            n = rotateRightThenLeft(n);
    }

    if (n->parent != NULL) {
        rebalance(n->parent);
    }
    else {
        root = n;
    }
}

template <class T>
AVLnode<T>* AVLtree<T>::rotateLeft(AVLnode<T>* a)
{
    AVLnode<T>* b = a->right;
    b->parent = a->parent;
    a->right = b->left;

    if (a->right != NULL)
        a->right->parent = a;

    b->left = a;
    a->parent = b;

    if (b->parent != NULL) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    setBalance(a);
    setBalance(b);
    return b;
}

template <class T>
AVLnode<T>* AVLtree<T>::rotateRight(AVLnode<T>* a)
{
    AVLnode<T>* b = a->left;
    b->parent = a->parent;
    a->left = b->right;

    if (a->left != NULL)
        a->left->parent = a;

    b->right = a;
    a->parent = b;

    if (b->parent != NULL) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    setBalance(a);
    setBalance(b);
    return b;
}

template <class T>
AVLnode<T>* AVLtree<T>::rotateLeftThenRight(AVLnode<T>* n)
{
    n->left = rotateLeft(n->left);
    return rotateRight(n);
}

template <class T>
AVLnode<T>* AVLtree<T>::rotateRightThenLeft(AVLnode<T>* n)
{
    n->right = rotateRight(n->right);
    return rotateLeft(n);
}

template <class T>
int AVLtree<T>::height(AVLnode<T>* n)
{
    if (n == NULL)
        return -1;
    return 1 + max(height(n->left), height(n->right));
}

template <class T>
void AVLtree<T>::setBalance(AVLnode<T>* n)
{
    n->balance = height(n->right) - height(n->left);
}

template <class T>
void AVLtree<T>::printBalance(AVLnode<T>* n)
{
    if (n != NULL) {
        printBalance(n->left);
        cout << n->balance << " ";
        printBalance(n->right);
    }
}

template <class T>
AVLtree<T>::AVLtree(void)
    : root(NULL)
{
}

template <class T>
AVLtree<T>::~AVLtree(void)
{
    delete root;
}

template <class T>
bool AVLtree<T>::insert(T key)
{
    if (root == NULL) {
        root = new AVLnode<T>(key, NULL);
    }
    else {
        AVLnode<T>
            *n = root,
            *parent;

        while (true) {
            if (n->key == key)
                return false;

            parent = n;

            bool goLeft = n->key > key;
            n = goLeft ? n->left : n->right;

            if (n == NULL) {
                if (goLeft) {
                    parent->left = new AVLnode<T>(key, parent);
                }
                else {
                    parent->right = new AVLnode<T>(key, parent);
                }

                rebalance(parent);
                break;
            }
        }
    }

    return true;
}

template <class T>
void AVLtree<T>::deleteKey(const T delKey)
{
    if (root == NULL)
        return;

    AVLnode<T>
        *n = root,
        *parent = root,
        *delNode = NULL,
        *child = root;

    while (child != NULL) {
        parent = n;
        n = child;
        child = delKey >= n->key ? n->right : n->left;
        if (delKey == n->key)
            delNode = n;
    }

    if (delNode != NULL) {
        delNode->key = n->key;

        child = n->left != NULL ? n->left : n->right;

        if (root->key == delKey) {
            root = child;
        }
        else {
            if (parent->left == n) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }

            rebalance(parent);
        }
    }
}

template <class T>
void AVLtree<T>::printBalance()
{
    printBalance(root);
    cout << endl;
}

void Ascendente(int arr[], int tamArreglo)
{

    sort(arr, arr + tamArreglo);

    cout << "El arreglo en orden ascendente es " << endl;

    for (int i = 0; i < tamArreglo; ++i) {
        cout << arr[i] << " ";
    }

    cout << "\n";
};

void Descendente(int arr[], int tamArreglo)
{

    sort(arr, arr + tamArreglo, greater<>());

    cout << "El arreglo en orden ascendente es " << endl;

    for (int i = 0; i < tamArreglo; ++i) {
        cout << arr[i] << " ";
    }

    cout << "\n";
};

void Buscar(int arr[], int tamArreglo, int valPerd)
{

    sort(arr, arr + tamArreglo);

    bool res = false;
    int i = 0;

    while (i < tamArreglo && res != true) {
        if (arr[i] == valPerd) {

            res = true;
        }
        else {

            i++;
        }
    }

    if (arr[i] == valPerd) {
        cout << "El valor " << valPerd << " si se encuentra en el árbol" << '\n';
    }
    else {

        cout << "El valor " << valPerd << " no se encuentra en el árbol" << '\n';
    }

    cout << "\n" << '\n';
};

int main()
{
    AVLtree<int> t;

    int tamArreglo, delVal, cant, newVal, tamRand, opcion, buscado, tamArregloB;

    tamRand = 100000;
    tamArreglo = 100000;

    tamArregloB = 10;

    tamArreglo = tamArreglo * 2;

    int arr[tamArreglo];

    int arrBuscable[tamArregloB];

    srand((unsigned)time(0));

    auto start = high_resolution_clock::now();

    for (int cont = 0; cont < tamArreglo; cont++) {

        arr[cont] = (rand() % tamRand) + 1;
    }

    int n = sizeof(arr) / sizeof(arr[0]);

    for (size_t i = 0; i < tamArreglo; i++) {
        t.insert(arr[i++]);
    }

		/*

    t.printBalance();

		cout << "\n" << '\n';

    cout << "Cuántos valores deseas añadir?" << endl;
    cin >> cant;
    cout << "\n";

    if (cant == 1) {
        for (int i = 0; i < cant; i++) {

            cout << "Inserta un valor" << '\n';
            cin >> newVal;
            cout << "\n";

            t.insert(newVal);
        }
    }

    for (int i = 0; i < cant; i++) {

        cout << "Inserta un valor" << '\n';
        cin >> newVal;
        cout << "\n";

        t.insert(newVal);
    }

		cout << "\n" << '\n';

    cout << "Cuántos valores deseas borrar?" << endl;
    cin >> cant;
    cout << "\n";

    if (cant == 1) {
        for (int i = 0; i < cant; i++) {

            cout << "Inserta el valor que se va a borrar" << '\n';
            cin >> delVal;
            cout << "\n";

            //root = deleteNode(root, delVal);
        }
    }

    for (int i = 0; i < cant; i++) {

        cout << "Inserta el valor que se va a borrar" << '\n';
        cin >> delVal;
        cout << "\n";

        deleteKey(root, delVal);
    }

		cout << "\n" << '\n';

    cout << "\n" << '\n';

    Ascendente(arr, tamArreglo);

		cout << "\n" << '\n';

    Descendente(arr, tamArreglo);

		*/

		cout << "\n" << '\n';

		for (int i = 0; i < tamArregloB; i++) {

        arrBuscable[i] = (rand() % tamRand) + 1;

        int valPerd = arrBuscable[i];

        cout << valPerd << endl;

        Buscar(arr, tamArreglo, valPerd);
    }

    cout << "\n";

    auto stop = high_resolution_clock::now();

    auto durationSeg = duration_cast<seconds>(stop - start);
    auto durationMilli = duration_cast<milliseconds>(stop - start);
    auto durationMicro = duration_cast<microseconds>(stop - start);

    cout << "\n";

    cout << "Le tomo " << durationSeg.count() << " segundos\n";
    cout << "Le tomo " << durationMilli.count() << " milisegundos\n";
    cout << "Le tomo " << durationMicro.count() << " microsegundos\n";

    cout << "\n";

    return 0;
}

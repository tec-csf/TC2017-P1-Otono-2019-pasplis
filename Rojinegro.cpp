#include <iostream>

#include <stdio.h>

#include <ctime>

#include <chrono>

#include <bits/stdc++.h>

#include <queue>

using namespace std::chrono;
using namespace std;

enum COLOR {
  RED,
  BLACK
};

template < class T >
  class Node {
    public:
      T val;
    COLOR color;
    Node < T > * left, * right, * parent;

    Node < T > (T val): val(val) {
      parent = left = right = NULL;
      color = RED;
    }

    Node < T > * uncle() {
      if (parent == NULL or parent - > parent == NULL)
        return NULL;

      if (parent - > isOnLeft())
        // uncle on right
        return parent - > parent - > right;
      else
        // uncle on left
        return parent - > parent - > left;
    }

    // check if node is left child of parent
    bool isOnLeft() {
      return this == parent - > left;
    }

    // returns pointer to sibling
    Node * sibling() {
      // sibling null if no parent
      if (parent == NULL)
        return NULL;

      if (isOnLeft())
        return parent - > right;

      return parent - > left;
    }

    // moves node down and moves given node in its place
    void moveDown(Node < T > * nParent) {
      if (parent != NULL) {
        if (isOnLeft()) {
          parent - > left = nParent;
        } else {
          parent - > right = nParent;
        }
      }
      nParent - > parent = parent;
      parent = nParent;
    }

    bool hasRedChild() {
      return (left != NULL and left - > color == RED) or(right != NULL and right - > color == RED);
    }
  };

template < class T >
  class RBTree {
    Node < T > * root;

    void leftRotate(Node < T > * x) {
      Node < T > * nParent = x - > right;

      // update root if current node is root
      if (x == root)
        root = nParent;

      x - > moveDown(nParent);

      // connect x with new parent's left element
      x - > right = nParent - > left;
      // connect new parent's left element with node
      // if it is not null
      if (nParent - > left != NULL)
        nParent - > left - > parent = x;

      // connect new parent with x
      nParent - > left = x;
    }

    void rightRotate(Node < T > * x) {
      // new parent will be node's left child
      Node < T > * nParent = x - > left;

      // update root if current node is root
      if (x == root)
        root = nParent;

      x - > moveDown(nParent);

      // connect x with new parent's right element
      x - > left = nParent - > right;
      // connect new parent's right element with node
      // if it is not null
      if (nParent - > right != NULL)
        nParent - > right - > parent = x;

      // connect new parent with x
      nParent - > right = x;
    }

    void swapColors(Node < T > * x1, Node < T > * x2) {
      COLOR temp;
      temp = x1 - > color;
      x1 - > color = x2 - > color;
      x2 - > color = temp;
    }

    void swapValues(Node < T > * u, Node < T > * v) {
      int temp;
      temp = u - > val;
      u - > val = v - > val;
      v - > val = temp;
    }

    void fixRedRed(Node < T > * x) {
      if (x == root) {
        x - > color = BLACK;
        return;
      }

      Node < T > * parent = x - > parent, * grandparent = parent - > parent,
        * uncle = x - > uncle();

      if (parent - > color != BLACK) {
        if (uncle != NULL && uncle - > color == RED) {
          // uncle red, perform recoloring and recurse
          parent - > color = BLACK;
          uncle - > color = BLACK;
          grandparent - > color = RED;
          fixRedRed(grandparent);
        } else {
          // Else perform LR, LL, RL, RR
          if (parent - > isOnLeft()) {
            if (x - > isOnLeft()) {
              // for left right
              swapColors(parent, grandparent);
            } else {
              leftRotate(parent);
              swapColors(x, grandparent);
            }
            // for left left and left right
            rightRotate(grandparent);
          } else {
            if (x - > isOnLeft()) {
              // for right left
              rightRotate(parent);
              swapColors(x, grandparent);
            } else {
              swapColors(parent, grandparent);
            }

            // for right right and right left
            leftRotate(grandparent);
          }
        }
      }
    }

    // find node that do not have a left child
    // in the subtree of the given node
    Node < T > * successor(Node < T > * x) {
      Node < T > * temp = x;

      while (temp - > left != NULL)
        temp = temp - > left;

      return temp;
    }

    // find node that replaces a deleted node in BST
    Node < T > * BSTreplace(Node < T > * x) {
      // when node have 2 children
      if (x - > left != NULL and x - > right != NULL)
        return successor(x - > right);

      // when leaf
      if (x - > left == NULL and x - > right == NULL)
        return NULL;

      // when single child
      if (x - > left != NULL)
        return x - > left;
      else
        return x - > right;
    }

    // deletes the given node
    void deleteNode(Node < T > * v) {
      Node < T > * u = BSTreplace(v);

      // True when u and v are both black
      bool uvBlack = ((u == NULL or u - > color == BLACK) and(v - > color == BLACK));
      Node < T > * parent = v - > parent;

      if (u == NULL) {
        // u is NULL therefore v is leaf
        if (v == root) {
          // v is root, making root null
          root = NULL;
        } else {
          if (uvBlack) {
            // u and v both black
            // v is leaf, fix double black at v
            fixDoubleBlack(v);
          } else {
            // u or v is red
            if (v - > sibling() != NULL)
              // sibling is not null, make it red"
              v - > sibling() - > color = RED;
          }

          // delete v from the tree
          if (v - > isOnLeft()) {
            parent - > left = NULL;
          } else {
            parent - > right = NULL;
          }
        }
        delete v;
        return;
      }

      if (v - > left == NULL or v - > right == NULL) {
        // v has 1 child
        if (v == root) {
          // v is root, assign the value of u to v, and delete u
          v - > val = u - > val;
          v - > left = v - > right = NULL;
          delete u;
        } else {
          // Detach v from tree and move u up
          if (v - > isOnLeft()) {
            parent - > left = u;
          } else {
            parent - > right = u;
          }
          delete v;
          u - > parent = parent;
          if (uvBlack) {
            // u and v both black, fix double black at u
            fixDoubleBlack(u);
          } else {
            // u or v red, color u black
            u - > color = BLACK;
          }
        }
        return;
      }

      // v has 2 children, swap values with successor and recurse
      swapValues(u, v);
      deleteNode(u);
    }

    void fixDoubleBlack(Node < T > * x) {
      if (x == root)
        // Reached root
        return;

      Node < T > * sibling = x - > sibling(), * parent = x - > parent;
      if (sibling == NULL) {
        // No sibiling, double black pushed up
        fixDoubleBlack(parent);
      } else {
        if (sibling - > color == RED) {
          // Sibling red
          parent - > color = RED;
          sibling - > color = BLACK;
          if (sibling - > isOnLeft()) {
            // left case
            rightRotate(parent);
          } else {
            // right case
            leftRotate(parent);
          }
          fixDoubleBlack(x);
        } else {
          // Sibling black
          if (sibling - > hasRedChild()) {
            // at least 1 red children
            if (sibling - > left != NULL and sibling - > left - > color == RED) {
              if (sibling - > isOnLeft()) {
                // left left
                sibling - > left - > color = sibling - > color;
                sibling - > color = parent - > color;
                rightRotate(parent);
              } else {
                // right left
                sibling - > left - > color = parent - > color;
                rightRotate(sibling);
                leftRotate(parent);
              }
            } else {
              if (sibling - > isOnLeft()) {
                // left right
                sibling - > right - > color = parent - > color;
                leftRotate(sibling);
                rightRotate(parent);
              } else {
                // right right
                sibling - > right - > color = sibling - > color;
                sibling - > color = parent - > color;
                leftRotate(parent);
              }
            }
            parent - > color = BLACK;
          } else {
            // 2 black children
            sibling - > color = RED;
            if (parent - > color == BLACK)
              fixDoubleBlack(parent);
            else
              parent - > color = BLACK;
          }
        }
      }
    }

    // prints level order for given node
    void levelOrder(Node < T > * x) {
      if (x == NULL)
        // return if node is null
        return;

      // queue for level order
      queue < Node < T > * > q;
      Node < T > * curr;

      // push x
      q.push(x);

      while (!q.empty()) {
        // while q is not empty
        // dequeue
        curr = q.front();
        q.pop();

        // print node value
        cout << curr - > val << " ";

        // push children to queue
        if (curr - > left != NULL)
          q.push(curr - > left);
        if (curr - > right != NULL)
          q.push(curr - > right);
      }
    }

    // prints inorder recursively
    void inorder(Node < T > * x) {
      if (x == NULL)
        return;
      inorder(x - > left);
      cout << x - > val << " ";
      inorder(x - > right);
    }

    public:
      // constructor
      // initialize root
      RBTree() {
        root = NULL;
      }

    Node < T > * getRoot() {
      return root;
    }

    // searches for given value
    // if found returns the node (used for delete)
    // else returns the last node while traversing (used in insert)
    Node < T > * search(int n) {
      Node < T > * temp = root;
      while (temp != NULL) {
        if (n < temp - > val) {
          if (temp - > left == NULL)
            break;
          else
            temp = temp - > left;
        } else if (n == temp - > val) {
          break;
        } else {
          if (temp - > right == NULL)
            break;
          else
            temp = temp - > right;
        }
      }

      return temp;
    }

    // inserts the given value to tree
    void insert(int n) {
      Node < T > * newNode = new Node < T > (n);
      if (root == NULL) {
        // when root is null
        // simply insert value at root
        newNode - > color = BLACK;
        root = newNode;
      } else {
        Node < T > * temp = search(n);

        if (temp - > val == n) {
          // return if value already exists
          return;
        }

        // if value is not found, search returns the node
        // where the value is to be inserted

        // connect new node to correct node
        newNode - > parent = temp;

        if (n < temp - > val)
          temp - > left = newNode;
        else
          temp - > right = newNode;

        // fix red red voilaton if exists
        fixRedRed(newNode);
      }
    }

    // utility function that deletes the node with given value
    void deleteByVal(T n) {
      if (root == NULL)
        // Tree is empty
        return;

      Node < T > * v = search(n), * u;

      if (v - > val != n) {
        cout << "No node found to delete with value:" << n << endl;
        return;
      }

      deleteNode(v);
    }

    // prints inorder of the tree
    void printInOrder() {
      cout << "Inorder: " << endl;
      if (root == NULL)
        cout << "Tree is empty" << endl;
      else
        inorder(root);
      cout << endl;
    }

    // prints level order of the tree
    void printLevelOrder() {
      cout << "Level order: " << endl;
      if (root == NULL)
        cout << "Tree is empty" << endl;
      else
        levelOrder(root);
      cout << endl;
    }
  };

template < class T >
  void Ascendente(T arr[], T tamArreglo) {

    sort(arr, arr + tamArreglo);

    cout << "El arreglo en orden ascendente es " << endl;

    for (int i = 0; i < tamArreglo; ++i) {
      cout << arr[i] << " ";
    }

    cout << "\n";

  };

template < class T >
  void Descendente(T arr[], T tamArreglo) {

    sort(arr, arr + tamArreglo, greater < > ());

    cout << "El arreglo en orden ascendente es " << endl;

    for (int i = 0; i < tamArreglo; ++i) {
      cout << arr[i] << " ";
    }

    cout << "\n";

  };

template < class T >
  void Buscar(T arr[], T tamArreglo, T buscado) {

    sort(arr, arr + tamArreglo);

    bool res = false;
    int i = 0;

    while (i < tamArreglo && res != true) {
      if (arr[i] == buscado) {

        res = true;

      } else {

        i++;

      }
    }

    if (arr[i] == buscado) {
      cout << "El valor " << buscado << " si se encuentra en el árbol" << '\n';
    } else {

      cout << "El valor " << buscado << " no se encuentra en el árbol" << '\n';

    }

    cout << "\n" << '\n';

  };

template < class T >
  int obtenerProfundidad(Node < T > * node, T val, T profundidad) {

    if ((val == node - > val) || (node - > right == NULL && node - > left == NULL)) {
      if (val == node - > val) {
        cout << "La profundidad del árbol es: " << profundidad << endl;
        return profundidad;
      } else {
        cout << "El nodo no se encuentra en el árbol" << endl;
        return -1;
      }
    }

    if (val < node - > val)
      obtenerProfundidad(node - > left, val, profundidad + 1);
    else {
      obtenerProfundidad(node - > right, val, profundidad + 1);
    }
  }

template < class T >
  int heightHelper(Node < T > * n) {
    if (n == NULL) {
      return -1;
    } else {
      return max(heightHelper(n - > left), heightHelper(n - > right)) + 1;
    }
  }

template < class T >
  int max(int x, int y) {
    if (x >= y) {
      return x;
    } else {
      return y;
    }
  }

int main() {
  RBTree < int > tree;

  Node < int > * root = NULL;

  int tamArreglo, delVal, cant, newVal, tamRand, opcion, buscado, profundidad;

  heightHelper(root);

  tamRand = 100000;
  tamArreglo = 100000;

  tamArreglo = tamArreglo * 2;

  int arr[tamArreglo];

  srand((unsigned) time(0));

  for (int cont = 0; cont < tamArreglo; cont++) {

    arr[cont] = (rand() % tamRand) + 1;

  }

  int n = sizeof(arr) / sizeof(arr[0]);

  for (size_t i = 0; i < tamArreglo; i++) {
    tree.insert(arr[i++]);
  }

  auto start = high_resolution_clock::now();

  tree.printInOrder();
  tree.printLevelOrder();

  cout << "Cuántos valores deseas añadir?" << endl;
  cin >> cant;
  cout << "\n";

  if (cant == 1) {
    for (int i = 0; i < cant; i++) {

      cout << "Inserta un valor" << '\n';
      cin >> newVal;
      cout << "\n";

      tree.insert(newVal);

    }
  }

  for (int i = 0; i < cant; i++) {

    cout << "Inserta un valor" << '\n';
    cin >> newVal;
    cout << "\n";

    tree.insert(newVal);

  }

  cout << "Cuántos valores deseas borrar?" << endl;
  cin >> cant;
  cout << "\n";

  if (cant == 1) {
    for (int i = 0; i < cant; i++) {

      cout << "Inserta el valor que se va a borrar" << '\n';
      cin >> delVal;
      cout << "\n";

      tree.deleteByVal(delVal);

    }
  }

  for (int i = 0; i < cant; i++) {

    cout << "Inserta el valor que se va a borrar" << '\n';
    cin >> delVal;
    cout << "\n";

    tree.deleteByVal(delVal);

  }

  cout << "Que valor desea buscar?" << '\n';

  cin >> buscado;

  cout << '\n';

  Buscar(arr, tamArreglo, buscado);

  cout << '\n';

  Ascendente(arr, tamArreglo);

  cout << '\n';

  Descendente(arr, tamArreglo);

  cout << '\n';

  auto stop = high_resolution_clock::now();

  auto durationSeg = duration_cast < seconds > (stop - start);
  auto durationMilli = duration_cast < milliseconds > (stop - start);
  auto durationMicro = duration_cast < microseconds > (stop - start);

  cout << "\n";

  cout << "Le tomo " << durationSeg.count() << " segundos\n";
  cout << "Le tomo " << durationMilli.count() << " milisegundos\n";
  cout << "Le tomo " << durationMicro.count() << " microsegundos\n";

  cout << "\n";

  return 0;

}

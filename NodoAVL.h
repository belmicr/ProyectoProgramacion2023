#ifndef PROYECTOPROGRAMACION2023_NODOAVL_H
#define PROYECTOPROGRAMACION2023_NODOAVL_H

#include <iostream>
#include <string.h>
using namespace std;

template <class T>
class NodoAVL
{
private:
  T data;
  NodoAVL *left, *right;
  int height;

public:
  NodoAVL()
  {
    left = nullptr;
    right = nullptr;
    height=1;
  }

  NodoAVL(T d)
  {
    data = d;
    left = nullptr;
    right = nullptr;
    height = 1;
  }

  T getData() const
  {
    return data;
  }

  void setData(T d)
  {
    this->data = d;
  }

  NodoAVL *getRight() const
  {
    return right;
  }

  void setRight(NodoAVL *r)
  {
    this->right = r;
  }
  NodoAVL *getLeft() const
  {
    return left;
  }

  void setLeft(NodoAVL *l)
  {
    this->left = l;
  }

  int getHeight(){
    return height;
  }

  void setHeight(int h){
    height = h;
  }

  void print(bool esDerecho, string identacion) {
    if (right != NULL) {
        right->print(true, identacion + (esDerecho ? "     " : "|    "));
    }
    cout << identacion;
    if (esDerecho) {
        cout << " /";
    } else {
        cout << " \\";
    }
    cout << "-- ";
    cout << data << endl;
    if (left != NULL) {
        left->print(false, identacion + (esDerecho ? "|    " : "     "));
    }
}

};

#endif
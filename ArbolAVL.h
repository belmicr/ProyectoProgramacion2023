#ifndef PROYECTOPROGRAMACION2023_ARBOLAVL_H
#define PROYECTOPROGRAMACION2023_ARBOLAVL_H

#include "NodoAVL.h"

template <class T>
class ArbolAVL
{
protected:
    NodoAVL<T> *root;

public:
    ArbolAVL();

    void put(T data);

    T search(T data);

    void remove(T data);

    void preorder();

    void inorder();

    void postorder();

    ~ArbolAVL();

    bool esVacio();

    void print();

    int getBalance()
    {
        return getBalance(root);
    }

private:
    T search(T data, NodoAVL<T> *r);
    void preorder(NodoAVL<T> *r);
    void inorder(NodoAVL<T> *r);
    void postorder(NodoAVL<T> *r);

    int max(int a, int b);
    int calculateHeight(NodoAVL<T> *r);
    int getBalance(NodoAVL<T> *r);
    NodoAVL<T> *rotacionDerecha(NodoAVL<T> *y);
    NodoAVL<T> *rotacionIzquierda(NodoAVL<T> *x);
    NodoAVL<T> *put(T data, NodoAVL<T> *r);
    NodoAVL<T> *remove(T data, NodoAVL<T> *r);

    NodoAVL<T> *findMin(NodoAVL<T> *r);
};

/**
 * Constructor del Arbol
 * @tparam K Clave por la cual va a ordenar el árbol
 * @tparam T Valor guardado por el árbol
 */
template <class T>
ArbolAVL<T>::ArbolAVL() { root = nullptr; }

/**
 * Destructor del Arbol
 */
template <class T>
ArbolAVL<T>::~ArbolAVL() {}

/**
 * Busca un dato en el árbol. Si no esta el dato en el árbol
 * tira una excepción
 * @param clave Valor a buscar
 * @return el valor buscado
 */
template <class T>
T ArbolAVL<T>::search(T data)
{
    return search(data, root);
}

template <class T>
T ArbolAVL<T>::search(T data, NodoAVL<T> *r)
{
    if (r == nullptr)
    {
        throw 404;
    }

    if (r->getData() == data)
    {
        return r->getData();
    }

    if (r->getData() > data)
    {
        return search(data, r->getLeft());
    }
    else
    {
        return search(data, r->getRight());
    }
}

/**
 * Agrega un dato al árbol
 * @param clave Clave para agregar el dato
 * @param dato Dato a agregar
 */
template <class T>
void ArbolAVL<T>::put(T data) { root = put(data, root); }

template <class T>
NodoAVL<T> *ArbolAVL<T>::put(T data, NodoAVL<T> *r)
{
    //1. Realizar Insercion normal
    if (r == nullptr)
    {
        return new NodoAVL<T>(data);
    }

    if (r->getData() == data)
    {
        throw 200;
    }

    if (r->getData() > data)
    {
        r->setLeft(put(data, r->getLeft()));
    }
    else
    {
        r->setRight(put(data, r->getRight()));
    }

    //2. Actualizar altura de este nodo padre
    r->setHeight(max(calculateHeight(r->getLeft()), calculateHeight(r->getRight())) + 1);

    //3. Obtener el factor de balance de este nodo padre
    // y chequear si este nodo se desbalanceo
    int balance = getBalance(r);

    //Quedo desbalanceado II: corresponde una rot Der
    if (balance > 1 && data < r->getLeft()->getData())
    {
        return rotacionDerecha(r);
    }

    //Quedo desbalanceado ID: corresponde una rot Izq Der
    if (balance > 1 && data > r->getLeft()->getData())
    {
        r->setLeft(rotacionIzquierda(r->getLeft()));
        return rotacionDerecha(r);
    }

    //Quedo desbalanceado DD: corresponde una rot Izq
    if (balance < -1 && data > r->getRight()->getData())
    {
        return rotacionIzquierda(r);
    }

    //Quedo desbalanceado DI: corresponde una rot Der Izq
    if (balance < -1 && data < r->getRight()->getData())
    {
        r->setRight(rotacionDerecha(r->getRight()));
        return rotacionIzquierda(r);
    }

    return r;
}

/**
 * Elimina un dato del árbol
 * @param clave Clave para identificar el nodo a borrar
 */
template <class T>
void ArbolAVL<T>::remove(T data)
{
    root = remove(data, root);
}

template <class T>
NodoAVL<T> *ArbolAVL<T>::remove(T data, NodoAVL<T> *r)
{
    if (r == nullptr)
        return r;

    // Si el valor data es menor al valor almacenado
    // en r, entonces debe estar en el subarbol
    // izquierdo
    if (data < r->getData())
        r->setLeft(remove(data, r->getLeft()));

        // Si el valor data es mayor al valor almacenado
        // en r, entonces debe estar en el subarbol
        // derecho
    else if (data > r->getData())
        r->setRight(remove(data, r->getRight()));

        // Si data es el mismo valor que esta almacenado
        // en r, entonces es el nodo que hay que eliminar
    else
    {
        // Si r no tiene sub nodos, o si tiene uno solo
        if ((r->getLeft() == nullptr) || (r->getRight() == nullptr))
        {
            NodoAVL<T> *temp = r->getLeft() ? r->getLeft() : r->getRight();

            // En caso de que no tenga
            if (temp == nullptr)
            {
                temp = r;
                r = nullptr;
            }
            else          // Caso con un solo sub nodo
                *r = *temp; // Se copian los valores del
            // sub nodo no vacio
            delete temp;
        }
        else
        {

            // Nodo r con dos sub nodos: Se debe obtener el
            // sucesor inorder (el mas chico en el subarbol derecho)
            NodoAVL<T> *temp = findMin(r->getRight());

            // Copiar la data del sucesor inorder en r
            r->setData(temp->getData());

            // Eliminar el sucesor inorder
            r->setRight(remove(temp->getData(), r->getRight()));
        }
    }

    // Si el arbol tuviera un solo nodo, return
    if (r == nullptr)
        return r;

    // 2. Actualizar la altura del nodo r
    r->setHeight(1 + max(calculateHeight(r->getLeft()),
                         calculateHeight(r->getRight())));

    // 3. Obtener el factor de balance del nodo r
    // para determinar si r se desbalanceo o no
    // luego de la eliminacion
    int balance = getBalance(r);

    //Quedo desbalanceado II: corresponde una rot Der
    if (balance > 1 && getBalance(r->getLeft()) >= 0)
        return rotacionDerecha(r);

    //Quedo desbalanceado ID: corresponde una rot Der Izq
    if (balance > 1 && getBalance(r->getLeft()) < 0)
    {
        r->setLeft(rotacionIzquierda(r->getLeft()));
        return rotacionDerecha(r);
    }

    //Quedo desbalanceado DD: corresponde una rot Izq
    if (balance < -1 && getBalance(r->getRight()) <= 0)
        return rotacionIzquierda(r);

    //Quedo desbalanceado DI: corresponde una rot Izq Der
    if (balance < -1 && getBalance(r->getRight()) > 0)
    {
        r->setRight(rotacionDerecha(r->getRight()));
        return rotacionIzquierda(r);
    }

    return r;
}

template <class T>
NodoAVL<T> *ArbolAVL<T>::findMin(NodoAVL<T> *r)
{
    {
        NodoAVL<T> *ret = r;
        while (ret->getLeft() != nullptr)
            ret = ret->getLeft();

        return ret;
    }
}

/**
 * Informa si un árbol esta vacío
 * @return
 */
template <class T>
bool ArbolAVL<T>::esVacio() { return root == nullptr; }

/**
 * Recorre un árbol en preorden
 */
template <class T>
void ArbolAVL<T>::preorder()
{
    preorder(root);
    std::cout << std::endl;
}

template <class T>
void ArbolAVL<T>::preorder(NodoAVL<T> *r)
{
    if (r == nullptr)
    {
        return;
    }

    std::cout << r->getData() << " ";
    preorder(r->getLeft());
    preorder(r->getRight());
}

/**
 * Recorre un árbol en orden
 */
template <class T>
void ArbolAVL<T>::inorder()
{
    inorder(root);
    std::cout << std::endl;
}

template <class T>
void ArbolAVL<T>::inorder(NodoAVL<T> *r)
{
    if (r == nullptr)
    {
        return;
    }

    inorder(r->getLeft());
    std::cout << r->getData() << " ";
    inorder(r->getRight());
}

/**
 * Recorre un árbol en postorden
 */
template <class T>
void ArbolAVL<T>::postorder()
{
    postorder(root);
    std::cout << std::endl;
}

template <class T>
void ArbolAVL<T>::postorder(NodoAVL<T> *r)
{
    if (r == nullptr)
    {
        return;
    }

    postorder(r->getLeft());
    postorder(r->getRight());
    std::cout << r->getData() << " ";
}

/**
 * Muestra un árbol por consola
 */
template <class T>
void ArbolAVL<T>::print()
{
    if (root != NULL)
        root->print(false, "");
}

template <class T>
int ArbolAVL<T>::max(int a, int b)
{
    return (a > b) ? a : b;
}

template <class T>
int ArbolAVL<T>::calculateHeight(NodoAVL<T> *r)
{
    if (r == nullptr)
    {
        return 0;
    }
    else
        return r->getHeight();
}
template <class T>
int ArbolAVL<T>::getBalance(NodoAVL<T> *r)
{
    if (r == nullptr)
    {
        return 0;
    }
    return calculateHeight(r->getLeft()) - calculateHeight(r->getRight());
}
template <class T>
NodoAVL<T> *ArbolAVL<T>::rotacionDerecha(NodoAVL<T> *y)
{
    NodoAVL<T> *x = y->getLeft();
    NodoAVL<T> *T2 = x->getRight();

    //Rotacion
    x->setRight(y);
    y->setLeft(T2);

    //Actualizar alturas
    y->setHeight(max(calculateHeight(y->getLeft()), calculateHeight(y->getRight())) + 1);
    x->setHeight(max(calculateHeight(x->getLeft()), calculateHeight(x->getRight())) + 1);

    //Devolver la nueva raiz;
    return x;
}

template <class T>
NodoAVL<T> *ArbolAVL<T>::rotacionIzquierda(NodoAVL<T> *x)
{
    NodoAVL<T> *y = x->getRight();
    NodoAVL<T> *T2 = y->getLeft();

    //Rotacion
    y->setLeft(x);
    x->setRight(T2);

    //Atualizar alturas
    x->setHeight(max(calculateHeight(x->getLeft()), calculateHeight(x->getRight())) + 1);
    y->setHeight(max(calculateHeight(y->getLeft()), calculateHeight(y->getRight())) + 1);

    //Devolver la nueva raiz
    return y;
}

#endif
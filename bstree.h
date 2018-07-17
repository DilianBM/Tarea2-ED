#ifndef BINARY_SEARCH_Tree
#define BINARY_SEARCH_Tree
#include <iostream>
#include <sstream>
#include <stack>
using namespace std;
// Nodos del arbol:
template <typename T>
class node
{
public:
    // Esta clase es usada por otras clases.
    // Para mayor eficiencia, los atributos se hacen publicos.
    T key;
    node<T> *p, *left, *right;
    // bool used;

    // Constructor por omision
    node()
    {
        right=left=p=NULL;
    };

    // Constructor por copia. Copia el nodo y sus hijos.

    node(const node<T> * obj, node<T> * padre)
    {
        if (padre->left == NULL && padre->right == NULL)   //Si el original no tiene hijos
        {
            obj->left = NULL;
            obj->right = NULL;

        }
        else
        {

            if (padre->left != NULL && padre->right != NULL)   //Si el original tiene los dos hijos
            {
                obj->left = new node<T>(padre->left->key);
                obj->right = new node<T>(padre->right->key);
            }
            else if (padre->left != NULL && padre->right ==NULL)   //Si el original tiene hijo izquierdo,pero no derecho
            {
                obj->left = new node<T>(padre->left->key); //Crea un nodo igual al hijo izquierdo del original
                obj->right = NULL;
            }
            else if (padre->left == NULL && padre->right != NULL)   //Si el original tiene hijo derecho,pero no izquierdo
            {
                obj->left = NULL;
                obj->right = new node<T>(padre->right->key); //Crea un nodo igual al hijo derecho del original
            }

        }

    }

    // Inicializacion de datos miembro
    node(const T& k, node<T> *w = NULL, node<T> *y = NULL, node<T> *z = NULL):key(k), p(w), left(y), right(z) {};

    ~node()
    {
    }
};

// Arbol:
template <typename T>
class tree
{
public:
    tree()
    {
        root=NULL;//crea el arbol vacio

    };
    // Constructor. Crea un arbol vacio

    tree(const tree<T>& obj)
    {
        copiaArbol(this->root, obj.getRoot());
    };
    // Constructor copia

    ~tree()
    {
        if(root!=NULL)
        {
            borreArbol(root);// llama a un metodo privado que  se encarga de borrar todos los nodos del arbol
        };
    };

    // Destructor (borra el arbol)

    void inorderTreeWalk(node<T>* x, stack<T> & pila)
    {
        if(x!=NULL)
        {
            if(x->left!=NULL)// en forma del recorrido inorden mete los valores del arbol en la pila
            {
                inorderTreeWalk(x->left,pila);// se mete a la parte izquierda del arbol

            }
            pila.push(x->key);//mete los valores en forma inorden IZQ-RAIZ-DER

            if(x->right!=NULL)
            {
                inorderTreeWalk(x->right,pila);//se mete a la parte derecha del arbol

            }
        }

    };

    // Efectua un recorrido en orden del sub‡rbol cuya raiz es apuntada
    // por x, guardando en cada visita la llave de cada nodo en la pila.
    // Es decir, cada vez que se llega a un nodo se hace
    // pila.push(x->key). Si se hace correctamente, al finalizar el
    // metodo la pila debe contener las llaves de los nodos del
    // subarbol ordenadas de mayor a menor.



    node<T>* treeSearch(const T& k)
    {
        node<T>* val=busqueda(root,k);//llama a un metodo de busqueda privado
        return val;
    };

    // Busca la llave recursivamente; si la encuentra, devuelve un
    // apuntador al nodo que la contiene, sino devuelve NULL


    node<T>* iterativeTreeSearch(const T& k)
    {
        node<T> *iter=root;// se posiciona en la raiz
        while(iter!=NULL && k!=iter->key)//mientras no llegue al final de la lista y mientras nolo encuentre
        {
            if(k<iter->key)// pregunta si  es metor  al iterador y si es asi es que puede estar a la izquierda
            {
                iter=iter->left;

            }
            else
            {
                iter=iter->right;//sino busca en la parte derecha
            }

        }
        return iter;
    };
    // Lo mismo que en el anterior pero usando un procedimiento
    // iterativo

    node<T>* treeMinimum()
    {
        node<T> *iter=root;
        while(iter->left!=NULL)//para saber cual es el  valor minimo hay que meterse lo mas a la izquierda posible
        {
            iter=iter->left;
        }
        return iter;
    };
    // Devuelve el nodo que tiene la llave menor.
    // Si el arbol est‡ vacio devuelve NULL.

    node<T>* treeMaximum()
    {
        node<T> *iter=root;
        while(iter->right!=NULL)//mientras existan hijos derechos busque el mas a la derecha y ese sera el maximo
        {
            iter=iter->right;
        }
        return iter;
    };
    // Devuelve el nodo que tiene la llave mayor.
    // Si el arbol esta vacio devuelve NULL.



    // Devuelve el nodo cuya llave es la que le sigue a la
    // del nodo x. Si no existe tal nodo devuelve NULL.
    node<T>* treeSuccessor(const node<T>* x)
    {

        node<T> *y=NULL;
        if(x!=NULL)
        {
            if(x->right!=NULL)// si tiene nodo derecho el sucesor va a ser el minimo de la parte derecha
            {

                return minimo(x->right);

            }
            y=x->p;
            while(y!=NULL && x==y->right)
            {
                x=y;
                y=y->p;

            }
        }
        else
        {
            return NULL;
        }
        return y;
    };


    void treeInsert(node<T>* z)
    {
        node<T>* y = NULL;
        node<T>* x = this->root;
        while( x != NULL)//mientras no haya llegado a una hoja
        {
            y =x;
            if (z->key < x->key)//si el que estoy buscando es menor a la raiz busquelo a la izquierda
            {
                x = x->left;

            }
            else// sino busquelo en la derecha
            {
                x =x->right;
            }
        }
        z->p = y;
        if (y == NULL)//si la raiz en nula ahora la raiz es el nodo que entra
        {
            this->root =z  ;// tree T was empty

        }
        else
        {
            if (z->key < y->key) // si es menor a la ultima hoja a el nodo le toca ir en la parte  derecha
            {
                y->left =z;
            }
            else
            {
                y->right=z;
            }
        }


    };// Inserta el nodo z en la posicion que le corresponde en el arbol.




    /* Saca del arbol la llave contenida en el nodo apuntado por z.
     Devuelve la direccion del nodo eliminado para que se pueda
     disponer de ella.*/
    node<T>* treeDelete(node<T>* z)
    {
        node<T> *temp;
        if(z!=NULL)
        {
            if(z->left==NULL)
            {
                transplanta(root,z,z->right);

            }
            else
            {
                if(z->right==NULL)
                {
                    transplanta(root,z,z->left);

                }
                else
                {
                    temp=minimo(z->right);
                    if(temp->p!=z)
                    {
                        transplanta(root,temp,temp->right);
                        temp->right=z->right;
                        temp->right->p=temp;


                    }
                    transplanta(root,z,temp);
                    temp->left=z->left;
                    temp->left->p=temp;

                }

            }
        }
        return z;
    };

    node<T> * getRoot() const
    {
        return this->root;
    };

// Devuelve la raiz del arbol. (Para efectos de revisi—n de la tarea).


private:
    node<T> *root;
 node<T>* minimo(node<T>*raiz)// busca el minimo de cualquier arbol
    {

        while(raiz->left!=NULL)// si existe nodo izquierdo metase lo mas a la izquierda posible
        {
            raiz=raiz->left;
        }
        return raiz;
    };


    node<T>* busqueda(node<T> *&raiz, T val)
    {
        if(raiz==NULL || raiz->key==val)//si la raiz esta en nulo o no lo esta y tiene la llave igual al valor que estamos buscando retorna el puntero de la raiz
        {
            return raiz;

        }
        else
        {
            if(raiz->key>val)//si la raiz es mayor al que busco metase a buscarlo en la izquierda
            {
                return busqueda(raiz->left,val);

            }
            else
            {

                if(raiz->key<val)
                {

                    return busqueda(raiz->right,val);

                }
            }
        }

    };

    void borreArbol(node<T> *raiz)// metodo llamado en el destructor del arbol
    {
        if (raiz->left!=NULL)// borra primero los nodos de la izquierda
        {
            borreArbol(raiz->left);
        }
        if (raiz->right != NULL)//luego borra los nodos de la derecha
        {
            borreArbol(raiz->right);
        }
        delete raiz;
    };
    void transplanta(node<T> *raiz,node<T> *u,node<T> *v )
    {

        if(u->p==NULL)
        {

            this->root=v;
        }
        else
        {
            if(u==u->p->left)
            {
                u->p->left=v;
            }
            else
            {
                u->p->right=v;
            }

        }
        if(v!=NULL)
        {
            v->p=u->p;

        }
    };

    void copiaArbol(node<T>* &nuevoNodo, node <T>* original)
    {
        if (original == NULL)// si el que  quiere copiar no tiene elementos
        {
            nuevoNodo = NULL;// su copia tampoco tendra
        }
        else
        {
            nuevoNodo= new node<T>;
            nuevoNodo->key = original->key;
            copiaArbol(nuevoNodo->left, original->left);//copia la parte izquierda del original en el nuevo arbol
            copiaArbol(nuevoNodo->right, original->right);// copia la ´parte derecha del original al nuevo arbol
            if (nuevoNodo->right != NULL)
            {
                nuevoNodo->right->p = nuevoNodo;
            }
            if (nuevoNodo->left !=NULL)
            {
                nuevoNodo->left->p = nuevoNodo;
            }

        }
    }
};
#endif	// BINARY_SEARCH_Tree

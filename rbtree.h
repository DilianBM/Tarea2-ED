#ifndef RED_BLACK_rbtree
#define RED_BLACK_rbtree
#include <stack>

enum colors {RED, BLACK};

// Nodos del arbol:
template <typename T>
class rbnode
{
public:
    // Esta clase es para ser usada por otras clases.
    // Por eficiencia se hacen los atributos publicos.
    T key;
    rbnode<T> *p, *left, *right;
    enum colors color;

    // Constructor por omision.
    rbnode()
    {
        p=left=right=nullptr;
    };

    // Constructor por copia del nodo.
    rbnode(const rbnode<T> * obj, const rbnode<T> * objNil, rbnode<T> * parent, rbnode<T> * nilPtr)
    {

    }

    // Inicializacion de datos miembro.
    rbnode (const T& k, rbnode<T> *w = NULL, rbnode<T> *y = NULL,
            rbnode<T> *z = NULL, enum colors c = RED):
        key(k), p(w), left(y), right(z), color(c)
    {};

    ~rbnode()
    {

    }
};

// Arbol:
template <typename T>
class rbtree
{
public:
    rbtree()
    {

        nil=new rbnode<T>(-1,nullptr,nullptr,nullptr);
        nil->color=BLACK;
        root=nil;
    };
    // Constructor (crea un arbol vacio)

    rbtree(const rbtree<T>& obj)
    {
        nil=new rbnode<T>(obj.nil->key,nullptr,nullptr,nullptr);
        nil->color=BLACK;
        root=nil;
        recorre(obj.getRoot(),obj.getNil());

    };
    // Constructor copia

    ~rbtree()
    {
        if(root!=nil)
        {
            borreArbol(root);// llama a un metodo privado que  se encarga de borrar todos los nodos del arbol
        };
        delete nil;
    };
    // Destructor (borra el arbol)

    void inorderTreeWalk(rbnode<T>* x, stack<T> & pila)
    {

        if(x!=nil)
        {
            if(x->left!=nil)// en forma del recorrido inorden mete los valores del arbol en la pila
            {
                inorderTreeWalk(x->left,pila);// se mete a la parte izquierda del arbol

            }
            pila.push(x->key);//mete los valores en forma inorden IZQ-RAIZ-DER
            pila.push(x->color);


            if(x->right!=nil)
            {
                inorderTreeWalk(x->right,pila);//se mete a la parte derecha del arbol

            }
        }
    };
    // Efectua un recorrido en orden del subarbol cuya raíz es apuntada
    // por x. En cada visita apila la llave de cada nodo y su color.
    // Es decir, cada vez que se llega a un nodo se ejecutan las
    // instrucciones pila.push(x->key); y luego pila.push(colorDeX).
    // Para efectos de la tarea, si el color del nodo es rojo,
    // ponga en la pila un 0, y si es negro, ponga un 1.
    // Si se hace correctamente, al finalizar el método la pila debería
    // contener las llaves de los nodos del subárbol (y su color)
    // ordenadas de mayor a menor.

    rbnode<T>* treeSearch(const T& k)
    {
        rbnode<T>* val=busqueda(root,k);//llama a un metodo de busqueda privado
        if(val==nil)
        {
            val=nullptr;

        }
        return val;
    };
    // Busca la llave recursivamente, si la encuentra devuelve un
    // puntero al nodo que la contiene, sino devuelve NULL.

    rbnode<T>* iterativeTreeSearch(const T& k)
    {
        rbnode<T> *iter=root;// se posiciona en la raiz

        while(iter!=nil && k!=iter->key)//mientras no llegue al final de la lista y mientras nolo encuentre
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
        if(iter==nil)
        {
            iter=nullptr;

        }
        return iter;
    };
    // Igual que en el anterior pero usa un procedimiento iterativo.

    rbnode<T>* treeMinimum()
    {
        rbnode<T> *iter=root;
        if(iter==nil)
        {

            return nullptr;
        }
        while(iter->left!=nil)//para saber cual es el  valor minimo hay que meterse lo mas a la izquierda posible
        {
            iter=iter->left;
        }
        return iter;
    };
    // Devuelve el nodo con la llave menor.
    // Si el arbol esta vacio devuelve NULL.

    rbnode<T>* treeMaximum()
    {
        rbnode<T> *iter=root;
        if(iter==nil)
        {

            return nullptr;
        }
        while(iter->right!=nil)//mientras existan hijos derechos busque el mas a la derecha y ese sera el maximo
        {
            iter=iter->right;
        }
        return iter;
    };
    // Devuelve el nodo con la llave mayor.
    // Si el arbol esta vacio devuelve NULL.

    rbnode<T>* treeSuccessor(const rbnode<T>* x)
    {
        rbnode<T> *ptr=nullptr;
        rbnode<T> *y=nil;

        if(x->right!=nil)// si tiene nodo derecho el sucesor va a ser el minimo de la parte derecha
        {

            ptr= minimo(x->right);
            if(ptr==nil)
            {
                return nullptr;

            }
            else
            {
                return ptr;
            }

        }
        y=x->p;
        while(y!=nil && x==y->right)
        {
            x=y;
            y=y->p;

        }
        if(y==nil)
        {
            y= nullptr;

        }





        return y;
    };
    // Devuelve el nodo cuya llave es la siguiente mas grande que
    // la del nodo x. Si no existe tal nodo devuelve NULL.

    void treeInsert(rbnode<T>* z)  //aux es y, actual es x.
    {
        rbnode<T> *y=getNil();
        rbnode<T> *x=getRoot();

        while(x!=nil)
        {
            y=x;
            if(z->key<x->key)
            {
                x=x->left;

            }
            else
            {
                x=x->right;
            }

        }
        z->p=y;
        if(y==nil)
        {
            root=z;

        }
        else
        {
            if(z->key<y->key)
            {
                y->left=z;
            }
            else
            {

                y->right=z;
            }
        }
        z->left=nil;
        z->right=nil;
        z->color=RED;
        RBINSERTFIXUP(root,z);
    };
    // Inserta el nodo z en la posicion que le corresponde en el arbol.

    rbnode<T> * getRoot() const
    {
        return this->root;
    };

    // Devuelve la raiz del arbol. (Para efectos de revision de la tarea).

    rbnode<T> * getNil() const
    {
        return this->nil;
    };
    // Devuelve T.nil. (Para efectos de revision de la tarea).

private:

    rbnode<T> *root;	// raiz del arbol
    rbnode<T> *nil;	    // nodo nil (hoja) del arbol

    void recorre(rbnode<T> *raiz,rbnode<T> *ni)
    {
        if(raiz!=ni)
        {
            rbnode<T> *it=new rbnode<T>();
            it->color=raiz->color;
            it->key=raiz->key;
            insertanodo(it);

            recorre(raiz->left,ni);
            recorre(raiz->right,ni);
        }
    };


    void insertanodo(rbnode<T>* z )//metodo usado para el copia de arbol solo que no se necesita balancear por lo que no se incluye
    {
        rbnode<T> *y=getNil();
        rbnode<T> *x=getRoot();

        while(x!=nil)
        {
            y=x;
            if(z->key<x->key)
            {
                x=x->left;

            }
            else
            {
                x=x->right;
            }

        }
        z->p=y;
        if(y==nil)
        {
            root=z;

        }
        else
        {
            if(z->key<y->key)
            {
                y->left=z;
            }
            else
            {

                y->right=z;
            }
        }
        z->left=nil;
        z->right=nil;

    };

    rbnode<T>* minimo(rbnode<T>*raiz)// busca el minimo de cualquier arbol
    {

        while(raiz->left!=nil)// si existe nodo izquierdo metase lo mas a la izquierda posible
        {
            raiz=raiz->left;
        }

        return raiz;
    };
    void LEFTROTATE(rbnode<T> *x)
    {
        rbnode<T> *y=x->right;
        x->right=y->left;
        if(y->left!=nil)
        {
            y->left->p=x;

        }
        y->p=x->p;
        if(x->p==nil)
        {
            root=y;

        }
        else
        {
            if(x==x->p->left)
            {
                x->p->left=y;

            }
            else
            {
                x->p->right=y;
            }
        }
        y->left=x;
        x->p=y;
    }
    void RIGHTROTATE(rbnode<T> *x)
    {
        rbnode<T> *y=x->left;
        x->left=y->right;
        if(y->right!=nil)
        {
            y->right->p=x;

        }
        y->p=x->p;
        if(x->p==nil)
        {
            root=y;

        }
        else
        {
            if(x==x->p->right)
            {
                x->p->right=y;

            }
            else
            {
                x->p->left=y;
            }
        }
        y->right=x;
        x->p=y;
    }

    void RBINSERTFIXUP(rbnode<T> *raiz,rbnode<T> *z)
    {
        rbnode<T> *y;
        while(z->p->color==RED)
        {
            if(z->p==z->p->p->left)
            {
                y=z->p->p->right;
                if(y->color==RED)
                {
                    z->p->color=BLACK;
                    y->color=BLACK;
                    z->p->p->color=RED;
                    z=z->p->p;
                }
                else
                {
                    if(z==z->p->right)
                    {
                        z=z->p;
                        LEFTROTATE(z);

                    }
                    z->p->color=BLACK;
                    z->p->p->color=RED;
                    RIGHTROTATE(z->p->p);
                }
            }
            else
            {

                rbnode<T> *y=z->p->p->left;

                if(y->color==RED)
                {
                    z->p->color=BLACK;
                    y->color=BLACK;
                    z->p->p->color=RED;
                    z=z->p->p;
                }
                else
                {
                    if(z==z->p->left)
                    {
                        z=z->p;
                        RIGHTROTATE(z);


                    }
                    z->p->color=BLACK;
                    z->p->p->color=RED;
                    LEFTROTATE(z->p->p);
                }
            }


        }
        getRoot()->color=BLACK;
    }

    rbnode<T>* busqueda(rbnode<T>* raiz, const T& val)
    {
        if(raiz==nil || raiz->key==val)//si la raiz esta en nulo o no lo esta y tiene la llave igual al valor que estamos buscando retorna el puntero de la raiz
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

    void borreArbol(rbnode<T> *raiz)// metodo llamado en el destructor del arbol
    {
        if (raiz->left!=nil)// borra primero los nodos de la izquierda
        {
            borreArbol(raiz->left);
        }
        if (raiz->right != nil)//luego borra los nodos de la derecha
        {
            borreArbol(raiz->right);
        }
        delete raiz;
    };

};

#endif	// RED_BLACK_rbtree

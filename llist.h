#ifndef LLIST_H
#define LLIST_H


template <typename T>
class llnode
{
public:
    // Esta clase es para ser usada por otras clases.
    // Por eficiencia los atributos se dejan publicos.

    T key;
    llnode<T> *prev, *next;
    //enum colors color;

    // Constructor por omision.
    llnode()
    {
        prev=NULL;
        next=NULL;
    };

    // Inicializacion de los datos miembro.
    llnode (const T& k, llnode<T> *w = NULL, llnode<T> *y = NULL):key(k), prev(w), next(y) {};

    ~llnode()
    {

    }
};

// Lista enlazada con nodo centinela:
template <typename T>
class llist
{
public:
    llist()
    {
        nil=new llnode<T>(-1);// consttruye el nodo centinela nil
        nil->next=nil;
        nil->prev=nil;
    };
    // Constructor (crea una lista vacia)

    llist(const llist<T>& obj)// Constructor copia
    {
        llnode<T> *p = obj.nil->prev; //Apunta al inicio de la lista original
        nil = new llnode <T> (obj.nil->key); //Crea la copia de nodo Centinela original
        nil->next = nil;
        nil->prev = nil;
        llnode<T> *it = nil;
        while (p != obj.nil)   //Mientras no se acabe la lista original
        {
            it = new llnode <T> (p->key);
            listInsert(it);
            p = p -> prev; //Camino sobre la lista original
            it = it->next;
        }
    };

    ~llist()
    {

        llnode<T> *iter=nil->next;// se posiciona en el primer elemento de la lista
        llnode<T> *aborrar;
        while(iter!=nil)//mientras  no llegue al final de la lista
        {
            aborrar=iter;// pasa la referencia del elemento a borrar
            iter=iter->next;//se mueve en la lista  para no perder la referencia de la lista
            delete aborrar;//una vez que se asegura que no se perdera la referencia de la lista procede a borrar el elemento de la lista

        }
        delete nil;// se procede a eliminar el nodo centinela
    };


    llnode<T>* listSearch(const T& k)
    {
        llnode<T> *iter=nil->next;// se posiciona en la primera posicion de la lista
        llnode<T> *it=NULL;
        while(iter!=nil && iter->key!=k )//pregunta mientras no llegue al final y mientras no la haya encontrado itere
        {
            iter=iter->next;
        }
        if(iter==nil)//si se salio por que llego al final y no lo encontro retorne null
        {

            return NULL;
        }
        else
        {
            return iter; //sino fue que  salio del while porque lo encontro
        }

        return NULL;
    };
// Busca la llave iterativamente. Si la encuentra, devuelve un
// apuntador al nodo que la contiene; sino devuelve NULL.

    void listInsert(llnode<T>* x)
    {
        x->next=this->nil->next;
        this->nil->next->prev=x;
        this->nil->next=x;
        x->prev=this->nil;
    };
// Inserta el nodo x en la lista.
    void imprime()// metodo de prueba para imprimir los elementos de la lista
    {
        llnode<T>* iter=nil->next;
        while(iter!=nil)
        {
            // cout << iter->key << endl;
            iter=iter->next;

        }
    };

    llnode<T>* listDelete(llnode<T>*x)
    {
        if(x==NULL)
        {
            return NULL;// si el nodo existe retorna null
        }
        else// inserta el nodo que entra siempre al inicio
        {
            x->prev->next=x->next;
            x->next->prev=x->prev;
            return x;

        }
        return NULL;
    };
// Saca de la lista la llave contenida en el nodo apuntado por x.
// Devuelve la direccion del nodo eliminado para que se pueda
// disponer de el.

    llnode<T> * getNil() const
    {
        return this->nil;
    };
// Devuelve el nodo centinela. (Para efectos de revision de la tarea).


private:

    llnode<T> *nil;	    // nodo centinela

};

#endif	// LINKED_LIST_llist

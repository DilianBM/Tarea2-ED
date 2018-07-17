#ifndef HASH_CLASS
#define HASH_CLASS
#include <list>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <sstream>
using namespace std;
template <typename T>

class hasht
{
public:
    hasht(int nEntradas)
    {
        numEntradas=nEntradas;
        tabla.resize(numEntradas);
    };
    // Constructor que especifica el numero de cubetas (entradas)
    // en la tabla
    hash(const hash<T>& obj)
    {
        typename std::list<T>::iterator it;//iterador que se usara para iterar sobre las listas
        typename std::vector<std::list<T> >::iterator iterator1;
        for (iterator1=obj.begin(); iterator1!=obj.end(); iterator1++)
        {
            std::list<T> ni(*iterator1);//se para en la i-esima lista del vector
            for (it=ni.begin(); it!=ni.end(); it++)// itera sobre la lista del i-esimo elemento del vector esto lo hace para todo el vector
            {
                tabla[*iterator1].insert(*it);
            }
        }
    };
    // Constructor copia
//		~hasht(){
//		};
    // Destructor (borra la tabla)

    T* search(const T& item)
    {

        typename std::list<T>::iterator it;//iterador de la lista
        int v=funcionHash(item);//se para en la posicion del vector donde puede estar el key

        for (it=tabla[v].begin(); it!=tabla[v].end(); it++)// itera sobre esa lista
        {
            if(*it==item)// si lo encuentra devuelve un puntero a este key
            {
                return &(*it);
            }
        }
        return nullptr;
    };
    // Retorna un puntero a la llave o NULL si no se encuentra

    void insert(const T& item)
    {
        int t=funcionHash(item);//con esto saca la funcion hash
        tabla[t].push_front(item);//inserta la llave en donde le corresponde de acuerdo con el valor devuelto en la funcion hash

    };
    // Inserta el elemento en la tabla
    void imprime()
    {
        typename std::list<T>::iterator it;//iterador que se usara para iterar sobre las listas
        typename std::vector<std::list<T> >::iterator iterator1;
        for (iterator1=tabla.begin(); iterator1!=tabla.end(); iterator1++)
        {
            std::list<T> ni(*iterator1);//se para en la i-esima lista del vector
            for (it=ni.begin(); it!=ni.end(); it++)// itera sobre la lista del i-esimo elemento del vector esto lo hace para todo el vector
            {
                cout << *it<<" ";// imprime los valores de esas listas
            }
            cout<<endl;
        }
    };
    int funcionHash(const T& item)
    {
        return (item%numEntradas);// saca la funcion hash
    }
private:
    int numEntradas;
    // Nœmero de entradas en la tabla
    vector<list<T> > tabla;
    // La tabla es un vector de listas de STL
};
#endif

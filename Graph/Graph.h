#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include "../List/VectorList.h"
#include "../Code/codav.h"

template<class P, class N>
class arco {
public:
    N nodo1;
    N nodo2;
    P peso;
    arco(N n1, N n2)
    {
        this->nodo1=n1;
        this->nodo2=n2;
    }
};


template<class E, class P, class N>
class grafo {
public:
    typedef E etichetta;
    typedef P peso;
    typedef N nodo;

    typedef arco<peso, nodo> arco;
    typedef List_vector<nodo> listaNodi;
    typedef typename List_vector<nodo>::posizione posizioneListaNodi;
    typedef List_vector<arco> listaArchi;
    typedef typename List_vector<arco>::posizione posizioneListaArchi;

    virtual bool vuoto() const = 0;

    virtual void insNodo(nodo &)=0;

    virtual  void insArco(const nodo,const  nodo,const peso)=0;

    virtual void cancNodo(nodo&) = 0;

    virtual void cancArco(nodo, nodo) = 0;

    virtual bool esisteNodo(nodo) const = 0;
    virtual bool esisteArco(arco) const = 0;
    virtual listaNodi adiacenti(nodo) const = 0;

    virtual listaNodi list_nodi() const = 0;

    virtual etichetta leggiEtichetta(nodo) const = 0;

    virtual void scriviEtichetta(nodo, etichetta&) = 0;

    virtual peso leggiPeso(nodo, nodo) const = 0;

    virtual void scriviPeso(nodo, nodo, peso) = 0;

    virtual int numNodi() = 0;

    virtual int numArchi() = 0;
    virtual void bfs(nodo) const =0;
    virtual void dfs(nodo) const =0;

};

#endif //GRAPH_GRAPH_H

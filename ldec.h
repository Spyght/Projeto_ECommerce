#ifndef JOSE_LDEC_H
#define JOSE_LDEC_H
#include <no.h>
#include <QString>


namespace jose {

template<class T>
class LDEC
{
private:
    No<T> * pInicio;
    No<T> * pFim;
    int quantidade;
public:
    LDEC():pInicio(nullptr),pFim(nullptr),quantidade(0){}
    ~LDEC(){while (!estaVazia()) {this->retirarFim();}}
    int getQuantidade() const {return quantidade;}
    bool estaVazia() const {return getQuantidade() == 0;}
    void inserirInicio(T);
    T retirarInicio();
    void inserirFim(T);
    T retirarFim();
    T operator[](int pos) const;
    int consultar(T) const;
    void inserirPosicao(int pos, T);
    T retirarPosicao(int pos);
    void inserirOrdemCrescente(T);
    void ordenarOrdemCrescente();
    void ordenarOrdemDecrescente();
};

template<class T>
void LDEC<T>::inserirInicio(T value){
    try {
        No<T>* pAux = new No<T>(value);
        if (estaVazia()){
            pInicio = pFim = pAux;
            pAux->setProximo(pAux);
            pAux->setAnterior(pAux);
            quantidade ++;
        }
        else{
            pAux->setProximo(pInicio);
            pAux->setAnterior(pFim);
            pInicio->setAnterior(pAux);
            pFim->setProximo(pAux);
            pInicio = pAux;
            quantidade ++;
        }
    } catch (std::bad_alloc&) {
        throw QString("Erro: Falta de memória. Elemento não inserido.");
    }
}

template <class T>
T LDEC<T>::retirarInicio(){
    if (estaVazia())
        throw QString("Lista vazia. Impossível retirar elemento.");
    if (quantidade == 1){
        T valor = pInicio->getDado();
        delete pInicio;
        pInicio = pFim = nullptr;
        quantidade = 0;
        return valor;
    }
    No<T>* pAux = pInicio;
    pInicio = pInicio->getProximo();
    pInicio->setAnterior(pFim);
    pFim->setProximo(pInicio);
    quantidade --;
    T valor = pAux->getDado();
    delete pAux;
    return valor;
}

template<class T>
void LDEC<T>::inserirFim(T value){
    try {
        No<T>* pAux = new No<T>(value);
        if (estaVazia()){
            pInicio = pFim = pAux;
            pAux->setProximo(pAux);
            pAux->setAnterior(pAux);
            quantidade ++;
        }
        else{
            pFim->setProximo(pAux);
            pAux->setAnterior(pFim);
            pAux->setProximo(pInicio);
            pInicio->setAnterior(pAux);
            pFim = pAux;
            quantidade ++;
        }
    } catch (std::bad_alloc&) {
        throw QString("Erro: Falta de memória. Elemento não inserido.");
    }
}

template <class T>
T LDEC<T>::retirarFim(){
    if (estaVazia())
        throw QString("Erro: Lista vazia. Elemento não retirado.");
    No<T>* pAux = pFim;
    if(quantidade == 1){
        pInicio = pFim = nullptr;
    }else{
        pFim = pAux->getAnterior();
        pFim->setProximo(pInicio);
        pInicio->setAnterior(pFim);
    }
    quantidade --;
    T aux = pAux->getDado();
    delete pAux;
    return aux;
}

template<class T>
T LDEC<T>::operator[](int pos) const{
    if (pos < 1 || pos > quantidade)
        throw QString("Erro: Posição inserida inválida.");
    if (pos == 1)
        return pInicio->getDado();
    if (pos == getQuantidade())
        return pFim->getDado();
    No<T>* pAux = pFim;
    if (pos <= getQuantidade() / 2){
        pAux = pInicio;
        for (int cont = 1; cont < pos; cont++)
            pAux = pAux->getProximo();
    } else
        for (int cont = getQuantidade(); cont > pos; cont--)
            pAux = pAux->getAnterior();
    return pAux->getDado();
}

template<class T>
int LDEC<T>::consultar(T value)const{
    for(int i = 0; i < getQuantidade(); i++)
        if(operator[](i + 1) == value)
            return i + 1;
    return -1;
}

template<class T>
void LDEC<T>::inserirPosicao(int pos, T value){
    try{
        if (pos < 1 || pos > getQuantidade() + 1)
            throw QString("Erro: Posição inserida inválida.");
        if (estaVazia() || pos == 1)
            inserirInicio(value);
        else {
            if (pos == getQuantidade() + 1)
                inserirFim(value);
            else{
                No<T>* pNo = new No<T>(value);
                No<T>* pAux = pFim;
                if (pos <= getQuantidade() / 2){
                    pAux = pInicio;
                    for (int cont = 1; cont < pos; cont++)
                        pAux = pAux->getProximo();
                } else
                    for (int cont = getQuantidade(); cont > pos; cont--)
                        pAux = pAux->getAnterior();
                pNo->setProximo(pAux);
                pNo->setAnterior(pAux->getAnterior());
                pAux->getAnterior()->setProximo(pNo);
                pAux->setAnterior(pNo);
                quantidade++;
            }
        }
    } catch(std::bad_alloc& erro){
        throw QString("Erro: Falta de memória. Elemento não inserido.");
    }
}

template<class T>
T LDEC<T>::retirarPosicao(int pos){
    if(estaVazia())
        throw QString("Lista vazia. Impossível retirar elemento.");
    if (pos < 1 || pos > quantidade)
        throw QString("Erro: Posição inserida inválida.");
    if (pos == 1)
        return retirarInicio();
    if (pos == getQuantidade())
        return retirarFim();
    No<T>* pAux = pFim;
    if (pos <= getQuantidade() / 2){
        pAux = pInicio;
        for (int cont = 1; cont < pos; cont++)
            pAux = pAux->getProximo();
    } else
        for (int cont = getQuantidade(); cont > pos; cont--)
            pAux = pAux->getAnterior();
    pAux->getAnterior()->setProximo(pAux->getProximo());
    pAux->getProximo()->setAnterior(pAux->getAnterior());
    T aux = pAux->getDado();
    delete pAux;
    quantidade--;
    return aux;
}

template<class T>
void LDEC<T>::inserirOrdemCrescente(T value){
    if(estaVazia())
        inserirInicio(value);
    else{
        No<T>* pAux = pInicio;
        int i;
        for(i = 1; i <= getQuantidade(); i ++){
            if(pAux->getDado() > value)
                break;
            pAux = pAux->getProximo();
        }
        inserirPosicao(i, value);
    }
}

template<> inline
void LDEC<QString>::inserirOrdemCrescente(QString value){
    if(getQuantidade() == 0)
        inserirInicio(value);
    else{
        No<QString>* pAux = pInicio;
        int pos;
        for(pos = 1; pos <= getQuantidade(); pos ++){
            if(pAux->getDado().toLower() > value.toLower())
                break;
            pAux = pAux->getProximo();
        }
        inserirPosicao(pos, value);
    }
}

template<class T>
void LDEC<T>::ordenarOrdemCrescente(){
    for (int i = 1; i < getQuantidade(); i ++)
        if (operator[](i) > operator[](i + 1))
            inserirOrdemCrescente(retirarPosicao(i + 1));
}

template<class T>
void LDEC<T>::ordenarOrdemDecrescente(){
    for (int i = 1; i < getQuantidade(); i ++)
        if (operator[](i) > operator[](i + 1))
            inserirOrdemCrescente(retirarPosicao(i + 1));
    for (int i = 0; i < getQuantidade() - 1; i ++)
        inserirPosicao(getQuantidade() - i + 1, retirarPosicao(1));
}

} // namespace jose

#endif // JOSE_LDEC_H

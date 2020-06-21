#ifndef JOSE_NO_H
#define JOSE_NO_H

namespace jose {

template <class T>
class LDEC;

template<class T>
class No
{
    friend class LDEC<T>;
    No * anterior;
    T dado;
    No * proximo;
    No(T dado):anterior(nullptr),dado(dado),proximo(nullptr){}
    No *getAnterior() const {return anterior;}
    void setAnterior(No * value){anterior = value;}
    T getDado() const {return dado;}
    void setDado(T dado){dado = this->dado;}
    No *getProximo() const {return proximo;}
    void setProximo(No * value){proximo = value;}
public:
    No():anterior(nullptr),dado(0),proximo(nullptr){}
};

} // namespace jose

#endif // JOSE_NO_H

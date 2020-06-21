#ifndef MRJP_CRUDVENDA_H
#define MRJP_CRUDVENDA_H
#include <crud.h>
#include <Venda.h>
#include <fstream>

namespace mrjp {

class crudVenda : public CRUD
{
public:
    QString nomeArquivoDiscVenda;
    jose::LDEC<Venda *> * pVenda;
public:

    crudVenda(QString nomeArquivoDisc);
    virtual void criarLista(); // revisar override
    virtual Venda * montar(std::string linha);
    virtual std::string desmontar(QString);
    void inserirLista(Venda *pVenda);

    jose::LDEC<Venda *> *getpVenda()const;
    void setPVenda(jose::LDEC<Produto* > * value);

};

} // namespace mrjp

#endif // MRJP_CRUDVENDA_H

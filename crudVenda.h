#ifndef MRJP_CRUDVENDA_H
#define MRJP_CRUDVENDA_H
#include <crud.h>
#include <Venda.h>
#include <fstream>

namespace mrjp {

class crudVenda
{
public:
    QString nomeArquivoDisc;
    jose::LDEC<Venda *> * pVenda;
public:

    crudVenda(QString nomeArquivoDisc);
    virtual void criarLista(); // revisar override
    virtual Venda * montar(std::string);
    virtual std::string desmontar(QString);
    void inserirLista(Venda *pVenda);

};

} // namespace mrjp

#endif // MRJP_CRUDVENDA_H

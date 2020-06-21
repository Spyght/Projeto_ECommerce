#ifndef MRJP_CRUDPRODUTOS_H
#define MRJP_CRUDPRODUTOS_H
#include<crud.h>
#include<Produto.h>


namespace mrjp {

class CRUDProdutos : public CRUD
{
    QString nomeDoArquivoNoDisco;
    jose::LDEC<Produto *> * listaDeProdutos;
public:
    CRUDProdutos();
    virtual void criarLista() override;
    virtual Produto* montar(std::string);
    virtual std::string desmontar(QString);
};

} // namespace mrjp

#endif // MRJP_CRUDPRODUTOS_H

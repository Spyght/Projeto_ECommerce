#ifndef MRJP_CRUDPRODUTOS_H
#define MRJP_CRUDPRODUTOS_H
#include<crud.h>
#include<Produto.h>
#include<fstream>


namespace mrjp {

class CRUDProdutos : public CRUD
{
    QString nomeDoArquivoNoDisco;
    jose::LDEC<Produto *> * pEstoque;
public:
    CRUDProdutos(QString nomeDoArquivoNoDisco);
    virtual void criarLista() override;
    virtual Produto* montar(std::string linha);
    virtual std::string desmontar(QString);

    void inserirNovoElemento(Produto *pProduto);
    int excluirElemento(unsigned int codigoDoProduto);
    void atualizarElemento(Produto *pProdutoExistente);

    unsigned int gerarID();

    jose::LDEC<Produto *> *getPEstoque() const;
//    void setPEstoque(jose::LDEC<Produto *> *value);
};

} // namespace mrjp

#endif // MRJP_CRUDPRODUTOS_H

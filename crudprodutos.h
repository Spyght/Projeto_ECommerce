#ifndef MRJP_CRUDPRODUTOS_H
#define MRJP_CRUDPRODUTOS_H
//#include<crud.h>
#include<QStringList> //
#include<ldec.h> //

#include<Produto.h>
#include<fstream>


namespace mrjp {

class CRUDProdutos
{
    QString nomeDoArquivoNoDisco;
    jose::LDEC<Produto *> * pEstoque;
public:
    CRUDProdutos(QString nomeDoArquivoNoDisco);
    void criarLista();
    Produto* montar(std::string linha);
    std::string desmontar(QString);

    void inserirNovoElemento(Produto *pProduto);
    int excluirElemento(unsigned int codigoDoProduto);
    void atualizarElemento(Produto *pProdutoExistente);

    unsigned int gerarID();

    jose::LDEC<Produto *> *getPEstoque() const;
//    void setPEstoque(jose::LDEC<Produto *> *value);
};

} // namespace mrjp

#endif // MRJP_CRUDPRODUTOS_H

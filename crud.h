#ifndef MRJP_CRUDPRODUTOS_H
#define MRJP_CRUDPRODUTOS_H
#include<ldec.h>
#include<QStringList>
#include<Produto.h>
#include<fstream>


namespace mrjp {

template <class T>
class CRUD
{
    QString nomeDoArquivoNoDisco;
    jose::LDEC<T *> * pEstoque;
public:
    CRUD(QString nomeDoArquivoNoDisco);
    void criarLista();
    T* montar(std::string linha);
    std::string desmontar(QString);

    void inserirNovoElemento(T *pProduto);
    int excluirElemento(unsigned int codigoDoProduto);
    void atualizarElemento(T *pProdutoExistente);

    unsigned int gerarID();

    jose::LDEC<T *> *getPEstoque() const;
//    void setPEstoque(jose::LDEC<Produto *> *value);
};

} // namespace mrjp

#endif // MRJP_CRUDPRODUTOS_H

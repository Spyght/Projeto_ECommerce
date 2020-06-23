#ifndef MRJP_CRUDCLIENTES_H
#define MRJP_CRUDCLIENTES_H
#include<ldec.h>
#include<QStringList>
#include<cliente.h>
#include<crudprodutos.h>
#include<fstream>


namespace mrjp {

class CRUDClientes
{
    QString nomeDoArquivoDeClientes;
    QString nomeDoAtquivoDeVendas;
    jose::LDEC<Cliente *> * pEstoque;
public:
    CRUDClientes(QString nomeDoArquivoDeClientes, QString nomeDoAtquivoDeVendas);
    void criarLista();
    Cliente* montar(std::string linha);
    Venda* montarVenda(std::string linha);
    std::string desmontar(Cliente * pCliente);

    void inserirNovoElemento(Cliente *pCliente);
    int excluirElemento(unsigned int codigoDoCliente);
    void atualizarElemento(Cliente *pClienteExistente, unsigned int Codigo);

    unsigned int gerarID();

    jose::LDEC<Cliente *> *getPEstoque() const;
//    void setPEstoque(jose::LDEC<Cliente *> *value);
};

} // namespace mrjp

#endif // MRJP_CRUDCLIENTES_H

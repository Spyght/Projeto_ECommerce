#ifndef MRJP_VENDA_H
#define MRJP_VENDA_H
#include<QString>
#include<ldec.h>
#include "Produto.h"

namespace mrjp {

class Venda
{
public:
    Venda();
    Venda(unsigned int idPedido, unsigned int idCliente, unsigned int dataCompra);
    unsigned int getIdPedido() const;
    void setIdPedido(unsigned int value);

    unsigned int getIdCliente() const;
    void setIdCliente(unsigned int value);

    unsigned int getDataCompra() const;
    void setDataCompra(unsigned int value);

    jose::LDEC<Produto *> *getPListaDeProdutos() const;
    void setPListaDeProdutos(jose::LDEC<Produto *> *value);

    double getValorTotalDaCompra();
    void setValorTotalDaCompra();

private:
    unsigned int idPedido;
    unsigned int idCliente;
    unsigned int dataCompra;
    double valorTotalDaCompra;
    jose::LDEC<Produto*> * pListaDeProdutos;
};

} // namespace mrjp

#endif // MRJP_VENDA_H

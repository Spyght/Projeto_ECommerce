#ifndef MRJP_VENDA_H
#define MRJP_VENDA_H
#include<QString>
#include<ldec.h>
#include "Produto.h"
#include<QDate>

namespace mrjp {

class Venda
{
public:
    Venda();
    Venda(unsigned int idPedido, unsigned int idCliente, QDate dataCompra);
    unsigned int getIdPedido() const;
    void setIdPedido(unsigned int value);

    unsigned int getIdCliente() const;
    void setIdCliente(unsigned int value);

    QDate getDataCompra() const;
    void setDataCompra(QDate value);

    jose::LDEC<Produto *> *getPListaDeProdutos() const;
    void setPListaDeProdutos(jose::LDEC<Produto *> *value);

    double getValorTotalDaCompra();
    void setValorTotalDaCompra();

    QString print()const;

private:
    unsigned int idPedido;
    unsigned int idCliente;
    QDate dataCompra;
    double valorTotalDaCompra;
    jose::LDEC<Produto*> * pListaDeProdutos;
};

} // namespace mrjp

#endif // MRJP_VENDA_H

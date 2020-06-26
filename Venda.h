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
    Venda(QString dataCompra);
    unsigned int getIdPedido() const;
    void setIdPedido(unsigned int value);

    unsigned int getIdCliente() const;
    void setIdCliente(unsigned int value);

    QString getDataCompra() const;
    void setDataCompra(QString value);

    jose::LDEC<Produto *> *getPListaDeProdutos() const;
    void setPListaDeProdutos(jose::LDEC<Produto *> *value);

    double getValorTotalDaCompra();

    QString print()const;

private:
    unsigned int idPedido;
    unsigned int idCliente;
    QString dataCompra;
    jose::LDEC<Produto*> * pListaDeProdutos;
};

} // namespace mrjp

#endif // MRJP_VENDA_H

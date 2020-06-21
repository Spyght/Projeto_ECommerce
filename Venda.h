#ifndef MRJP_VENDA_H
#define MRJP_VENDA_H
#include<QString>
#include "Produto.h"

namespace mrjp {

class Venda
{
public:
    Venda();
    unsigned int getIdPedido() const;
    void setIdPedido(unsigned int value);

    unsigned int getIdCliente() const;
    void setIdCliente(unsigned int value);

    unsigned int getDataCompra() const;
    void setDataCompra(unsigned int value);

    float calcularValorTotalCompra();


private:
    unsigned int idPedido;
    unsigned int idCliente;
    unsigned int dataCompra;

};

} // namespace mrjp

#endif // MRJP_VENDA_H

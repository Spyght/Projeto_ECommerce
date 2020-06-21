#include "Venda.h"

namespace mrjp {

Venda::Venda()
{

}

unsigned int Venda::getIdPedido() const
{
    return idPedido;
}

void Venda::setIdPedido(unsigned int value)
{
    idPedido = value;
}

unsigned int Venda::getIdCliente() const
{
    return idCliente;
}

void Venda::setIdCliente(unsigned int value)
{
    idCliente = value;
}

unsigned int Venda::getDataCompra() const
{
    return dataCompra;
}

void Venda::setDataCompra(unsigned int value)
{
    dataCompra = value;
}

float Venda::calcularValorTotalCompra()
{

}

} // namespace mrjp

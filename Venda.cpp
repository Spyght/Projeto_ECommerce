#include "Venda.h"

namespace mrjp {

Venda::Venda():
    valorTotalDaCompra(0)
{

}

Venda::Venda(unsigned int idPedido, unsigned int idCliente, unsigned int dataCompra)
{
    setIdPedido(idPedido);
    setIdCliente(idCliente);
    setDataCompra(dataCompra);
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

jose::LDEC<Produto *> *Venda::getPListaDeProdutos() const
{
    return pListaDeProdutos;
}

void Venda::setPListaDeProdutos(jose::LDEC<Produto *> *value)
{
    pListaDeProdutos = value;
}

double Venda::getValorTotalDaCompra()
{
    return valorTotalDaCompra;
}

void Venda::setValorTotalDaCompra()
{
    double aux = 0;
    for(int i = 0; i < getPListaDeProdutos()->getQuantidade(); i++){
        aux += getPListaDeProdutos()->operator[](i)->getPrecoTotal();
    }
    valorTotalDaCompra = aux;
}

QString Venda::print() const
{
    return (QString::number(idPedido) + QString::number(idCliente) + QString::number(dataCompra) + QString::number(valorTotalDaCompra));
}

} // namespace mrjp

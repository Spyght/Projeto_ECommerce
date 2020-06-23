#include "Produto.h"

namespace mrjp {

Produto::Produto()
{

}

unsigned int Produto::getCodigo() const
{
    return codigo;
}

void Produto::setCodigo(unsigned int value)
{
    codigo = value;
}

QString Produto::getDescricao() const
{
    return descricao;
}

void Produto::setDescricao(const QString &value)
{
    descricao = value;
}

unsigned int Produto::getQuantidade() const
{
    return quantidade;
}

void Produto::setQuantidade(unsigned int value)
{
    quantidade = value;
    precoTotal = (double)value * getPrecoUnitario();
}

float Produto::getPrecoUnitario() const
{
    return precoUnitario;
}

void Produto::setPrecoUnitario(float value)
{
    precoUnitario = value;
    precoTotal = (double)value * getQuantidade();
}

double Produto::getPrecoTotal() const
{
    return precoTotal;
}

QString Produto::print() const
{
    return QString::number(getCodigo()) + "\n" + getDescricao() + "\n" + QString::number(getQuantidade()) + "\n" + QString::number(getPrecoUnitario()) + "\n";
}

Produto::Produto(QString desc, unsigned int qtde, float precoUn)
{
    descricao = desc;
    quantidade = qtde;
    precoUnitario = precoUn;
}

}

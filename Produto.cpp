#include "Produto.h"

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
}

float Produto::getPrecoUnitario() const
{
    return precoUnitario;
}

void Produto::setPrecoUnitario(float value)
{
    precoUnitario = value;
}

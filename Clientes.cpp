#include "Clientes.h"

namespace mrjp {
class Clientes;

}
Clientes::Clientes()
{

}

int Clientes::getId() const
{
    return id;
}

void Clientes::setId(int value)
{
    id = value;
}

QString Clientes::getNome() const
{
    return nome;
}

void Clientes::setNome(const QString &value)
{
    nome = value;
}

QString Clientes::getEndereco() const
{
    return endereco;
}

void Clientes::setEndereco(const QString &value)
{
    endereco = value;
}

unsigned int Clientes::getTelefone() const
{
    return telefone;
}

void Clientes::setTelefone(unsigned int value)
{
    telefone = value;
}

unsigned int Clientes::getCpf() const
{
    return cpf;
}

void Clientes::setCpf(unsigned int value)
{
    cpf = value;
}

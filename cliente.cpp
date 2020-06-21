#include "cliente.h"

namespace mrjp {

Clientes::Clientes(QString nome,QString endereco,unsigned int telefone, unsigned int cpf,unsigned int id)
{
    setNome(nome);
    setEndereco(endereco);
    setTelefone(telefone);
    setCpf(cpf);
    setCodigoCliente(id);

}

void Clientes::setTelefone(unsigned int value)
{
    // verificando a validade do telefone.
    QString verificador = QString::number( value);
    if( verificador.length() >8 || verificador.length() < 9 ){
        throw "Numero invalido";
    }else
       telefone = value;
}

void Clientes::setNome(const QString &value)
{
    if(value != "")
        nome = value;
    else
        throw "Nome invalido !";
}

void Clientes::setEndereco(const QString &value)
{
    if(value != "")
      endereco = value;
    else
        throw "Endereço invalido !";
}

void Clientes::setCpf(unsigned int value)
{
    cpf = value;
}

QString Clientes::print()const
{
    return (nome + endereco + QString::number(telefone) + QString::number(cpf));
}

unsigned int Clientes::getCodigoCliente() const
{
    return codigoCliente;
}

void Clientes::setCodigoCliente(unsigned int value)
{
    codigoCliente = value;
}


//void Clientes::montar(QString entrada)




} // namespace mrjp

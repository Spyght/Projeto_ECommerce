#include "clientes.h"

namespace mrjp {

Clientes::Clientes(QString nome,QString endereco,unsigned int telefone, unsigned int cpf)
{
    setNome(nome);
    setEndereco(endereco);
    setTelefone(telefone);
    setCpf(cpf);

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

void Clientes::montar(QString entrada)
{
    QStri

}

} // namespace mrjp

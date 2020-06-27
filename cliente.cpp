#include "cliente.h"

namespace mrjp {

Cliente::Cliente(QString nome, QString endereco, unsigned long telefone, unsigned long long cpf)
{
    try {
        pVendas = new jose::LDEC<Venda *>;
    } catch (std::bad_alloc &) {
        throw QString("Erro: Falta de memória. Elemento não inserido.");
    }
    setNome(nome);
    setEndereco (endereco);
    setTelefone(telefone);
    setCpf(cpf);
}

void Cliente::setTelefone(unsigned long value)
{
    // verificando a validade do telefone.
    QString verificador = QString::number(value);
    if( verificador.length() < 8 /*|| (verificador.length() == 10 || verificador.length() > 11*/){
        throw QString("Número de telefone inválido");
    } else {
        if(verificador.size() == 8)
            verificador.prepend("9");
        else verificador.replace(0,1,"9");
//        if(verificador.size() == 9)
//            verificador.prepend("62");
        telefone = verificador.toULong();
    }
}

void Cliente::setNome(const QString &value)
{
//    if(value != "")
//        throw "Nome invalido !";
    nome = value;
}

void Cliente::setEndereco(const QString &value)
{
//    if(value != "")
//        throw "Endereço invalido !";
    endereco = value;
}

void Cliente::setCpf(unsigned long long value)
{
    cpf = value;
}

QString Cliente::print()const
{
    return QString::number(getId()) + "\n" + getNome() + "\n" + getEndereco() + "\n" + QString::number(getTelefone()) + "\n" + QString::number(getCpf());
}

unsigned int Cliente::getId() const
{
    return id;
}

void Cliente::setId(unsigned int value)
{
    id = value;
}

QString Cliente::getNome() const
{
    return nome;
}

QString Cliente::getEndereco() const
{
    return endereco;
}

unsigned long Cliente::getTelefone() const
{
    return telefone;
}

unsigned long long Cliente::getCpf() const
{
    return cpf;
}

jose::LDEC<Venda *> *Cliente::getPVendas() const
{
    return pVendas;
}

void Cliente::setPVendas(jose::LDEC<Venda *> *value)
{
    pVendas = value;
}

} // namespace mrjp

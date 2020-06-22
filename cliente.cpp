//#include "cliente.h"

//namespace mrjp {

//Clientes::Clientes(QString nome,QString endereco,unsigned int telefone, unsigned int cpf)
//{
//    setNome(nome);
//    setEndereco(endereco);
//    setTelefone(telefone);
//    setCpf(cpf);
//}

//void Clientes::setTelefone(unsigned int value)
//{
//    // verificando a validade do telefone.
//    QString verificador = QString::number( value);
//    if( verificador.length() >8 || verificador.length() < 9 ){
//        throw "Numero invalido";
//    }else
//       telefone = value;
//}

//void Clientes::setNome(const QString &value)
//{
//    if(value != "")
//        nome = value;
//    else
//        throw "Nome invalido !";
//}

//void Clientes::setEndereco(const QString &value)
//{
//    if(value != "")
//      endereco = value;
//    else
//        throw "Endereço invalido !";
//}

//void Clientes::setCpf(unsigned int value)
//{
//    cpf = value;
//}

//QString Clientes::print()const
//{
//    return QString::number(getCodigoCliente()) + "\n" + getNome() + "\n" + getEndereco() + "\n" + QString::number(getTelefone()) + "\n" + QString::number(getCpf());
//}

//unsigned int Clientes::getCodigoCliente() const
//{
//    return codigoCliente;
//}

//void Clientes::setCodigoCliente(unsigned int value)
//{
//    codigoCliente = value;
//}

//QString Clientes::getNome() const
//{
//    return nome;
//}

//QString Clientes::getEndereco() const
//{
//    return endereco;
//}

//unsigned int Clientes::getTelefone() const
//{
//    return telefone;
//}

//unsigned int Clientes::getCpf() const
//{
//    return cpf;
//}


////void Clientes::montar(QString entrada)




//} // namespace mrjp

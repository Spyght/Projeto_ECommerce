#ifndef CLIENTES_H
#define CLIENTES_H
#include"transformarDados.h"
#include<QString>
#include<QStringList>
namespace mrjp {
class Clientes;

}

class Clientes :public transformarDados
{
public:
    Clientes();
    virtual ~Clientes();



    virtual void montar(QString entrada) override;
    virtual void desmontar() override;

private:
    int id;
    QString nome;
    QString endereco;
    unsigned int telefone;
    unsigned int cpf;

};

#endif // CLIENTES_H

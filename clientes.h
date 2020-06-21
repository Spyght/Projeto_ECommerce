#ifndef MRJP_CLIENTES_H
#define MRJP_CLIENTES_H
#include"transformarDados.h"
#include<QString>
#include<QStringList>


namespace mrjp {

class Clientes : public TransformarDados
{
public:
    Clientes();
    virtual ~Clientes();

    virtual Clientes* montar(std::string entrada) override;
    virtual std::string desmontar(QString) override;

private:
    int id;

    QString nome;
    QString endereco;
    unsigned int telefone;
    unsigned int cpf;

};

} // namespace mrjp

#endif // MRJP_CLIENTES_H

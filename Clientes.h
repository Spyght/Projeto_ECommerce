#ifndef CLIENTES_H
#define CLIENTES_H
#include"transformarDados.h"
#include<QString>
namespace mrjp {
class Clientes;

}

class Clientes :public transformarDados
{
public:
    Clientes();
    virtual ~Clientes();

    int getId() const;
    void setId(int value);

    QString getNome() const;
    void setNome(const QString &value);

    QString getEndereco() const;
    void setEndereco(const QString &value);

    unsigned int getTelefone() const;
    void setTelefone(unsigned int value);

    unsigned int getCpf() const;
    void setCpf(unsigned int value);

    virtual void montar() override;
    virtual void desmontar() override;

private:
    int id;
    QString nome;
    QString endereco;
    unsigned int telefone;
    unsigned int cpf;

};

#endif // CLIENTES_H

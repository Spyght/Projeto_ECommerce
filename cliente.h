#ifndef MRJP_CLIENTES_H
#define MRJP_CLIENTES_H
#include<Venda.h>
#include<QString>
#include<QStringList>


namespace mrjp {

class Cliente
{
public:
    Cliente(QString nome,QString endereco,unsigned int telefone, unsigned int cpf);

    void setTelefone(unsigned int value);

    void setNome(const QString &value);

    void setEndereco(const QString &value);

    void setCpf(unsigned int value);

    QString print ()const;


    unsigned int getId() const;
    void setId(unsigned int value);

    QString getNome() const;

    QString getEndereco() const;

    unsigned int getTelefone() const;

    unsigned int getCpf() const;

    jose::LDEC<Venda *> *getPVendas() const;
    void setPVendas(jose::LDEC<Venda *> *value);

private:
    jose::LDEC<Venda *> * pVendas;
    unsigned int id;
    QString nome;
    QString endereco;
    unsigned int telefone;
    unsigned int cpf;

};

} // namespace mrjp

#endif // MRJP_CLIENTES_H

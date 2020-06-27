#ifndef MRJP_CLIENTES_H
#define MRJP_CLIENTES_H
#include<Venda.h>
#include<QString>
#include<QStringList>


namespace mrjp {

class Cliente
{
public:
    Cliente(QString nome, QString endereco, unsigned long telefone, unsigned long long cpf);

    void setTelefone(unsigned long value);

    void setNome(const QString &value);

    void setEndereco(const QString &value);

    void setCpf(unsigned long long value);

    QString print ()const;

    unsigned int getId() const;
    void setId(unsigned int value);

    QString getNome() const;

    QString getEndereco() const;

    unsigned long getTelefone() const;

    unsigned long long getCpf() const;

    jose::LDEC<Venda *> *getPVendas() const;
    void setPVendas(jose::LDEC<Venda *> *value);

private:
    jose::LDEC<Venda *> * pVendas;
    unsigned int id;
    QString nome;
    QString endereco;
    unsigned long telefone;
    unsigned long long cpf;

};

} // namespace mrjp

#endif // MRJP_CLIENTES_H

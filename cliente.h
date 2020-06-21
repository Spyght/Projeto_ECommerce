#ifndef MRJP_CLIENTES_H
#define MRJP_CLIENTES_H
#include<QString>
#include<QStringList>


namespace mrjp {

class Clientes
{
public:
    Clientes(QString nome,QString endereço,unsigned int telefone, unsigned int cpf);
    virtual ~Clientes();

//    virtual Clientes* montar(std::string entrada) override;
//    virtual std::string desmontar(QString) override;

    void setTelefone(unsigned int value);

    void setNome(const QString &value);

    void setEndereco(const QString &value);

    void setCpf(unsigned int value);

private:
    int id;

    QString nome;
    QString endereco;
    unsigned int telefone;
    unsigned int cpf;

};

} // namespace mrjp

#endif // MRJP_CLIENTES_H

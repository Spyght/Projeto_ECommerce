#ifndef MRJP_CLIENTES_H
#define MRJP_CLIENTES_H
#include<QString>
#include<QStringList>


namespace mrjp {

class Clientes
{
public:
    Clientes(QString nome,QString endereco,unsigned int telefone, unsigned int cpf,unsigned int id);
    virtual ~Clientes();

//    virtual Clientes* montar(std::string entrada) override;
//    virtual std::string desmontar(QString) override;

    void setTelefone(unsigned int value);

    void setNome(const QString &value);

    void setEndereco(const QString &value);

    void setCpf(unsigned int value);

    QString print ()const;


    unsigned int getCodigoCliente() const;
    void setCodigoCliente(unsigned int value);

private:
    int id;

    QString nome;
    QString endereco;
    unsigned int telefone;
    unsigned int cpf;
    unsigned int codigoCliente;

};

} // namespace mrjp

#endif // MRJP_CLIENTES_H

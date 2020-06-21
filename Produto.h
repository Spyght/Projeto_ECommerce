#ifndef PRODUTO_H
#define PRODUTO_H
#include <QString>

namespace mrjp {

class Produto
{
public:
    Produto();
    Produto(QString descricao, unsigned int quantidade, float precoUnitario);

    unsigned int getCodigo() const;
    void setCodigo(unsigned int value);

    QString getDescricao() const;
    void setDescricao(const QString &value);

    unsigned int getQuantidade() const;
    void setQuantidade(unsigned int value);

    float getPrecoUnitario() const;
    void setPrecoUnitario(float value);

    double getPrecoTotal() const;

    QString print() const;

private:
    unsigned int codigo;
    QString descricao;
    unsigned int quantidade;
    float precoUnitario;
    double precoTotal;
};

}

#endif // PRODUTO_H

#ifndef PRODUTO_H
#define PRODUTO_H
#include <QString>

namespace mrjp {

class Produto
{
public:
    Produto();
    Produto(QString descricao, int quantidade, float precoUnitario);

    unsigned int getCodigo() const;
    void setCodigo(unsigned int value);

    QString getDescricao() const;
    void setDescricao(const QString &value);

    int getQuantidade() const;
    void setQuantidade(int value);

    float getPrecoUnitario() const;
    void setPrecoUnitario(float value);

    double getPrecoTotal() const;

    QString print() const;


private:
    unsigned int codigo;
    QString descricao;
    int quantidade;
    float precoUnitario;
    double precoTotal;
};

}

#endif // PRODUTO_H

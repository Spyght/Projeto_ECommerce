#include "crudprodutos.h"

namespace mrjp {

CRUDProdutos::CRUDProdutos()
{

}

void CRUDProdutos::criarLista()
{
    //abrir arquivo
}

Produto *CRUDProdutos::montar(std::string linha)
{
    QStringList list = QString::fromStdString(linha).split(';');
    Produto * pProduto = new Produto(list[0].toUInt(),list[1],list[2].toUInt(),list[3].toFloat());
    return pProduto;
}

} // namespace mrjp

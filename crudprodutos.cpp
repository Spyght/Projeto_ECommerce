#include "crudprodutos.h"

namespace mrjp {

jose::LDEC<Produto *> *CRUDProdutos::getPEstoque() const
{
    return pEstoque;
}

void CRUDProdutos::setPEstoque(jose::LDEC<Produto *> *value)
{
    pEstoque = value;
}

CRUDProdutos::CRUDProdutos(QString nomeDoArquivoNoDisco):nomeDoArquivoNoDisco(nomeDoArquivoNoDisco)
{
   std::ifstream arquivo;
    arquivo.open(nomeDoArquivoNoDisco.toStdString().c_str());

    if(!arquivo.is_open()){
        std::ofstream novoArquivo(nomeDoArquivoNoDisco.toStdString().c_str());
        novoArquivo.close();
    }
    arquivo.close();

    try {
        pEstoque = new jose::LDEC<Produto *>;
    } catch (std::bad_alloc &) {
        throw QString("Erro: Falta de memória. Elemento não inserido.");
    }
}

void CRUDProdutos::criarLista()
{
    //abrir arquivo
    std::ifstream arquivo;
    arquivo.open(nomeDoArquivoNoDisco.toStdString().c_str(), std::ios::in);

    if(!arquivo.is_open())
        throw QString("Arquivo de produtos nao foi aberto");

    std::string linha;
    while(!arquivo.eof()){
        getline(arquivo,linha);
        getPEstoque()->inserirOrdemCrescente(montar(linha));
    }
    arquivo.close();
}

Produto *CRUDProdutos::montar(std::string linha)
{
    QStringList list = QString::fromStdString(linha).split(';');
    Produto * pProduto = new Produto(list[0].toUInt(),list[1],list[2].toUInt(),list[3].toFloat());
    return pProduto;
}

} // namespace mrjp

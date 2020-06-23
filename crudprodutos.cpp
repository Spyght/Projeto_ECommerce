#include "crudprodutos.h"

namespace mrjp {

jose::LDEC<Produto *> *CRUDProdutos::getPEstoque() const
{
    return pEstoque;
}

//void CRUDProdutos::setPEstoque(jose::LDEC<Produto *> *value)
//{
//    pEstoque = value;
//}

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
//    while(!arquivo.eof()){
//        getline(arquivo,linha);
//        if(linha != "")
//            getPEstoque()->inserirFim(montar(linha));
//    }
    while(getline(arquivo,linha)){
        if(linha != "")
            getPEstoque()->inserirFim(montar(linha));
    }
    arquivo.close();
}

Produto *CRUDProdutos::montar(std::string linha)
{
    QStringList list = QString::fromStdString(linha).split(';', Qt::SkipEmptyParts);
    Produto * pProduto = new Produto(list[1],list[2].toUInt(),list[3].toFloat());
    pProduto->setCodigo(list[0].toUInt());

    return pProduto;
}

std::string CRUDProdutos::desmontar(Produto *pProduto)
{
    QStringList list = pProduto->print().split('\n', Qt::SkipEmptyParts);
    QString print = QString();
    for(int i = 0; i < list.size(); i++)
        print += list[i] + ";";
    return print.toStdString();
}

void CRUDProdutos::inserirNovoElemento(Produto *pProduto)
{    
    pProduto->setCodigo(gerarID()); //revisao: se colocar um if podemos usar esse metodo no metodo atualizar

    std::ofstream arquivo;
    arquivo.open(nomeDoArquivoNoDisco.toStdString().c_str(), std::ios::out | std::ios::app);
    if(!arquivo.is_open())
        throw QString("Erro ao abrir arquivo de produtos - Metodo inserir");

//    if(pEstoque->getQuantidade() == 0)
//        arquivo << desmontar(pProduto->print());
//    else
    arquivo << desmontar(pProduto) << "\n";
    arquivo.close();

    getPEstoque()->inserirFim(pProduto);
}

int CRUDProdutos::excluirElemento(unsigned int codProduto)
{
    for(int i = 0; i < pEstoque->getQuantidade(); i++)
        if(pEstoque->operator[](i + 1)->getCodigo() == codProduto)
        {
            std::ifstream arquivo;
            arquivo.open(nomeDoArquivoNoDisco.toStdString().c_str(), std::ios::in);

            if(!arquivo.is_open())
                throw QString("Arquivo nao foi aberto");

            std::ofstream arqTemp;
            arqTemp.open("temp.txt", std::ios::out);
            if(!arqTemp.is_open()){
                throw QString("Arquivo temporario nao foi aberto");
            }
            std::string linha;

            while(getline(arquivo, linha))
                if(linha != desmontar(pEstoque->operator[](i + 1)) && linha != "")
                    arqTemp << linha + "\n";
            //fecha os arquivos
            arquivo.close();
            arqTemp.close();

            remove(nomeDoArquivoNoDisco.toStdString().c_str());
            rename("temp.txt", nomeDoArquivoNoDisco.toStdString().c_str());

            pEstoque->retirarPosicao(i + 1);
            return 0;
        }
    return -1;
}

void CRUDProdutos::atualizarElemento(Produto *pProdutoExistente, unsigned int cod)
{
    pProdutoExistente->setCodigo(cod);

    for(int i = 0; i < pEstoque->getQuantidade(); i++)
    {
        if(cod == pEstoque->operator[](i + 1)->getCodigo()){
            excluirElemento(cod);

            std::ofstream arquivo;
            arquivo.open(nomeDoArquivoNoDisco.toStdString().c_str(), std::ios::out | std::ios::app);
            if(!arquivo.is_open())
                throw QString("Erro ao abrir arquivo de produtos - Metodo inserir");

            arquivo << desmontar(pProdutoExistente) << "\n";
            arquivo.close();

            getPEstoque()->inserirFim(pProdutoExistente);
            break;
        }
        if(i == pEstoque->getQuantidade() - 1)
            inserirNovoElemento(pProdutoExistente); //se nao existir nenhum elemento igual, cria um novo
    }
}

unsigned int CRUDProdutos::gerarID()
{
    int i = 1;
    for(; i <= getPEstoque()->getQuantidade(); i++){
        for(int j = 0; j < getPEstoque()->getQuantidade(); j++){
            if(getPEstoque()->operator[](j + 1)->getCodigo() == unsigned(i)){
                break;
            }
            else{
                if (j == getPEstoque()->getQuantidade() - 1){
                    return i;
                }
            }
        }
    }
    return i;
}

} // namespace mrjp

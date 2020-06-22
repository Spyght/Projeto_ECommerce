#include "crudVenda.h"

namespace mrjp {

crudVenda::crudVenda(QString nomeArquivoDiscVenda):nomeArquivoDiscVenda(nomeArquivoDiscVenda)
{
    std::ifstream arquivoVenda;
    arquivoVenda.open(nomeArquivoDiscVenda.toStdString().c_str());

    if(! arquivoVenda.is_open()){
        std::ofstream novoArquivo(nomeArquivoDiscVenda.toStdString().c_str());
        novoArquivo.close();
    }
    arquivoVenda.close();

        try{
        pVenda = new jose::LDEC<Venda *>;
    }catch(std::bad_alloc &){
        throw  QString("Erro: Falta de memoria.");
    }
}

void crudVenda::criarLista()
{
    //abrir arquivo
    std::ifstream arquivoVenda;
    arquivoVenda.open(nomeArquivoDiscVenda.toStdString().c_str(),std::ios::in);

    if(!arquivoVenda.is_open())
        throw QString("Arquivo de Vendas nao foi aberto");

    std::string linha;
    while(! arquivoVenda.eof()){
        getline(arquivoVenda,linha);
        getpVenda()->inserirFim(montar(linha));
    }
    arquivoVenda.close();
}

Venda *crudVenda::montar(std::string linha)
{
    QStringList list = QString::fromStdString(linha).split(';');
    QDate
    Venda *pVenda = new Venda(list[0].toUInt(),list[1].toUInt());
}





}// namespace mrjp

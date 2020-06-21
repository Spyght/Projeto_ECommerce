#include "crudClientes.h"

namespace mrjp {

crudClientes::crudClientes(QString nomeArquivoDisco):nomeArquivoDisco(nomeArquivoDisco)
{
    std::ifstream arquivo;
    arquivo.open(nomeArquivoDisco.toStdString().c_str());

    if(! arquivo.is_open()){
        std::ofstream novoArquivo(nomeArquivoDisco.toStdString().c_str());
        novoArquivo.close(); //perguntar jose
    }
    arquivo.close();

    try {
        pCliente = new jose::LDEC<Clientes *>;
    } catch (std:: bad_alloc &) {
        throw QString ("ERRO: FALTA MEMORIA.\n Elemento nao inserido");

    }
}

void crudClientes::criarLista()
{
    //abrir aquivo

    std::ifstream arquivo;
    arquivo.open(nomeArquivoDisco.toStdString().c_str());

    if(! arquivo.is_open())
        throw QString ("Arquivo nao aberto");

    std::string linha;

    while(! arquivo.eof()){
        getline(arquivo,linha);
        getpCliente()->inserirFim(montar(linha));
    }
    arquivo.close();
}

Clientes *crudClientes::montar(std::string linha)
{
    QStringList list = QString::fromStdString(linha).split(';');
    Clientes * pCliente =new Clientes(list[0],list[1],list[2].toUInt(),list[3].toUInt(),list[4].toUInt());
    return pCliente;
}

void crudClientes::inserirLista(Clientes *cliente)
{
    getpCliente()->inserirFim(cliente);
}

unsigned int crudClientes::gerarID()
{
    for(int i = 0; i <getpCliente()->getQuantidade();i++){
        if(getpCliente()->operator[](i + 1)->getCodigoCliente() != i)
            return i;

    }
}




jose::LDEC<Clientes *> *crudClientes::getpCliente() const
{
    return pCliente;
}

void crudClientes::setpCliente(jose::LDEC<Clientes *> *value)
{
    pCliente = value;
}



} // namespace mrjp

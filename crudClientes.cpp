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
    Clientes * pCliente =new Clientes(list[0],list[1],list[2].toUInt(),list[3].toUInt());
    return pCliente;
}

std::string crudClientes::desmontar(QString print)
{
    QStringList list = print.split('\n');
    print = QString();

    for(int i = 0 ; i < list.size(); i++)
        print += list[i] + ";" ;

        print.chop(1); //nao incluir o ultimo ';'

        return print.toStdString();

}


void crudClientes::inserirLista(Clientes *cliente)
{
    cliente->setCodigoCliente(gerarID());

    std::ofstream arquivo;
    arquivo.open(nomeArquivoDisco.toStdString().c_str(), std::ios::out | std::ios::app);
    if(!arquivo.is_open())
        throw QString ("Erro ao abrir aquivo Clientes");

    arquivo << desmontar(cliente->print());
    arquivo.close();

    getpCliente()->inserirFim(cliente);
}

int crudClientes::excluirCliente(unsigned int codigoCliente)
{
    for(int i = 0; i < pCliente->getQuantidade(); i++)
        if(pCliente->operator[](i+1)->getCodigoCliente() ==codigoCliente){

            std::ifstream arquivo;
            arquivo.open(nomeArquivoDisco.toStdString().c_str(),std::ios::in);

            if(! arquivo.is_open())
                throw  QString("Arquivo nao foi aberto");

            std::ofstream arqTemp;
            arqTemp.open("temp.txt",std::ios::out);

            if(! arqTemp.is_open())
                throw QString("Arquivo temporario nao aberto");

            std::string linha;

            while(getline(arquivo,linha))
                if(QString::fromStdString(linha) == pCliente->operator[](i+1)->print())
                    continue;
                else
                    arqTemp << linha + "\n";

            // fecha os arquivos
            arquivo.close();
            arqTemp.close();

            remove(nomeArquivoDisco.toStdString().c_str());
            rename("temp.txt",nomeArquivoDisco.toStdString().c_str());

            pCliente->retirarPosicao(i+1);
            return 0;
        }
    return -1;
}

void crudClientes::atualizarCliente(Clientes *clienteExistente)
{
    for(int i = 0; i < pCliente->getQuantidade(); i++){

        if(clienteExistente->getCodigoCliente() == pCliente->operator[](i+1)->getCodigoCliente()){
            excluirCliente(clienteExistente->getCodigoCliente());

        std::ofstream arquivo;
        arquivo.open(nomeArquivoDisco.toStdString().c_str(), std::ios::out | std::ios::app);

        if(!arquivo.is_open())
            throw QString ("Erro ao abrir arquivo de Clientes");

        arquivo << desmontar(clienteExistente->print());
        arquivo.close();

        getpCliente()->inserirFim(clienteExistente);
        break;
    }
    if(i == pCliente->getQuantidade()-1)
        inserirLista(clienteExistente);
    }
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

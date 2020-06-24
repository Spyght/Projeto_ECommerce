#include<crudClientes.h>

namespace mrjp {

jose::LDEC<Cliente *> *CRUDClientes::getPEstoque() const
{
    return pEstoque;
}

//void CRUDClientes::setPEstoque(jose::LDEC<Cliente *> *value)
//{
//    pEstoque = value;
//}

CRUDClientes::CRUDClientes(QString arquivoDeClientes, QString arquivoDeVendas):
    nomeDoArquivoDeClientes(arquivoDeClientes),
    nomeDoAtquivoDeVendas(arquivoDeVendas)
{
    std::ifstream arquivo;
    arquivo.open(arquivoDeClientes.toStdString().c_str());

    if(!arquivo.is_open()){
        std::ofstream novoArquivo(arquivoDeClientes.toStdString().c_str());
        novoArquivo.close();
    }
    arquivo.close();

    arquivo.open(arquivoDeVendas.toStdString().c_str());

    if(!arquivo.is_open()){
        std::ofstream novoArquivo(arquivoDeVendas.toStdString().c_str());
        novoArquivo.close();
    }
    arquivo.close();

    try {
        pEstoque = new jose::LDEC<Cliente *>;
    } catch (std::bad_alloc &) {
        throw QString("Erro: Falta de memória. Elemento não inserido.");
    }
}

void CRUDClientes::criarLista()
{
    //abrir arquivo
    std::ifstream arquivo, arquivoVendas;
    arquivo.open(nomeDoArquivoDeClientes.toStdString().c_str(), std::ios::in);
    arquivoVendas.open(nomeDoAtquivoDeVendas.toStdString().c_str(), std::ios::in);

    if(!arquivo.is_open())
        throw QString("Arquivo de Clientes nao foi aberto");
    if(!arquivoVendas.is_open())
        throw QString("Arquivo de Vendas nao foi aberto");

    std::string linha;
    std::string linhaVendas;

    while(getline(arquivo,linha)){
        if(linha != "")
            getPEstoque()->inserirFim(montar(linha));
    }
    arquivo.close();

    while(getline(arquivoVendas,linhaVendas)){
        if(linhaVendas != "")
            for(int i = 0; i < getPEstoque()->getQuantidade(); i++){
                if(montarVenda(linhaVendas)->getIdCliente() == pEstoque->operator[](i + 1)->getId()){
                    pEstoque->operator[](i + 1)->getPVendas()->inserirFim(montarVenda(linhaVendas)); //preenchendo a lista de vendas de um determinado cliente
                    break;
                }
            }
    }
    arquivoVendas.close();
}

Cliente *CRUDClientes::montar(std::string linha)
{
    QStringList list = QString::fromStdString(linha).split(';');
    Cliente * pCliente = new Cliente(list[1], list[2], list[3].toUInt(), list[4].toUInt());
    pCliente->setId(list[0].toUInt());

    return pCliente;
}

Venda *CRUDClientes::montarVenda(std::string linha)
{
    QStringList list = QString::fromStdString(linha).split(';', Qt::SkipEmptyParts);
    Venda * pVendas = new Venda(list[2]);
    pVendas->setIdPedido(list[0].toUInt());
    pVendas->setIdCliente(list[1].toUInt());
    for(int i = 3; i < list.size(); i+=4){
        QString s = list[i] + ";" + list[i + 1] + ";" + list[i + 2] + ";" + list[i + 3] + ";";
        pVendas->getPListaDeProdutos()->inserirFim(CRUDProdutos::montar(s.toStdString()));
    }
    return pVendas;
}

std::string CRUDClientes::desmontar(Cliente *pCliente)
{
    QStringList list = pCliente->print().split('\n');
    QString print = QString();
    for(int i = 0; i < list.size(); i++)
        print += list[i] + ";";
    print.chop(1); //nao incluir ultimo ';'
    return print.toStdString();
}

std::string CRUDClientes::desmontarVenda(Venda *pVenda)
{
    QStringList list = pVenda->print().split('\n', Qt::SkipEmptyParts);
    QString print = QString();
    for(int i = 0; i < list.size(); i++)
        print += list[i] + ";";
    print.chop(1); //nao incluir ultimo ';'
    return print.toStdString();
}

void CRUDClientes::inserirNovoElemento(Cliente *pCliente)
{
    pCliente->setId(gerarID());

    std::ofstream arquivo;
    arquivo.open(nomeDoArquivoDeClientes.toStdString().c_str(), std::ios::out | std::ios::app);
    if(!arquivo.is_open())
        throw QString("Erro ao abrir arquivo de Clientes - Metodo inserir");

    arquivo << desmontar(pCliente) << "\n";
    arquivo.close();

    getPEstoque()->inserirFim(pCliente);
}

int CRUDClientes::excluirElemento(unsigned int codCliente)
{
    for(int i = 0; i < pEstoque->getQuantidade(); i++)
        if(pEstoque->operator[](i + 1)->getId() == codCliente)
        {
            std::ifstream arquivo;
            arquivo.open(nomeDoArquivoDeClientes.toStdString().c_str(), std::ios::in);

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

            remove(nomeDoArquivoDeClientes.toStdString().c_str());
            rename("temp.txt", nomeDoArquivoDeClientes.toStdString().c_str());

            pEstoque->retirarPosicao(i + 1);
            return 0;
        }
    return -1;
}

void CRUDClientes::atualizarElemento(Cliente *pClienteExistente, unsigned int cod)
{
    pClienteExistente->setId(cod);

    for(int i = 0; i < pEstoque->getQuantidade(); i++)
    {
        if(cod == pEstoque->operator[](i + 1)->getId()){
            excluirElemento(cod);

            std::ofstream arquivo;
            arquivo.open(nomeDoArquivoDeClientes.toStdString().c_str(), std::ios::out | std::ios::app);
            if(!arquivo.is_open())
                throw QString("Erro ao abrir arquivo de Clientes - Metodo inserir");

            arquivo << desmontar(pClienteExistente) << "\n";
            arquivo.close();

            getPEstoque()->inserirFim(pClienteExistente);
            break;
        }
        if(i == pEstoque->getQuantidade() - 1)
            inserirNovoElemento(pClienteExistente); //se nao existir nenhum elemento igual, cria um novo
    }
}

void CRUDClientes::inserirPedido(Venda *pPedido, unsigned int IDCliente)
{
    pPedido->setIdPedido(gerarIDVenda());
    pPedido->setIdCliente(IDCliente);

    for(int i = 0; i < pEstoque->getQuantidade(); i++)
    {
        if(pEstoque->operator[](i+ 1)->getId() == IDCliente){            

            std::ofstream arquivo;
            arquivo.open(nomeDoAtquivoDeVendas.toStdString().c_str(), std::ios::out | std::ios::app);
            if(!arquivo.is_open())
                throw QString("Erro ao abrir arquivo de Vendas - Metodo inserir");

            arquivo << desmontarVenda(pPedido) << "\n";
            arquivo.close();

            pEstoque->operator[](i + 1)->getPVendas()->inserirFim(pPedido);

            break;
            }
    }
}

unsigned int CRUDClientes::gerarID()
{
    int i = 1;
    for(; i <= getPEstoque()->getQuantidade(); i++){
        for(int j = 0; j < getPEstoque()->getQuantidade(); j++){
            if(getPEstoque()->operator[](j + 1)->getId() == unsigned(i)){
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

unsigned int CRUDClientes::gerarIDVenda()
{
    int i = 1;
    for(int k = 1; k <= pEstoque->getQuantidade(); k++){
        for(int j = 1; j <= pEstoque->operator[](k)->getPVendas()->getQuantidade(); j++){
            if(pEstoque->operator[](k)->getPVendas()->operator[](j)->getIdPedido() == unsigned(i)){
                i++;
                k = 0;
                break;
            }
        }
    }
    return i;
}

} // namespace mrjp

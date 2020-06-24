#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pListaDeProdutos = new jose::LDEC<mrjp::Produto *>;
    pListaNovoEstoque = new jose::LDEC<mrjp::Produto *>;

    ui->QFrameEstoque->hide();
    ui->QFrameEstoque_2->hide();
    ui->qFrameVendas->hide();
    ui->pushButtonMostrarLista->hide();
    ui->pushButtonMostrarLista_2->hide();
    ui->pushButtonMostrarLista_3->hide();

    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setMinimumDate(QDate::currentDate());

    //configuraçoes da tabela de Produtos
    ui->tableWidgetEstoque->sortByColumn(0, Qt::SortOrder(0));
    ui->tableWidgetEstoque->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableWidgetEstoque->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    ui->tableWidgetEstoque->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tableWidgetEstoque->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);

    //tabela Clientes configuraçoes
    ui->tableWidgetEstoque_2->sortByColumn(0, Qt::SortOrder(0));
    ui->tableWidgetEstoque_2->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableWidgetEstoque_2->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    ui->tableWidgetEstoque_2->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tableWidgetEstoque_2->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);

    //configurações da tabela Vendas
    ui->tableWidgetEstoque_3->sortByColumn(0, Qt::SortOrder(0));
    ui->tableWidgetEstoque_3->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableWidgetEstoque_3->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    ui->tableWidgetEstoque_3->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->tableWidgetEstoque_3->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
    ui->tableWidgetEstoque_3->horizontalHeader()->setSectionResizeMode(3,QHeaderView::ResizeToContents);

    pCRUDProdutos = new mrjp::CRUDProdutos("estoque.txt");
    pCRUDProdutos->criarLista();

    pCRUDClientes = new mrjp::CRUDClientes("clientes.txt","vendas.txt");
    pCRUDClientes->criarLista();

    for(int i = 0; i < pCRUDClientes->getPEstoque()->getQuantidade(); i++){
        QStringList list = QString::fromStdString(pCRUDClientes->desmontar(pCRUDClientes->getPEstoque()->operator[](i + 1))).split(';');
        ui->comboBoxClientes->insertItem(i,list[0] + " - " + list[1]);
    }

    for(int i = 0; i < pCRUDProdutos->getPEstoque()->getQuantidade(); i++){
        QStringList list = QString::fromStdString(pCRUDProdutos->desmontar(pCRUDProdutos->getPEstoque()->operator[](i + 1))).split(';');
        ui->comboBoxProdutos->insertItem(i,list[0] + " - " + list[1]);
    }

    ui->tableWidgetEstoque_3->setSortingEnabled(0);
    ui->tableWidgetEstoque_3->setRowCount(0);
    for(int i = 1; i <= pCRUDClientes->getPEstoque()->getQuantidade(); i++){

        for(int j = 1; j <= pCRUDClientes->getPEstoque()->operator[](i)->getPVendas()->getQuantidade(); j++){

            QStringList list = QString::fromStdString(pCRUDClientes->desmontarVenda(pCRUDClientes->getPEstoque()->operator[](i)->getPVendas()->operator[](j))).split(';');

            ui->tableWidgetEstoque_3->insertRow(ui->tableWidgetEstoque_3->rowCount());

            QTableWidgetItem * item = new QTableWidgetItem(list[0]);
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidgetEstoque_3->setItem(ui->tableWidgetEstoque_3->rowCount() - 1,0,item);

            item = new QTableWidgetItem(list[1]);
            ui->tableWidgetEstoque_3->setItem(ui->tableWidgetEstoque_3->rowCount() - 1,1,item);
            item->setTextAlignment(Qt::AlignCenter);

            item = new QTableWidgetItem(pCRUDClientes->getPEstoque()->operator[](i)->getNome());
            ui->tableWidgetEstoque_3->setItem(ui->tableWidgetEstoque_3->rowCount() - 1,2,item);
            item->setTextAlignment(Qt::AlignCenter);

            item = new QTableWidgetItem(list[2]);
            ui->tableWidgetEstoque_3->setItem(ui->tableWidgetEstoque_3->rowCount() - 1,3,item);
            item->setTextAlignment(Qt::AlignCenter);
        }
    }
    ui->tableWidgetEstoque_3->setSortingEnabled(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearTextEstoque()
{
    ui->lineEditDescricaoEstoque->clear();
    ui->spinBoxCodEstoque->clear();
    ui->spinBoxQtdeEstoque->clear();
    ui->doubleSpinBoxPrecoUnitarioEstoque->clear();
}

void MainWindow::blockEstoqueEdit()
{
    ui->pushButtonAddEstoque->setEnabled(1);
    ui->lineEditDescricaoEstoque->setReadOnly(true);
    ui->spinBoxCodEstoque->setReadOnly(true);
    ui->spinBoxQtdeEstoque->setReadOnly(true);
    ui->doubleSpinBoxPrecoUnitarioEstoque->setReadOnly(true);
}

void MainWindow::freeEstoqueEdit()
{
    ui->pushButtonAddEstoque->setEnabled(0);

    ui->lineEditDescricaoEstoque->setReadOnly(false);
    ui->spinBoxCodEstoque->setReadOnly(false);
    ui->spinBoxQtdeEstoque->setReadOnly(false);
    ui->doubleSpinBoxPrecoUnitarioEstoque->setReadOnly(false);
}


void MainWindow::on_pushButtonAddEstoque_clicked()
{
    ui->pushButtonAddEstoque->setEnabled(0);
    clearTextEstoque();
    ui->qgbAlterarEstoque->hide();
    ui->qgbOpcoesEstoque->show();
    ui->QFrameEstoque->show();
    ui->spinBoxCodEstoque->setValue(0);
    freeEstoqueEdit();
    ui->label_Opcoes->setText("Adicionar:");
}

void MainWindow::on_pushButtonConfirmar_clicked()
{
    try {
        if(isLabelsEmpty1() == 1){
            QMessageBox::information(this,"Campo vazio","Campo \"Descrição\" vazio");
        } else {
            if(isLabelsEmpty1() == 2){
                QMessageBox::information(this,"Campo vazio","Campo \"Preço Unitário\" vazio");
            }else{
                if(ui->lineEditDescricaoEstoque->isReadOnly())
                    pCRUDProdutos->excluirElemento(ui->spinBoxCodEstoque->value());
                else {
                    mrjp::Produto * pAux = new mrjp::Produto(ui->lineEditDescricaoEstoque->text(),
                                                             ui->spinBoxQtdeEstoque->value(),ui->doubleSpinBoxPrecoUnitarioEstoque->value());
                    if(ui->spinBoxCodEstoque->value() == 0){
                        pCRUDProdutos->inserirNovoElemento(pAux);
        //                QMessageBox::information(this,"Estoque Atualizado","Produto Adicionado:\n" + pCRUDProdutos->getPEstoque()->operator[](pCRUDProdutos->getPEstoque()->getQuantidade())->print());
                    }
                    else
                        pCRUDProdutos->atualizarElemento(pAux, ui->spinBoxCodEstoque->value());
                }
                ui->pushButtonMostrarLista->click();
                ui->QFrameEstoque->hide();
                clearTextEstoque();
                blockEstoqueEdit();
            }
        }
    } catch (QString &erro) {
        QMessageBox::information(this,"Erro",erro);
    }
}

void MainWindow::on_tableWidgetEstoque_cellDoubleClicked(int row, int)
{
    ui->QFrameEstoque->show();
    ui->qgbAlterarEstoque->show();
    ui->qgbOpcoesEstoque->hide();

    QString cod = ui->tableWidgetEstoque->item(row, 0)->text();

    for(int i = 1; i <= pCRUDProdutos->getPEstoque()->getQuantidade(); i++)
        if(pCRUDProdutos->getPEstoque()->operator[](i)->getCodigo() == cod.toUInt())
        {
            ui->spinBoxCodEstoque->setValue(pCRUDProdutos->getPEstoque()->operator[](i)->getCodigo());
            ui->lineEditDescricaoEstoque->setText(pCRUDProdutos->getPEstoque()->operator[](i)->getDescricao());
            ui->spinBoxQtdeEstoque->setValue(pCRUDProdutos->getPEstoque()->operator[](i)->getQuantidade());
            ui->doubleSpinBoxPrecoUnitarioEstoque->setValue(pCRUDProdutos->getPEstoque()->operator[](i)->getPrecoUnitario());

            blockEstoqueEdit();
            break;
        }
}

void MainWindow::on_tableWidgetEstoque_cellClicked(int, int)
{
    ui->QFrameEstoque->hide();
}

void MainWindow::on_pushButtonMostrarLista_clicked()
{
    ui->tableWidgetEstoque->setSortingEnabled(0);
    ui->tableWidgetEstoque->setRowCount(0);

    for(int i = 1; i <= pCRUDProdutos->getPEstoque()->getQuantidade(); i++){

        QStringList list = QString::fromStdString(pCRUDProdutos->desmontar(pCRUDProdutos->getPEstoque()->operator[](i))).split(';');

        ui->tableWidgetEstoque->insertRow(ui->tableWidgetEstoque->rowCount());

        QTableWidgetItem * item = new QTableWidgetItem(list[0]);
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetEstoque->setItem(ui->tableWidgetEstoque->rowCount() - 1,0,item);

        item = new QTableWidgetItem(list[1]);
        ui->tableWidgetEstoque->setItem(ui->tableWidgetEstoque->rowCount() - 1,1,item);
        item->setTextAlignment(Qt::AlignCenter);

        item = new QTableWidgetItem(list[2]);
        ui->tableWidgetEstoque->setItem(ui->tableWidgetEstoque->rowCount() - 1,2,item);
        item->setTextAlignment(Qt::AlignCenter);

        item = new QTableWidgetItem(list[3]);
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetEstoque->setItem(ui->tableWidgetEstoque->rowCount() - 1,3,item);
    }
    ui->tableWidgetEstoque->setSortingEnabled(1);
}

void MainWindow::on_pushButtonExcluirEstoque_clicked()
{
    blockEstoqueEdit();
    ui->qgbAlterarEstoque->hide();
    ui->qgbOpcoesEstoque->show();
    ui->label_Opcoes->setText("Excluir:");
}

void MainWindow::on_pushButtonEditarEstoque_clicked()
{
    ui->qgbAlterarEstoque->hide();
    ui->qgbOpcoesEstoque->show();
    freeEstoqueEdit();
    ui->label_Opcoes->setText("Editar:");
}

void MainWindow::on_pushButtonCancelar_clicked()
{
    if(ui->spinBoxCodEstoque->value() == 0){
        ui->QFrameEstoque->hide();
    } else {
        ui->qgbOpcoesEstoque->hide();
        ui->qgbAlterarEstoque->show();
    }
    blockEstoqueEdit();
}

// Clientes

void MainWindow::clearTextEstoque2()
{
    ui->spinBoxCodEstoque_2->clear();
    ui->lineEditDescricaoEstoque_2->clear();
    ui->lineEditEndereco->clear();
    ui->spinBoxCliente->clear();
    ui->lineEditCpf->clear();

}

void MainWindow::blockEstoqueEdit2()
{
    ui->pushButtonAddEstoque_2->setEnabled(1);
    ui->lineEditDescricaoEstoque_2->setReadOnly(true);
    ui->spinBoxCodEstoque_2->setReadOnly(true);
    ui->lineEditEndereco->setReadOnly(true);
    ui->spinBoxCliente->setReadOnly(true);
    ui->lineEditCpf->setReadOnly(true);
}

void MainWindow::freeEstoqueEdit2()
{
    ui->pushButtonAddEstoque_2->setEnabled(0);

    ui->lineEditDescricaoEstoque_2->setReadOnly(false);
    ui->spinBoxCodEstoque_2->setReadOnly(false);
    ui->lineEditEndereco->setReadOnly(false);
    ui->spinBoxCliente->setReadOnly(false);
    ui->lineEditCpf->setReadOnly(false);
}

void MainWindow::printListProducts()
{
    QString s = QString();
    for(int i = 0; i < pListaDeProdutos->getQuantidade(); i++){
        s += imprimirProduto(pListaDeProdutos->operator[](i + 1));
    }
    ui->textEdit->setText(s);
}

//imprimir produto no textEdit de Vendas
QString MainWindow::imprimirProduto(mrjp::Produto * pProduto)
{
    QStringList list = pProduto->print().split('\n', Qt::SkipEmptyParts);
    QString s = "<b>Código do Produto: </b>" + list[0] + "<br>"
            + "<b>Descrição:</b> " + list[1] + "<br>"
            + "<b>Quantidade:</b> " + list[2] + "<br>"
            + "<b>Preço Unitário:</b> " + list[3] + "<br><br>";
    return s;

}

int MainWindow::isLabelsEmpty2()
{
    if(ui->lineEditDescricaoEstoque_2->text() == "")
        return 1;
    if(ui->lineEditEndereco->text() == "")
        return 2;
    if(ui->lineEditCpf->text() == "")
        return 3;
    return 0;
}

int MainWindow::isLabelsEmpty1()
{
    if(ui->lineEditDescricaoEstoque->text() == "")
        return 1;
    if(ui->doubleSpinBoxPrecoUnitarioEstoque->value() == 0)
        return 2;
    return 0;
}


void MainWindow::on_pushButtonAddEstoque_2_clicked()
{
    ui->pushButtonAddEstoque_2->setEnabled(0);
    clearTextEstoque2();
    ui->qgbAlterarEstoque_2->hide();
    ui->qgbOpcoesEstoque_2->show();
    ui->QFrameEstoque_2->show();
    ui->spinBoxCodEstoque_2->setValue(0);
    freeEstoqueEdit2();
    ui->label_Opcoes_2->setText("Adicionar:");
}

void MainWindow::on_pushButtonConfirmar_2_clicked()
{
    try {
        if(isLabelsEmpty2() == 1){
            QMessageBox::information(this,"Campo vazio","Campo \"Nome\" vazio");
        }else{
            if(isLabelsEmpty2() == 2)
                QMessageBox::information(this,"Campo vazio","Campo \"Endereço\" vazio");
                else{
                if(isLabelsEmpty2() == 3)
                    QMessageBox::information(this,"Campo vazio","Campo \"CPF\" vazio");
                    else{
                        if(ui->lineEditDescricaoEstoque_2->isReadOnly())
                            pCRUDClientes->excluirElemento(ui->spinBoxCodEstoque_2->value());
                        else {
                            mrjp::Cliente * pAux = new mrjp::Cliente(ui->lineEditDescricaoEstoque_2->text(),
                                                                     ui->lineEditEndereco->text(),ui->spinBoxCliente->value(),ui->lineEditCpf->text().toUInt());
                            if(ui->spinBoxCodEstoque_2->value() == 0){
                                pCRUDClientes->inserirNovoElemento(pAux);
                            }
                            else
                                pCRUDClientes->atualizarElemento(pAux, ui->spinBoxCodEstoque_2->value());
                        }
                        ui->pushButtonMostrarLista_2->click();
                        ui->QFrameEstoque_2->hide();
                        clearTextEstoque2();
                        blockEstoqueEdit2();
                }
            }
        }

    } catch (QString &erro) {
        QMessageBox::information(this,"Erro",erro);
    }
}

void MainWindow::on_tableWidgetEstoque_2_cellDoubleClicked(int row, int)
{
    ui->QFrameEstoque_2->show();
    ui->qgbAlterarEstoque_2->show();
    ui->qgbOpcoesEstoque_2->hide();

    QString cod = ui->tableWidgetEstoque_2->item(row, 0)->text();

    for(int i = 1; i <= pCRUDClientes->getPEstoque()->getQuantidade(); i++)
        if(pCRUDClientes->getPEstoque()->operator[](i)->getId() == cod.toUInt())
        {
            ui->spinBoxCodEstoque_2->setValue(pCRUDClientes->getPEstoque()->operator[](i)->getId());
            ui->lineEditDescricaoEstoque_2->setText(pCRUDClientes->getPEstoque()->operator[](i)->getNome());
            ui->lineEditEndereco->setText(pCRUDClientes->getPEstoque()->operator[](i)->getEndereco());
            ui->spinBoxCliente->setValue(pCRUDClientes->getPEstoque()->operator[](i)->getTelefone());
            ui->lineEditCpf->setText(QString::number(pCRUDClientes->getPEstoque()->operator[](i)->getCpf()));

            blockEstoqueEdit2();
            break;
        }
}

void MainWindow::on_tableWidgetEstoque_2_cellClicked(int, int)
{
    ui->QFrameEstoque_2->hide();
}

void MainWindow::on_pushButtonMostrarLista_2_clicked()
{
    ui->tableWidgetEstoque_2->setSortingEnabled(0);
    ui->tableWidgetEstoque_2->setRowCount(0);

    for(int i = 1; i <= pCRUDClientes->getPEstoque()->getQuantidade(); i++){

        QStringList list = QString::fromStdString(pCRUDClientes->desmontar(pCRUDClientes->getPEstoque()->operator[](i))).split(';');

        ui->tableWidgetEstoque_2->insertRow(ui->tableWidgetEstoque_2->rowCount());

        QTableWidgetItem * item = new QTableWidgetItem(list[0]);
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetEstoque_2->setItem(ui->tableWidgetEstoque_2->rowCount() - 1,0,item);

        item = new QTableWidgetItem(list[1]);
        ui->tableWidgetEstoque_2->setItem(ui->tableWidgetEstoque_2->rowCount() - 1,1,item);
        item->setTextAlignment(Qt::AlignCenter);

        item = new QTableWidgetItem(list[2]);
        ui->tableWidgetEstoque_2->setItem(ui->tableWidgetEstoque_2->rowCount() - 1,2,item);
        item->setTextAlignment(Qt::AlignCenter);

        item = new QTableWidgetItem(list[3]);
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetEstoque_2->setItem(ui->tableWidgetEstoque_2->rowCount() - 1,3,item);
    }
    ui->tableWidgetEstoque_2->setSortingEnabled(1);
}

void MainWindow::on_pushButtonExcluirEstoque_2_clicked()
{
    blockEstoqueEdit2();
    ui->qgbAlterarEstoque_2->hide();
    ui->qgbOpcoesEstoque_2->show();
    ui->label_Opcoes_2->setText("Excluir:");
}

void MainWindow::on_pushButtonEditarEstoque_2_clicked()
{
    ui->qgbAlterarEstoque_2->hide();
    ui->qgbOpcoesEstoque_2->show();
    freeEstoqueEdit2();
    ui->label_Opcoes_2->setText("Editar:");
}

void MainWindow::on_pushButtonCancelar_2_clicked()
{
    if(ui->spinBoxCodEstoque_2->value() == 0){
        ui->QFrameEstoque_2->hide();
    } else {
        ui->qgbOpcoesEstoque_2->hide();
        ui->qgbAlterarEstoque_2->show();
    }
    blockEstoqueEdit2();
}

// VENDAS ------------------------------------------------------------------------



void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if(index == 1)
    {
        ui->tableWidgetEstoque_2->setSortingEnabled(0);
        ui->tableWidgetEstoque_2->setRowCount(0);

        for(int i = 1; i <= pCRUDClientes->getPEstoque()->getQuantidade(); i++){

            QStringList list = QString::fromStdString(pCRUDClientes->desmontar(pCRUDClientes->getPEstoque()->operator[](i))).split(';');

            ui->tableWidgetEstoque_2->insertRow(ui->tableWidgetEstoque_2->rowCount());

            QTableWidgetItem * item = new QTableWidgetItem(list[0]);
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidgetEstoque_2->setItem(ui->tableWidgetEstoque_2->rowCount() - 1,0,item);

            item = new QTableWidgetItem(list[1]);
            ui->tableWidgetEstoque_2->setItem(ui->tableWidgetEstoque_2->rowCount() - 1,1,item);
            item->setTextAlignment(Qt::AlignCenter);

            item = new QTableWidgetItem(list[2]);
            ui->tableWidgetEstoque_2->setItem(ui->tableWidgetEstoque_2->rowCount() - 1,2,item);
            item->setTextAlignment(Qt::AlignCenter);

            item = new QTableWidgetItem(list[3]);
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidgetEstoque_2->setItem(ui->tableWidgetEstoque_2->rowCount() - 1,3,item);
        }
        ui->tableWidgetEstoque_2->setSortingEnabled(1);
    }
    if(index == 2)
    {
        ui->tableWidgetEstoque->setSortingEnabled(0);
        ui->tableWidgetEstoque->setRowCount(0);

        for(int i = 1; i <= pCRUDProdutos->getPEstoque()->getQuantidade(); i++){

            QStringList list = QString::fromStdString(pCRUDProdutos->desmontar(pCRUDProdutos->getPEstoque()->operator[](i))).split(';');

            ui->tableWidgetEstoque->insertRow(ui->tableWidgetEstoque->rowCount());

            QTableWidgetItem * item = new QTableWidgetItem(list[0]);
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidgetEstoque->setItem(ui->tableWidgetEstoque->rowCount() - 1,0,item);

            item = new QTableWidgetItem(list[1]);
            ui->tableWidgetEstoque->setItem(ui->tableWidgetEstoque->rowCount() - 1,1,item);
            item->setTextAlignment(Qt::AlignCenter);

            item = new QTableWidgetItem(list[2]);
            ui->tableWidgetEstoque->setItem(ui->tableWidgetEstoque->rowCount() - 1,2,item);
            item->setTextAlignment(Qt::AlignCenter);

            item = new QTableWidgetItem(list[3]);
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidgetEstoque->setItem(ui->tableWidgetEstoque->rowCount() - 1,3,item);
        }
        ui->tableWidgetEstoque->setSortingEnabled(1);
    }
}

void MainWindow::on_pushButtonAddEstoque_3_clicked()
{
    ui->pushButtonAddEstoque_3->setEnabled(0);    

    ui->qFrameVendas->show();
    ui->qGBPedido->hide();
    ui->qGBOpcoes->hide();
}

void MainWindow::on_pushButtonNovoPedido_clicked()
{
    if(ui->comboBoxClientes->count()){
        ui->pushButtonNovoPedido->setEnabled(0);
        ui->comboBoxClientes->setEnabled(0);
        ui->qGBPedido->show();
        ui->qGBOpcoes->show();
        ui->textEdit->clear();
        for(int i = 0; i < pCRUDProdutos->getPEstoque()->getQuantidade(); i++){
            mrjp::Produto *pAux = new mrjp::Produto(pCRUDProdutos->getPEstoque()->operator[](i+1)->getDescricao()
                    ,pCRUDProdutos->getPEstoque()->operator[](i+1)->getQuantidade(), pCRUDProdutos->getPEstoque()->operator[](i+1)->getPrecoUnitario());
            pAux->setCodigo(pCRUDProdutos->getPEstoque()->operator[](i+1)->getCodigo());
            pListaNovoEstoque->inserirFim(pAux);
        }
    }
    else QMessageBox::information(this,"Erro Adicionar Cliente", "Adicione um Cliente primeiro");

//    ui->textEdit->setText(pCRUDClientes->getPEstoque()->operator[](1)->getPVendas()->operator[](1)->print());
}

void MainWindow::on_tableWidgetEstoque_3_cellClicked(int , int )
{
    ui->pushButtonAddEstoque_3->setEnabled(1);
    ui->qFrameVendas->hide();
    ui->pushButtonCancelarPedido->click();
}

void MainWindow::on_tableWidgetEstoque_3_cellDoubleClicked(int row, int column)
{
    this->row = row;
    this->column = column;
//    QString cod = ui->tableWidgetEstoque_2->item(row, 0)->text();
//    for(int i = 0; i < pCRUDClientes->getPEstoque()->)
    ui->comboBoxClientes->setEnabled(1);
    ui->pushButtonNovoPedido->setEnabled(1);
    ui->comboBoxClientes->setCurrentIndex(row);
    ui->comboBoxClientes->currentIndexChanged(row);
    ui->qFrameVendas->show();
//    ui->textEdit->setText(pCRUDClientes->getPEstoque()->operator[](1)->getPVendas()->operator[](1)->print());
}

void MainWindow::on_pushButtonCancelarPedido_clicked()
{
    while(pListaNovoEstoque->getQuantidade() > 0)
        pListaNovoEstoque->retirarFim();
    while(pListaDeProdutos->getQuantidade() > 0)
        pListaDeProdutos->retirarFim();
    ui->qGBOpcoes->hide();
    ui->qGBPedido->hide();
    ui->pushButtonAddEstoque_3->setEnabled(1);
    ui->qFrameVendas->hide();
    ui->pushButtonNovoPedido->setEnabled(1);
    ui->comboBoxClientes->setEnabled(1);
    ui->textEdit->clear();
}

void MainWindow::on_pushButtonConfirmarPedido_clicked()
{
    try {
        mrjp::Venda * pAux = new mrjp::Venda(ui->dateEdit->text());
        while(pListaDeProdutos->getQuantidade() > 0){
            pAux->getPListaDeProdutos()->inserirFim(pListaDeProdutos->retirarInicio());
        }
        pCRUDClientes->inserirPedido(pAux, pCRUDClientes->getPEstoque()->operator[](ui->comboBoxClientes->currentIndex() + 1)->getId());

        while(pListaNovoEstoque->getQuantidade()>0)
            pCRUDProdutos->atualizarElemento(pListaNovoEstoque->retirarFim()
                                             ,pCRUDProdutos->getPEstoque()->operator[](pListaNovoEstoque->getQuantidade())->getCodigo());
        ui->pushButtonMostrarLista_3->click();
        ui->comboBoxClientes->setEnabled(1);
        ui->pushButtonNovoPedido->setEnabled(1);
        ui->qGBPedido->hide();
        ui->qGBOpcoes->hide();


        ui->comboBoxClientes->clear();
        ui->comboBoxProdutos->clear();
        for(int i = 0; i < pCRUDClientes->getPEstoque()->getQuantidade(); i++){
            QStringList list = QString::fromStdString(pCRUDClientes->desmontar(pCRUDClientes->getPEstoque()->operator[](i + 1))).split(';');
            ui->comboBoxClientes->insertItem(i,list[0] + " - " + list[1]);
        }

        for(int i = 0; i < pCRUDProdutos->getPEstoque()->getQuantidade(); i++){
            QStringList list = QString::fromStdString(pCRUDProdutos->desmontar(pCRUDProdutos->getPEstoque()->operator[](i + 1))).split(';');
            ui->comboBoxProdutos->insertItem(i,list[0] + " - " + list[1]);
        }
    } catch (QString &erro) {
        QMessageBox::information(this,"Erro ao confirmar Venda",erro);
    }


}

void MainWindow::on_pushButtonAdd_clicked()
{
    if(pListaNovoEstoque->getQuantidade() > 0){
        int index = ui->comboBoxProdutos->currentIndex() + 1;
        int novaQuantidade = pListaNovoEstoque->operator[](index)->getQuantidade() - ui->spinBoxVenda->value();
        if(novaQuantidade < 0)
            QMessageBox::information(this,"Erro Adicionar Produto", "Há apenas "
                                     + QString::number(pListaNovoEstoque->operator[](index)->getQuantidade()) + " unidades desse produto no estoque");
        else{
            pListaNovoEstoque->operator[](index)->setQuantidade(novaQuantidade);
            if(pListaDeProdutos->getQuantidade() > 0){
                for(int i = 1; i <= pListaDeProdutos->getQuantidade(); i++){
                    if(pListaNovoEstoque->operator[](index)->getCodigo() == pListaDeProdutos->operator[](i)->getCodigo()){
                        pListaDeProdutos->operator[](i)->setQuantidade(pListaDeProdutos->operator[](i)->getQuantidade() + ui->spinBoxVenda->value());
                        break;
                    }else{
                        if(i == pListaDeProdutos->getQuantidade()){
                            mrjp::Produto * pAux = new mrjp::Produto(pListaNovoEstoque->operator[](index)->getDescricao()
                                    , ui->spinBoxVenda->value(),pListaNovoEstoque->operator[](index)->getPrecoUnitario());
                            pAux->setCodigo(pListaNovoEstoque->operator[](index)->getCodigo());
                            pListaDeProdutos->inserirFim(pAux);
                            break;
                        }
                    }
                }
            } else {
                mrjp::Produto * pAux = new mrjp::Produto(pListaNovoEstoque->operator[](index)->getDescricao()
                        , ui->spinBoxVenda->value(),pListaNovoEstoque->operator[](index)->getPrecoUnitario());
                pAux->setCodigo(pListaNovoEstoque->operator[](index)->getCodigo());
                pListaDeProdutos->inserirFim(pAux);
            }
            printListProducts();
//            ui->textEdit->append("\n" + QString::number(ui->spinBoxVenda->value()));
        }
    }
    else QMessageBox::information(this,"Erro Adicionar Produto", "Adicione um produto primeiro");

}

void MainWindow::on_pushButtonSub_clicked()
{
    for (int i = 0; i < pListaNovoEstoque->getQuantidade(); i++) {
        if(pListaDeProdutos->getQuantidade() > 0){
            if(pListaNovoEstoque->operator[](i + 1)->getCodigo() == pListaDeProdutos->operator[](pListaDeProdutos->getQuantidade())->getCodigo()){
                pListaNovoEstoque->operator[](i + 1)->setQuantidade(pListaNovoEstoque->operator[](i + 1)->getQuantidade() + pListaDeProdutos->retirarFim()->getQuantidade());

                printListProducts();
                break;
            }
        } else break;
    }
}

void MainWindow::on_pushButtonMostrarLista_3_clicked()
{
    ui->tableWidgetEstoque_3->setSortingEnabled(0);
    ui->tableWidgetEstoque_3->setRowCount(0);
    for(int i = 1; i <= pCRUDClientes->getPEstoque()->getQuantidade(); i++){

        for(int j = 1; j <= pCRUDClientes->getPEstoque()->operator[](i)->getPVendas()->getQuantidade(); j++){

            QStringList list = QString::fromStdString(pCRUDClientes->desmontarVenda(pCRUDClientes->getPEstoque()->operator[](i)->getPVendas()->operator[](j))).split(';');

            ui->tableWidgetEstoque_3->insertRow(ui->tableWidgetEstoque_3->rowCount());

            QTableWidgetItem * item = new QTableWidgetItem(list[0]);
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidgetEstoque_3->setItem(ui->tableWidgetEstoque_3->rowCount() - 1,0,item);

            item = new QTableWidgetItem(list[1]);
            ui->tableWidgetEstoque_3->setItem(ui->tableWidgetEstoque_3->rowCount() - 1,1,item);
            item->setTextAlignment(Qt::AlignCenter);

            item = new QTableWidgetItem(pCRUDClientes->getPEstoque()->operator[](i)->getNome());
            ui->tableWidgetEstoque_3->setItem(ui->tableWidgetEstoque_3->rowCount() - 1,2,item);
            item->setTextAlignment(Qt::AlignCenter);

            item = new QTableWidgetItem(list[2]);
            ui->tableWidgetEstoque_3->setItem(ui->tableWidgetEstoque_3->rowCount() - 1,3,item);
            item->setTextAlignment(Qt::AlignCenter);
        }
    }
    ui->tableWidgetEstoque_3->setSortingEnabled(1);
}

void MainWindow::on_textEdit_textChanged()
{
    if(ui->textEdit->document()->isEmpty())
        ui->pushButtonConfirmarPedido->setEnabled(0);
    else
        ui->pushButtonConfirmarPedido->setEnabled(1);
}

void MainWindow::on_comboBoxClientes_activated(int index)
{
    if(pCRUDClientes->getPEstoque()->getQuantidade() > 0){
        index++;
        QString s = QString();
        for(int i = 1; i <= pCRUDClientes->getPEstoque()->operator[](index)->getPVendas()->getQuantidade(); i++){
            s += "<b>ID da Venda:</b> " + QString::number(pCRUDClientes->getPEstoque()->operator[](index)->getPVendas()->operator[](i)->getIdPedido()) + "<br>";
            for (int j = 1; j <= pCRUDClientes->getPEstoque()->operator[](index)->getPVendas()->operator[](i)->getPListaDeProdutos()->getQuantidade(); j++) {
                s += imprimirProduto(pCRUDClientes->getPEstoque()->operator[](index)->getPVendas()->operator[](i)->getPListaDeProdutos()->operator[](j));
            }
        }
        ui->textEdit->setText(s);
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 0) {
        ui->pushButtonCancelarPedido->click();
        ui->comboBoxClientes->setEnabled(1);
        ui->comboBoxClientes->clear();
        ui->comboBoxProdutos->clear();
        for(int i = 0; i < pCRUDClientes->getPEstoque()->getQuantidade(); i++){
            QStringList list = QString::fromStdString(pCRUDClientes->desmontar(pCRUDClientes->getPEstoque()->operator[](i + 1))).split(';');
            ui->comboBoxClientes->insertItem(i,list[0] + " - " + list[1]);
        }

        for(int i = 0; i < pCRUDProdutos->getPEstoque()->getQuantidade(); i++){
            QStringList list = QString::fromStdString(pCRUDProdutos->desmontar(pCRUDProdutos->getPEstoque()->operator[](i + 1))).split(';');
            ui->comboBoxProdutos->insertItem(i,list[0] + " - " + list[1]);
        }

        ui->tableWidgetEstoque_3->setSortingEnabled(0);
        ui->tableWidgetEstoque_3->setRowCount(0);
        for(int i = 1; i <= pCRUDClientes->getPEstoque()->getQuantidade(); i++){

            for(int j = 1; j <= pCRUDClientes->getPEstoque()->operator[](i)->getPVendas()->getQuantidade(); j++){

                QStringList list = QString::fromStdString(pCRUDClientes->desmontarVenda(pCRUDClientes->getPEstoque()->operator[](i)->getPVendas()->operator[](j))).split(';');

                ui->tableWidgetEstoque_3->insertRow(ui->tableWidgetEstoque_3->rowCount());

                QTableWidgetItem * item = new QTableWidgetItem(list[0]);
                item->setTextAlignment(Qt::AlignCenter);
                ui->tableWidgetEstoque_3->setItem(ui->tableWidgetEstoque_3->rowCount() - 1,0,item);

                item = new QTableWidgetItem(list[1]);
                ui->tableWidgetEstoque_3->setItem(ui->tableWidgetEstoque_3->rowCount() - 1,1,item);
                item->setTextAlignment(Qt::AlignCenter);

                item = new QTableWidgetItem(pCRUDClientes->getPEstoque()->operator[](i)->getNome());
                ui->tableWidgetEstoque_3->setItem(ui->tableWidgetEstoque_3->rowCount() - 1,2,item);
                item->setTextAlignment(Qt::AlignCenter);

                item = new QTableWidgetItem(list[2]);
                ui->tableWidgetEstoque_3->setItem(ui->tableWidgetEstoque_3->rowCount() - 1,3,item);
                item->setTextAlignment(Qt::AlignCenter);
            }
        }
        ui->tableWidgetEstoque_3->setSortingEnabled(1);
    }
}

void MainWindow::on_comboBoxClientes_currentIndexChanged(int index)
{
    if(pCRUDClientes->getPEstoque()->getQuantidade() > 0 && ui->comboBoxClientes->count() > 0){
        index++;
        QString s = QString();
        for(int i = 1; i <= pCRUDClientes->getPEstoque()->operator[](index)->getPVendas()->getQuantidade(); i++){
            s += "<b>ID da Venda:</b> " + QString::number(pCRUDClientes->getPEstoque()->operator[](index)->getPVendas()->operator[](i)->getIdPedido()) + "<br>";
            for (int j = 1; j <= pCRUDClientes->getPEstoque()->operator[](index)->getPVendas()->operator[](i)->getPListaDeProdutos()->getQuantidade(); j++) {
                s += imprimirProduto(pCRUDClientes->getPEstoque()->operator[](index)->getPVendas()->operator[](i)->getPListaDeProdutos()->operator[](j));
            }
        }
        ui->textEdit->setText(s);
    }
}

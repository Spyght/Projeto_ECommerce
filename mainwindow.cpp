#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->QFrameEstoque->hide();
    ui->QFrameEstoque_2->hide();

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

    pCRUDProdutos = new mrjp::CRUDProdutos("estoque.txt");
    pCRUDProdutos->criarLista();

    pCRUDClientes = new mrjp::CRUDClientes("clientes.txt","vendas.txt");
    pCRUDClientes->criarLista();

    ui->tableWidgetEstoque->setSortingEnabled(0);
    ui->tableWidgetEstoque->setRowCount(0);
    for(int i = 1; i <= pCRUDClientes->getPEstoque()->getQuantidade(); i++){

        for(int j = 1; j <= pCRUDClientes->getPEstoque()->operator[](i)->getPVendas()->getQuantidade(); j++){

            QStringList list = QString::fromStdString(pCRUDClientes->desmontarVenda(pCRUDClientes->getPEstoque()->operator[](i)->getPVendas()->operator[](j))).split(';');

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
        }
    }
    ui->tableWidgetEstoque->setSortingEnabled(1);
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
//            delete pAux;
        }
    } catch (QString &erro) {
        QMessageBox::information(this,"Erro",erro);
    }
    ui->pushButtonMostrarLista->click();
    ui->QFrameEstoque->hide();
    clearTextEstoque();
    blockEstoqueEdit();
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
    freeEstoqueEdit2();
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

//bool MainWindow::isLabelsEmpty()
//{
//    if(ui->lineEditDescricaoEstoque->text() == "" or ui->spinBoxQtdeEstoque->value() == 0)
//    ui->spinBoxQtdeEstoque->clear();
//    ui->doubleSpinBoxPrecoUnitarioEstoque->clear();
//}


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
        if(ui->lineEditDescricaoEstoque_2->isReadOnly())
            pCRUDClientes->excluirElemento(ui->spinBoxCodEstoque_2->value());
        else {
            mrjp::Cliente * pAux = new mrjp::Cliente(ui->lineEditDescricaoEstoque_2->text(),
                                                     ui->lineEditEndereco->text(),ui->spinBoxCliente->value(),ui->lineEditCpf->text().toUInt());
            if(ui->spinBoxCodEstoque_2->value() == 0){
                pCRUDClientes->inserirNovoElemento(pAux);
//                QMessageBox::information(this,"Estoque Atualizado","Cliente Adicionado:\n" + pCRUDClientes->getPEstoque()->operator[](pCRUDClientes->getPEstoque()->getQuantidade())->print());
            }
            else
                pCRUDClientes->atualizarElemento(pAux, ui->spinBoxCodEstoque_2->value());
        }
    } catch (QString &erro) {
        QMessageBox::information(this,"Erro",erro);
    }
    ui->pushButtonMostrarLista_2->click();
    ui->QFrameEstoque_2->hide();
    clearTextEstoque2();
    blockEstoqueEdit2();
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
    if(index == 0) {
        ui->tableWidgetEstoque->setSortingEnabled(0);
        ui->tableWidgetEstoque->setRowCount(0);

        for(int i = 1; i <= pCRUDClientes->getPEstoque()->getQuantidade(); i++){

            for(int j = 1; j <= pCRUDClientes->getPEstoque()->operator[](i)->getPVendas()->getQuantidade(); j++){

                QStringList list = QString::fromStdString(pCRUDClientes->desmontarVenda(pCRUDClientes->getPEstoque()->operator[](i)->getPVendas()->operator[](j))).split(';');

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
            }
        }
        ui->tableWidgetEstoque->setSortingEnabled(1);
    }
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
    ui->pushButtonNovoPedido->setEnabled(0);
    ui->qGBPedido->show();
    ui->qGBOpcoes->show();
}

void MainWindow::on_tableWidgetEstoque_3_cellClicked(int , int )
{
    ui->qFrameVendas->hide();
}

void MainWindow::on_tableWidgetEstoque_3_cellDoubleClicked(int row, int column)
{

}

void MainWindow::on_pushButtonCancelarPedido_clicked()
{

}

void MainWindow::on_pushButtonConfirmarPedido_clicked()
{
    if(pListaDePedidos->getQuantidade() > 0){
        for (;;) {

        }(
    }
}

void MainWindow::on_pushButtonAdd_clicked()
{

}

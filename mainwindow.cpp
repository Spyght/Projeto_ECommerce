#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->qgbOpcoesEstoque->hide();
    ui->qgbAlterarEstoque->hide();
    ui->formFrame->hide();

    ui->tableWidgetEstoque->sortByColumn(0, Qt::SortOrder(0));
    ui->tableWidgetEstoque->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableWidgetEstoque->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    ui->tableWidgetEstoque->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tableWidgetEstoque->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);

    ui->tableWidgetEstoque->setSortingEnabled(0);
    ui->tableWidgetEstoque->setRowCount(0);

    pCRUDProdutos = new mrjp::CRUDProdutos("estoque.txt");
    pCRUDProdutos->criarLista();

    ui->tableWidgetEstoque->setSortingEnabled(0);
    ui->tableWidgetEstoque->setRowCount(0);

    for(int i = 1; i <= pCRUDProdutos->getPEstoque()->getQuantidade(); i++){

        QStringList list = QString::fromStdString(pCRUDProdutos->desmontar(pCRUDProdutos->getPEstoque()->operator[](i)->print())).split(';');

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
    ui->formFrame->show();
    ui->spinBoxCodEstoque->setValue(-1);
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
            if(ui->spinBoxCodEstoque->value() == -1){
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
    ui->qgbOpcoesEstoque->hide();
    ui->qgbAlterarEstoque->hide();
    ui->formFrame->hide();
    clearTextEstoque();
    blockEstoqueEdit();
}

void MainWindow::on_tableWidgetEstoque_cellDoubleClicked(int row, int column)
{
    ui->formFrame->show();
    ui->qgbAlterarEstoque->show();

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

void MainWindow::on_tableWidgetEstoque_cellClicked(int row, int column)
{
    ui->qgbOpcoesEstoque->hide();
    ui->qgbAlterarEstoque->hide();
    ui->formFrame->hide();
}

void MainWindow::on_pushButtonMostrarLista_clicked()
{
    ui->tableWidgetEstoque->setSortingEnabled(0);
    ui->tableWidgetEstoque->setRowCount(0);

    for(int i = 1; i <= pCRUDProdutos->getPEstoque()->getQuantidade(); i++){

        QStringList list = QString::fromStdString(pCRUDProdutos->desmontar(pCRUDProdutos->getPEstoque()->operator[](i)->print())).split(';');

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
    if(ui->spinBoxCodEstoque->value() == -1){
        ui->qgbOpcoesEstoque->hide();
        ui->qgbAlterarEstoque->hide();
        ui->formFrame->hide();
    } else {
        ui->qgbOpcoesEstoque->hide();
        ui->qgbAlterarEstoque->show();
    }
    blockEstoqueEdit();
}

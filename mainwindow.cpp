#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pCRUDProdutos = new mrjp::CRUDProdutos("estoque.txt");
    pCRUDProdutos->criarLista();
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


void MainWindow::on_pushButtonAddEstoque_clicked()
{
    clearTextEstoque();
}

void MainWindow::on_pushButtonConfirmar_clicked()
{
    mrjp::Produto * pAux = new mrjp::Produto(ui->lineEditDescricaoEstoque->text(),ui->spinBoxQtdeEstoque->value(),ui->doubleSpinBoxPrecoUnitarioEstoque->value());
    pCRUDProdutos->inserirNovoElemento(pAux);

}

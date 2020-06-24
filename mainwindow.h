#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include<crudprodutos.h>
#include<Produto.h>
#include<crudClientes.h>
#include<cliente.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void clearTextEstoque();
    void blockEstoqueEdit();
    void freeEstoqueEdit();
    void clearTextEstoque2();
    void blockEstoqueEdit2();
    void freeEstoqueEdit2();
    void printListProducts();

    QString imprimirProduto(mrjp::Produto *);
    int isLabelsEmpty1();
    int isLabelsEmpty2();

private slots:
    void on_pushButtonAddEstoque_clicked();

    void on_pushButtonConfirmar_clicked();

    void on_tableWidgetEstoque_cellDoubleClicked(int row, int column);

    void on_tableWidgetEstoque_cellClicked(int row, int column);

    void on_pushButtonMostrarLista_clicked();

    void on_pushButtonExcluirEstoque_clicked();

    void on_pushButtonEditarEstoque_clicked();

    void on_pushButtonCancelar_clicked();

    //Clientes
    void on_pushButtonAddEstoque_2_clicked();

    void on_pushButtonConfirmar_2_clicked();

    void on_tableWidgetEstoque_2_cellDoubleClicked(int row, int column);

    void on_tableWidgetEstoque_2_cellClicked(int row, int column);

    void on_pushButtonMostrarLista_2_clicked();

    void on_pushButtonExcluirEstoque_2_clicked();

    void on_pushButtonEditarEstoque_2_clicked();

    void on_pushButtonCancelar_2_clicked();


    void on_tabWidget_tabBarClicked(int index);

    void on_pushButtonAddEstoque_3_clicked();

    void on_pushButtonNovoPedido_clicked();

    void on_tableWidgetEstoque_3_cellClicked(int row, int column);

    void on_tableWidgetEstoque_3_cellDoubleClicked(int row, int column);

    void on_pushButtonCancelarPedido_clicked();

    void on_pushButtonConfirmarPedido_clicked();

    void on_pushButtonAdd_clicked();

    void on_pushButtonSub_clicked();

    void on_pushButtonMostrarLista_3_clicked();

    void on_textEdit_textChanged();

    void on_comboBoxClientes_activated(int index);

    void on_tabWidget_currentChanged(int index);

    void on_comboBoxClientes_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    mrjp::CRUDProdutos *pCRUDProdutos;

    mrjp::CRUDClientes *pCRUDClientes;

    jose::LDEC<mrjp::Produto *> * pListaDeProdutos;
    jose::LDEC<mrjp::Produto *> * pListaNovoEstoque;

    int row;
    int column;
//    mrjp::CRUD *pCRUD;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include<crudprodutos.h>
#include<Produto.h>

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

private slots:
    void on_pushButtonAddEstoque_clicked();

    void on_pushButtonConfirmar_clicked();

    void on_tableWidgetEstoque_cellDoubleClicked(int row, int column);

    void on_tableWidgetEstoque_cellClicked(int row, int column);

    void on_pushButtonMostrarLista_clicked();

    void on_pushButtonExcluirEstoque_clicked();

    void on_pushButtonEditarEstoque_clicked();

    void on_pushButtonCancelar_clicked();

private:
    Ui::MainWindow *ui;
    mrjp::CRUDProdutos *pCRUDProdutos;
//    mrjp::CRUD *pCRUD;
};
#endif // MAINWINDOW_H

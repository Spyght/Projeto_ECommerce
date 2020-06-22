#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<crud.h>
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

private slots:
    void on_pushButtonAddEstoque_clicked();

    void on_pushButtonConfirmar_clicked();

private:
    Ui::MainWindow *ui;
    mrjp::CRUDProdutos *pCRUDProdutos;
    mrjp::CRUD *pCRUD;
};
#endif // MAINWINDOW_H

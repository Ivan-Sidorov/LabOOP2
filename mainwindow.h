#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "hashtable.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_butDel_clicked();

    void on_butFind_clicked();

    void on_butAdd_clicked();

    void on_butTop_clicked();

    void on_butClear_clicked();

    void on_butOpen_clicked();

    void on_butSave_clicked();

    void on_butCnt_clicked();

private:
    Hashtable<string> coll;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int checkName(string name)
{
    int flag = 0;
    if(!name.size())
        return 0;
    for (int i = 0; i < name.size(); i++)
    {
        if (isdigit(name[i]))
            return 0;
        if(name[i] != ' ')
            flag = 1;
    }
    if(!flag)
        return 0;
    return 1;
}

void MainWindow::on_butDel_clicked() {
    char *curr = ui->listWidget_2->currentItem()->text().toLocal8Bit().data();
    string word(strchr(curr,' '),1, strchr(curr,'\n') - strchr(curr,' ') - 1);
    this->coll.delPlayer(word);
    ui->listWidget_2->takeItem(ui->listWidget_2->currentRow());
}

void MainWindow::on_butFind_clicked() {
    string word = ui->lineFind->text().toStdString();
    if (!checkName(word))
        QMessageBox::critical(this, "Find word", "Please, write correct data");
    else
        if (this->coll.inTable(word))
            QMessageBox::information(this, "Find word",
                                     "This word (" +
                                     QString::fromStdString(word) +
                                     ") is in dictionary with count " +
                                     QString::number(this->coll[word]));
        else
            QMessageBox::information(this, "Find word",
                                     "Sorry, but there is"
                                     " no such word in dictionary");
}

void MainWindow::on_butAdd_clicked() {
    if(!checkName(ui->lineAdd->text().toStdString()))
        QMessageBox::critical(this, "Add player", "Please, write correct data");
    else {
        if(!this->coll.inTable(ui->lineAdd->text().toStdString())) {
            this->coll << ui->lineAdd->text().toStdString();
            ui->listWidget_2->addItem("Word: " + ui->lineAdd->text() + "\nCount: " + QString::number(this->coll[ui->lineAdd->text().toStdString()]));
        }
        else {
            this->coll << ui->lineAdd->text().toStdString();
            int row = -1;
            for(int i = 0; i < ui->listWidget_2->count(); i++)
            {
                QListWidgetItem* item = ui->listWidget_2->item(i);
                char *str = (char *)item->text().toStdString().c_str();
                if(strstr(str, ui->lineAdd->text().toLocal8Bit().data())) {
                    row = i;
                    break;
                }
            }
            if(row != -1) {
               ui->listWidget_2->item(row)->setText("Word: " + ui->lineAdd->text() +
                                         "\nCount: " +
                                         QString::number(this->
                                         coll.getScore(ui->
                                         lineAdd->text().toStdString())));
                ui->listWidget_2->update();
            }
        }
    }
    ui->lineAdd->setText("");
}

void MainWindow::on_butTop_clicked() {
    tuple<string, string, string> top = coll.topPlayers();
    QString first = QString::fromStdString(get<0>(top));
    QString second = QString::fromStdString(get<1>(top));
    QString third = QString::fromStdString(get<2>(top));
    QMessageBox::information(this, "Top players", first + second + third);
}

void MainWindow::on_butClear_clicked() {
    coll.clear();
    ui->listWidget_2->clear();
}

void MainWindow::on_butOpen_clicked() {
    string name = ui->lineOpen->text().toStdString();
    if(name.size()) {
        this->coll.clear();
        this->coll.fromFile(name);
        for(auto &i: this->coll.get())
            for(auto &j: i)
                ui->listWidget_2->addItem("Word: " +
                                    QString::fromStdString(j.first) +
                                    "\nCount: " +
                                    QString::number(j.second));
    }
    QMessageBox::information(this, "Input data", "Opened successfully");
    ui->lineOpen->clear();
}

void MainWindow::on_butSave_clicked() {
    string name = ui->lineSave->text().toStdString();
    if(name.size())
        this->coll.toFile(name);
    QMessageBox::information(this, "Output data", "Saved successfully");
    ui->lineSave->clear();
}

void MainWindow::on_butCnt_clicked() {
    QMessageBox::information(this, "Size", "Number of players:  " + QString::number(this->coll.size()));
}

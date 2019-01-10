#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "savedialog.h"
#include <QCloseEvent>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->centralWidget);
    populateListItems();
}

MainWindow::~MainWindow()
{
    clearCache();
    delete ui;
}

void MainWindow::updateList(QString name)
{
    ui->listWidget->item(0)->setText(name);
}

void MainWindow::updateList(QListWidgetItem* item)
{
     ui->listWidget->removeItemWidget(item);
     int row = ui->listWidget->row(item);
     item = ui->listWidget->takeItem(row);
//     delete item;
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    QFile cache("D:\\daoai\\Notepad\\sys\\cache");
    if (!cache.exists() && ui->textEdit->toPlainText().size() == 0) {
        event->accept();
        return;
    }
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Exiting..",
                                                                tr("Do you wish to save?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn == QMessageBox::No) {
        event->accept();
    } else if (resBtn == QMessageBox::Cancel){
        event->ignore();
    } else if (resBtn == QMessageBox::Yes) {
        SaveDialog dialog(ui->textEdit->toPlainText());
//        dialog.setContent(ui->textEdit->toPlainText());
        dialog.setMain(this);
        dialog.exec();
        event->accept();
    }
}

void MainWindow::populateListItems()
{
    QDir dir("D:\\daoai\\Notepad\\saved");
    QFileInfoList list = dir.entryInfoList();
    for (int i = 2; i < list.size(); i++) {
        QFileInfo fileInfo = list.at(i);
        ui->listWidget->addItem(fileInfo.fileName());
    }
}

void MainWindow::updateListItems()
{

}

void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::update_textEdit_after_itemUpdate(QListWidgetItem *item)
{
    QListWidgetItem* curr = ui->listWidget->item(0);
    QString tmp;
    if (curr == item) {
        tmp = "D:\\daoai\\Notepad\\sys\\cache";
    } else {
        tmp = "D:\\daoai\\Notepad\\saved\\" + item->text();
    }
    QFile file(tmp);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    QListWidgetItem* curr = ui->listWidget->item(0);
    if (previous == nullptr) {
        return;
    }
    if (current == previous) {
        return;
    }
    // if previous is curr
    QString filename;
    if (previous == curr) {
        filename = "D:\\daoai\\Notepad\\sys\\cache";
    } else {
        filename = "D:\\daoai\\Notepad\\saved\\"+previous->text();
    }
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    QString tmp_output = ui->textEdit->toPlainText();
    out << tmp_output;
    file.close();
    if (previous == curr) {
        clearCache();
    }
    update_textEdit_after_itemUpdate(current);
}

void MainWindow::on_deleteItem_clicked()
{
    QList<QListWidgetItem*> list = ui->listWidget->selectedItems();
    for (QListWidgetItem* item : list) {
        deleteItem(item);
    }
}

void MainWindow::clearCache() {
    QFile file("D:\\daoai\\Notepad\\sys\\cache");
    file.remove();
}

void MainWindow::deleteItem(QListWidgetItem* item)
{
    if (ui->listWidget->item(0) == item) {
        item->setText("New File..");
        ui->textEdit->setText("");
        clearCache();
        return;
    }
    QString filename = item->text();
    updateList(item);
    QFile file("D:\\daoai\\Notepad\\saved\\"+filename);
    if (!file.remove()) {
        QMessageBox::warning(this, "Warning", "Cannot delete file: " + file.errorString());
        return;
    }
}

void MainWindow::on_saveItem_clicked()
{
    SaveDialog dialog(ui->textEdit->toPlainText());
    dialog.setMain(this);
    dialog.exec();
}

void MainWindow::on_newItem_clicked()
{
//    SaveDialog dialog(ui->textEdit->toPlainText());
//    dialog.setMain(this);
//    dialog.exec();
}

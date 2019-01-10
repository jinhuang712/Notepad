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
    QFile temp("D:\\daoai\\Notepad\\sys\\temp");
    temp.remove();
    delete ui;
}

void MainWindow::updateList(QString name)
{
    ui->listWidget->item(0)->setText(name);
}

void MainWindow::closeEvent (QCloseEvent *event)
{
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
    QListWidgetItem curr = *(ui->listWidget->item(0));
    ui->listWidget->clear();
    ui->listWidget->addItem(&curr);
    QDir dir("D:\\daoai\\Notepad\\saved");
    QFileInfoList list = dir.entryInfoList();
    for (int i = 2; i < list.size(); i++) {
        QFileInfo fileInfo = list.at(i);
        ui->listWidget->addItem(fileInfo.fileName());
    }
}

void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::on_actionSave_triggered()
{
    // attempt
    SaveDialog dialog(ui->textEdit->toPlainText());
    dialog.setMain(this);
    dialog.exec();
}

void MainWindow::on_bye_clicked()
{
    QString currentText = ui->textEdit->toPlainText();
    ui->textEdit->setText(currentText + "bye");
}

void MainWindow::itemUpdate_changeText(QListWidgetItem *item)
{
    QListWidgetItem* curr = ui->listWidget->item(0);
    QString tmp;
    if (curr == item) {
        tmp = "D:\\daoai\\Notepad\\sys\\temp";
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
        filename = "D:\\daoai\\Notepad\\sys\\temp";
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
    itemUpdate_changeText(current);
}

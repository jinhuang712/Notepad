#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "savedialog.h"

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

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open the File");
    QFile file(filename);
    currentFile = filename;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    // attempt
    SaveDialog dialog(this);
    dialog.setModal(true);
    dialog.setContent(ui->textEdit->toPlainText());
    dialog.exec();
    updateListItems();
}

void MainWindow::on_bye_clicked()
{
    QString currentText = ui->textEdit->toPlainText();
    ui->textEdit->setText(currentText + "bye");
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QListWidgetItem* curr = ui->listWidget->item(0);
    if (currItem) { // if current item is the first item
        if (item == curr) {
            // if current item is the first item and the first item is clicked
            return; // do nothing
        }
        QFile fileTmp("D:\\daoai\\Notepad\\sys\\temp");
        if (!fileTmp.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot save file: " + fileTmp.errorString());
            return;
        }
        QTextStream out(&fileTmp);
        QString tmp_output = ui->textEdit->toPlainText();
        out << tmp_output;
        fileTmp.close();
    }
    QString tmp;
    if (curr == item) {
        tmp = "D:\\daoai\\Notepad\\sys\\temp";
        currItem = true;
    } else {
        tmp = "D:\\daoai\\Notepad\\saved\\" + item->text();
        currItem = false;
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

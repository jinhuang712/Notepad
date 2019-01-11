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
    ui->listWidget->setCurrentRow(0);
    caches("");
}

MainWindow::~MainWindow()
{
    clearCache();
    delete this;
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    if (!checkCache()) {
        saves_file(ui->listWidget->currentItem());
        event->accept();
        return;
    }
    if (!shouldSaveCache())
        return;
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Exiting..",
                                                                tr("Do you wish to save?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn == QMessageBox::No) {
        event->accept();
    } else if (resBtn == QMessageBox::Cancel){
        event->ignore();
    } else if (resBtn == QMessageBox::Yes) {
        QString content;
        if (ui->listWidget->currentRow() == 0) {
            content = ui->textEdit->toPlainText();
        } else {
            content = getCache();
        }
        SaveDialog dialog(content, this);
        dialog.exec();
        event->accept();
    }
}

void MainWindow::populateListItems()
{
    QDir dir("D:\\daoai\\Notepad\\saved");
    QFileInfoList list = dir.entryInfoList();
    // todo: add sorting for last edited
    for (int i = 2; i < list.size(); i++) {
        QFileInfo fileInfo = list.at(i);
        ui->listWidget->addItem(fileInfo.fileName());
    }
}

/* cache functions */
void MainWindow::clearCache() {
    QFile file("D:\\daoai\\Notepad\\sys\\cache");
    file.remove();
}

bool MainWindow::checkCache()
{
    QFile file("D:\\daoai\\Notepad\\sys\\cache");
    return file.exists();
}

bool MainWindow::shouldSaveCache()
{
    if (!checkCache())
        return false;
    if (ui->listWidget->currentRow() == 0
            && ui->textEdit->toPlainText().size() == 0)
        return false;
    return true;
}

void MainWindow::caches(QString content)
{
    if (content.size() == 0) {
        clearCache();
    }
    QFile file("D:\\daoai\\Notepad\\sys\\cache");
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    out << content;
    file.close();
}

void MainWindow::delete_file(QListWidgetItem * item) {
    QString filename = item->text();
    ondelete_updateList(item);
    QFile file("D:\\daoai\\Notepad\\saved\\"+filename);
    if (!file.remove()) {
        QMessageBox::warning(this, "Warning", "Cannot delete file: " + file.errorString());
        return;
    }
}

QString MainWindow::getCache()
{
    QFile file("D:\\daoai\\Notepad\\sys\\cache");
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return "";
    }
    QTextStream in(&file);
    QString content = in.readAll();
    file.close();
    return content;
}

/* slots */
void MainWindow::on_deleteItem_clicked()
{
    QList<QListWidgetItem*> list = ui->listWidget->selectedItems();
    for (QListWidgetItem* item : list)
        deleteItem(item);
}

void MainWindow::on_saveItem_clicked()
{
    SaveDialog dialog(ui->textEdit->toPlainText(), this);
    dialog.exec();
}

void MainWindow::on_newItem_clicked()
{
    if (shouldSaveCache()) {
        QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Exiting..",
                                                                    tr("Do you wish to save?\n"),
                                                                    QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                    QMessageBox::Yes);
        if (resBtn == QMessageBox::No) {
            deleteItem(ui->listWidget->currentItem());
        } else if (resBtn == QMessageBox::Cancel){
            return;
        } else if (resBtn == QMessageBox::Yes) {
            QString content;
            if (ui->listWidget->currentRow() == 0) {
                content = ui->textEdit->toPlainText();
            } else {
                content = getCache();
            }
            SaveDialog dialog(content, this);
            dialog.exec();
            newItem();
        }
    } else if (!checkCache()){
        newItem();

    }
}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    qDebug() << "reached";
    if (previous == nullptr) {
        return;
    }
    if (current == previous) {
        return;
    }
    if (previous == ui->listWidget->item(0) && shouldSaveCache())
        caches(ui->textEdit->toPlainText());
    else if (!checkCache())
        saves_file(previous);
    update_textEdit_after_list(current);
}

/* helpers */

void MainWindow::newItem() {
    ui->listWidget->insertItem(0, "New File..");
    clearCache();
    caches("");
    ui->listWidget->setCurrentRow(0);
    ui->textEdit->setText("");
    ui->listWidget->repaint();
}

void MainWindow::deleteItem(QListWidgetItem* item)
{
    if (ui->listWidget->item(0) != item || !checkCache())
        delete_file(item);
    else {
        clearCache();
        caches("");
        ui->textEdit->setText("");
    }
}

void MainWindow::saves_file(QListWidgetItem* item)
{
    QString filename = item->text();
    QFile file("D:\\daoai\\Notepad\\saved\\"+filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    QString tmp_output = ui->textEdit->toPlainText();
    out << tmp_output;
    file.close();
}

void MainWindow::ondelete_updateList(QListWidgetItem* item)
{
    ui->listWidget->removeItemWidget(item);
    int row = ui->listWidget->row(item);
    item = ui->listWidget->takeItem(row);
    if (ui->listWidget->count() == 0) {
        newItem();
    }
//    delete item;
}

void MainWindow::updateListItems()
{

}

void MainWindow::updateCurr(QString name)
{
    ui->listWidget->item(0)->setText(name);
}

void MainWindow::update_textEdit_after_list(QListWidgetItem *item)
{
    QString tmp;
    if (ui->listWidget->item(0) == item && checkCache()) {
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



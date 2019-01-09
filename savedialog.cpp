#include "savedialog.h"
#include "ui_savedialog.h"
#include "mainwindow.h"

SaveDialog::SaveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveDialog)
{
    ui->setupUi(this);
}

SaveDialog::SaveDialog(MainWindow* mainwindow) :
    ui(new Ui::SaveDialog)
{
    ui->setupUi(this);
    this->mainwindow = mainwindow;
}

SaveDialog::~SaveDialog()
{
    delete ui;
}

void SaveDialog::setContent(QString cont)
{
    this->content = cont;
}

void SaveDialog::on_pushButton_clicked()
{
    // todo
    QString filename = "D:\\daoai\\Notepad\\saved\\" + ui->lineEdit->text();
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    out << content;
    file.close();
    this->close();
}

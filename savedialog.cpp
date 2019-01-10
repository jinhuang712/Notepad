#include "savedialog.h"
#include "ui_savedialog.h"
#include "mainwindow.h"
#include <QCloseEvent>

SaveDialog::SaveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveDialog)
{
    ui->setupUi(this);
}

SaveDialog::SaveDialog(QString content,
                       QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveDialog)
{
    ui->setupUi(this);
    this->content = content;
}

SaveDialog::~SaveDialog()
{
    delete ui;
}

void SaveDialog::setContent(QString cont)
{
    this->content = cont;
}

void SaveDialog::setMain(MainWindow *main) {
    this->main = main;
}

void SaveDialog::on_pushButton_clicked()
{
    QString filename = ui->lineEdit->text();
    QFile file( "D:\\daoai\\Notepad\\saved\\" + filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    out << content;
    file.close();
    this->main->updateList(filename);
    this->close();
}

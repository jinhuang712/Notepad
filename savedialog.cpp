#include "savedialog.h"
#include "ui_savedialog.h"
#include "mainwindow.h"
#include <QCloseEvent>

SaveDialog::SaveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveDialog)
{
    ui->setupUi(this);
    this->main = nullptr;
    caching = false;
}

SaveDialog::SaveDialog(QString content, MainWindow * main,
                       QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveDialog)
{
    ui->setupUi(this);
    this->main = main;
    this->content = content;
}

SaveDialog::~SaveDialog()
{
    delete ui;
}

void SaveDialog::setCaching()
{
    caching = true;
}

void SaveDialog::setContent(QString cont)
{
    this->content = cont;
}

void SaveDialog::setMain(MainWindow *main) {
    this->main = main;
}

// this process will
// - either save or not save the cache
// - then clears the cache
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
    this->main->updateCurr(filename);
    this->main->clearCache();
    this->close();
}

#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QMainWindow>
#include <QListWidgetItem>
#include "mainwindow.h"

namespace Ui {
class SaveDialog;
}

class SaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveDialog(QWidget *parent = nullptr);
    explicit SaveDialog(MainWindow* mainwindow);
    ~SaveDialog();
    void setContent(QString content);

private slots:
    void on_pushButton_clicked();

private:
    Ui::SaveDialog *ui;
    QString content;
    MainWindow* mainwindow;
};

#endif // SAVEDIALOG_H

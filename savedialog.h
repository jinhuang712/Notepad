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
    explicit SaveDialog(QString content, QWidget *parent = nullptr);
    ~SaveDialog();
    void setContent(QString content);
    void setMain(MainWindow *main);

private slots:
    void on_pushButton_clicked();

private:
    Ui::SaveDialog *ui;
    QString content;
    MainWindow* main;
};

#endif // SAVEDIALOG_H

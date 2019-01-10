#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QMainWindow>
#include <QListWidgetItem>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    Ui::MainWindow *ui;
    ~MainWindow();
    void updateList(QString name);


private slots:
    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void populateListItems();

    void updateListItems();

    void on_bye_clicked();

    void itemUpdate_changeText(QListWidgetItem *item);

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    QString currentFile = "";
    void closeEvent (QCloseEvent *event);
};

#endif // MAINWINDOW_H

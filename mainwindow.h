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
    void updateList(QListWidgetItem*);

private slots:
    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void populateListItems();

    void updateListItems();

    void itemUpdate_changeText(QListWidgetItem *item);

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_actionClear_triggered();

    void on_deleteItem_clicked();

    void deleteItem(QListWidgetItem* item);

private:
    QString currentFile = "";
    void closeEvent (QCloseEvent *event);
};

#endif // MAINWINDOW_H

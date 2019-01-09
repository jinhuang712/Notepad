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


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;

private slots:
    void on_actionOpen_triggered();

    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void populateListItems();

    void updateListItems();

    void on_bye_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    QString currentFile = "";
    bool currItem = true;
};

#endif // MAINWINDOW_H

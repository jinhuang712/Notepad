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

    void populateListItems();

    void updateListItems();

    void update_textEdit_after_itemUpdate(QListWidgetItem *item);

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_deleteItem_clicked();

    void deleteItem(QListWidgetItem* item);

    void clearCache();

    void on_saveItem_clicked();

    void on_newItem_clicked();

private:
    QString currentFile = "";
    void closeEvent (QCloseEvent *event);
};

#endif // MAINWINDOW_H

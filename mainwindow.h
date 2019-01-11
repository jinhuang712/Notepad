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

    void updateCurr(QString name);

    bool checkCache();

    void clearCache();

    bool shouldSaveCache();

    void caches(QString content);

    QString getCache();

    void saves_file(QListWidgetItem *);

    void delete_file(QListWidgetItem *);

private slots:

    void populateListItems();

    void updateListItems();

    void update_textEdit_after_list(QListWidgetItem *item);

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_deleteItem_clicked();

    void deleteItem(QListWidgetItem* item);

    void on_saveItem_clicked();

    void on_newItem_clicked();

private:
    QString currentFile = "";

    void closeEvent (QCloseEvent *event);

    void newItem();

    void ondelete_updateList(QListWidgetItem*);
};

#endif // MAINWINDOW_H

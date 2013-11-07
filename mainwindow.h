#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
   void on_pushButton_browseInputFiles_clicked();

    void on_pushButton_browseOutputFolder_clicked();

    void on_pushButton_login_clicked();




    void on_lineEdit_passWord_returnPressed();

    void on_lineEdit_userName_returnPressed();

    void on_pushButton_quit_clicked();

    void on_pushButton_fire_clicked();

    void on_lineEdit_OutputFolder_textEdited(const QString &arg1);

    void on_lineEdit_OutputFolder_returnPressed();

    void on_pushButton_browseKeyFile_clicked();

private:
    Ui::MainWindow *ui;
    bool fireButtonActivate();
};

#endif // MAINWINDOW_H

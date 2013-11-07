#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include<QString>
#include<QStringList>
#include<QMessageBox>
 #include <QFileInfo>
#include<QDir>
#include<QDebug>
#include<stdlib.h>


#include "encodeFunction.h"


#include<iostream>
#include<string>


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*
    ui->pushButton_browseInputFiles->setEnabled(0);
    ui->textBrowser_allName->setEnabled(0);
    ui->lineEdit_OutputFolder->setEnabled(0);
    ui->pushButton_browseOutputFolder->setEnabled(0);
    ui->pushButton_fire->setEnabled(0);
    */


}

MainWindow::~MainWindow()
{
    delete ui;
}




/* global varialbes here */
QStringList files;
QString toPath, secretFilePath;



/* functions here */

bool matchPassword(string usr, string pass)
{
    string correctUserName = "hasib";
    string correctPassWord = "google";

   if(usr==correctUserName && pass == correctPassWord)
       return true;
   else
       return false;
}

void showError(string title, string msg)
{
    QMessageBox message;
    message.setText(QString::fromStdString(msg));
    message.setWindowTitle(QString::fromStdString(title));
    message.exec();
}

bool MainWindow::fireButtonActivate()
{
    if(files.size() > 0)
    {
        if(toPath.size() != 0)
        {
            QDir dir;
            if(  dir.mkpath(toPath) )
            {
                return true;
            }
            else
            {
                showError("Error Output Folder", "Can't create or open output folder!");
            }
        }
        else
        {
            showError("Error", "Output Folder??");
        }
    }
    else
    {
        showError("Error", "No Input File(s) selected!!");
    }


    return false;

}


void MainWindow::on_pushButton_browseInputFiles_clicked()
{
        this->setCursor(Qt::WaitCursor);
        QString tmpPath = "";
        if(files.size() > 0)
        {
            QFileInfo fi(files[0]);
            tmpPath = fi.path();
        }
        files = QFileDialog::getOpenFileNames(
                    this,
                    "select one or more files to open",
                    tmpPath);

        QString names;

        for(int i=0; i<files.size(); i++)
        {
            names.push_back(files[i]);
            names.push_back("\n\n");
        }

        ui->textBrowser_allName->setText(names);

        this->setCursor(Qt::ArrowCursor);
}




void MainWindow::on_pushButton_browseOutputFolder_clicked()
{
    QString tmpPath;
    tmpPath = QFileDialog::getExistingDirectory (this, tr("Directory"), ui->lineEdit_OutputFolder->text(), QFileDialog::ShowDirsOnly);
    if(tmpPath.size() != 0)
    {

        toPath = tmpPath;
        ui->lineEdit_OutputFolder->setText(toPath);
    }
}

void MainWindow::on_pushButton_login_clicked()
{

    if(matchPassword(ui->lineEdit_userName->text().toStdString(), ui->lineEdit_passWord->text().toStdString()))
    {
        ui->pushButton_browseInputFiles->setEnabled(1);
        ui->textBrowser_allName->setEnabled(1);
        ui->lineEdit_OutputFolder->setEnabled(1);
        ui->pushButton_browseOutputFolder->setEnabled(1);
        ui->pushButton_fire->setEnabled(1);
        ui->pushButton_browseKeyFile->setEnabled(1);
    }
    else
    {
        showError("Login Failed", "Username or password mismathced!!");
    }
}



void MainWindow::on_lineEdit_passWord_returnPressed()
{
    this->on_pushButton_login_clicked();
}

void MainWindow::on_lineEdit_userName_returnPressed()
{
    this->on_pushButton_login_clicked();
}

void MainWindow::on_pushButton_quit_clicked()
{
    qApp->quit();
}

void MainWindow::on_pushButton_fire_clicked()
{
    if(fireButtonActivate())
    {

        /*
        int cnt = 0;
        this->setCursor(Qt::WaitCursor);
        string inFileName, outFileName, path;
        path = toPath.toStdString() + QDir::separator().toAscii();
        for(int i=0; i<files.size(); i++)
        {
                 files[i] = files[i].toUtf8();
                inFileName = files[i].toStdString();

                QFileInfo fi(files[i]);
                outFileName =path  + fi.fileName().toStdString();

               // int errorCode = encode(inFileName, outFileName);
                int errorCode = 0;
                if(errorCode == 1)
                {
                    showError("Error", "Can't open input file: "+inFileName);
                }
                else if(errorCode == 2)
                {
                    showError("Error","Can't open output file: "+outFileName);
                }
                else
                {
                    cnt++;
                }

        }


        showError("Successful!!", QString::number(cnt).toStdString() +  " file(s) out of " + QString::number(files.size()).toStdString() +  " file(s) successfully converted!!");
        this->setCursor(Qt::ArrowCursor);
        */


        int cnt = 0;
        this->setCursor(Qt::WaitCursor);
        QString qInFileName, qOutFileName, path;
        path = toPath + QDir::separator();

        for(int i=0; i<files.size(); i++)
        {
            QFileInfo fi(files[i]);
            qOutFileName = path + fi.fileName();
            qOutFileName = qOutFileName.toUtf8();
            qInFileName = files[i].toUtf8();
            secretFilePath = secretFilePath.toUtf8();

            string inFileName = qInFileName.toStdString();
            string outFileName = qOutFileName.toStdString();


            int errorCode = encode(inFileName, outFileName + ".converting", secretFilePath.toStdString());

            if(errorCode == 1)
            {
                showError("Error", "Can't open input file: "+inFileName);
            }
            else if(errorCode == 2)
            {
                showError("Error","Can't open output file: "+outFileName);
            }
            else if(errorCode == 3)
            {
                showError("Error", "Can't open secret key file.");
            }
            else
            {
                remove(outFileName.c_str());
                if( rename((outFileName+".converting").c_str(), outFileName.c_str()) == 0  )
                {//successfully removed
                    cnt++;
                }
                else
                {
                    showError("Error", "Can't rename and remove file!!! Permission Denied!!!");
                }

            }

        }

        showError("Successful!!", QString::number(cnt).toStdString() +  " file(s) out of " + QString::number(files.size()).toStdString() +  " file(s) successfully converted!!");
        this->setCursor(Qt::ArrowCursor);


     }
}

void MainWindow::on_lineEdit_OutputFolder_textEdited(const QString &arg1)
{
    toPath = ui->lineEdit_OutputFolder->text();
}

void MainWindow::on_lineEdit_OutputFolder_returnPressed()
{
    this->on_pushButton_browseOutputFolder_clicked();
}



void MainWindow::on_pushButton_browseKeyFile_clicked()
{
    QString tmpFileName = "";

    if(secretFilePath.size() != 0)
    {
        QFileInfo fi(secretFilePath);
        tmpFileName = fi.path();
    }



         tmpFileName =  QFileDialog::getOpenFileName(
                this,
                "select one or more files to open",
                tmpFileName);
    if(tmpFileName.size() != 0)
    {
        secretFilePath = tmpFileName;
        QFileInfo fi(secretFilePath);
        ui->label_keyFileName->setText(fi.fileName());
    }



}

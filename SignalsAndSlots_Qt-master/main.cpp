#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <exception>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //try{
        MainWindow w;
        w.setWindowTitle("Main Window");
        w.show();
   /* }catch(std::exception &e){
        QMessageBox msgBox;
        msgBox.setText("Exeption: "+QString( e.what()));
        //msgBox.setInformativeText("Do you want to save your changes?");
        //msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }*/

    return a.exec();
}

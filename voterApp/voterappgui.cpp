#include "voterappgui.h"
#include "ui_voterappgui.h"

#include <iostream>

voterAppGUI::voterAppGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::voterAppGUI)
{
    ui->setupUi(this);
    // Create the button, make "this" the parent
   // m_button = new QPushButton("Push me", this);
    // set size and location of the button
   // m_button->setGeometry(QRect(QPoint(100, 100),
    //QSize(200, 50)));

    // Connect button signal to appropriate slot
    //connect(m_button, SIGNAL (released()), this, SLOT (handleButton()));

}
/*void voterAppGUI::handleButton()
{
   // change the text
   m_button->setText("Yay you pushed me! Hello"); //link function for input data from
   // resize button
   m_button->resize(200,100);
   QString output("No info to display");
   voterAppGUI::on_textBrowser_textChanged();
}*/

voterAppGUI::~voterAppGUI()
{
    delete ui;
}

void voterAppGUI::on_textBrowser_textChanged()
{
    QString showme = "display this if lineEdit is linked"; // set return value as showme to display string of text to screen.
    ui->displayBox->setText(showme);
    //QMessageBox::about(this, "Title", showme);

}

void voterAppGUI::on_lineEdit_returnPressed()
{
    QString address = ui->lineEdit->text();
    //qStdOut << address;
   // ui->lineEdit->show();
    //ui->inputLine->displayText(address);
    //QMessageBox::about(this, "Title", address);
    voterAppGUI::on_textBrowser_textChanged();
}

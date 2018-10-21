#ifndef VOTERAPPGUI_H
#define VOTERAPPGUI_H

#include <QMessageBox>
#include <QTextStream>
#include <QMainWindow>
#include <QPushButton>
#include <QProcess>
#include <QString>
#include <QFile>
#include <QLabel>

namespace Ui {
class voterAppGUI;
}

class voterAppGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit voterAppGUI(QWidget *parent = nullptr);
    ~voterAppGUI();

private slots:
   void on_textBrowser_textChanged();
   void on_lineEdit_returnPressed();

private:
    Ui::voterAppGUI *ui;
};

#endif // VOTERAPPGUI_H

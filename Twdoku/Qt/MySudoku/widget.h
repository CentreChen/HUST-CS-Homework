#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent*);
private slots:
    void on_pushButton_clear_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_check_clicked();

    void on_pushButton_delete_error_clicked();

    void on_pushButton_center_clicked();

    void on_pushButton_answer_clicked();

private:
    Ui::Widget *ui;
};

class myQDialog : public QDialog{
public:
    int flag = 0;
    void makeFlagOne(){
        this->flag = 1;
        this->close();
    }
    void makeFlagTwo(){
        this->flag = 2;
        this->close();
    }
    void makeFlagThree(){
        this->flag = 3;
        this->close();
    }
    void makeFlagFour(){
        this->flag = 4;
        this->close();
    }
    void makeFlagFive(){
        this->flag = 5;
        this->close();
    }
};


#endif // WIDGET_H

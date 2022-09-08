
#include "widget.h"
#include "./ui_widget.h"
#include "Sudoku.h"
#include "QHeaderView"
#include "QDialog"
#include "QFontDialog"
#include "QMessageBox"
#include "QPainter"
using namespace std;

int sudoku1[9][9], sudoku2[9][9];
int answer1[9][9], answer2[9][9];
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    ui->setupUi(this);
    this->setWindowIcon(QPixmap("picture/sudoku.png"));
    this->setWindowTitle("Centre带你体验双数独");
    this->setStyleSheet("QWidget{background:rgb(227, 242, 253);}");
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->verticalHeader()->setVisible(false);

    ui->tableWidget->setStyleSheet("border:2px solid orange;");

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clear_clicked()
{
    ui->tableWidget->clearContents();
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            if(i < 9 and j < 9 and sudoku1[i][j] != 0)
            {
                QTableWidgetItem *temp1 = new QTableWidgetItem(QString::number(sudoku1[i][j]));
                ui->tableWidget->setItem(i, j, temp1);
                ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget->item(i,j)->setForeground(Qt::blue);
            }
            if(i >= 6 and j >= 6 and sudoku2[i - 6][j - 6] != 0)
            {
                QTableWidgetItem *temp2 = new QTableWidgetItem(QString::number(sudoku2[i - 6][j - 6]));
                ui->tableWidget->setItem(i,j,temp2);
                ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget->item(i,j)->setForeground(Qt::blue);
            }
        }
    }
}

void Widget::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap(pix);
    pix.load("picture/balloon.jpg");
    painter.drawPixmap(0,0,pix);
//    QPalette PAllbackground = this->palette();
//    QImage ImgAllbackground("picture/starsky.jpg");
//    QImage fitimgpic=ImgAllbackground.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
//    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
//    this->setPalette(PAllbackground);
}


void Widget::on_pushButton_start_clicked()
{
    int holeNums = 0;

    myQDialog *level = new myQDialog;
    level->resize(350,400);
    QPushButton *btn1 = new QPushButton;
    btn1->setText("简单");
    btn1->setParent(level);
    btn1->setGeometry(50,50,250,50);
    connect(btn1,&QPushButton::clicked, level, &myQDialog::makeFlagOne);
    QPushButton *btn2 = new QPushButton;
    btn2->setText("普通");
    btn2->setParent(level);
    btn2->setGeometry(50,110,250,50);
    connect(btn2,&QPushButton::clicked, level, &myQDialog::makeFlagTwo);
    QPushButton *btn3 = new QPushButton;
    btn3->setText("困难");
    btn3->setParent(level);
    btn3->setGeometry(50,170,250,50);
    connect(btn3,&QPushButton::clicked, level, &myQDialog::makeFlagThree);
    QPushButton *btn4 = new QPushButton;
    btn4->setText("噩梦");
    btn4->setParent(level);
    btn4->setGeometry(50,230,250,50);
    connect(btn4,&QPushButton::clicked, level, &myQDialog::makeFlagFour);
    QPushButton *btn5 = new QPushButton;
    btn5->setText("骨灰");
    btn5->setParent(level);
    btn5->setGeometry(50,300,250,50);
    connect(btn5,&QPushButton::clicked, level, &myQDialog::makeFlagFive);
    level->exec();
    srand((unsigned)time(nullptr));
    switch (level->flag) {
    case 1:
        holeNums = rand()%15 + 15;
        break;
    case 2:
        holeNums = rand()%10 + 50;
        break;
    case 3:
        holeNums = rand()%5 + 80;
        break;
    case 4:
        holeNums = rand()%3 + 105;
        break;
    case 5:
        holeNums = 119;
        break;
    }
    delete level;



    ui->tableWidget->clearContents();
    memset(sudoku1,0,sizeof(sudoku1));
    memset(sudoku2,0,sizeof(sudoku2));
    memset(answer1,0,sizeof(answer1));
    memset(answer2,0,sizeof(answer2));
    GenerateTwoSudoku(answer1,answer2);
//    if(flagGenerate == 1){
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                sudoku1[i][j] = answer1[i][j];
                sudoku2[i][j] = answer2[i][j];
            }
        }
        Dig(holeNums, sudoku1, sudoku2);
//        if(flagDig){
            for(int i = 0; i < 15; i++)
            {
                for(int j = 0; j < 15; j++)
                {
                    if(i < 9 and j < 9 and sudoku1[i][j] > 0)
                    {
                            QTableWidgetItem *temp1 = new QTableWidgetItem(QString::number(sudoku1[i][j]));
                            ui->tableWidget->setItem(i ,j ,temp1);
                            ui->tableWidget->item(i ,j )->setTextAlignment(Qt::AlignCenter);
                            ui->tableWidget->item(i,j)->setForeground(Qt::blue);
                    }
                    if(i >= 6 and j >= 6 and sudoku2[i-6][j-6] > 0)
                    {
                            QTableWidgetItem *temp2 = new QTableWidgetItem(QString::number(sudoku2[i - 6][j - 6]));
                            ui->tableWidget->setItem(i ,j ,temp2);
                            ui->tableWidget->item(i ,j )->setTextAlignment(Qt::AlignCenter);
                            ui->tableWidget->item(i,j)->setForeground(Qt::blue);
                    }
                }
            }
//        }
//    }
}


void Widget::on_pushButton_answer_clicked()
{
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            if(i < 9 and j < 9 )
            {
                QTableWidgetItem *temp1 = new QTableWidgetItem(QString::number(answer1[i][j]));
                ui->tableWidget->setItem(i ,j ,temp1);
                ui->tableWidget->item(i ,j )->setTextAlignment(Qt::AlignCenter);
                if(sudoku1[i][j] != 0)
                    ui->tableWidget->item(i,j)->setForeground(Qt::blue);
            }
            if(i >= 6 and j >= 6 )
            {
                QTableWidgetItem *temp2 = new QTableWidgetItem(QString::number(answer2[i - 6][j - 6]));
                ui->tableWidget->setItem(i ,j ,temp2);
                ui->tableWidget->item(i ,j )->setTextAlignment(Qt::AlignCenter);
                if(sudoku2[i-6][j-6] != 0)
                    ui->tableWidget->item(i,j)->setForeground(Qt::blue);
            }
        }
    }
}


void Widget::on_pushButton_check_clicked()
{
    int flag1 = 0, flag2 = 0;
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            if(i < 9 and j < 9)
            {
                if(ui->tableWidget->item(i ,j ) == nullptr)
                    flag2 = 1;
                else{
                    QString temp = ui->tableWidget->item(i , j )->text();
                    int temp_cnt = temp.toInt();
                    if(temp_cnt != answer1[i][j])
                        flag1 = 1;
                    else{
                        ui->tableWidget->item(i ,j )->setForeground(Qt::black);
                        ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignCenter);
                        if(sudoku1[i][j] != 0)
                            ui->tableWidget->item(i,j)->setForeground(Qt::blue);
                    }

                }
            }
            if(i >= 6 and j >= 6)
            {
                if(ui->tableWidget->item(i ,j ) == nullptr)
                    flag2 = 1;
                else{
                    QString temp = ui->tableWidget->item(i , j )->text();
                    int temp_cnt = temp.toInt();
                    if(temp_cnt != answer2[i - 6][j - 6])
                        flag1 = 1;
                    else{
                        ui->tableWidget->item(i ,j )->setForeground(Qt::black);
                        ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignCenter);
                        if(sudoku2[i-6][j-6] != 0)
                            ui->tableWidget->item(i,j)->setForeground(Qt::blue);
                    }
                }
            }
        }
    }
    if(flag1 == 0 && flag2 == 0)
    {
        QMessageBox message(QMessageBox::NoIcon, "Success!", "秀儿！");
        message.setIconPixmap(QPixmap("picture/good.png"));
        message.exec();
    }
    else if(flag1 == 1){
        int ret = QMessageBox::critical(NULL, "Fail!", "很遗憾，回答错误\n是否标记错误位置", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(ret == QMessageBox::Yes){
            for(int i = 0; i < 15; i++)
            {
                for(int j = 0; j < 15; j++)
                {
                    if(i < 9 and j < 9 and ui->tableWidget->item(i ,j ) != nullptr)
                    {
                        QString temp = ui->tableWidget->item(i , j )->text();
                        int temp_cnt = temp.toInt();
                        if(temp_cnt != answer1[i][j])
                        {
                            ui->tableWidget->item(i ,j )->setForeground(Qt::red);
                            ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignCenter);
                        }

                    }
                    if(i >= 6 and j >= 6 and ui->tableWidget->item(i ,j ) != nullptr)
                    {
                        QString temp = ui->tableWidget->item(i , j )->text();
                        int temp_cnt = temp.toInt();
                        if(temp_cnt != answer2[i - 6][j - 6])
                        {
                            ui->tableWidget->item(i ,j )->setForeground(Qt::red);
                            ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignCenter);
                        }
                    }
                }
            }
        }
    }
    else if(flag2 == 1){
        QMessageBox::about(this, tr("Sorry!"), tr("您的数独还未完成"));
    }
}


void Widget::on_pushButton_delete_error_clicked()
{
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            if(i < 9 and j < 9 and ui->tableWidget->item(i ,j ) != nullptr)
            {
                QString temp = ui->tableWidget->item(i , j )->text();
                int temp_cnt = temp.toInt();
                if(temp_cnt != answer1[i][j])
                    ui->tableWidget->takeItem(i , j );

            }
            if(i >= 6 and j >= 6 and ui->tableWidget->item(i ,j) != nullptr)
            {
                QString temp = ui->tableWidget->item(i , j )->text();
                int temp_cnt = temp.toInt();
                if(temp_cnt != answer2[i - 6][j - 6])
                    ui->tableWidget->takeItem(i , j );
            }
        }
    }
}


void Widget::on_pushButton_center_clicked()
{
    for(int i = 0; i < 15; i++)
        for(int j = 0; j < 15; j++){
            if(ui->tableWidget->item(i,j) != nullptr){
                ui->tableWidget->item(i,j)->setForeground(Qt::black);
                ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignCenter);
                if(i<9 and j<9 and sudoku1[i][j] != 0)
                    ui->tableWidget->item(i,j)->setForeground(Qt::blue);
                else if(i>=6 and j>=6 and sudoku2[i-6][j-6] != 0)
                    ui->tableWidget->item(i,j)->setForeground(Qt::blue);
            }
        }


}

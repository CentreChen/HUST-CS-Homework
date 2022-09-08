/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_start;
    QPushButton *pushButton_clear;
    QPushButton *pushButton_check;
    QPushButton *pushButton_delete_error;
    QPushButton *pushButton_center;
    QPushButton *pushButton_answer;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1354, 845);
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(150, 10, 861, 811));
        layoutWidget->setMaximumSize(QSize(941, 16777215));
        layoutWidget->setBaseSize(QSize(0, 0));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_start = new QPushButton(layoutWidget);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));
        pushButton_start->setMaximumSize(QSize(182, 16777215));
        pushButton_start->setBaseSize(QSize(0, 0));
        QFont font;
        font.setPointSize(20);
        pushButton_start->setFont(font);

        horizontalLayout_3->addWidget(pushButton_start);

        pushButton_clear = new QPushButton(layoutWidget);
        pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));
        pushButton_clear->setMaximumSize(QSize(151, 16777215));
        pushButton_clear->setBaseSize(QSize(0, 0));
        pushButton_clear->setFont(font);

        horizontalLayout_3->addWidget(pushButton_clear);

        pushButton_check = new QPushButton(layoutWidget);
        pushButton_check->setObjectName(QString::fromUtf8("pushButton_check"));
        pushButton_check->setMaximumSize(QSize(182, 16777215));
        pushButton_check->setBaseSize(QSize(0, 0));
        pushButton_check->setFont(font);

        horizontalLayout_3->addWidget(pushButton_check);

        pushButton_delete_error = new QPushButton(layoutWidget);
        pushButton_delete_error->setObjectName(QString::fromUtf8("pushButton_delete_error"));
        pushButton_delete_error->setMaximumSize(QSize(181, 16777215));
        pushButton_delete_error->setBaseSize(QSize(0, 0));
        pushButton_delete_error->setFont(font);

        horizontalLayout_3->addWidget(pushButton_delete_error);

        pushButton_center = new QPushButton(layoutWidget);
        pushButton_center->setObjectName(QString::fromUtf8("pushButton_center"));
        pushButton_center->setMaximumSize(QSize(182, 16777215));
        pushButton_center->setBaseSize(QSize(0, 0));
        pushButton_center->setFont(font);

        horizontalLayout_3->addWidget(pushButton_center);

        pushButton_answer = new QPushButton(layoutWidget);
        pushButton_answer->setObjectName(QString::fromUtf8("pushButton_answer"));
        pushButton_answer->setMaximumSize(QSize(176, 16777215));
        pushButton_answer->setBaseSize(QSize(0, 0));
        pushButton_answer->setFont(font);

        horizontalLayout_3->addWidget(pushButton_answer);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableWidget = new QTableWidget(layoutWidget);
        if (tableWidget->columnCount() < 15)
            tableWidget->setColumnCount(15);
        if (tableWidget->rowCount() < 15)
            tableWidget->setRowCount(15);
        QFont font1;
        font1.setUnderline(false);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font1);
        tableWidget->setItem(0, 0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(9, 0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(9, 1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(9, 2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(10, 0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(10, 1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(10, 2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(11, 0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(11, 1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(11, 2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(12, 0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        __qtablewidgetitem11->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(12, 1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        __qtablewidgetitem12->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(12, 2, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        __qtablewidgetitem13->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(13, 0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        __qtablewidgetitem14->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(13, 1, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        __qtablewidgetitem15->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(13, 2, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        __qtablewidgetitem16->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(14, 0, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        __qtablewidgetitem17->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(14, 1, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        __qtablewidgetitem18->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(14, 2, __qtablewidgetitem18);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setEnabled(true);
        tableWidget->setMaximumSize(QSize(933, 16777215));
        tableWidget->setBaseSize(QSize(0, 0));
        QFont font2;
        font2.setPointSize(15);
        tableWidget->setFont(font2);
        tableWidget->setAutoFillBackground(false);
        tableWidget->setGridStyle(Qt::SolidLine);
        tableWidget->setSortingEnabled(false);
        tableWidget->setRowCount(15);
        tableWidget->setColumnCount(15);
        tableWidget->horizontalHeader()->setDefaultSectionSize(57);
        tableWidget->verticalHeader()->setDefaultSectionSize(50);

        verticalLayout->addWidget(tableWidget);


        horizontalLayout->addLayout(verticalLayout);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        pushButton_start->setText(QApplication::translate("Widget", "\345\274\200\345\247\213", nullptr));
        pushButton_clear->setText(QApplication::translate("Widget", "\351\207\215\346\235\245", nullptr));
        pushButton_check->setText(QApplication::translate("Widget", "\346\243\200\346\237\245", nullptr));
        pushButton_delete_error->setText(QApplication::translate("Widget", "\346\270\205\351\231\244\351\224\231\350\257\257", nullptr));
        pushButton_center->setText(QApplication::translate("Widget", "\345\210\267\346\226\260", nullptr));
        pushButton_answer->setText(QApplication::translate("Widget", "\347\255\224\346\241\210", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        tableWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H

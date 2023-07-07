/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QChartView *pieChart;
    QChartView *BarUni;
    QChartView *BarEmi;
    QLabel *labelUni;
    QLabel *labelEmi;
    QTableWidget *uniView;
    QTableWidget *emiView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1600, 700);
        MainWindow->setMinimumSize(QSize(1600, 700));
        MainWindow->setMaximumSize(QSize(1600, 700));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pieChart = new QChartView(centralwidget);
        pieChart->setObjectName("pieChart");
        pieChart->setGeometry(QRect(600, 20, 400, 400));
        pieChart->setMinimumSize(QSize(400, 400));
        pieChart->setMaximumSize(QSize(400, 400));
        BarUni = new QChartView(centralwidget);
        BarUni->setObjectName("BarUni");
        BarUni->setGeometry(QRect(0, 440, 800, 200));
        BarUni->setMinimumSize(QSize(800, 200));
        BarUni->setMaximumSize(QSize(800, 200));
        BarEmi = new QChartView(centralwidget);
        BarEmi->setObjectName("BarEmi");
        BarEmi->setGeometry(QRect(800, 440, 800, 200));
        BarEmi->setMinimumSize(QSize(800, 200));
        BarEmi->setMaximumSize(QSize(800, 200));
        labelUni = new QLabel(centralwidget);
        labelUni->setObjectName("labelUni");
        labelUni->setGeometry(QRect(10, 10, 311, 41));
        labelEmi = new QLabel(centralwidget);
        labelEmi->setObjectName("labelEmi");
        labelEmi->setGeometry(QRect(1260, 10, 311, 41));
        uniView = new QTableWidget(centralwidget);
        uniView->setObjectName("uniView");
        uniView->setGeometry(QRect(10, 70, 330, 350));
        uniView->setMinimumSize(QSize(330, 350));
        uniView->setMaximumSize(QSize(330, 350));
        emiView = new QTableWidget(centralwidget);
        emiView->setObjectName("emiView");
        emiView->setGeometry(QRect(1260, 70, 330, 350));
        emiView->setMinimumSize(QSize(330, 350));
        emiView->setMaximumSize(QSize(350, 350));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1600, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        labelUni->setText(QCoreApplication::translate("MainWindow", "Universal", nullptr));
        labelEmi->setText(QCoreApplication::translate("MainWindow", "EMI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QListView *baseView;
    QListView *facesView;
    QLabel *label;
    QDoubleSpinBox *inputScF;
    QSpinBox *inputMinN;
    QSpinBox *inputMinSize;
    QPushButton *runVJ;
    QPushButton *delFace;
    QSpinBox *inputX;
    QSpinBox *inputY;
    QSpinBox *inputWidth;
    QSpinBox *inputHeight;
    QPushButton *addFace;
    QCheckBox *showPr;
    QPushButton *saveDescr;
    QPushButton *delDescr;
    QPushButton *renameAll;
    QLabel *labelDescr;
    QPushButton *delIm;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(700, 480);
        MainWindow->setMinimumSize(QSize(700, 480));
        MainWindow->setMaximumSize(QSize(10000, 10000));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        baseView = new QListView(centralWidget);
        baseView->setObjectName(QStringLiteral("baseView"));
        baseView->setGeometry(QRect(10, 10, 130, 171));
        facesView = new QListView(centralWidget);
        facesView->setObjectName(QStringLiteral("facesView"));
        facesView->setGeometry(QRect(10, 200, 130, 101));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(250, 10, 301, 231));
        inputScF = new QDoubleSpinBox(centralWidget);
        inputScF->setObjectName(QStringLiteral("inputScF"));
        inputScF->setGeometry(QRect(10, 310, 45, 22));
        inputScF->setMinimum(1.01);
        inputScF->setSingleStep(0.01);
        inputScF->setValue(1.05);
        inputMinN = new QSpinBox(centralWidget);
        inputMinN->setObjectName(QStringLiteral("inputMinN"));
        inputMinN->setGeometry(QRect(60, 310, 35, 22));
        inputMinN->setValue(3);
        inputMinSize = new QSpinBox(centralWidget);
        inputMinSize->setObjectName(QStringLiteral("inputMinSize"));
        inputMinSize->setGeometry(QRect(100, 310, 40, 22));
        inputMinSize->setSingleStep(5);
        runVJ = new QPushButton(centralWidget);
        runVJ->setObjectName(QStringLiteral("runVJ"));
        runVJ->setEnabled(true);
        runVJ->setGeometry(QRect(10, 340, 131, 23));
        delFace = new QPushButton(centralWidget);
        delFace->setObjectName(QStringLiteral("delFace"));
        delFace->setGeometry(QRect(10, 370, 131, 23));
        inputX = new QSpinBox(centralWidget);
        inputX->setObjectName(QStringLiteral("inputX"));
        inputX->setGeometry(QRect(150, 10, 42, 22));
        inputX->setMaximum(10000);
        inputX->setValue(100);
        inputY = new QSpinBox(centralWidget);
        inputY->setObjectName(QStringLiteral("inputY"));
        inputY->setGeometry(QRect(200, 10, 42, 22));
        inputY->setMaximum(10000);
        inputY->setValue(100);
        inputWidth = new QSpinBox(centralWidget);
        inputWidth->setObjectName(QStringLiteral("inputWidth"));
        inputWidth->setGeometry(QRect(150, 40, 42, 22));
        inputWidth->setMaximum(500);
        inputHeight = new QSpinBox(centralWidget);
        inputHeight->setObjectName(QStringLiteral("inputHeight"));
        inputHeight->setGeometry(QRect(200, 40, 42, 22));
        inputHeight->setMaximum(500);
        addFace = new QPushButton(centralWidget);
        addFace->setObjectName(QStringLiteral("addFace"));
        addFace->setGeometry(QRect(150, 90, 91, 23));
        showPr = new QCheckBox(centralWidget);
        showPr->setObjectName(QStringLiteral("showPr"));
        showPr->setGeometry(QRect(150, 70, 91, 17));
        saveDescr = new QPushButton(centralWidget);
        saveDescr->setObjectName(QStringLiteral("saveDescr"));
        saveDescr->setGeometry(QRect(150, 120, 91, 23));
        delDescr = new QPushButton(centralWidget);
        delDescr->setObjectName(QStringLiteral("delDescr"));
        delDescr->setGeometry(QRect(150, 150, 91, 21));
        renameAll = new QPushButton(centralWidget);
        renameAll->setObjectName(QStringLiteral("renameAll"));
        renameAll->setGeometry(QRect(150, 180, 91, 23));
        labelDescr = new QLabel(centralWidget);
        labelDescr->setObjectName(QStringLiteral("labelDescr"));
        labelDescr->setGeometry(QRect(150, 240, 91, 16));
        delIm = new QPushButton(centralWidget);
        delIm->setObjectName(QStringLiteral("delIm"));
        delIm->setGeometry(QRect(150, 210, 91, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 700, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label->setText(QString());
        runVJ->setText(QApplication::translate("MainWindow", "Run Viola-Jones", 0));
        delFace->setText(QApplication::translate("MainWindow", "Delete selected face", 0));
        addFace->setText(QApplication::translate("MainWindow", "Add face", 0));
        showPr->setText(QApplication::translate("MainWindow", "Show preview", 0));
        saveDescr->setText(QApplication::translate("MainWindow", "Save description", 0));
        delDescr->setText(QApplication::translate("MainWindow", "Delete descript", 0));
        renameAll->setText(QApplication::translate("MainWindow", "Rename all", 0));
        labelDescr->setText(QString());
        delIm->setText(QApplication::translate("MainWindow", "Delete image", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCarica;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTextEdit *txtVisualizza;
    QTableWidget *tabella;
    QHBoxLayout *grafico;
    QPushButton *btnAnalizza;
    QMenuBar *menubar;
    QMenu *menuMenu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(782, 635);
        actionCarica = new QAction(MainWindow);
        actionCarica->setObjectName(QString::fromUtf8("actionCarica"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        txtVisualizza = new QTextEdit(centralwidget);
        txtVisualizza->setObjectName(QString::fromUtf8("txtVisualizza"));

        gridLayout->addWidget(txtVisualizza, 0, 0, 1, 1);

        tabella = new QTableWidget(centralwidget);
        if (tabella->columnCount() < 1)
            tabella->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tabella->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tabella->rowCount() < 5)
            tabella->setRowCount(5);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tabella->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tabella->setVerticalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tabella->setVerticalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tabella->setVerticalHeaderItem(3, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tabella->setVerticalHeaderItem(4, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tabella->setItem(1, 0, __qtablewidgetitem6);
        tabella->setObjectName(QString::fromUtf8("tabella"));
        tabella->setEditTriggers(QAbstractItemView::NoEditTriggers);

        gridLayout->addWidget(tabella, 1, 0, 1, 1);

        grafico = new QHBoxLayout();
        grafico->setObjectName(QString::fromUtf8("grafico"));
        grafico->setSizeConstraint(QLayout::SetDefaultConstraint);

        gridLayout->addLayout(grafico, 1, 1, 1, 1);

        btnAnalizza = new QPushButton(centralwidget);
        btnAnalizza->setObjectName(QString::fromUtf8("btnAnalizza"));

        gridLayout->addWidget(btnAnalizza, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 782, 25));
        menuMenu = new QMenu(menubar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionCarica);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionCarica->setText(QCoreApplication::translate("MainWindow", "Carica", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tabella->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Dati", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tabella->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Caratteri", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tabella->verticalHeaderItem(1);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Caratteri (senza spazi)", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tabella->verticalHeaderItem(2);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Parole", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tabella->verticalHeaderItem(3);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Frasi", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tabella->verticalHeaderItem(4);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Paragrafi", nullptr));

        const bool __sortingEnabled = tabella->isSortingEnabled();
        tabella->setSortingEnabled(false);
        tabella->setSortingEnabled(__sortingEnabled);

        btnAnalizza->setText(QCoreApplication::translate("MainWindow", "Analizza", nullptr));
        menuMenu->setTitle(QCoreApplication::translate("MainWindow", "Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

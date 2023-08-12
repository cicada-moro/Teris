/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <gameview.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    gameview *panel;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *next;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *score;
    QLabel *level;
    QLabel *time;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *start;
    QPushButton *restart;
    QPushButton *pause;
    QGroupBox *groupBox_4;
    QCheckBox *music;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        panel = new gameview(centralwidget);
        panel->setObjectName(QString::fromUtf8("panel"));

        horizontalLayout->addWidget(panel);

        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::WinPanel);
        frame->setFrameShadow(QFrame::Sunken);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFlat(false);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        next = new QLabel(frame);
        next->setObjectName(QString::fromUtf8("next"));

        verticalLayout->addWidget(next);

        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        score = new QLabel(groupBox_2);
        score->setObjectName(QString::fromUtf8("score"));

        gridLayout_2->addWidget(score, 0, 0, 1, 1);

        level = new QLabel(groupBox_2);
        level->setObjectName(QString::fromUtf8("level"));

        gridLayout_2->addWidget(level, 1, 0, 1, 1);

        time = new QLabel(groupBox_2);
        time->setObjectName(QString::fromUtf8("time"));

        gridLayout_2->addWidget(time, 2, 0, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(frame);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        start = new QPushButton(groupBox_3);
        start->setObjectName(QString::fromUtf8("start"));

        horizontalLayout_2->addWidget(start);

        restart = new QPushButton(groupBox_3);
        restart->setObjectName(QString::fromUtf8("restart"));
        restart->setEnabled(false);

        horizontalLayout_2->addWidget(restart);

        pause = new QPushButton(groupBox_3);
        pause->setObjectName(QString::fromUtf8("pause"));
        pause->setEnabled(false);

        horizontalLayout_2->addWidget(pause);


        verticalLayout->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(frame);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        music = new QCheckBox(groupBox_4);
        music->setObjectName(QString::fromUtf8("music"));
        music->setGeometry(QRect(10, 0, 359, 23));

        verticalLayout->addWidget(groupBox_4);


        horizontalLayout->addWidget(frame);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\346\223\215\344\275\234\346\226\271\345\274\217\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\347\251\272\346\240\274\351\224\256\357\274\232\347\247\273\345\210\260\345\272\225", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\344\270\212\351\224\256\357\274\232\345\217\230\345\275\242", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\267\246\345\217\263\344\270\213\351\224\256\357\274\232\347\247\273\344\270\200\346\240\274", nullptr));
        next->setText(QCoreApplication::translate("MainWindow", "\344\270\213\344\270\200\344\270\252\357\274\232", nullptr));
        groupBox_2->setTitle(QString());
        score->setText(QCoreApplication::translate("MainWindow", "\345\276\227\345\210\206\357\274\232", nullptr));
        level->setText(QCoreApplication::translate("MainWindow", "\345\205\263\345\215\241\357\274\232", nullptr));
        time->setText(QCoreApplication::translate("MainWindow", "\350\256\241\346\227\266\357\274\232", nullptr));
        groupBox_3->setTitle(QString());
        start->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        restart->setText(QCoreApplication::translate("MainWindow", "\351\207\215\346\226\260\345\274\200\345\247\213", nullptr));
        pause->setText(QCoreApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
        groupBox_4->setTitle(QString());
        music->setText(QCoreApplication::translate("MainWindow", "\351\237\263\344\271\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

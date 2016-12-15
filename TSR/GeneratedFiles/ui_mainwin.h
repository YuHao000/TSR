/********************************************************************************
** Form generated from reading UI file 'mainwin.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIN_H
#define UI_MAINWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ImageViewer.h"

QT_BEGIN_NAMESPACE

class Ui_MainWinClass
{
public:
    QAction *actionQuit;
    QAction *actionOpenImg;
    QAction *actionOpenVideo;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    ImageViewer *PicArea;
    QVBoxLayout *verticalLayout;
    QGroupBox *VideoControlBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnPlay;
    QPushButton *btnPrevious;
    QPushButton *btnNext;
    QSlider *ProgressBar;
    QSlider *conScroll;
    QLabel *label;
    QWidget *widget;
    QMenuBar *menuBar;
    QMenu *mainMenu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWinClass)
    {
        if (MainWinClass->objectName().isEmpty())
            MainWinClass->setObjectName(QStringLiteral("MainWinClass"));
        MainWinClass->resize(1062, 736);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWinClass->sizePolicy().hasHeightForWidth());
        MainWinClass->setSizePolicy(sizePolicy);
        MainWinClass->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        MainWinClass->setFont(font);
        actionQuit = new QAction(MainWinClass);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(9);
        actionQuit->setFont(font1);
        actionOpenImg = new QAction(MainWinClass);
        actionOpenImg->setObjectName(QStringLiteral("actionOpenImg"));
        actionOpenImg->setFont(font);
        actionOpenVideo = new QAction(MainWinClass);
        actionOpenVideo->setObjectName(QStringLiteral("actionOpenVideo"));
        centralWidget = new QWidget(MainWinClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        PicArea = new ImageViewer(centralWidget);
        PicArea->setObjectName(QStringLiteral("PicArea"));
        sizePolicy.setHeightForWidth(PicArea->sizePolicy().hasHeightForWidth());
        PicArea->setSizePolicy(sizePolicy);

        gridLayout->addWidget(PicArea, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        VideoControlBox = new QGroupBox(centralWidget);
        VideoControlBox->setObjectName(QStringLiteral("VideoControlBox"));
        VideoControlBox->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(VideoControlBox->sizePolicy().hasHeightForWidth());
        VideoControlBox->setSizePolicy(sizePolicy1);
        VideoControlBox->setMinimumSize(QSize(250, 110));
        VideoControlBox->setMaximumSize(QSize(250, 110));
        VideoControlBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        verticalLayout_2 = new QVBoxLayout(VideoControlBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(11, 5, -1, 5);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnPlay = new QPushButton(VideoControlBox);
        btnPlay->setObjectName(QStringLiteral("btnPlay"));

        horizontalLayout->addWidget(btnPlay);

        btnPrevious = new QPushButton(VideoControlBox);
        btnPrevious->setObjectName(QStringLiteral("btnPrevious"));

        horizontalLayout->addWidget(btnPrevious);

        btnNext = new QPushButton(VideoControlBox);
        btnNext->setObjectName(QStringLiteral("btnNext"));

        horizontalLayout->addWidget(btnNext);


        verticalLayout_2->addLayout(horizontalLayout);

        ProgressBar = new QSlider(VideoControlBox);
        ProgressBar->setObjectName(QStringLiteral("ProgressBar"));
        ProgressBar->setMinimum(0);
        ProgressBar->setMaximum(100);
        ProgressBar->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(ProgressBar);


        verticalLayout->addWidget(VideoControlBox);

        conScroll = new QSlider(centralWidget);
        conScroll->setObjectName(QStringLiteral("conScroll"));
        sizePolicy1.setHeightForWidth(conScroll->sizePolicy().hasHeightForWidth());
        conScroll->setSizePolicy(sizePolicy1);
        conScroll->setMinimumSize(QSize(250, 30));
        conScroll->setMaximumSize(QSize(250, 30));
        conScroll->setMinimum(1);
        conScroll->setMaximum(50);
        conScroll->setSingleStep(1);
        conScroll->setValue(1);
        conScroll->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(conScroll);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout->addWidget(label);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));

        verticalLayout->addWidget(widget);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        MainWinClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWinClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1062, 26));
        mainMenu = new QMenu(menuBar);
        mainMenu->setObjectName(QStringLiteral("mainMenu"));
        mainMenu->setFont(font);
        MainWinClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWinClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWinClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWinClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWinClass->setStatusBar(statusBar);

        menuBar->addAction(mainMenu->menuAction());
        mainMenu->addAction(actionOpenImg);
        mainMenu->addAction(actionOpenVideo);
        mainMenu->addSeparator();
        mainMenu->addAction(actionQuit);

        retranslateUi(MainWinClass);
        QObject::connect(actionQuit, SIGNAL(triggered()), MainWinClass, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWinClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWinClass)
    {
        MainWinClass->setWindowTitle(QApplication::translate("MainWinClass", "\344\272\244\351\200\232\346\240\207\345\277\227\350\257\206\345\210\253\347\263\273\347\273\237", 0));
        actionQuit->setText(QApplication::translate("MainWinClass", "\351\200\200\345\207\272", 0));
        actionOpenImg->setText(QApplication::translate("MainWinClass", "\346\211\223\345\274\200\345\233\276\347\211\207", 0));
        actionOpenVideo->setText(QApplication::translate("MainWinClass", "\346\211\223\345\274\200\350\247\206\351\242\221", 0));
        VideoControlBox->setTitle(QApplication::translate("MainWinClass", "\350\247\206\351\242\221\346\216\247\345\210\266", 0));
        btnPlay->setText(QApplication::translate("MainWinClass", "\346\222\255\346\224\276", 0));
        btnPrevious->setText(QApplication::translate("MainWinClass", "\344\270\212\344\270\200\345\270\247", 0));
        btnNext->setText(QApplication::translate("MainWinClass", "\344\270\213\344\270\200\345\270\247", 0));
        label->setText(QApplication::translate("MainWinClass", "TextLabel", 0));
        mainMenu->setTitle(QApplication::translate("MainWinClass", "\346\226\207\344\273\266", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWinClass: public Ui_MainWinClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIN_H

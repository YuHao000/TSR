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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
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
    QAction *actionResend;
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
    QToolBox *toolBox;
    QWidget *page;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *boxDetectArea;
    QFormLayout *formLayout;
    QLabel *label_2;
    QDoubleSpinBox *edtDetectTop;
    QLabel *label_3;
    QDoubleSpinBox *edtDetectSide;
    QLabel *label_4;
    QDoubleSpinBox *edtDetectBottom;
    QLabel *label_5;
    QComboBox *comboDetectDiv;
    QGroupBox *boxEnhance;
    QFormLayout *formLayout_2;
    QLabel *label_6;
    QSlider *sliderSatur;
    QCheckBox *checkHistogram;
    QGroupBox *boxGrayscale;
    QFormLayout *formLayout_3;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QWidget *widget;
    QWidget *page_3;
    QWidget *page_2;
    QMenuBar *menuBar;
    QMenu *mainMenu;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWinClass)
    {
        if (MainWinClass->objectName().isEmpty())
            MainWinClass->setObjectName(QStringLiteral("MainWinClass"));
        MainWinClass->resize(443, 773);
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
        actionResend = new QAction(MainWinClass);
        actionResend->setObjectName(QStringLiteral("actionResend"));
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

        toolBox = new QToolBox(centralWidget);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(toolBox->sizePolicy().hasHeightForWidth());
        toolBox->setSizePolicy(sizePolicy2);
        toolBox->setMinimumSize(QSize(250, 0));
        toolBox->setMaximumSize(QSize(250, 16777215));
        toolBox->setFrameShape(QFrame::StyledPanel);
        toolBox->setFrameShadow(QFrame::Sunken);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, -30, 234, 423));
        verticalLayout_3 = new QVBoxLayout(page);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, 7, -1, -1);
        boxDetectArea = new QGroupBox(page);
        boxDetectArea->setObjectName(QStringLiteral("boxDetectArea"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(boxDetectArea->sizePolicy().hasHeightForWidth());
        boxDetectArea->setSizePolicy(sizePolicy3);
        boxDetectArea->setMinimumSize(QSize(0, 0));
        boxDetectArea->setMaximumSize(QSize(16777215, 16777215));
        boxDetectArea->setCheckable(true);
        formLayout = new QFormLayout(boxDetectArea);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setHorizontalSpacing(11);
        formLayout->setContentsMargins(-1, 7, -1, -1);
        label_2 = new QLabel(boxDetectArea);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        edtDetectTop = new QDoubleSpinBox(boxDetectArea);
        edtDetectTop->setObjectName(QStringLiteral("edtDetectTop"));
        sizePolicy1.setHeightForWidth(edtDetectTop->sizePolicy().hasHeightForWidth());
        edtDetectTop->setSizePolicy(sizePolicy1);
        edtDetectTop->setMinimumSize(QSize(70, 30));
        edtDetectTop->setMaximumSize(QSize(70, 30));
        edtDetectTop->setMaximum(1);
        edtDetectTop->setSingleStep(0.01);

        formLayout->setWidget(0, QFormLayout::FieldRole, edtDetectTop);

        label_3 = new QLabel(boxDetectArea);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        edtDetectSide = new QDoubleSpinBox(boxDetectArea);
        edtDetectSide->setObjectName(QStringLiteral("edtDetectSide"));
        sizePolicy1.setHeightForWidth(edtDetectSide->sizePolicy().hasHeightForWidth());
        edtDetectSide->setSizePolicy(sizePolicy1);
        edtDetectSide->setMinimumSize(QSize(70, 30));
        edtDetectSide->setMaximumSize(QSize(70, 30));
        edtDetectSide->setMaximum(1);
        edtDetectSide->setSingleStep(0.01);

        formLayout->setWidget(1, QFormLayout::FieldRole, edtDetectSide);

        label_4 = new QLabel(boxDetectArea);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        edtDetectBottom = new QDoubleSpinBox(boxDetectArea);
        edtDetectBottom->setObjectName(QStringLiteral("edtDetectBottom"));
        sizePolicy1.setHeightForWidth(edtDetectBottom->sizePolicy().hasHeightForWidth());
        edtDetectBottom->setSizePolicy(sizePolicy1);
        edtDetectBottom->setMinimumSize(QSize(70, 30));
        edtDetectBottom->setMaximumSize(QSize(70, 30));
        edtDetectBottom->setMaximum(1);
        edtDetectBottom->setSingleStep(0.01);

        formLayout->setWidget(2, QFormLayout::FieldRole, edtDetectBottom);

        label_5 = new QLabel(boxDetectArea);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_5);

        comboDetectDiv = new QComboBox(boxDetectArea);
        comboDetectDiv->setObjectName(QStringLiteral("comboDetectDiv"));
        sizePolicy1.setHeightForWidth(comboDetectDiv->sizePolicy().hasHeightForWidth());
        comboDetectDiv->setSizePolicy(sizePolicy1);
        comboDetectDiv->setMinimumSize(QSize(70, 30));
        comboDetectDiv->setMaximumSize(QSize(70, 30));

        formLayout->setWidget(3, QFormLayout::FieldRole, comboDetectDiv);


        verticalLayout_3->addWidget(boxDetectArea);

        boxEnhance = new QGroupBox(page);
        boxEnhance->setObjectName(QStringLiteral("boxEnhance"));
        sizePolicy3.setHeightForWidth(boxEnhance->sizePolicy().hasHeightForWidth());
        boxEnhance->setSizePolicy(sizePolicy3);
        boxEnhance->setCheckable(true);
        formLayout_2 = new QFormLayout(boxEnhance);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setContentsMargins(-1, 7, -1, -1);
        label_6 = new QLabel(boxEnhance);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_6);

        sliderSatur = new QSlider(boxEnhance);
        sliderSatur->setObjectName(QStringLiteral("sliderSatur"));
        sliderSatur->setMinimum(100);
        sliderSatur->setMaximum(1000);
        sliderSatur->setPageStep(50);
        sliderSatur->setOrientation(Qt::Horizontal);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, sliderSatur);

        checkHistogram = new QCheckBox(boxEnhance);
        checkHistogram->setObjectName(QStringLiteral("checkHistogram"));
        sizePolicy3.setHeightForWidth(checkHistogram->sizePolicy().hasHeightForWidth());
        checkHistogram->setSizePolicy(sizePolicy3);
        checkHistogram->setMinimumSize(QSize(0, 0));
        checkHistogram->setMaximumSize(QSize(1111111, 1111111));

        formLayout_2->setWidget(1, QFormLayout::SpanningRole, checkHistogram);


        verticalLayout_3->addWidget(boxEnhance);

        boxGrayscale = new QGroupBox(page);
        boxGrayscale->setObjectName(QStringLiteral("boxGrayscale"));
        sizePolicy3.setHeightForWidth(boxGrayscale->sizePolicy().hasHeightForWidth());
        boxGrayscale->setSizePolicy(sizePolicy3);
        boxGrayscale->setMinimumSize(QSize(0, 100));
        boxGrayscale->setCheckable(true);
        formLayout_3 = new QFormLayout(boxGrayscale);
        formLayout_3->setSpacing(6);
        formLayout_3->setContentsMargins(11, 11, 11, 11);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        formLayout_3->setContentsMargins(-1, 7, -1, -1);
        radioButton = new QRadioButton(boxGrayscale);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setMinimumSize(QSize(0, 30));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, radioButton);

        radioButton_2 = new QRadioButton(boxGrayscale);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setMinimumSize(QSize(0, 30));
        radioButton_2->setChecked(true);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, radioButton_2);

        radioButton_3 = new QRadioButton(boxGrayscale);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setMinimumSize(QSize(0, 30));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, radioButton_3);

        radioButton_4 = new QRadioButton(boxGrayscale);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setMinimumSize(QSize(0, 30));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, radioButton_4);

        radioButton_5 = new QRadioButton(boxGrayscale);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));
        radioButton_5->setMinimumSize(QSize(0, 30));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, radioButton_5);


        verticalLayout_3->addWidget(boxGrayscale);

        widget = new QWidget(page);
        widget->setObjectName(QStringLiteral("widget"));

        verticalLayout_3->addWidget(widget);

        toolBox->addItem(page, QString::fromUtf8("\345\233\276\345\203\217\351\242\204\345\244\204\347\220\206\350\256\276\347\275\256"));
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        toolBox->addItem(page_3, QString::fromUtf8("\351\241\265"));
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setGeometry(QRect(0, 0, 248, 414));
        toolBox->addItem(page_2, QStringLiteral("Page 2"));

        verticalLayout->addWidget(toolBox);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        MainWinClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWinClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 443, 26));
        mainMenu = new QMenu(menuBar);
        mainMenu->setObjectName(QStringLiteral("mainMenu"));
        mainMenu->setFont(font);
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWinClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWinClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWinClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWinClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWinClass->setStatusBar(statusBar);

        menuBar->addAction(mainMenu->menuAction());
        menuBar->addAction(menu->menuAction());
        mainMenu->addAction(actionOpenImg);
        mainMenu->addAction(actionOpenVideo);
        mainMenu->addSeparator();
        mainMenu->addAction(actionQuit);
        menu->addAction(actionResend);

        retranslateUi(MainWinClass);
        QObject::connect(actionQuit, SIGNAL(triggered()), MainWinClass, SLOT(close()));
        QObject::connect(boxGrayscale, SIGNAL(toggled(bool)), checkHistogram, SLOT(setEnabled(bool)));

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWinClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWinClass)
    {
        MainWinClass->setWindowTitle(QApplication::translate("MainWinClass", "\344\272\244\351\200\232\346\240\207\345\277\227\350\257\206\345\210\253\347\263\273\347\273\237", 0));
        actionQuit->setText(QApplication::translate("MainWinClass", "\351\200\200\345\207\272", 0));
        actionOpenImg->setText(QApplication::translate("MainWinClass", "\346\211\223\345\274\200\345\233\276\347\211\207", 0));
        actionOpenVideo->setText(QApplication::translate("MainWinClass", "\346\211\223\345\274\200\350\247\206\351\242\221", 0));
        actionResend->setText(QApplication::translate("MainWinClass", "\345\206\215\346\254\241\345\244\204\347\220\206", 0));
        VideoControlBox->setTitle(QApplication::translate("MainWinClass", "\350\247\206\351\242\221\346\216\247\345\210\266", 0));
        btnPlay->setText(QApplication::translate("MainWinClass", "\346\222\255\346\224\276", 0));
        btnPrevious->setText(QApplication::translate("MainWinClass", "\344\270\212\344\270\200\345\270\247", 0));
        btnNext->setText(QApplication::translate("MainWinClass", "\344\270\213\344\270\200\345\270\247", 0));
        label->setText(QApplication::translate("MainWinClass", "TextLabel", 0));
        boxDetectArea->setTitle(QApplication::translate("MainWinClass", "\346\243\200\346\265\213\345\214\272\345\237\237", 0));
        label_2->setText(QApplication::translate("MainWinClass", "\351\241\266\351\203\250\346\243\200\346\265\213\345\214\272\345\237\237\357\274\232", 0));
        label_3->setText(QApplication::translate("MainWinClass", "\344\276\247\350\276\271\346\243\200\346\265\213\345\214\272\345\237\237\357\274\232", 0));
        label_4->setText(QApplication::translate("MainWinClass", "\345\272\225\351\203\250\346\243\200\346\265\213\345\214\272\345\237\237\357\274\232", 0));
        label_5->setText(QApplication::translate("MainWinClass", "\351\232\224\350\241\214\345\244\204\347\220\206        \357\274\232", 0));
        comboDetectDiv->clear();
        comboDetectDiv->insertItems(0, QStringList()
         << QApplication::translate("MainWinClass", "/ 1", 0)
         << QApplication::translate("MainWinClass", "/ 2", 0)
         << QApplication::translate("MainWinClass", "/ 4", 0)
         << QApplication::translate("MainWinClass", "/ 8", 0)
        );
        boxEnhance->setTitle(QApplication::translate("MainWinClass", "\345\233\276\345\203\217\345\242\236\345\274\272", 0));
        label_6->setText(QApplication::translate("MainWinClass", "\351\245\261\345\222\214\345\272\246\357\274\232", 0));
        checkHistogram->setText(QApplication::translate("MainWinClass", "\347\233\264\346\226\271\345\233\276\345\235\207\350\241\241\345\214\226", 0));
        boxGrayscale->setTitle(QApplication::translate("MainWinClass", "\347\201\260\345\272\246\345\233\276\346\217\220\345\217\226", 0));
        radioButton->setText(QApplication::translate("MainWinClass", "\347\201\260\345\272\246\345\200\274", 0));
        radioButton_2->setText(QApplication::translate("MainWinClass", "\350\211\262\350\260\203\345\210\206\351\207\217", 0));
        radioButton_3->setText(QApplication::translate("MainWinClass", "R\345\210\206\351\207\217", 0));
        radioButton_4->setText(QApplication::translate("MainWinClass", "G\345\210\206\351\207\217", 0));
        radioButton_5->setText(QApplication::translate("MainWinClass", "B\345\210\206\351\207\217", 0));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("MainWinClass", "\345\233\276\345\203\217\351\242\204\345\244\204\347\220\206\350\256\276\347\275\256", 0));
        toolBox->setItemText(toolBox->indexOf(page_3), QApplication::translate("MainWinClass", "\351\241\265", 0));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("MainWinClass", "Page 2", 0));
        mainMenu->setTitle(QApplication::translate("MainWinClass", "\346\226\207\344\273\266", 0));
        menu->setTitle(QApplication::translate("MainWinClass", "\346\223\215\344\275\234", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWinClass: public Ui_MainWinClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIN_H

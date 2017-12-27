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
#include <QtWidgets/QSpinBox>
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
    QAction *actionSaveImage;
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
    QLabel *label;
    QToolBox *toolBox;
    QWidget *page;
    QFormLayout *formLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioTypeLimit;
    QRadioButton *radioTypeWarning;
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
    QWidget *widget;
    QWidget *page_3;
    QGridLayout *gridLayout_2;
    QGroupBox *boxBinaryRGB;
    QGridLayout *gridLayout_4;
    QLabel *label_12;
    QSpinBox *edtBinaryRed;
    QLabel *label_14;
    QSpinBox *edtBinaryYellow;
    QWidget *widget_2;
    QGroupBox *boxBinarySVF;
    QGridLayout *gridLayout_5;
    QLabel *label_17;
    QSpinBox *edtBinaryD;
    QGroupBox *boxBinaryHSV;
    QGridLayout *gridLayout_3;
    QLabel *label_7;
    QSpinBox *edtBinaryHmin;
    QLabel *label_10;
    QSpinBox *edtBinarySmin;
    QLabel *label_9;
    QSpinBox *edtBinaryVmin;
    QSpinBox *edtBinaryHmax;
    QLabel *label_8;
    QGroupBox *boxBianryPost;
    QGridLayout *gridLayout_6;
    QLabel *label_13;
    QSpinBox *edtBinaryDilate;
    QLabel *label_11;
    QSpinBox *edtBinaryErode;
    QGroupBox *boxBinaryMixed;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *boxShapeHoughCircle;
    QGridLayout *gridLayout_7;
    QLabel *label_15;
    QSpinBox *edtHoughP1;
    QLabel *label_16;
    QSpinBox *edtHoughP2;
    QGroupBox *boxShpaePatternCircle;
    QGridLayout *gridLayout_8;
    QLabel *label_18;
    QLabel *label_19;
    QSpinBox *edtShapeDmin;
    QLabel *label_20;
    QSpinBox *edtShapeVariance;
    QSpinBox *edtShapeDmax;
    QGroupBox *boxShapeTriangle;
    QGridLayout *gridLayout_9;
    QSpinBox *edtShapeVariance_2;
    QLabel *label_21;
    QLabel *label_23;
    QSpinBox *edtShapeCorner;
    QWidget *widget_3;
    QMenuBar *menuBar;
    QMenu *mainMenu;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWinClass)
    {
        if (MainWinClass->objectName().isEmpty())
            MainWinClass->setObjectName(QStringLiteral("MainWinClass"));
        MainWinClass->resize(688, 881);
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
        actionSaveImage = new QAction(MainWinClass);
        actionSaveImage->setObjectName(QStringLiteral("actionSaveImage"));
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
        page->setGeometry(QRect(0, 0, 248, 553));
        formLayout_4 = new QFormLayout(page);
        formLayout_4->setSpacing(6);
        formLayout_4->setContentsMargins(11, 11, 11, 11);
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        formLayout_4->setContentsMargins(-1, 7, -1, -1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        radioTypeLimit = new QRadioButton(page);
        radioTypeLimit->setObjectName(QStringLiteral("radioTypeLimit"));
        radioTypeLimit->setChecked(true);

        horizontalLayout_2->addWidget(radioTypeLimit);

        radioTypeWarning = new QRadioButton(page);
        radioTypeWarning->setObjectName(QStringLiteral("radioTypeWarning"));

        horizontalLayout_2->addWidget(radioTypeWarning);


        formLayout_4->setLayout(0, QFormLayout::FieldRole, horizontalLayout_2);

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


        formLayout_4->setWidget(1, QFormLayout::SpanningRole, boxDetectArea);

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


        formLayout_4->setWidget(2, QFormLayout::SpanningRole, boxEnhance);

        widget = new QWidget(page);
        widget->setObjectName(QStringLiteral("widget"));

        formLayout_4->setWidget(3, QFormLayout::FieldRole, widget);

        toolBox->addItem(page, QString::fromUtf8("\345\233\276\345\203\217\351\242\204\345\244\204\347\220\206"));
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        page_3->setGeometry(QRect(0, 0, 248, 553));
        page_3->setToolTipDuration(1);
        gridLayout_2 = new QGridLayout(page_3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(11);
        gridLayout_2->setContentsMargins(-1, 7, -1, -1);
        boxBinaryRGB = new QGroupBox(page_3);
        boxBinaryRGB->setObjectName(QStringLiteral("boxBinaryRGB"));
        boxBinaryRGB->setEnabled(true);
        sizePolicy3.setHeightForWidth(boxBinaryRGB->sizePolicy().hasHeightForWidth());
        boxBinaryRGB->setSizePolicy(sizePolicy3);
        boxBinaryRGB->setCheckable(true);
        boxBinaryRGB->setChecked(false);
        gridLayout_4 = new QGridLayout(boxBinaryRGB);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label_12 = new QLabel(boxBinaryRGB);
        label_12->setObjectName(QStringLiteral("label_12"));
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy4);

        gridLayout_4->addWidget(label_12, 0, 0, 1, 1);

        edtBinaryRed = new QSpinBox(boxBinaryRGB);
        edtBinaryRed->setObjectName(QStringLiteral("edtBinaryRed"));
        edtBinaryRed->setMinimum(0);
        edtBinaryRed->setMaximum(255);

        gridLayout_4->addWidget(edtBinaryRed, 0, 1, 1, 1);

        label_14 = new QLabel(boxBinaryRGB);
        label_14->setObjectName(QStringLiteral("label_14"));
        sizePolicy4.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy4);

        gridLayout_4->addWidget(label_14, 1, 0, 1, 1);

        edtBinaryYellow = new QSpinBox(boxBinaryRGB);
        edtBinaryYellow->setObjectName(QStringLiteral("edtBinaryYellow"));
        edtBinaryYellow->setMinimum(0);
        edtBinaryYellow->setMaximum(255);

        gridLayout_4->addWidget(edtBinaryYellow, 1, 1, 1, 1);


        gridLayout_2->addWidget(boxBinaryRGB, 1, 0, 1, 1);

        widget_2 = new QWidget(page_3);
        widget_2->setObjectName(QStringLiteral("widget_2"));

        gridLayout_2->addWidget(widget_2, 5, 0, 1, 1);

        boxBinarySVF = new QGroupBox(page_3);
        boxBinarySVF->setObjectName(QStringLiteral("boxBinarySVF"));
        boxBinarySVF->setEnabled(true);
        sizePolicy3.setHeightForWidth(boxBinarySVF->sizePolicy().hasHeightForWidth());
        boxBinarySVF->setSizePolicy(sizePolicy3);
        boxBinarySVF->setCheckable(true);
        boxBinarySVF->setChecked(false);
        gridLayout_5 = new QGridLayout(boxBinarySVF);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label_17 = new QLabel(boxBinarySVF);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout_5->addWidget(label_17, 0, 0, 1, 1);

        edtBinaryD = new QSpinBox(boxBinarySVF);
        edtBinaryD->setObjectName(QStringLiteral("edtBinaryD"));
        edtBinaryD->setMinimum(0);
        edtBinaryD->setMaximum(100);

        gridLayout_5->addWidget(edtBinaryD, 0, 1, 1, 1);


        gridLayout_2->addWidget(boxBinarySVF, 2, 0, 1, 1);

        boxBinaryHSV = new QGroupBox(page_3);
        boxBinaryHSV->setObjectName(QStringLiteral("boxBinaryHSV"));
        boxBinaryHSV->setEnabled(true);
        sizePolicy3.setHeightForWidth(boxBinaryHSV->sizePolicy().hasHeightForWidth());
        boxBinaryHSV->setSizePolicy(sizePolicy3);
        boxBinaryHSV->setCheckable(true);
        boxBinaryHSV->setChecked(true);
        gridLayout_3 = new QGridLayout(boxBinaryHSV);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(-1, -1, -1, 11);
        label_7 = new QLabel(boxBinaryHSV);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy4.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy4);

        gridLayout_3->addWidget(label_7, 0, 0, 1, 1);

        edtBinaryHmin = new QSpinBox(boxBinaryHSV);
        edtBinaryHmin->setObjectName(QStringLiteral("edtBinaryHmin"));
        edtBinaryHmin->setMinimum(-360);
        edtBinaryHmin->setMaximum(360);

        gridLayout_3->addWidget(edtBinaryHmin, 0, 1, 1, 1);

        label_10 = new QLabel(boxBinaryHSV);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_3->addWidget(label_10, 1, 0, 1, 1);

        edtBinarySmin = new QSpinBox(boxBinaryHSV);
        edtBinarySmin->setObjectName(QStringLiteral("edtBinarySmin"));
        edtBinarySmin->setMinimum(0);
        edtBinarySmin->setMaximum(255);

        gridLayout_3->addWidget(edtBinarySmin, 1, 1, 1, 1);

        label_9 = new QLabel(boxBinaryHSV);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_3->addWidget(label_9, 1, 2, 1, 2);

        edtBinaryVmin = new QSpinBox(boxBinaryHSV);
        edtBinaryVmin->setObjectName(QStringLiteral("edtBinaryVmin"));
        edtBinaryVmin->setMinimum(0);
        edtBinaryVmin->setMaximum(255);

        gridLayout_3->addWidget(edtBinaryVmin, 1, 4, 1, 1);

        edtBinaryHmax = new QSpinBox(boxBinaryHSV);
        edtBinaryHmax->setObjectName(QStringLiteral("edtBinaryHmax"));
        edtBinaryHmax->setMinimum(0);
        edtBinaryHmax->setMaximum(360);

        gridLayout_3->addWidget(edtBinaryHmax, 0, 4, 1, 1);

        label_8 = new QLabel(boxBinaryHSV);
        label_8->setObjectName(QStringLiteral("label_8"));
        sizePolicy2.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy2);
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_8, 0, 2, 1, 2);


        gridLayout_2->addWidget(boxBinaryHSV, 0, 0, 1, 1);

        boxBianryPost = new QGroupBox(page_3);
        boxBianryPost->setObjectName(QStringLiteral("boxBianryPost"));
        sizePolicy3.setHeightForWidth(boxBianryPost->sizePolicy().hasHeightForWidth());
        boxBianryPost->setSizePolicy(sizePolicy3);
        boxBianryPost->setCheckable(true);
        gridLayout_6 = new QGridLayout(boxBianryPost);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        label_13 = new QLabel(boxBianryPost);
        label_13->setObjectName(QStringLiteral("label_13"));
        sizePolicy4.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy4);

        gridLayout_6->addWidget(label_13, 0, 0, 1, 1);

        edtBinaryDilate = new QSpinBox(boxBianryPost);
        edtBinaryDilate->setObjectName(QStringLiteral("edtBinaryDilate"));
        edtBinaryDilate->setMinimum(0);
        edtBinaryDilate->setMaximum(99);
        edtBinaryDilate->setValue(0);

        gridLayout_6->addWidget(edtBinaryDilate, 0, 1, 1, 1);

        label_11 = new QLabel(boxBianryPost);
        label_11->setObjectName(QStringLiteral("label_11"));
        sizePolicy2.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy2);
        label_11->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_11, 0, 2, 1, 1);

        edtBinaryErode = new QSpinBox(boxBianryPost);
        edtBinaryErode->setObjectName(QStringLiteral("edtBinaryErode"));
        edtBinaryErode->setMinimum(0);
        edtBinaryErode->setMaximum(99);
        edtBinaryErode->setValue(0);

        gridLayout_6->addWidget(edtBinaryErode, 0, 3, 1, 1);


        gridLayout_2->addWidget(boxBianryPost, 4, 0, 1, 1);

        boxBinaryMixed = new QGroupBox(page_3);
        boxBinaryMixed->setObjectName(QStringLiteral("boxBinaryMixed"));
        sizePolicy3.setHeightForWidth(boxBinaryMixed->sizePolicy().hasHeightForWidth());
        boxBinaryMixed->setSizePolicy(sizePolicy3);
        boxBinaryMixed->setCheckable(true);

        gridLayout_2->addWidget(boxBinaryMixed, 3, 0, 1, 1);

        toolBox->addItem(page_3, QString::fromUtf8("\344\272\214\345\200\274\345\214\226"));
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setGeometry(QRect(0, 0, 248, 553));
        verticalLayout_3 = new QVBoxLayout(page_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        boxShapeHoughCircle = new QGroupBox(page_2);
        boxShapeHoughCircle->setObjectName(QStringLiteral("boxShapeHoughCircle"));
        sizePolicy3.setHeightForWidth(boxShapeHoughCircle->sizePolicy().hasHeightForWidth());
        boxShapeHoughCircle->setSizePolicy(sizePolicy3);
        boxShapeHoughCircle->setCheckable(true);
        gridLayout_7 = new QGridLayout(boxShapeHoughCircle);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        label_15 = new QLabel(boxShapeHoughCircle);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_7->addWidget(label_15, 0, 0, 1, 1);

        edtHoughP1 = new QSpinBox(boxShapeHoughCircle);
        edtHoughP1->setObjectName(QStringLiteral("edtHoughP1"));
        edtHoughP1->setMaximum(999);
        edtHoughP1->setValue(0);

        gridLayout_7->addWidget(edtHoughP1, 0, 1, 1, 1);

        label_16 = new QLabel(boxShapeHoughCircle);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout_7->addWidget(label_16, 0, 2, 1, 1);

        edtHoughP2 = new QSpinBox(boxShapeHoughCircle);
        edtHoughP2->setObjectName(QStringLiteral("edtHoughP2"));
        edtHoughP2->setMaximum(999);
        edtHoughP2->setValue(0);

        gridLayout_7->addWidget(edtHoughP2, 0, 3, 1, 1);


        verticalLayout_3->addWidget(boxShapeHoughCircle);

        boxShpaePatternCircle = new QGroupBox(page_2);
        boxShpaePatternCircle->setObjectName(QStringLiteral("boxShpaePatternCircle"));
        sizePolicy3.setHeightForWidth(boxShpaePatternCircle->sizePolicy().hasHeightForWidth());
        boxShpaePatternCircle->setSizePolicy(sizePolicy3);
        boxShpaePatternCircle->setCheckable(true);
        gridLayout_8 = new QGridLayout(boxShpaePatternCircle);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        label_18 = new QLabel(boxShpaePatternCircle);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout_8->addWidget(label_18, 0, 0, 1, 1);

        label_19 = new QLabel(boxShpaePatternCircle);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout_8->addWidget(label_19, 1, 0, 1, 1);

        edtShapeDmin = new QSpinBox(boxShpaePatternCircle);
        edtShapeDmin->setObjectName(QStringLiteral("edtShapeDmin"));
        edtShapeDmin->setMaximum(99);
        edtShapeDmin->setSingleStep(1);
        edtShapeDmin->setValue(0);

        gridLayout_8->addWidget(edtShapeDmin, 1, 1, 1, 1);

        label_20 = new QLabel(boxShpaePatternCircle);
        label_20->setObjectName(QStringLiteral("label_20"));

        gridLayout_8->addWidget(label_20, 1, 2, 1, 1);

        edtShapeVariance = new QSpinBox(boxShpaePatternCircle);
        edtShapeVariance->setObjectName(QStringLiteral("edtShapeVariance"));
        edtShapeVariance->setMaximum(100000000);
        edtShapeVariance->setSingleStep(1000);
        edtShapeVariance->setValue(0);

        gridLayout_8->addWidget(edtShapeVariance, 0, 1, 1, 3);

        edtShapeDmax = new QSpinBox(boxShpaePatternCircle);
        edtShapeDmax->setObjectName(QStringLiteral("edtShapeDmax"));
        edtShapeDmax->setMaximum(999);
        edtShapeDmax->setSingleStep(1);
        edtShapeDmax->setValue(0);

        gridLayout_8->addWidget(edtShapeDmax, 1, 3, 1, 1);


        verticalLayout_3->addWidget(boxShpaePatternCircle);

        boxShapeTriangle = new QGroupBox(page_2);
        boxShapeTriangle->setObjectName(QStringLiteral("boxShapeTriangle"));
        sizePolicy3.setHeightForWidth(boxShapeTriangle->sizePolicy().hasHeightForWidth());
        boxShapeTriangle->setSizePolicy(sizePolicy3);
        boxShapeTriangle->setCheckable(true);
        gridLayout_9 = new QGridLayout(boxShapeTriangle);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        edtShapeVariance_2 = new QSpinBox(boxShapeTriangle);
        edtShapeVariance_2->setObjectName(QStringLiteral("edtShapeVariance_2"));
        edtShapeVariance_2->setMaximum(100000000);
        edtShapeVariance_2->setSingleStep(1000);
        edtShapeVariance_2->setValue(0);

        gridLayout_9->addWidget(edtShapeVariance_2, 0, 1, 1, 2);

        label_21 = new QLabel(boxShapeTriangle);
        label_21->setObjectName(QStringLiteral("label_21"));

        gridLayout_9->addWidget(label_21, 0, 0, 1, 1);

        label_23 = new QLabel(boxShapeTriangle);
        label_23->setObjectName(QStringLiteral("label_23"));

        gridLayout_9->addWidget(label_23, 1, 0, 1, 1);

        edtShapeCorner = new QSpinBox(boxShapeTriangle);
        edtShapeCorner->setObjectName(QStringLiteral("edtShapeCorner"));
        edtShapeCorner->setMaximum(99);
        edtShapeCorner->setSingleStep(1);
        edtShapeCorner->setValue(0);

        gridLayout_9->addWidget(edtShapeCorner, 1, 2, 1, 1);


        verticalLayout_3->addWidget(boxShapeTriangle);

        widget_3 = new QWidget(page_2);
        widget_3->setObjectName(QStringLiteral("widget_3"));

        verticalLayout_3->addWidget(widget_3);

        toolBox->addItem(page_2, QString::fromUtf8("\345\275\242\347\212\266\346\243\200\346\265\213\345\256\232\344\275\215"));

        verticalLayout->addWidget(toolBox);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        MainWinClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWinClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 688, 26));
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
        menu->addAction(actionSaveImage);

        retranslateUi(MainWinClass);
        QObject::connect(actionQuit, SIGNAL(triggered()), MainWinClass, SLOT(close()));

        toolBox->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWinClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWinClass)
    {
        MainWinClass->setWindowTitle(QApplication::translate("MainWinClass", "\344\272\244\351\200\232\346\240\207\345\277\227\350\257\206\345\210\253\347\263\273\347\273\237", 0));
        actionQuit->setText(QApplication::translate("MainWinClass", "\351\200\200\345\207\272", 0));
        actionOpenImg->setText(QApplication::translate("MainWinClass", "\346\211\223\345\274\200\345\233\276\347\211\207", 0));
        actionOpenVideo->setText(QApplication::translate("MainWinClass", "\346\211\223\345\274\200\350\247\206\351\242\221", 0));
        actionResend->setText(QApplication::translate("MainWinClass", "\345\206\215\346\254\241\345\244\204\347\220\206", 0));
        actionSaveImage->setText(QApplication::translate("MainWinClass", "\344\277\235\345\255\230\345\233\276\347\211\207", 0));
        VideoControlBox->setTitle(QApplication::translate("MainWinClass", "\350\247\206\351\242\221\346\216\247\345\210\266", 0));
        btnPlay->setText(QApplication::translate("MainWinClass", "\346\222\255\346\224\276", 0));
        btnPrevious->setText(QApplication::translate("MainWinClass", "\344\270\212\344\270\200\345\270\247", 0));
        btnNext->setText(QApplication::translate("MainWinClass", "\344\270\213\344\270\200\345\270\247", 0));
        label->setText(QApplication::translate("MainWinClass", "TextLabel", 0));
        radioTypeLimit->setText(QApplication::translate("MainWinClass", "\351\231\220\351\200\237\346\240\207\345\277\227", 0));
        radioTypeWarning->setText(QApplication::translate("MainWinClass", "\350\255\246\345\221\212\346\240\207\345\277\227", 0));
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
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("MainWinClass", "\345\233\276\345\203\217\351\242\204\345\244\204\347\220\206", 0));
        boxBinaryRGB->setTitle(QApplication::translate("MainWinClass", "RGB", 0));
        label_12->setText(QApplication::translate("MainWinClass", "Red\357\274\232", 0));
        label_14->setText(QApplication::translate("MainWinClass", "Yellow\357\274\232", 0));
        boxBinarySVF->setTitle(QApplication::translate("MainWinClass", "SVF", 0));
        label_17->setText(QApplication::translate("MainWinClass", "D\357\274\232", 0));
        boxBinaryHSV->setTitle(QApplication::translate("MainWinClass", "HSV", 0));
        label_7->setText(QApplication::translate("MainWinClass", "H\357\274\232", 0));
        label_10->setText(QApplication::translate("MainWinClass", "S > ", 0));
        label_9->setText(QApplication::translate("MainWinClass", "V > ", 0));
        label_8->setText(QApplication::translate("MainWinClass", "~", 0));
        boxBianryPost->setTitle(QApplication::translate("MainWinClass", "\351\231\204\345\212\240\345\244\204\347\220\206", 0));
        label_13->setText(QApplication::translate("MainWinClass", "\350\206\250\350\203\200\357\274\232", 0));
        label_11->setText(QApplication::translate("MainWinClass", "\350\205\220\350\232\200\357\274\232", 0));
        boxBinaryMixed->setTitle(QApplication::translate("MainWinClass", "Mixed Method", 0));
        toolBox->setItemText(toolBox->indexOf(page_3), QApplication::translate("MainWinClass", "\344\272\214\345\200\274\345\214\226", 0));
        boxShapeHoughCircle->setTitle(QApplication::translate("MainWinClass", "Hough\345\234\206\346\243\200\346\265\213", 0));
        label_15->setText(QApplication::translate("MainWinClass", "p1:", 0));
        label_16->setText(QApplication::translate("MainWinClass", "p2:", 0));
        boxShpaePatternCircle->setTitle(QApplication::translate("MainWinClass", "\345\277\253\351\200\237\346\250\241\346\235\277\345\214\271\351\205\215\345\234\206\346\243\200\346\265\213", 0));
        label_18->setText(QApplication::translate("MainWinClass", "\346\226\271\345\267\256\357\274\232", 0));
        label_19->setText(QApplication::translate("MainWinClass", "\347\233\264\345\276\204\357\274\232", 0));
        label_20->setText(QApplication::translate("MainWinClass", "~", 0));
        boxShapeTriangle->setTitle(QApplication::translate("MainWinClass", "\345\277\253\351\200\237\350\247\222\347\202\271\344\270\211\350\247\222\345\275\242\346\243\200\346\265\213", 0));
        label_21->setText(QApplication::translate("MainWinClass", "\346\226\271\345\267\256\357\274\232", 0));
        label_23->setText(QApplication::translate("MainWinClass", "\350\247\222\347\202\271\357\274\232", 0));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("MainWinClass", "\345\275\242\347\212\266\346\243\200\346\265\213\345\256\232\344\275\215", 0));
        mainMenu->setTitle(QApplication::translate("MainWinClass", "\346\226\207\344\273\266", 0));
        menu->setTitle(QApplication::translate("MainWinClass", "\346\223\215\344\275\234", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWinClass: public Ui_MainWinClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIN_H

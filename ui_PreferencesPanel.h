/********************************************************************************
** Form generated from reading UI file 'PreferencesPanel.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCESPANEL_H
#define UI_PREFERENCESPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreferencesPanel
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *headingScaleLineEdit;
    QLineEdit *pitchScaleLineEdit;
    QLabel *label_3;
    QLineEdit *ttyPathLineEdit;
    QPushButton *savePushButton;
    QLabel *label_5;
    QLineEdit *rollScaleLineEdit;
    QLabel *label_6;
    QLineEdit *filterLagLineEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PreferencesPanel)
    {
        if (PreferencesPanel->objectName().isEmpty())
            PreferencesPanel->setObjectName(QStringLiteral("PreferencesPanel"));
        PreferencesPanel->setEnabled(true);
        PreferencesPanel->resize(444, 358);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PreferencesPanel->sizePolicy().hasHeightForWidth());
        PreferencesPanel->setSizePolicy(sizePolicy);
        PreferencesPanel->setMinimumSize(QSize(444, 358));
        PreferencesPanel->setMaximumSize(QSize(444, 358));
        centralwidget = new QWidget(PreferencesPanel);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 50, 141, 17));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 90, 121, 20));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        headingScaleLineEdit = new QLineEdit(centralwidget);
        headingScaleLineEdit->setObjectName(QStringLiteral("headingScaleLineEdit"));
        headingScaleLineEdit->setGeometry(QRect(190, 50, 91, 27));
        headingScaleLineEdit->setAlignment(Qt::AlignCenter);
        pitchScaleLineEdit = new QLineEdit(centralwidget);
        pitchScaleLineEdit->setObjectName(QStringLiteral("pitchScaleLineEdit"));
        pitchScaleLineEdit->setGeometry(QRect(190, 90, 91, 27));
        pitchScaleLineEdit->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(110, 10, 61, 20));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ttyPathLineEdit = new QLineEdit(centralwidget);
        ttyPathLineEdit->setObjectName(QStringLiteral("ttyPathLineEdit"));
        ttyPathLineEdit->setGeometry(QRect(190, 10, 91, 27));
        savePushButton = new QPushButton(centralwidget);
        savePushButton->setObjectName(QStringLiteral("savePushButton"));
        savePushButton->setGeometry(QRect(190, 250, 91, 27));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(60, 130, 121, 20));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        rollScaleLineEdit = new QLineEdit(centralwidget);
        rollScaleLineEdit->setObjectName(QStringLiteral("rollScaleLineEdit"));
        rollScaleLineEdit->setGeometry(QRect(190, 130, 91, 27));
        rollScaleLineEdit->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(60, 170, 121, 20));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        filterLagLineEdit = new QLineEdit(centralwidget);
        filterLagLineEdit->setObjectName(QStringLiteral("filterLagLineEdit"));
        filterLagLineEdit->setGeometry(QRect(190, 170, 91, 27));
        filterLagLineEdit->setAlignment(Qt::AlignCenter);
        PreferencesPanel->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PreferencesPanel);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 444, 27));
        PreferencesPanel->setMenuBar(menubar);
        statusbar = new QStatusBar(PreferencesPanel);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        PreferencesPanel->setStatusBar(statusbar);

        retranslateUi(PreferencesPanel);

        QMetaObject::connectSlotsByName(PreferencesPanel);
    } // setupUi

    void retranslateUi(QMainWindow *PreferencesPanel)
    {
        PreferencesPanel->setWindowTitle(QApplication::translate("PreferencesPanel", "PreferencesPanel", 0));
        label->setText(QApplication::translate("PreferencesPanel", "Heading Curvature", 0));
        label_2->setText(QApplication::translate("PreferencesPanel", "Pitch Curvature", 0));
        headingScaleLineEdit->setText(QApplication::translate("PreferencesPanel", "1.0", 0));
        pitchScaleLineEdit->setText(QApplication::translate("PreferencesPanel", "1.0", 0));
        label_3->setText(QApplication::translate("PreferencesPanel", "TTY Path", 0));
        ttyPathLineEdit->setText(QApplication::translate("PreferencesPanel", "/dev/ttyUSB0", 0));
        savePushButton->setText(QApplication::translate("PreferencesPanel", "Save", 0));
        label_5->setText(QApplication::translate("PreferencesPanel", "Roll Curvature", 0));
        rollScaleLineEdit->setText(QApplication::translate("PreferencesPanel", "1.0", 0));
        label_6->setText(QApplication::translate("PreferencesPanel", "Smoothing", 0));
        filterLagLineEdit->setText(QApplication::translate("PreferencesPanel", "20.0", 0));
    } // retranslateUi

};

namespace Ui {
    class PreferencesPanel: public Ui_PreferencesPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCESPANEL_H

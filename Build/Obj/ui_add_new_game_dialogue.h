/********************************************************************************
** Form generated from reading UI file 'add_new_game_dialogue.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_NEW_GAME_DIALOGUE_H
#define UI_ADD_NEW_GAME_DIALOGUE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Add_New_Game_Dialogue
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *comboBox;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QComboBox *comboBox_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Add_New_Game_Dialogue)
    {
        if (Add_New_Game_Dialogue->objectName().isEmpty())
            Add_New_Game_Dialogue->setObjectName(QString::fromUtf8("Add_New_Game_Dialogue"));
        Add_New_Game_Dialogue->resize(400, 301);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Add_New_Game_Dialogue->sizePolicy().hasHeightForWidth());
        Add_New_Game_Dialogue->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(Add_New_Game_Dialogue);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_4 = new QWidget(Add_New_Game_Dialogue);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        horizontalLayout_2 = new QHBoxLayout(widget_4);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(widget_4);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(widget_4);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);


        verticalLayout->addWidget(widget_4);

        widget_3 = new QWidget(Add_New_Game_Dialogue);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(widget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        comboBox = new QComboBox(widget_3);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(3);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(comboBox);


        verticalLayout->addWidget(widget_3);

        widget_2 = new QWidget(Add_New_Game_Dialogue);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_4 = new QHBoxLayout(widget_2);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        comboBox_2 = new QComboBox(widget_2);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        sizePolicy1.setHeightForWidth(comboBox_2->sizePolicy().hasHeightForWidth());
        comboBox_2->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(comboBox_2);


        verticalLayout->addWidget(widget_2);

        widget = new QWidget(Add_New_Game_Dialogue);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(widget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy2);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);


        verticalLayout->addWidget(widget);


        retranslateUi(Add_New_Game_Dialogue);
        QObject::connect(buttonBox, SIGNAL(accepted()), Add_New_Game_Dialogue, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Add_New_Game_Dialogue, SLOT(reject()));

        QMetaObject::connectSlotsByName(Add_New_Game_Dialogue);
    } // setupUi

    void retranslateUi(QDialog *Add_New_Game_Dialogue)
    {
        Add_New_Game_Dialogue->setWindowTitle(QApplication::translate("Add_New_Game_Dialogue", "Add New Game", nullptr));
        label->setText(QApplication::translate("Add_New_Game_Dialogue", "Game Title", nullptr));
        label_2->setText(QApplication::translate("Add_New_Game_Dialogue", "Game Icon", nullptr));
        label_3->setText(QApplication::translate("Add_New_Game_Dialogue", "Launch Script", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Add_New_Game_Dialogue: public Ui_Add_New_Game_Dialogue {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_NEW_GAME_DIALOGUE_H

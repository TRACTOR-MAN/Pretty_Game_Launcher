/********************************************************************************
** Form generated from reading UI file 'add_new_game_dialogue.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_NEW_GAME_DIALOGUE_H
#define UI_ADD_NEW_GAME_DIALOGUE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Add_New_Game_Dialogue
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *gameTitleWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QWidget *widget_7;
    QLineEdit *gameTitle;
    QWidget *gameIconWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QWidget *widget_6;
    QLineEdit *gameIcon;
    QToolButton *toolButton_2;
    QWidget *launchScriptWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *launchScript;
    QToolButton *toolButton;
    QWidget *launchCommandWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_3;
    QPlainTextEdit *launchCommand;
    QWidget *gameDescriptionWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_2;
    QPlainTextEdit *gameDescription;
    QWidget *okCancelWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Add_New_Game_Dialogue)
    {
        if (Add_New_Game_Dialogue->objectName().isEmpty())
            Add_New_Game_Dialogue->setObjectName(QString::fromUtf8("Add_New_Game_Dialogue"));
        Add_New_Game_Dialogue->resize(468, 696);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Add_New_Game_Dialogue->sizePolicy().hasHeightForWidth());
        Add_New_Game_Dialogue->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(Add_New_Game_Dialogue);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gameTitleWidget = new QWidget(Add_New_Game_Dialogue);
        gameTitleWidget->setObjectName(QString::fromUtf8("gameTitleWidget"));
        horizontalLayout_2 = new QHBoxLayout(gameTitleWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(gameTitleWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        widget_7 = new QWidget(gameTitleWidget);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        widget_7->setMinimumSize(QSize(10, 0));

        horizontalLayout_2->addWidget(widget_7);

        gameTitle = new QLineEdit(gameTitleWidget);
        gameTitle->setObjectName(QString::fromUtf8("gameTitle"));

        horizontalLayout_2->addWidget(gameTitle);


        verticalLayout->addWidget(gameTitleWidget);

        gameIconWidget = new QWidget(Add_New_Game_Dialogue);
        gameIconWidget->setObjectName(QString::fromUtf8("gameIconWidget"));
        horizontalLayout_3 = new QHBoxLayout(gameIconWidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(gameIconWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        widget_6 = new QWidget(gameIconWidget);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        widget_6->setMinimumSize(QSize(15, 0));

        horizontalLayout_3->addWidget(widget_6);

        gameIcon = new QLineEdit(gameIconWidget);
        gameIcon->setObjectName(QString::fromUtf8("gameIcon"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(gameIcon->sizePolicy().hasHeightForWidth());
        gameIcon->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(gameIcon);

        toolButton_2 = new QToolButton(gameIconWidget);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));

        horizontalLayout_3->addWidget(toolButton_2);


        verticalLayout->addWidget(gameIconWidget);

        launchScriptWidget = new QWidget(Add_New_Game_Dialogue);
        launchScriptWidget->setObjectName(QString::fromUtf8("launchScriptWidget"));
        horizontalLayout_4 = new QHBoxLayout(launchScriptWidget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(launchScriptWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        launchScript = new QLineEdit(launchScriptWidget);
        launchScript->setObjectName(QString::fromUtf8("launchScript"));

        horizontalLayout_4->addWidget(launchScript);

        toolButton = new QToolButton(launchScriptWidget);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));

        horizontalLayout_4->addWidget(toolButton);


        verticalLayout->addWidget(launchScriptWidget);

        launchCommandWidget = new QWidget(Add_New_Game_Dialogue);
        launchCommandWidget->setObjectName(QString::fromUtf8("launchCommandWidget"));
        verticalLayout_2 = new QVBoxLayout(launchCommandWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(launchCommandWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_5);

        launchCommand = new QPlainTextEdit(launchCommandWidget);
        launchCommand->setObjectName(QString::fromUtf8("launchCommand"));

        verticalLayout_2->addWidget(launchCommand);


        verticalLayout->addWidget(launchCommandWidget);

        gameDescriptionWidget = new QWidget(Add_New_Game_Dialogue);
        gameDescriptionWidget->setObjectName(QString::fromUtf8("gameDescriptionWidget"));
        verticalLayout_3 = new QVBoxLayout(gameDescriptionWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_5 = new QLabel(gameDescriptionWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_6->addWidget(label_5);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_6);

        gameDescription = new QPlainTextEdit(gameDescriptionWidget);
        gameDescription->setObjectName(QString::fromUtf8("gameDescription"));

        verticalLayout_3->addWidget(gameDescription);


        verticalLayout->addWidget(gameDescriptionWidget);

        okCancelWidget = new QWidget(Add_New_Game_Dialogue);
        okCancelWidget->setObjectName(QString::fromUtf8("okCancelWidget"));
        horizontalLayout = new QHBoxLayout(okCancelWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(okCancelWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        sizePolicy.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);


        verticalLayout->addWidget(okCancelWidget);


        retranslateUi(Add_New_Game_Dialogue);
        QObject::connect(buttonBox, SIGNAL(rejected()), Add_New_Game_Dialogue, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), Add_New_Game_Dialogue, SLOT(accept()));
        QObject::connect(toolButton, SIGNAL(clicked()), Add_New_Game_Dialogue, SLOT(searchForLaunchScript()));
        QObject::connect(Add_New_Game_Dialogue, SIGNAL(launchScriptTextChanged(QString)), launchScript, SLOT(setText(QString)));
        QObject::connect(toolButton_2, SIGNAL(clicked()), Add_New_Game_Dialogue, SLOT(searchForGameIcon()));
        QObject::connect(Add_New_Game_Dialogue, SIGNAL(gameIconTextChanged(QString)), gameIcon, SLOT(setText(QString)));
        QObject::connect(buttonBox, SIGNAL(accepted()), Add_New_Game_Dialogue, SLOT(addNewGameToDbc()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Add_New_Game_Dialogue, SLOT(clearDialogueElements()));

        QMetaObject::connectSlotsByName(Add_New_Game_Dialogue);
    } // setupUi

    void retranslateUi(QDialog *Add_New_Game_Dialogue)
    {
        Add_New_Game_Dialogue->setWindowTitle(QCoreApplication::translate("Add_New_Game_Dialogue", "Add New Game", nullptr));
        label->setText(QCoreApplication::translate("Add_New_Game_Dialogue", "Game Title", nullptr));
        label_2->setText(QCoreApplication::translate("Add_New_Game_Dialogue", "Game Icon", nullptr));
        toolButton_2->setText(QCoreApplication::translate("Add_New_Game_Dialogue", "...", nullptr));
        label_3->setText(QCoreApplication::translate("Add_New_Game_Dialogue", "Launch Script", nullptr));
        toolButton->setText(QCoreApplication::translate("Add_New_Game_Dialogue", "...", nullptr));
        label_4->setText(QCoreApplication::translate("Add_New_Game_Dialogue", "Launch Command", nullptr));
        label_5->setText(QCoreApplication::translate("Add_New_Game_Dialogue", "Game Description", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Add_New_Game_Dialogue: public Ui_Add_New_Game_Dialogue {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_NEW_GAME_DIALOGUE_H

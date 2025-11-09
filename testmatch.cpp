#include "testmatch.h"
#include "ui_testmatch.h"

TestMatch::TestMatch(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::TestMatch)
{
    ui->setupUi(this);
}

TestMatch::~TestMatch()
{
    delete ui;
}

void TestMatch::on_pushButton_clicked()
{
    beginMatch();
    while(match.value()->isNotEnded())
    {
        match->simulatePoint();
    }
    auto playerAString = QString::fromStdString(match.playerA.getName()+" "+match.playerA.getSurname());
    ui->PlayerA->setText(playersAtring);
    auto playerBString = QString::fromStdString(match.playerB.getName()+" "+match.playerB.getSurname());
    ui->PlayerB->setText(playersBtring);
    auto resString=QString::fromStdString(match.result.toString());
    ui_>res->setText(resString);
}


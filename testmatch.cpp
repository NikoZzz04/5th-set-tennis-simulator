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

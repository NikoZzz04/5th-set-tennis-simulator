#ifndef TESTMATCH_H
#define TESTMATCH_H

#include <QMainWindow>

namespace Ui {
class TestMatch;
}

class TestMatch : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestMatch(QWidget *parent = nullptr);
    ~TestMatch();

private:
    Ui::TestMatch *ui;
};

#endif // TESTMATCH_H

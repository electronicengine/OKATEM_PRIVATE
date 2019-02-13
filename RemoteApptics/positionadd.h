#ifndef POSITIONADD_H
#define POSITIONADD_H

#include <QDialog>

namespace Ui {
class PositionAdd;
}


enum CommandType{
    position,
    direction
};

class PositionAdd : public QDialog
{
    Q_OBJECT

private slots:
    void autoDiretionButtonToggled(bool);


public:

    Ui::PositionAdd *ui;

    explicit PositionAdd(QWidget *parent = nullptr);
    ~PositionAdd();

private:
};

#endif // POSITIONADD_H

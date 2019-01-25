#ifndef INITIALVALUESETTINGS_H
#define INITIALVALUESETTINGS_H

#include <QDialog>
#include "controller.h"
#include "datatypes.h"

namespace Ui {
class InitialValueSettings;
}

class InitialValueSettings : public QDialog
{
    Q_OBJECT

public:
    explicit InitialValueSettings(QWidget *parent = nullptr);
    ~InitialValueSettings();

    void setDefaultValues(const CONTROL_DATA_FORMAT &ControlData);

private:
    Ui::InitialValueSettings *ui;
};

#endif // INITIALVALUESETTINGS_H

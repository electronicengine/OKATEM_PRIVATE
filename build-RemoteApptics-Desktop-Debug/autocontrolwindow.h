#ifndef AUTOCONTROLWINDOW_H
#define AUTOCONTROLWINDOW_H

#include <QWidget>

namespace Ui {
class AutoControlWindow;
}

class AutoControlWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AutoControlWindow(QWidget *parent = nullptr);
    ~AutoControlWindow();

private:
    Ui::AutoControlWindow *ui;
};

#endif // AUTOCONTROLWINDOW_H

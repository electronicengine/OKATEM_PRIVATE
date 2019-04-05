#ifndef AUTOCONTROLPANEL_H
#define AUTOCONTROLPANEL_H


#include "autocontrolwindow.h"
#include "command.h"



enum CommandActions
{
    goto_position,
    goto_direction
};

class AutoControlPanel : public AutoControlWindow
{
    Q_OBJECT

public:
    AutoControlPanel(AutoControlWindow *Window);
    void deployPanel();
    void stopExecution();
    int executeCommands();
    void deleteCommand();
    void putPositionCommand();
    void putDirectionCommand();

signals:
    void addButtonSetEnable(bool);
    void deleteButtonSetEnable(bool);
    void addCommand(QString);
    void markCommand(int);
    int showMessageBox(QWidget*, QString, QString, MessageBoxType);


private:


    void execute();
    void setPanelEnable(bool Value);
    void attachAutoControlWindow();


    Command *gpCommand;
    std::vector<std::pair<uint32_t, uint32_t>> commandListValues;
    std::vector<CommandActions> commandListActions;


    volatile bool gmExecutionAvailable = false;
    volatile bool gmExecutionStop = false;

};

#endif // AUTOCONTROLPANEL_H

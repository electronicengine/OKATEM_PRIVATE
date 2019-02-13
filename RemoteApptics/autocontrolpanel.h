#ifndef AUTOCONTROLPANEL_H
#define AUTOCONTROLPANEL_H


#include "autocontrolwindow.h"
#include "positionadd.h"
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


signals:
    void addButtonSetEnable(bool);
    void deleteButtonSetEnable(bool);
    void addCommand(QString);
    void markCommand(int);

public slots:
    void addButtonPressed();
    void deleteButtonPressed();
    void commandAddAccepted();
    void commandAddRejected();
    void addList(QString);
    void markRow(int Row);

private:

    void putPositionCommand();
    void putDirectionCommand();

    void execute();
    void setPanelEnable(bool Value);
    void attachAutoControlWindow();


    PositionAdd *gpAddingWindow;
    Command *gpCommand;
    std::vector<std::pair<uint32_t, uint32_t>> commandListValues;
    std::vector<CommandActions> commandListActions;


    volatile bool gmExecutionAvailable = false;
    volatile bool gmExecutionStop = false;

};

#endif // AUTOCONTROLPANEL_H

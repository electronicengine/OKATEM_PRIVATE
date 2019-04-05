#include "ui_positionadd.h"
#include "positionadd.h"
#include "autocontrolpanel.h"
#include "ui_autocontrolwindow.h"
#include "controlwindow.h"
#include "displaypanel.h"

AutoControlPanel::AutoControlPanel(AutoControlWindow *Window) : AutoControlWindow(Window)
{


    attachAutoControlWindow();

    gpCommand = new Command;

}



void AutoControlPanel::deployPanel()
{

}

void AutoControlPanel::stopExecution()
{
    gmExecutionStop = true;
}



int AutoControlPanel::executeCommands()
{

    std::cout << "Commands Executing..." << std::endl;

    std::thread command(&AutoControlPanel::execute, this);
    command.detach();

    return SUCCESS;
}



void AutoControlPanel::execute()
{

    int repeat = 0;
    int index = 0;
    CommandExecutionStatus status;

    gmExecutionAvailable = true;
    setPanelEnable(false);
    gpControlWindow->setPanelEnable(false);

    repeat = autocontrol_ui->spinBox->text().toInt();

    for(int i = 0; i < repeat; i++)
    {

        for(int i = 0; i < gpCommand->getCurrentCommandIndex(); i++)
        {

            if(gmExecutionStop == true)
            {
                break;
            }

            emit markCommand(i);

            std::cout << "executing command index: " << std::to_string(i) << std::endl;

            status = gpCommand->executeatIndex(i);

            if(status == failed)
                std::cout << "executing command failed: " << std::to_string(i) << std::endl;

            index++;

        }

        if(gmExecutionStop == true)
        {
            gmExecutionStop = false;
            break;
        }

    }




    setPanelEnable(true);
    gpControlWindow->setPanelEnable(true);

    gmExecutionAvailable = false;

    emit showMessageBox(gpAutoControlWindow, "Info", "Command Execution Complited", MessageBoxType::information);

    std::cout << "Command Execution Terminating..." << std::endl;


}

void AutoControlPanel::setPanelEnable(bool Value)
{
    emit addButtonSetEnable(Value);
    emit deleteButtonSetEnable(Value);
}




void AutoControlPanel::deleteCommand()
{


    typedef int(RemoteController:: *Action)(uint32_t, uint32_t);
    Action action;

    std::pair<uint32_t, uint32_t> values;

    int index = autocontrol_ui->command_list->currentRow();

    std::cout << "current: " << std::to_string(index) << std::endl;

    gpCommand->erase(index);
    autocontrol_ui->command_list->clear();

    for(int i = 0; i < gpCommand->getCurrentCommandIndex(); i++)
    {


        action = gpCommand->getActionsatIndex(i);
        values = gpCommand->getValuesatIndex(i);

        if(action == &RemoteController::gotoPositions)
        {
            emit addCommand(QString::number(i) + " - " + "X Position: "
                                                  + QString::number(values.first) + " - " + "Y Position: "
                                                  + QString::number(values.second));

        }
        else
        {
            emit addCommand(QString::number(i) + " - " + "Direction: "
                                                  + gpCommand->gmDirectionList[values.first] + " - " + "Duration: "
                                                  + QString::number(values.second));
        }


    }

}



void AutoControlPanel::putPositionCommand()
{


    gpCommand->giveCommand(gpController, &RemoteController::gotoPositions,
                           std::make_pair(gpAddingWindow->ui->x_position->text().toInt(),
                                        gpAddingWindow->ui->y_position->text().toInt()));


    emit addCommand(QString::number(gpCommand->getCurrentCommandIndex() - 1) + " - " + "X Position: "
                                          + gpAddingWindow->ui->x_position->text() + " - " + "Y Position: "
                    + gpAddingWindow->ui->y_position->text());


}

void AutoControlPanel::putDirectionCommand()
{

    gpCommand->giveCommand(gpController, &RemoteController::turntoDirection,
                           std::make_pair(gpAddingWindow->ui->direction_command->text(),
                                        gpAddingWindow->ui->duration_command->text().toInt()));


    emit addCommand(QString::number(gpCommand->getCurrentCommandIndex() - 1) + " - " + "Direction: "
                                          + gpAddingWindow->ui->direction_command->text() + " - " + "Duration: "
                                          + gpAddingWindow->ui->duration_command->text());
}



void AutoControlPanel::attachAutoControlWindow()
{

    connect(this, SIGNAL(addButtonSetEnable(bool)), autocontrol_ui->add_button, SLOT(setEnabled(bool)));

    connect(this, SIGNAL(addCommand(QString)), this, SLOT(addList(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(markCommand(int)), this, SLOT(markRow(int)), Qt::QueuedConnection);
    connect(this, SIGNAL(showMessageBox(QWidget*, QString, QString, MessageBoxType)), gpMainWindow, SLOT(showMessage(QWidget*,QString, QString , MessageBoxType)), Qt::BlockingQueuedConnection);

}

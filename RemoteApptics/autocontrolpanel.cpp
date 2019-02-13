#include "ui_positionadd.h"
#include "autocontrolpanel.h"
#include "ui_autocontrolwindow.h"
#include "controlpanel.h"
#include "displaypanel.h"

AutoControlPanel::AutoControlPanel(AutoControlWindow *Window) : AutoControlWindow(Window)
{

    gpAddingWindow = new PositionAdd(gpAutoControlWindow);

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
    gpControlPanel->setPanelEnable(false);

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
    gpControlPanel->setPanelEnable(true);

    gmExecutionAvailable = false;

    emit gpDisplaypanel->showMessageBox(gpAutoControlWindow, "Info", "Command Execution Complited", MessageBoxType::information);

    std::cout << "Command Execution Terminating..." << std::endl;


}

void AutoControlPanel::setPanelEnable(bool Value)
{
    emit addButtonSetEnable(Value);
    emit deleteButtonSetEnable(Value);
}



void AutoControlPanel::addButtonPressed()
{

    if(gpAddingWindow->ui->x_position->text() == NULL)
        gpAddingWindow->ui->x_position->setText(QString::number(gpEnvironmentInfo->step_motor2_step));

    if(gpAddingWindow->ui->y_position->text() == NULL)
        gpAddingWindow->ui->y_position->setText(QString::number(gpEnvironmentInfo->step_motor1_step));

    gpAddingWindow->show();
}



void AutoControlPanel::deleteButtonPressed()
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



void AutoControlPanel::commandAddAccepted()
{
    gpAddingWindow->hide();

    int command_type = gpAddingWindow->ui->stackedWidget->currentIndex();


    switch (command_type) {
    case position:

        putPositionCommand();

        break;

    case direction:

        putDirectionCommand();

        break;
    }



}

void AutoControlPanel::commandAddRejected()
{
    gpAddingWindow->hide();
}

void AutoControlPanel::addList(QString Str)
{
    autocontrol_ui->command_list->addItem(Str);
}

void AutoControlPanel::markRow(int Row)
{

    autocontrol_ui->command_list->setCurrentItem(autocontrol_ui->command_list->item(Row));

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

    connect(autocontrol_ui->add_button, SIGNAL(pressed()), this, SLOT(addButtonPressed()));
    connect(autocontrol_ui->delete_button, SIGNAL(pressed()), this, SLOT(deleteButtonPressed()));

    connect(this, SIGNAL(addButtonSetEnable(bool)), autocontrol_ui->add_button, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(pressed()), autocontrol_ui->delete_button, SLOT(deleteButtonPressed()));

    connect(gpAddingWindow->ui->buttonBox, SIGNAL(accepted()), this, SLOT(commandAddAccepted()));
    connect(gpAddingWindow->ui->buttonBox, SIGNAL(rejected()), this, SLOT(commandAddRejected()));

    connect(this, SIGNAL(addCommand(QString)), this, SLOT(addList(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(markCommand(int)), this, SLOT(markRow(int)), Qt::QueuedConnection);

}

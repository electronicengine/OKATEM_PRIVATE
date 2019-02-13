#include "command.h"


Command::Command()
{

}


int Command::erase(int Index)
{
   gmActions.erase(gmActions.begin() + Index, gmActions.begin() + Index + 1);
   gmValues.erase(gmValues.begin() + Index, gmValues.begin() + Index + 1);

   return SUCCESS;

}

int Command::getCurrentCommandIndex()
{
    return (int) gmActions.size();
}

void Command::giveCommand(RemoteController *Controller, Command::Action Function, std::pair<uint32_t, uint32_t> Values)
{
    gmController = Controller;

    gmActions.push_back(Function);
    gmValues.push_back(Values);

}

void Command::giveCommand(RemoteController *Controller, Command::Action Function, std::pair<QString, uint32_t> Values)
{

    std::pair<uint32_t, uint32_t> values;

    values = std::make_pair((uint32_t) convertToDirectionCommand(Values.first), Values.second);

    gmController = Controller;

    gmActions.push_back(Function);
    gmValues.push_back(values);
}


Direction Command::convertToDirectionCommand(const QString &Str)
{

    if(Str == gmDirectionList[Up])
        return Up;
    else if(Str == gmDirectionList[Down])
        return Down;
    else if(Str == gmDirectionList[Down])
        return Down;
    else if(Str == gmDirectionList[Left])
        return Left;
    else if(Str == gmDirectionList[Right])
        return Right;
    else if(Str == gmDirectionList[UpLeft])
        return UpLeft;
    else if(Str == gmDirectionList[UpRight])
        return UpRight;
    else if(Str == gmDirectionList[DownLeft])
        return DownLeft;
    else if(Str == gmDirectionList[DownRight])
        return DownRight;
    else
        return stop;

}



CommandExecutionStatus Command::executeatIndex(int Index)
{


    int ret = FAIL;

    if(gmActions.size() != 0)
    {
        ret = (gmController->*gmActions[Index])(gmValues[Index].first, gmValues[Index].second);

        if(ret == SUCCESS)
            return succesfull;
        else
            return failed;

    }
    else
    {
        return failed;
    }

}

CommandExecutionStatus Command::executeAll()
{
    int ret;

    for(size_t i = 0; i < gmActions.size(); i++)
        ret = (gmController->*gmActions[i])(gmValues[i].first, gmValues[i].second);

    if(ret == FAIL)
        return failed;
    else
        return succesfull;

}

Command::Action Command::getActionsatIndex(int Index)
{
    return gmActions[Index];
}

std::pair<uint32_t, uint32_t> Command::getValuesatIndex(int Index)
{
    return gmValues[Index];
}


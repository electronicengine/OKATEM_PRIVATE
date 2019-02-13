#ifndef COMMAND_H
#define COMMAND_H

#include "remotecontroller.h"


enum CommandExecutionStatus
{
    succesfull,
    finished,
    failed
};


class Command
{
public:
   typedef int(RemoteController:: *Action)(uint32_t, uint32_t);

   QStringList gmDirectionList = {"Up", "Down", "Left", "Right", "UpLeft", "UpRight", "DownLeft", "DownRight"};

   Command();
   int erase(int Index);
   int getCurrentCommandIndex();
   void giveCommand(RemoteController *Controller, Command::Action Function, std::pair<uint32_t, uint32_t> Values);
   void giveCommand(RemoteController *Controller, Command::Action Function, std::pair<QString, uint32_t> Values);

   CommandExecutionStatus executeatIndex(int Index);
   CommandExecutionStatus executeAll();
   Action getActionsatIndex(int index);
   std::pair<uint32_t, uint32_t> getValuesatIndex(int Index);

 private:

   Direction convertToDirectionCommand(const QString &Str);

   std::vector<Command::Action> gmActions;

   std::vector<std::pair<uint32_t, uint32_t>> gmValues;

   RemoteController *gmController;
   Action gmFunction;
};

#endif // COMMAND_H

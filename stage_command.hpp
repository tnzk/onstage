#ifndef COMMAND_HEADER

#define COMMAND_HEADER

#include "picojson.h"
class TheStage;

class IStageCommand
{
private:
  
public:
  virtual bool Execute(TheStage&) = 0;
};

class MoveStageCommand : public IStageCommand
{
private:
public:
  MoveStageCommand();
  ~MoveStageCommand();
  virtual bool Execute(TheStage&);
};

class NullStageCommand : public IStageCommand
{
private:
public:
  NullStageCommand();
  ~NullStageCommand();
  virtual bool Execute(TheStage&);
};

class SyncStageCommand : public IStageCommand
{
private:
  int sync_at;
public:
  SyncStageCommand(int frame);
  ~SyncStageCommand();
  virtual bool Execute(TheStage&);
};

class StageCommandFactory
{
public:
  static IStageCommand& Create(picojson::value&);
};
// 

#endif

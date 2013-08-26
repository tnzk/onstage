#include "picojson.h"

#ifndef COMMAND_HEADER

#define COMMAND_HEADER

class IStageCommand
{
private:
  
public:
  virtual bool Execute() = 0;
};

class MoveStageCommand : public IStageCommand
{
private:
public:
  MoveStageCommand();
  ~MoveStageCommand();
  virtual bool Execute();
};

class NullStageCommand : public IStageCommand
{
private:
public:
  NullStageCommand();
  ~NullStageCommand();
  virtual bool Execute();
};

class SyncStageCommand : public IStageCommand
{
private:
  int sync_at;
public:
  SyncStageCommand(int frame);
  ~SyncStageCommand();
  virtual bool Execute();
};

class StageCommandFactory
{
public:
  static IStageCommand& Create(picojson::value&);
};
// 

#endif

#ifndef COMMAND_HEADER

#define COMMAND_HEADER

class IStageCommand
{
private:
  
public:
  virtual bool Execute();
};

class MoveStageCommand : public IStageCommand
{
private:
public:
  MoveStageCommand();
  ~MoveStageCommand();
  virtual bool Execute();
};

#endif

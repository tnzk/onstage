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

#endif

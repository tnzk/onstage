import os
import os.path
import sys
import itertools

if not os.path.isfile('onstage.cpp'):
    print('Use this script at the repositry root.')
    sys.exit()

if len(sys.argv) < 2:
    print('Usage: ' + sys.argv[0] + ' command_name_like_this s s d d...')
    sys.exit()

command_name = sys.argv[1]
arg_types = sys.argv[2:]

words = command_name.split('_')
macro_name = '_'.join([w.upper() for w in words])
class_name = ''.join([w.capitalize() for w in words])

type_map = {'s': 'std::string', 'd': 'double'}
constructor_arg_types = ', '.join([type_map[c] for c in arg_types])
constructor_arg_names = ', '.join(['%s param%s' % t for t in zip([type_map[c] for c in arg_types], itertools.count())])

hpp_filename = 'stage_command_%s.hpp' % command_name
hpp_content = '''\
#ifndef STAGE_COMMAND_%s_HPP
#define STAGE_COMMAND_%s_HPP

#include <string>
#include "thestage.hpp"

class %sStageCommand : public IStageCommand
{
public:
  %sStageCommand(%s);
  ~%sStageCommand();
  virtual bool Execute(TheStage&);
  virtual std::string Serialize();
private:
  // Declare here private members for paramters.
};

#endif''' % (macro_name, macro_name, class_name, class_name, constructor_arg_types, class_name)

cpp_filename = 'stage_command_%s.cpp' % command_name
cpp_content = '''
#include "%s"
#include "thestage.hpp"
#include <sstream>

%sStageCommand::%sStageCommand(%s)
{
}

%sStageCommand::~%sStageCommand()
{
}

bool %sStageCommand::Execute(TheStage& stage)
{
  // TODO: Implement here.
}

std::string %sStageCommand::Serialize()
{
  // TODO: Implement here.
  std::stringstream ss;
  ss << "[\\"%s\\", \\"" << "]";
  return ss.str();
}''' % (hpp_filename, class_name, class_name, constructor_arg_names, class_name, class_name, class_name, class_name, command_name)

# TODO: Check if the files to be written have already existed.

cpp_path = 'commands/%s' % cpp_filename
cpp = open(cpp_path, 'w')
cpp.write(cpp_content)
cpp.close()
print 'Generated %s.' % cpp_path

hpp_path = 'headers/%s' % hpp_filename
hpp = open(hpp_path, 'w')
hpp.write(hpp_content)
hpp.close()
print 'Generated %s.' % hpp_path

# TODO: Show this.
generator_args = ', '.join(['command[%s].get<%s>()' % (t[1] + 1, t[0]) for t in zip([type_map[c] for c in arg_types], itertools.count())])
generator_snippet = '''\
    stageCommandFactoryMap.insert(std::make_pair("left_hand", [](picojson::array& command) -> IStageCommand* {
      IStageCommand* cmd = new LeftHandStageCommand(
        %s
      );
      return cmd;
    }));''' % generator_args

print '''TODO:
    * Paste the generator code below to stage_command.cpp.
    * Add object file for this to Makefile.
    * Insert new #include to header_inclusion.hpp.
    * Implement cpp.

----
%s
----

Done. Yey.
''' % generator_snippet

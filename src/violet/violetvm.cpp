#include <iostream>
#include <algorithm>
#include <boost/algorithm/string/join.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include "headers/violetvm.hpp"
#include "intermediate/headers/bytecode.hpp"
#include "runtime/headers/stdclass.hpp"
#include "runtime/headers/valueobject.hpp"
#include "runtime/headers/lambda.hpp"
#include "intermediate/headers/context.hpp"

void
VioletVM::run(std::vector<int> instructions, std::vector< boost::variant<int,float,std::string> > literals, std::vector<Context*> scopes)
{

  this->instructions = instructions;
  this->literals     = literals;
  this->scopes       = scopes;

  for (std::vector<int>::iterator ip = instructions.begin() ; ip != instructions.end(); ++ip)
  {
    switch(*ip)
    {
      case CALL:
      {
        ip++;
        int argc = *ip;

        std::vector<Runtime::Object*> arguments;
        std::string method        = boost::get<std::string>((STACK_POP())->getValue());
        Runtime::Object *receiver = STACK_POP();
        for(int i = 0; i < argc; i++)
        {
          arguments.push_back(STACK_POP());
        }
        std::reverse(arguments.begin(),arguments.end());
        // push the returned valued onto the stack
        STACK_PUSH(receiver->call(method, arguments));
        receiver = NULL;
        break;
      }
      case PUSH_STRING:
      {
        ip++;
        STACK_PUSH(new Runtime::ValueObject(boost::get<std::string>(literals[*ip])));
        break;
      }
      case PUSH_INTEGER:
      {
        ip++;
        STACK_PUSH(new Runtime::ValueObject(boost::get<int>(literals[*ip])));
        break;
      }
      case PUSH_FLOAT:
      {
        ip++;
        STACK_PUSH(new Runtime::ValueObject(boost::get<float>(literals[*ip])));
        break;
      }
      case PUSH_SELF:
      {
        ip++;
        STACK_PUSH((scopes[*ip])->getCurrentSelf());
        break;
      }
      case PUSH_CONSTANT:
      {
        ip++;
        int obj_name = *ip;
        ip++;
        STACK_PUSH(scopes[*ip]->getCurrentClass()->getConstant(boost::get<std::string>(literals[obj_name])));
        break;
      }
      case JUMP_UNLESS:
      {
        Runtime::Object *bool_result = STACK_POP();
        ip++;
        int instruction_count = *ip;
        if(bool_result->getStdClass()->getName() == std::string("FalseClass")) ip += instruction_count;
        break;
      }
      case PUSH_LAMBDA:
      {
        ip++;
        int context = *ip;
        std::vector<std::string> parameters;
        std::vector<int> instructions;

        //parameter information
        ip++;
        int parameter_count = *ip;
        for(int i = 1; i <= parameter_count; i++)
        {
          ip++;
          parameters.push_back(boost::get<std::string>( literals[((scopes[context])->local_bytes[*ip])] ));
        }

        // setting locals
        ip++;
        int argument_count = *ip;
        for(int i = 1; i <= argument_count; i++)
        {
          for(int j = 1; j <= 3; j++)
          {
            ip++;
            instructions.push_back(*ip);
          }
        }

        // lambda body code
        ip++;
        int instruction_count = *ip;
        for(int i = 1; i <= instruction_count; i++)
        {
          ip++;
          instructions.push_back(*ip);
        }

        // RETURN opcode
        ip++;
        instructions.push_back(*ip);

        STACK_PUSH(new Runtime::LambdaObject(parameters, instructions, context, this));
        break;
      }
      case SET_LOCAL:
      {
        ip++;
        int local = *ip;
        ip++;
        (scopes[*ip])->setLocal(local, STACK_POP());
        break;
      }
      case GET_LOCAL:
      {
        ip++;
        int local = *ip;
        ip++;
        STACK_PUSH((scopes[*ip])->getLocal(local));
        break;
      }
      case RETURN:
      {
        goto stackdump;
        break;
      }
    }
  }

  stackdump:
    std::string joinedString = boost::algorithm::join(instructions |
      boost::adaptors::transformed(static_cast<std::string(*)(int)>(std::to_string))
    , " ");
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "Total Instructions: " << instructions.size() << std::endl;
    std::cout << "Total Literals: "     << literals.size()     << std::endl;
    std::cout << "Total Scopes: "       << scopes.size()       << std::endl;
    std::cout << "Stack Size: "         << stack.size()        << std::endl;
    std::cout << joinedString << std::endl;
}

void
VioletVM::STACK_PUSH(Runtime::Object* object)
{
  this->stack.push_back(object);
}

Runtime::Object*
VioletVM::STACK_POP()
{
  Runtime::Object* object = *(this->stack.end() - 1);
  this->stack.pop_back();
  return object;
}
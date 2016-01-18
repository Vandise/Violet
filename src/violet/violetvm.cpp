#include <iostream>
#include "headers/violetvm.hpp"
#include "intermediate/headers/bytecode.hpp"
#include "runtime/headers/stdclass.hpp"
#include "runtime/headers/valueobject.hpp"
#include "intermediate/headers/context.hpp"

void
VioletVM::run(std::vector<int> instructions, std::vector< boost::variant<int,float,std::string> > literals, std::vector<Context*> scopes)
{
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
      case PUSH_SELF:
      {
        ip++;
        STACK_PUSH((scopes[*ip])->getCurrentSelf());
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
    std::cout << "Total Instructions: " << instructions.size() << std::endl;
    std::cout << "Total Literals: "     << literals.size()     << std::endl;
    std::cout << "Total Scopes: "       << scopes.size()       << std::endl;
    std::cout << "Stack Size: "         << stack.size()        << std::endl;
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
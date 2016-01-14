#ifndef __BYTECODETBL_HPP__
#define __BYTECODETBL_HPP__ 1

enum
{
  //                                                            ------------ STACK ----------
  // Opcode                         operands                    before                  after
  //-----------------------------------------------------------------------------------------------------
  /* 00 */    CALL,             // index, argc                 [rcv, arg...]           [returned]
  /* 01 */    PUSH_INTEGER,     // index                       []                      [ValueObj]
  /* 02 */    PUSH_FLOAT,       // index                       []                      [ValueObj]
  /* 03 */    PUSH_STRING,      // index                       []                      [ValueObj]

  /* FF */    RETURN            //                             []                      []
};

#endif
#ifndef __BYTECODETBL_HPP__
#define __BYTECODETBL_HPP__ 1

enum
{
  //                                                            ------------ STACK ----------
  // Opcode                         operands                    before                  after
  //-----------------------------------------------------------------------------------------------------
  /* 00 */    CALL,             // index, argc, context        [rcv, args]             [returned]
  /* 01 */    PUSH_INTEGER,     // index                       []                      [ValueObj]
  /* 02 */    PUSH_FLOAT,       // index                       []                      [ValueObj]
  /* 03 */    PUSH_STRING,      // index                       []                      [ValueObj]
  /* 04 */    PUSH_ARRAY,       // index                       []                      [ArrayObj]
  /* 05 */    PUSH_HASH,        // index                       []                      [HashObj]
  /* 06 */    PUSH_LAMBDA,      // index                       []                      [LambdaObj]
  /* 07 */    PUSH_SELF,        // index, context              []                      [self]
  /* 08 */    GET_LOCAL,        // index, context              []                      [value]
  /* 09 */    SET_LOCAL,        // index, context              []                      []

  /* FF */    RETURN            //                             []                      []
};

#endif
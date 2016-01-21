#ifndef __BYTECODETBL_HPP__
#define __BYTECODETBL_HPP__ 1

enum
{
  //                                                            ------------ STACK ----------
  // Opcode                         operands                    before                  after
  //-----------------------------------------------------------------------------------------------------
  /* 00 */    CALL,             // index, argc                 [rcv, args]             [returned]

// PUSH Opcodes
  /* 01 */    PUSH_INTEGER,     // index                       []                      [ValueObj]
  /* 02 */    PUSH_FLOAT,       // index                       []                      [ValueObj]
  /* 03 */    PUSH_STRING,      // index                       []                      [ValueObj]
  /* 04 */    PUSH_ARRAY,       // index                       []                      [ArrayObj]
  /* 05 */    PUSH_HASH,        // index                       []                      [HashObj]
  /* 06 */    PUSH_LAMBDA,      // index                       []                      [LambdaObj]
  /* 07 */    PUSH_SELF,        // index, context              []                      [self]
  /* 08 */    PUSH_OBJECT,      // index                       []                      [object]
  /* 09 */    PUSH_CONSTANT,    // index                       []                      [object]
  /* 10 */    PUSH_RESV3,
  /* 11 */    PUSH_RESV4,
  /* 12 */    PUSH_RESV5,
  /* 13 */    PUSH_RESV6,
  /* 14 */    PUSH_RESV7,
  /* 15 */    PUSH_RESV8,

// LOCAL Opcodes
  /* 16 */    GET_LOCAL,        // index, context              []                      [value]
  /* 17 */    SET_LOCAL,        // index, context              []                      []
  /* 18 */    LOCAL_RESV1,
  /* 19 */    LOCAL_RESV2,
  /* 20 */    LOCAL_RESV3,

  /* FF */    RETURN            //                             []                      []
};

#endif
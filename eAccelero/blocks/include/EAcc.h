#ifndef __EACC_EAcc_h
#define __EACC_EAcc_h

#include <sys/types.h>
#include <stdint.h>

// Used for branch prediction in conditional statements
#define BRANCH_EXPECT   __builtin_expect

#define EACC_LIKELY(_cond_)    BRANCH_EXPECT((_cond_), 1)
#define EACC_UNLIKELY(_cond_)  BRANCH_EXPECT((_cond_), 0)

#endif // __EACC_EAcc_h

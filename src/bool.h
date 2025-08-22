#ifndef __bool__
#define __bool__

#ifdef __cplusplus
extern "C" {
#endif
/**
 * Type: bool
 * ----------
 * Provides a lame but adequate stand-in for the bool we're used
 * to having around in C++.  Recall that enum definitions by default
 * associate the integer 0 with the first enumerated constant, 1
 * with the second, etc.  That means that false is equated with 0 and
 * true is equated with 1.
 */

typedef enum {
  FALSE=0,TRUE=1 
} mybool;

#ifdef __cplusplus
}
#endif

#endif

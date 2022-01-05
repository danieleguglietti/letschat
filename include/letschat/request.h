#ifndef __REQUEST__
#define __REQUEST__

#ifndef __PRIVATE_MODIFIER
#   define __PRIVATE_MODIFIER(x) __##x
#   define private(x) __PRIVATE_MODIFIER(x)
#endif

#endif
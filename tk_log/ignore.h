#ifndef _IGNORE_H
#define _IGNORE_H



#define IGN_1(X) ((void)(X))
#define IGN_2(X, ...) ((void)(X));IGN_1(__VA_ARGS__)
#define IGN_3(X, ...) ((void)(X));IGN_2(__VA_ARGS__)
#define IGN_4(X, ...) ((void)(X));IGN_3(__VA_ARGS__)
#define IGN_5(X, ...) ((void)(X));IGN_4(__VA_ARGS__)
#define IGN_6(X, ...) ((void)(X));IGN_5(__VA_ARGS__)
#define IGN_7(X, ...) ((void)(X));IGN_6(__VA_ARGS__)
#define IGN_8(X, ...) ((void)(X));IGN_7(__VA_ARGS__)
#define IGN_9(X, ...) ((void)(X));IGN_8(__VA_ARGS__)
#define IGN_10(X, ...) ((void)(X));IGN_9(__VA_ARGS__)
#define IGN_11(X, ...) ((void)(X));IGN_10(__VA_ARGS__)
#define IGN_12(X, ...) ((void)(X));IGN_11(__VA_ARGS__)
#define IGN_13(X, ...) ((void)(X));IGN_12(__VA_ARGS__)
#define IGN_14(X, ...) ((void)(X));IGN_13(__VA_ARGS__)
#define IGN_15(X, ...) ((void)(X));IGN_14(__VA_ARGS__)
#define IGN_16(X, ...) ((void)(X));IGN_15(__VA_ARGS__)
#define IGN_17(X, ...) ((void)(X));IGN_16(__VA_ARGS__)
#define IGN_18(X, ...) ((void)(X));IGN_17(__VA_ARGS__)
#define IGN_19(X, ...) ((void)(X));IGN_18(__VA_ARGS__)
#define IGN_20(X, ...) ((void)(X));IGN_19(__VA_ARGS__)

#define GET_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, \
                  _13, _14, _15, _16, _17, _18, _19, _20, NAME, ...) NAME
#define IGNORE(...) \
    GET_MACRO(__VA_ARGS__, IGN_20, IGN_19, IGN_18, IGN_17, IGN_16, IGN_15, \
              IGN_14, IGN_13, IGN_12, IGN_11, IGN_10, IGN_9, IGN_8, IGN_7, \
              IGN_6, IGN_5, IGN_4, IGN_3, IGN_2, IGN_1)(__VA_ARGS__)

#endif

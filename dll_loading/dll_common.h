#ifdef EXPLORERDLL_EXPORT

#define EXPLORERDLL_API __declspec(dllexport)

#else

#define EXPLORERDLL_API __declspec(dllimport)

#endif

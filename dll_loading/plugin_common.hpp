#ifdef EXPLORERDLL_EXPORT

#pragma warning(push)
#pragma warning(disable: 4005)
#define EXPLORERDLL_API __declspec(dllexport)

#else

#define EXPLORERDLL_API __declspec(dllimport)
#pragma warning(pop)
#endif

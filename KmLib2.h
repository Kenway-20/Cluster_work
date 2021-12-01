//
// Created by LENOVO on 2021/11/25.
//


#ifdef _WIN32
#ifdef KM_EXPORTS
#define KM_API __declspec(dllexport)
#else
#define KM_API __declspec(dllimport)
#endif
#else
#define KM_API
#endif

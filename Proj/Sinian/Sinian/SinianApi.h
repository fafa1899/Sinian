#ifndef SINIAN_API_H
#define SINIAN_API_H

#ifdef SINIAN_EXPORTS
#define SINIAN_API __declspec(dllexport)
#else
#define SINIAN_API __declspec(dllimport)
#endif

typedef void* (*LoadProc)(const char* name);

//Todo:Need Fix
void SINIAN_API PrepareGraphicContext(LoadProc load);

#endif
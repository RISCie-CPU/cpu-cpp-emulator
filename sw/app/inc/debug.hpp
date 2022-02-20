#pragma once

#ifdef DEBUG
# define dbg(MSG) (std::cerr << "\033[33;1m\033[1mDEBUG >> " MSG << "\033[0\n")
#else
# define dbg(MSG) do { } while (0)
#endif

#define info(MSG) (std::cout << "\033[35;1m\033[1mINFO  >> " MSG << "\033[0\n")

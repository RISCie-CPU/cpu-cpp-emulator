#pragma once

#ifdef DEBUG
# define dbg(MSG) (std::cerr << "\033[33;1m\033[1mDEBUG: " MSG << "\033[0\n")
#else
# define dbg(MSG) do { } while (0)
#endif

#pragma once

#ifdef DEBUG
# define dbg(MSG) (std::cerr << (MSG) << '\n')
#else
# define dbg(MSG) do { } while (0)
#endif

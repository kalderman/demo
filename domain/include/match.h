#ifndef __MATCH_H__
#define __MATCH_H__

template<class... Ts> struct match : Ts... { using Ts::operator()...; };
template<class... Ts> match(Ts...) -> match<Ts...>;

#endif // __MATCH_H__

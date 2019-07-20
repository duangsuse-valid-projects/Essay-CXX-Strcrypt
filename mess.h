#ifndef MESS_H
#define MESS_H

#ifndef MESS_KEY
#define MESS_KEY (-1)
#endif
#ifndef MESS_BUF
#define MESS_BUF 1024
#endif

#include <vector>
#include <iostream>

#include "literal_str.hpp"

constexpr literal_str make_a_mess(const literal_str s, unsigned offset);
const char *unmess(const literal_str &);

template <size_t N>
constexpr literal_str messy(const char (&raw)[N]) {
  return make_a_mess(raw, MESS_KEY);
}

/*template <size_t N>
const static inline char *mess(const char (&raw)[N]) {
  return unmess(messy<N>(raw));
}*/

#define mess(s) unmess(messy(s))

constexpr literal_str make_a_mess(const literal_str s, unsigned offset) {
  char buffer[MESS_BUF] = {'\00'};
  //static_assert (sizeof(buffer) >= s.head_size(), "");
  if (sizeof(buffer) <= s.head_size()) return "ERROR, increase your MESS_BUF macro definition";
  s.copy_to(&buffer[0], &buffer[sizeof(buffer)]);
  //cout << "Got " << buffer << endl;
  for (size_t i = 0; i < s.size(); ++i) {
    buffer[i] = buffer[i] + static_cast<char>(offset);
  }
  buffer[s.last_idx()+1] = '\0';
  //cout << "Proc " << buffer << endl;
  //if (s.tail() ==nullptr) return literal_str(buffer);
  //return literal_str(buffer) + make_a_mess(*s.tail(), offset);
  return literal_str(buffer, s.size());
}

const char *unmess(const literal_str &lit) {
  char *result = new char[lit.size()];
  result[sizeof(result)-1] = '\00';
  lit.copy_to(&result[0], &result[lit.size()]);

  for (size_t i = 0; i < lit.size(); ++i) {
    result[i] = result[i] - static_cast<char>(MESS_KEY);
  }

  result[lit.last_idx()+1] = '\00';

  return result;
}

#endif // MESS_H

#pragma once

#include <string>
#include <cstring>

using namespace std;
// Ref: https://www.daniweb.com/programming/software-development/code/482276/c-11-compile-time-string-concatenation-with-constexpr
class literal_str {
private:
  typedef size_t usize;
  const char *const str;
  const usize len;
  const literal_str *const prefix;

public:
  template <usize N>
  constexpr
  literal_str(const char (&head)[N], const literal_str *tail = nullptr)
    : str(head), len(N-1), prefix(tail) {
    static_assert ((N-1) >=0, "Length must not be negative");
  }
  constexpr explicit
  literal_str(const char* head, usize n, const literal_str* tail = nullptr)
    : str(head), len(n), prefix(tail) {}

  constexpr const char *head() const { return this->str; }
  constexpr usize head_size() const { return this->len; }
  constexpr const literal_str *tail() const { return this->prefix; }

  constexpr usize size() const {
    return this->len + tail_len();
  }

  constexpr usize last_idx() const { return size() -1; }

  constexpr char operator[](usize n)
    const { return get_char(n); }

  template <usize N>
  constexpr literal_str operator+(const char (&rhs)[N]) const {
    return literal_str(rhs, this);
  }
  constexpr literal_str operator+(const literal_str &rhs) const {
    return literal_str(rhs.str, rhs.len, this);
  }

  template <typename Iter>
  void copy_to(Iter beg, Iter end) const {
    copy_to_recurse(beg, end);
  }
  void copy_to(char* beg, char* end) const {
    copy_to_recurse(beg, end);
  }

  static string to_str(const literal_str &lit) {
    string result(lit.size(), ' ');
    lit.copy_to(result.begin(), result.end());
    return result;
  }

protected:
  constexpr usize slice_size() const { return this->len; }
  constexpr char at(usize idx) const { return this->str[idx]; }

  constexpr usize tail_len() const
    { return (prefix !=nullptr)? prefix->size() : 0; }

  constexpr char get_char(usize idx) const {
    if (idx >= this->size()) return '\00';
    if (prefix ==nullptr) return this->at(idx);
    return (idx >= this->prefix->size())?
      this->at(idx - prefix->size())
    : prefix->get_char(idx);
  }

  template <typename Iter>
  void copy_to_recurse(Iter &beg, Iter end) const {
    if(prefix !=nullptr)
      prefix->copy_to_recurse(beg, end);
    for(unsigned i = 0;
       (beg != end) && (i < len);
        ++i, ++beg) *beg = str[i];
  }

  void copy_to_recurse(char* &beg, char* end) const {
    if(prefix != nullptr)
      prefix->copy_to_recurse(beg, end);
    usize sziter = static_cast<usize>(end - beg);
    usize szncpy = static_cast<usize>(min(sziter, len));
    memcpy(beg, str, szncpy);
    beg += szncpy;
  }
};

#ifndef HANDLECHARS__H
#define HANDLECHARS__H
#include <string>
#include <map>
using std::multimap;
using std::string;

class HandleChars {
public:
  HandleChars() : xmlData() {}
  void operator()(const string&);
  const multimap<string, string>& getData() const { return xmlData; }
private:
  multimap<string, string> xmlData;
};
#endif

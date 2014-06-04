#include <string>
#include <map>
using std::multimap;
using std::string;

#include "parseXML.h"

void HandleChars::operator()(const string& str) {
  string lastTag = ParseXML::getInstance()->getLastTag();
  xmlData.insert(std::pair<string,string>(lastTag, str));
}

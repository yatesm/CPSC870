#ifndef PARSEXML__H
#define PARSEXML__H
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <expat.h>

#include "handleChars.h"

using std::cerr; using std::cout; using std::endl;
using std::string; 
const int BUFSIZE = 8192;

class ParseXML {
public:
  static ParseXML* getInstance();
  //parseXML choreographs the parse of filename & possibly calls handle()
  void parseXML(const string& filename, HandleChars* hand = NULL);
  const string& getLastTag() const { return lastTag; }

  static void wrapper4Start(void *data, const char *el, const char **attr);
  static void wrapper4End(void *data, const char *el);
  static void wrapper4Chars(void *data, const char *text, int textlen);
  ~ParseXML() { XML_ParserFree(parser); }
private:
  XML_Parser parser;
  HandleChars* handle;

  char buff[BUFSIZE];
  static ParseXML* instance;
  string  nextToLastTag;
  string  lastTag;

  ParseXML() : 
    parser(NULL), 
    handle(NULL),
    nextToLastTag(), lastTag()
  {}

  void start(void *data, const char *el, const char **attr);
//  void end(void *data, const char *el) {}
  void end(void *, const char *) {}
  void chars(void *data, const char *text, int textlen);
  void stripWhiteSpace(string&) const;
  void stripTrailWhiteSpace(string&) const;
  ParseXML& operator=(const ParseXML&);
  ParseXML(const ParseXML&);
};
#endif

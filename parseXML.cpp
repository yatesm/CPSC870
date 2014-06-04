#include "parseXML.h"

void ParseXML::start(void *, const char *el, const char **) {
  nextToLastTag = lastTag;
  lastTag = el;
  //cout << el;
  //for (int i = 0; attr[i]; i += 2) {
    //cout << ' ' << attr[i] << " = " << attr[i + 1] << endl;
  //}
}

void ParseXML::stripTrailWhiteSpace(std::string& str) const {
  int length = str.size();   
  int i = length-1;
  while (i >= 0) { 
    if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t') {
      break;
    }
    else if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t') {
      str.erase(i, 1);
    }
    --i;
  }
}

void ParseXML::stripWhiteSpace(std::string& str) const {
  int length = str.size();   
  int i = 0;
  while (i < length) { 
    if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t') {
      str.erase(i, 1);
      i--;
    }
    ++i;
  }
  str[i]='\0';
}

void ParseXML::chars(void *, const char *text, int textlen) {
  // The text is not zero terminated; thus we need the  length:
  std::string str(text, textlen);
  // The text is loaded with white space:
  stripTrailWhiteSpace(str);
  if ( str.size() ) {
    if ( handle ) (*handle)(str); 
    //std::cout << str << std::endl;
  }
}

void ParseXML::parseXML(const std::string& filename, HandleChars* hand) {
  parser = XML_ParserCreate(NULL);
  if (!parser) {
    throw std::string("Couldn't allocate memory for parser");
  }
  if ( hand ) handle = hand;

  XML_SetElementHandler(parser, wrapper4Start, wrapper4End);
  XML_SetCharacterDataHandler(parser, wrapper4Chars);
  std::fstream in;
  in.open(filename.c_str(), std::ios::in);
  if (!in) { // couldn't open the game file
    throw std::string("Cannot open xml file: ")+filename;
  }

  int length = 0;
  in.read( buff, BUFSIZE );
  while ( true ) {

    if (! XML_Parse(parser, buff, in.gcount(), length)) {
      cerr << "Parse error at line "
	         << XML_GetCurrentLineNumber(parser)
	         << XML_ErrorString(XML_GetErrorCode(parser))
           << endl;
      exit(-1);
    }

    if ( in.eof() ) break;
    else in.read( buff, BUFSIZE );
  }
  XML_ParserFree(parser);
}

ParseXML* ParseXML::getInstance() {
  if (!instance) instance = new ParseXML;
  return instance;
}

void ParseXML::
wrapper4Start(void *data, const char *el, const char **attr) {
  ParseXML::getInstance()->start(data, el, attr);
}

void ParseXML::wrapper4End(void *data, const char *el) {
  ParseXML::getInstance()->end(data, el);
}

void ParseXML::wrapper4Chars(void *data, const char *text, int textlen) {
  ParseXML::getInstance()->chars(data, text, textlen);
}


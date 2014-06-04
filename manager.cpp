#include <cmath>
#include <ctime>
#include <string>

#include "manager.h"

Manager::~Manager() {}

Manager::Manager() :
   io(IOManager::getInstance()), fact(Factory::getInstance()), 
/*   sManager(SoundManager::getInstance()),   mFact(MusicFactory::getInstance()),*/
   collisions(CollisionSingleton::getInstance()), flee(FleeSingleton::getInstance()),
   screen(io->getScreen()),  done(false), timer(), loadFlag(false), amPlaying(false)
{
 	//sManager->load();
}

void Manager::drawAndUpdateSprite(vector<Sprite *> &v, Uint32 ticks) {
	for(unsigned int i = 0; i < v.size(); ++i) {
		v[i]->update(ticks);
		v[i]->draw();
	}
}

void Manager::saveSprite(const vector<Sprite *> &v, const char *filename, const char *directory) const {
	std::fstream out;
	string saveString = "save/";
	saveString += directory;
	saveString += "/";
	saveString += filename;
	saveString += "s.xml";
	out.open(saveString.c_str(), std::ios::out);
	if(!out) {
		throw std::string(saveString);
	}
	out << "<"<<filename<<"s>"<<endl;
	for(unsigned int i = 0; i < v.size(); ++i) {
		cout<<fact->getFrameKey(v[i]->getFrame())<<endl;
		v[i]->save(out);
	}
	out << "</"<<filename<<"s>" << endl;
	out.close();
}

void Manager::saveBullets(const vector<Bullet> &v, const char *filename, const char *directory) const {
	std::fstream out;
	string saveString = "save/";
	saveString += directory;
	saveString += "/";
	saveString += filename;
	saveString += "s.xml";
	out.open(saveString.c_str(), std::ios::out);
	if(!out) {
		throw std::string(saveString);
	}
	out << "<"<<filename<<"s>"<<endl;
	for(unsigned int i = 0; i < v.size(); ++i) {
		v[i].save(out);
	}
	out << "</"<<filename<<"s>" << endl;
	out.close();
}

void Manager::loadBullets(vector<Bullet> &v, const char *filename, const char *directory) {
	string loadString = "save/";
	loadString += directory;
	loadString += "/";
	loadString += filename;
	loadString += "s.xml";
	HandleChars * h = new HandleChars();
	ParseXML * p = ParseXML::getInstance();
	p->parseXML(loadString.c_str(), h);	
	float x, y, xs, ys;
	string frameString;
	multimap<string, string> bulletMap = h->getData();
	multimap<string, string>::iterator it = bulletMap.begin();
	while(it != bulletMap.end()) {
		it = bulletMap.find("x");
		x = atof(it->second.c_str());	
		bulletMap.erase(it);
		it = bulletMap.find("y");
		y = atof(it->second.c_str());
		bulletMap.erase(it);
		it = bulletMap.find("xInitialSpeed"); bulletMap.erase(it);
		it = bulletMap.find("yInitialSpeed"); bulletMap.erase(it);
		it = bulletMap.find("xSpeed");
		xs = atof(it->second.c_str());
		bulletMap.erase(it);
		it = bulletMap.find("ySpeed");
		ys = atof(it->second.c_str());
		bulletMap.erase(it);
		it = bulletMap.find("isTracked");
		bulletMap.erase(it);
		it = bulletMap.find("frameString");
		frameString = it->second;
		bulletMap.erase(it);
		cout<<"Pushing back bullet"<<endl;
		cout<<"frameString = "<<frameString<<endl;
		v.push_back(Bullet(x, y, xs, ys, fact->getFrame(frameString)));
		it = bulletMap.begin();
	}
	delete h;
	bulletMap.clear();
}


void Manager::loadSprite(vector<Sprite *> &v, const char *filename, const char *directory) {
	string loadString = "save/";
	loadString += directory;
	loadString += "/";
	loadString += filename;
	loadString += "s.xml";
	HandleChars * h = new HandleChars();
	ParseXML * p = ParseXML::getInstance();
	p->parseXML(loadString.c_str(), h);	
	float x, y, xs, ys, ixs, iys;
	bool isTracked = false;
	string frameString;
	multimap<string, string> spriteMap = h->getData();
	multimap<string, string>::iterator it = spriteMap.begin();
	while(it != spriteMap.end()) {
		it = spriteMap.find("x");
		x = atof(it->second.c_str());	
		spriteMap.erase(it);
		it = spriteMap.find("y");
		y = atof(it->second.c_str());
		spriteMap.erase(it);
		it = spriteMap.find("xInitialSpeed");
		ixs = atof(it->second.c_str());
		spriteMap.erase(it);
		it = spriteMap.find("yInitialSpeed");
		iys = atof(it->second.c_str());
		spriteMap.erase(it);
		it = spriteMap.find("xSpeed");
		xs = atof(it->second.c_str());
		spriteMap.erase(it);
		it = spriteMap.find("ySpeed");
		ys = atof(it->second.c_str());
		spriteMap.erase(it);
		it = spriteMap.find("isTracked");
		if(it->second == "0")
			isTracked = false;
		else
			isTracked = true;
		spriteMap.erase(it);
		it = spriteMap.find("frameString");
		frameString = it->second;
		spriteMap.erase(it);
		v.push_back(new Sprite(x, y, xs, ys, ixs, iys, isTracked, fact->getFrame(frameString)));
		it = spriteMap.begin();	
	}
	spriteMap.clear();
	delete h;
}

void Manager::loadExplosion(vector<Sprite *> &v, const char *filename, const char *directory) {
	string loadString = "save/";
	loadString += directory;
	loadString += "/";
	loadString += filename;
	loadString += "s.xml";
	HandleChars * h = new HandleChars();
	ParseXML * p = ParseXML::getInstance();
	p->parseXML(loadString.c_str(), h);	
	float x, y, xs, ys;
	string frameString;
	multimap<string, string> spriteMap = h->getData();
	multimap<string, string>::iterator it = spriteMap.begin();
	while(it != spriteMap.end()) {
		it = spriteMap.find("x");
		x = atof(it->second.c_str());	
		spriteMap.erase(it);
		it = spriteMap.find("y");
		y = atof(it->second.c_str());
		spriteMap.erase(it);
		it = spriteMap.find("xInitialSpeed"); spriteMap.erase(it);
		it = spriteMap.find("yInitialSpeed"); spriteMap.erase(it);
		it = spriteMap.find("xSpeed");
		xs = atof(it->second.c_str());
		spriteMap.erase(it);
		it = spriteMap.find("ySpeed");
		ys = atof(it->second.c_str());
		spriteMap.erase(it);
		it = spriteMap.find("isTracked"); spriteMap.erase(it);
		it = spriteMap.find("frameString");
		frameString = it->second;
		spriteMap.erase(it);
		v.push_back(new Explosion(frameString, x, y, xs, ys, fact->getFrame(frameString)));
		it = spriteMap.begin();	
	}
	spriteMap.clear();
	delete h;
}

void Manager::saveStats(Stats *stats, const char *filename, const char *directory) {
	std::fstream out;
	string saveString = "save/";
	saveString += directory;
	saveString += "/";
	saveString += filename;
	saveString += "s.xml";
	out.open(saveString.c_str(), std::ios::out);
	if(!out)
		throw std::string("Cannot open file stats.xml");  
	out << "<stats>" << endl;
	out << "<zombiesKilled>" << stats->getZombiesKilled() << "</zombiesKilled>" << endl;
	out << "<peopleShot>" << stats->getPeopleShot() << "</peopleShot>" << endl;
	out << "<peopleEaten>" << stats->getPeopleEaten() << "</peopleEaten>" << endl;
	out << "<timesDied>" << stats->getTimesDied() << "</timesDied>" << endl;
	out << "<score>" << stats->getScore() << "</score>" << endl;
	out << "</stats>" << endl;
	out.close();
}
	
void Manager::loadStats(Stats *stats, const char *filename, const char *directory) {
	HandleChars * h = new HandleChars();
	ParseXML * p = ParseXML::getInstance();
	string saveString = "save/";
	saveString += directory;
	saveString += "/";
	saveString += filename;
	saveString += "s.xml";
	p->parseXML(saveString.c_str(), h);
	multimap<string, string> statsMap = h->getData();
	multimap<string, string>::iterator it = statsMap.begin();
	while(it != statsMap.end()) {
		if(it->first == "zombiesKilled")
			stats->setZombiesKilled(atoi(it->second.c_str()));
		else if(it->first == "peopleShot")
			stats->setPeopleShot(atoi(it->second.c_str()));
		else if(it->first == "peopleEaten")	
			stats->setPeopleEaten(atoi(it->second.c_str()));
		else if(it->first == "timesDied")
			stats->setTimesDied(atoi(it->second.c_str()));
		else if(it->first == "score")
			stats->setScore(atoi(it->second.c_str()));
		it++;
	}
	delete h;
	statsMap.clear();	
}

# Change the following values to suit your system.

#CFLAGS=`sdl-config --cflags` -W -Wall -Weffc++ -Wextra -ggdb -O0

CFLAGS=`sdl-config --cflags` -pedantic -Wextra -Wall -Weffc++ -ggdb -O0
SDL_LIB=`sdl-config --libs` -lSDL_ttf -lSDL_image -lexpat #-lSDL_mixer -lSDL_draw
CCC=g++

OBJECTS = manager.o sprite.o frame.o explosion.o explodingSprite.o \
							vector2d.o world.o viewport.o ioManager.o factory.o \
							game.o fleeStrategy.o collisionStrategy.o parallax.o handleChars.o \
							parseXML.o zombieChaseManager.o zombieDefenseManager.o \
							gameManager.o #soundManager.o musicFactory.o

run: main.o $(OBJECTS)
	$(CCC) $(CFLAGS) main.cpp -o run $(OBJECTS) $(SDL_LIB)

main.o: main.cpp manager.h
	$(CCC) $(CFLAGS) -c main.cpp
	
game.o: game.h game.cpp
	$(CCC) $(CFLAGS) -c game.cpp

manager.o: manager.cpp manager.h sprite.h zombie.h factory.h #soundManager.o \
                    #musicFactory.h
	$(CCC) $(CFLAGS) -c manager.cpp

zombieChaseManager.o: zombieChaseManager.cpp manager.cpp manager.h \
  													  sprite.h factory.h #soundManager.o musicFactory.h
	$(CCC) $(CFLAGS) -c zombieChaseManager.cpp
	
zombieDefenseManager.o: zombieDefenseManager.cpp manager.cpp manager.h \
  													  sprite.h factory.h #soundManager.o #musicFactory.h
	$(CCC) $(CFLAGS) -c zombieDefenseManager.cpp

gameManager.o: gameManager.cpp manager.cpp manager.h \
  													  sprite.h factory.h #soundManager.o #musicFactory.h
	$(CCC) $(CFLAGS) -c gameManager.cpp

viewport.o: viewport.cpp viewport.h drawable.h
	$(CCC) $(CFLAGS) -c viewport.cpp

world.o: world.cpp world.h frame.h viewport.h
	$(CCC) $(CFLAGS) -c world.cpp

sprite.o: sprite.cpp sprite.h frame.h drawable.h
	$(CCC) $(CFLAGS) -c sprite.cpp

frame.o: frame.cpp frame.h 
	$(CCC) $(CFLAGS) -c frame.cpp

explodingSprite.o: explodingSprite.cpp explodingSprite.h sprite.h
	$(CCC) $(CFLAGS) -c explodingSprite.cpp

explosion.o: explosion.cpp explosion.h explodingSprite.h
	$(CCC) $(CFLAGS) -c explosion.cpp

zombie.o: zombie.h sprite.h frame.h drawable.h
	$(CCC) $(CFLAGS) -c zombie.h
	
people.o: people.h sprite.h frame.h drawable.h
	$(CCC) $(CFLAGS) -c people.h

ioManager.o: ioManager.cpp ioManager.h
	$(CCC) $(CFLAGS) -c ioManager.cpp

vector2d.o: vector2d.cpp vector2d.h
	$(CCC) $(CFLAGS) -c vector2d.cpp

factory.o: factory.cpp factory.h ioManager.h frame.h
	$(CCC) $(CFLAGS) -c factory.cpp

fleeStrategy.o: fleeStrategy.cpp fleeStrategy.h
	$(CCC) $(CFLAGS) -c fleeStrategy.cpp
	
collisionStrategy.o: collisionStrategy.cpp collisionStrategy.h
	$(CCC) $(CFLAGS) -c collisionStrategy.cpp
	
parallax.o: parallax.cpp parallax.h
	$(CCC) $(CFLAGS) -c parallax.cpp

handleChars.o: handleChars.cpp handleChars.h
	$(CCC) $(CFLAGS) -c handleChars.cpp

parseXML.o: parseXML.cpp parseXML.h
	$(CCC) $(CFLAGS) -c parseXML.cpp

#I FUCKING HATE SDL_MIXER

#musicFactory.o: musicFactory.cpp musicFactory.h ioManager.h
#	$(CCC) $(CFLAGS) -c musicFactory.cpp

#soundManager.o: soundManager.cpp soundManager.h
#	$(CCC) $(CFLAGS) -c soundManager.cpp
	
#lsystem.o:lsystem.cpp lsystem.h
#	$(CCC) $(CFLAGS) -c lsystem.cpp

clean:
	rm -f run *.o
	rm -f *~
	reset
	
valid:
	@echo
	@echo Validating ZombieChase Saved Game Data
	@xmllint -noout --schema schemas/bullets.xsd save/chase/bullets.xml
	@xmllint -noout --schema schemas/zombies.xsd save/chase/zombies.xml
	@xmllint -noout --schema schemas/peoples.xsd save/chase/peoples.xml
	@xmllint -noout --schema schemas/splats.xsd save/chase/splats.xml
	@xmllint -noout --schema schemas/stats.xsd save/chase/stats.xml		
	@xmllint -noout --schema schemas/splosions.xsd save/chase/splosions.xml
	@echo
	@echo
	@echo Validating ZombieDefense Saved Game Data
	@xmllint -noout --schema schemas/bullets.xsd save/defense/bullets.xml
	@xmllint -noout --schema schemas/zombies.xsd save/defense/zombies.xml
	@xmllint -noout --schema schemas/peoples.xsd save/defense/peoples.xml
	@xmllint -noout --schema schemas/splats.xsd save/defense/splats.xml
	@xmllint -noout --schema schemas/stats.xsd save/defense/stats.xml		
	@xmllint -noout --schema schemas/splosions.xsd save/defense/splosions.xml	
	@echo Validating Loaded Game Data
	@xmllint -noout --schema schemas/imageData.xsd data/imageData.xml
	@xmllint -noout --schema schemas/gameData.xsd data/gameData.xml
	@echo

cleansave:
	rm -f *.xml
	rm -f *~
	
memcheck:
	rm -f valgrindOutput.out
	valgrind -v --log-file=valgrindOutput.out --leak-check=full --track-origins=yes ./run
valgrind:
	rm -f valgrindOutput.out
	valgrind -v --log-file=valgrindOutput.out --leak-check=full --track-origins=yes --xml=yes\
	--xml-file=fullValgrindOutput --show-below-main=yes --gen-suppressions=all ./run

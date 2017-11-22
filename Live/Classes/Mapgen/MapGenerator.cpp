#include "FastNoise/FastNoise.h"
#include "MapGenerator.h"
#include "Animal.h"

#include <iostream>
#include <fstream>
#include <math.h>
#include "cocos2d.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h> 

#define CLEARING_RADIUS 130

MapGenerator::MapGenerator( int seed ){
	std::srand(seed);
}

GeneratedResources MapGenerator::createMap(int width, int length) {
	int seed = rand();

	TileParam **map = new TileParam*[width];
	for(int x = 0; x < width; x ++) {
		map[x] = new TileParam[length];
	}

	applyNoise(width, length, map, seed);
	applyGradient(width, length, map);

	generateEnvironmentFromHeight(width, length, map);
	outputToFile(width, length, map);

	cocos2d::Point spawn = generateSpawnPoint(width, length, map);

	std::vector<ResourceObstacle*>* obstacles = generateObstacles(width, length, map, spawn);
	std::vector<Tree*>* trees = generateTrees(width, length, map, spawn);

	std::vector<Animal*>* animals = new std::vector<Animal*>();
	animals->push_back(new Animal("SheepAnimation/0.plist", 2000, 2000, 0, 0.1));
	animals->push_back(new Animal("SheepAnimation/0.plist", 2070, 2070, 0, 0.1));

	for(int x = 0; x < width; x ++) {
		delete [] map[x];
	}
	delete [] map;

	return GeneratedResources(*obstacles, *trees, *animals, spawn);
}

void MapGenerator::applyNoise(int width ,int length, TileParam** map, int seed) {
	FastNoise perlin; 
	perlin.SetSeed(seed);
	perlin.SetFrequency(0.03);
	perlin.SetNoiseType(FastNoise::NoiseType::PerlinFractal);

	for(int x = 0; x < width; x ++) {
		for (int y = 0; y < length; y++) {
			map[x][y].height = perlin.GetNoise(x,y);
		}
	}
}

void MapGenerator::generateEnvironmentFromHeight(int width ,int length, TileParam** map) {
	for(int x = 0; x<width; x++) {
		for(int y = 0; y<length; y++) {
  			if(map[x][y].height >= -0.5 ) {
  				map[x][y].biome = TileParam::Biome::Forest;
  			} else if(map[x][y].height  >= -0.6) {
  				map[x][y].biome = TileParam::Biome::Beach;
  			} else {
  				map[x][y].biome = TileParam::Biome::Water;
  			}
		}
	}
}

void MapGenerator::applyGradient(int width, int length, TileParam** map) {

	int centerX = (width-1)/2;
	int centerY = (length-1)/2;
	int maxSide = width;
	if(length > width) {
		maxSide = length;
	}

	for (int x = 0; x < width; x++) {
	    for (int y = 0; y < length; y++) {
	        float distanceX = (centerX - x) * (centerX - x);
	        float distanceY = (centerY - y) * (centerY - y);

	        float distanceToCenter = sqrt(distanceX + distanceY);
	        distanceToCenter = (distanceToCenter*2)/maxSide;
	        if(distanceToCenter > 1) {
	        	distanceToCenter = 1;
	        }
	        map[x][y].height -= distanceToCenter;

	    }
	}
}

void MapGenerator::outputToFile(int width, int length, TileParam** map) {
	std::ofstream out;
	out.open(MAP_OUTPUT_FILE_NAME);

	out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<< "\n"
		<< "<map version=\"1.0\" tiledversion=\"1.0.3\" orientation=\"orthogonal\" renderorder=\"right-down\" width=\"" << width
		<< "\" height=\"" << length
		<< "\" tilewidth=\"32\" tileheight=\"32\" nextobjectid=\"1\">" << "\n"
		<< "<tileset firstgid=\"1\" source=\"sample_tileset.tsx\"/>" << "\n"
		<< "<layer name=\"Tile Layer 1\" width=\""<< width << "\" height=\"" << length << "\">" << "\n"
		<< "<data encoding=\"csv\">" << "\n";

	for(int x = 0; x<width; x++) {
		for(int y = 0; y<length; y++) {
			if(map[x][y].biome == TileParam::Biome::Forest) {
				out << FOREST_TILE_ID;
			} else if(map[x][y].biome == TileParam::Biome::Beach) {
				out << BEACH_TILE_ID;
			} else {
				out<<"0";
			}
			if(!(x == width-1 && y== length-1)) {
				out<<",";
			}

		}
		out<<"\n";
	}

	out << "</data>" << "\n"
			<< "</layer>" << "\n"
			<<	"<layer name=\"Meta\" width=\"" << width << "\" height=\"" << length << "\">" << "\n"
			<< "<data encoding=\"csv\">" << "\n";

	for(int x = 0; x<width; x++) {
		for(int y = 0; y<length; y++) {
			if(map[x][y].biome == TileParam::Biome::Water) {
				out<< WATER_TILE_ID;
			} else {
				out<<"0";
			}
			if(!(x == width-1 && y== length-1)) {
				out<<",";
			}
			
		}
		out<<"\n";
	}

	out<<"</data>\n</layer>\n</map>";

    out.close();
}

std::vector<ResourceObstacle*>* MapGenerator::generateObstacles(int width, int length, TileParam** map, cocos2d::Point spawn) {
	std::vector<ResourceObstacle*>* output = new std::vector<ResourceObstacle*>();
	for(int i = 0; i < (width*length)/10; i++) {
		int r = rand() % (width*320);
        float x = r/10;
        r = rand() % (length*320);
        float y = r/10;

        int tileX = (int)floor(x/32);
        int tileY = (int)floor(y/32);
        float displayX = x;
        float displayY = (length*32)-y;

        // Obstacle spawn on top of the player
        if((std::abs(displayX-spawn.x)<50 && std::abs(displayY-spawn.y) < 50) || (std::abs(displayX-2050)<CLEARING_RADIUS && std::abs(displayY-2050)<CLEARING_RADIUS) ) {
        	continue;
        }

        if(map[tileY][tileX].biome == TileParam::Biome::Forest) {
        	r = rand() % 8;
	        if(r == 1) {
	            output->push_back(new ResourceObstacle("Spritesheet/mapPack_spritesheet.png", 10*64, 3*64, x, (length*32)-y));
	        } else if(r<=5) {
	            output->push_back(new ResourceObstacle(x,(length*32)-y));
	        }

        } else if (map[tileY][tileX].biome == TileParam::Biome::Beach) {
        	r = rand() % 2;
	        if(r == 1) {
	            output->push_back(new ResourceObstacle("Spritesheet/mapPack_spritesheet.png", 10*64, 3*64, x, (length*32)-y));
	        }
        }
	}

	return output;
}

std::vector<Tree*>* MapGenerator::generateTrees(int width, int length, TileParam** map, cocos2d::Point spawn) {
	std::vector<Tree*>* output = new std::vector<Tree*>();
	for(int i = 0; i < (width*length)/100; i++) {
		int r = rand() % (width*320);
        float x = r/10;
        r = rand() % (length*320);
        float y = r/10;
        int tileX = (int)floor(x/32);
        int tileY = (int)floor(y/32);
        float displayX = x;
        float displayY = (length*32)-y;


        if((std::abs(displayX-spawn.x)<50 && std::abs(displayY-spawn.y) < 50) || (std::abs(displayX-2050)<CLEARING_RADIUS && std::abs(displayY-2050)<CLEARING_RADIUS ) ){
        	continue;
        }

        if(map[tileY][tileX].biome == TileParam::Biome::Forest) {
        	int r = rand() & 6;
        	if(r == 0) {
        		output->push_back(new Tree("Foliage/PNG/foliagePack_008.png", x, (length*32)-y));
        	} else if (r==1) {
        		output->push_back(new Tree("Foliage/PNG/foliagePack_011.png", x, (length*32)-y));
        	} else if (r==2) {
        		output->push_back(new Tree("Foliage/PNG/foliagePack_010.png", x, (length*32)-y));
        	} else if(r == 3) {
        		output->push_back(new Tree("Foliage/PNG/foliagePack_008.png", x, (length*32)-y, Tree::FruitType::APPLE));
        	} else if (r==4) {
        		output->push_back(new Tree("Foliage/PNG/foliagePack_011.png", x, (length*32)-y, Tree::FruitType::APPLE));
        	} else if (r==5) {
        		output->push_back(new Tree("Foliage/PNG/foliagePack_010.png", x, (length*32)-y, Tree::FruitType::APPLE));
        	}
        }
	}

	return output;
}

cocos2d::Point MapGenerator::generateSpawnPoint(int width, int length, TileParam** map) {
	cocos2d::Point spawn(width*32/2, length*32/2);
	
	for(int y = length/2; y<length; y++) {
		if(map[y][width/2].biome == TileParam::Biome::Beach) {		// Since the map is transposed, y must be used as the TileParam map's x coordinate
			spawn.setPoint(width*32/2, (length-y)*32);
			break;
		}
	}
	return spawn;
}


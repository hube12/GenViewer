#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include "generationByCubitect/generator.hpp"
#include "xmap.h"


constexpr unsigned int str2int(const char *str, int h = 0) {
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ (unsigned int) (str[h]);
}

versions parse_version(std::string &s) {
	versions v;
	switch (str2int(s.c_str())) {
		case str2int("1.7"):
			v = MC_1_7;
			break;
		case str2int("1.8"):
			v = MC_1_8;
			break;
		case str2int("1.9"):
			v = MC_1_9;
			break;
		case str2int("1.10"):
			v = MC_1_10;
			break;
		case str2int("1.11"):
			v = MC_1_11;
			break;
		case str2int("1.12"):
			v = MC_1_12;
			break;
		case str2int("1.13"):
			v = MC_1_13;
			break;
		case str2int("1.13.2"):
			v = MC_1_13_2;
			break;
		case str2int("1.14"):
			v = MC_1_14;
			break;
		default:
			v = MC_LEG;
			break;
	}
	return v;
}

int main(int argc, char *argv[]) {
	int sizeX = 2048;
	int sizeZ = 2048;
	int x = -1024;
	int z = -1024;
	initBiomes();


	if (argc <= 1) {
		std::cout << "Program should be called with at least the version number, possible ones are 1.7, 1.8, 1.9, 1.10, 1.11, 1.12, 1.13, 1.13.2, 1.14 ." << std::endl;
		exit(1);
	}
	std::string arg1(argv[1]);
	versions v = parse_version(arg1);
	if (v == MC_LEG) {
		std::cout << "Program should be called with a valid version number, possible ones are 1.7, 1.8, 1.9, 1.10, 1.11, 1.12, 1.13, 1.13.2, 1.14 ." << std::endl;
		exit(1);
	}

	LayerStack g = setupGenerator(v);
	unsigned char biomeColours[256][3];
	initBiomeColours(biomeColours);
	if (argc == 2) {

		std::cout << "Using the in.txt to produce high quality images" << std::endl;
		std::string line;
		std::ifstream datafile("in.txt", std::ios::in);
		if (datafile.fail() || !datafile) {
			printf("file was not loaded\n");
			throw std::runtime_error("file was not loaded");
		}

		while (std::getline(datafile, line)) {
			int64_t seed = stoll(line, nullptr, 10);
			std::string name = "img/" + std::to_string(seed) + ".png";
			int n = name.length();
			char char_array[n + 1];
			strcpy(char_array, name.c_str());
			applySeed(&g, (int64_t) seed);

			viewmap(&g.layers[g.layerNum - 1], biomeColours, x, z, sizeX, sizeZ, 1, char_array);
		}
	} else {
		int64_t seed = 1;
		std::string name = "img/" + std::to_string(seed) + ".png";
		int n = name.length();
		char char_array[n + 1];
		strcpy(char_array, name.c_str());
		applySeed(&g, (int64_t) seed);
		viewmap(&g.layers[g.layerNum - 1], biomeColours, x, z, sizeX, sizeZ, 1, char_array);

	}

}


int genPerLayer(int64_t seed, versions version, long x, long z, int sizeX, int sizeZ) {

	/*viewmap(&g.layers[42],biomeColours,x,z,sizeX,sizeZ,1,"rivermix.png");
	viewmap(&g.layers[24],biomeColours,x,z,sizeX,sizeZ,1,"hills.png");
	viewmap(&g.layers[18],biomeColours,x,z,sizeX,sizeZ,1,"biome.png");
	viewmap(&g.layers[21],biomeColours,x,z,sizeX,sizeZ,1,"biomeedge.png");
	viewmap(&g.layers[22],biomeColours,x,z,sizeX,sizeZ,1,"riverinit.png");
	viewmap(&g.layers[41],biomeColours,x,z,sizeX,sizeZ,1,"smooth.png");
	viewmap(&g.layers[40],biomeColours,x,z,sizeX,sizeZ,1,"river.png");
	viewmap(&g.layers[27],biomeColours,x,z,sizeX,sizeZ,1,"rare.png");
	viewmap(&g.layers[30],biomeColours,x,z,sizeX,sizeZ,1,"shore.png");
	viewmap(&g.layers[0],biomeColours,x,z,sizeX,sizeZ,1,"smoothbiome.png");*/

	/*viewmap(&g.layers[0],biomeColours,x,z,sizeX,sizeZ,1,"1island.png");
	viewmap(&g.layers[1],biomeColours,x,z,sizeX,sizeZ,1,"2zoom.png");
	viewmap(&g.layers[2],biomeColours,x,z,sizeX,sizeZ,1,"3island1.png");
	viewmap(&g.layers[3],biomeColours,x,z,sizeX,sizeZ,1,"4zoom1.png");
	viewmap(&g.layers[4],biomeColours,x,z,sizeX,sizeZ,1,"5island2.png");
	viewmap(&g.layers[5],biomeColours,x,z,sizeX,sizeZ,1,"6island3.png");
	viewmap(&g.layers[6],biomeColours,x,z,sizeX,sizeZ,1,"7island4.png");
	viewmap(&g.layers[7],biomeColours,x,z,sizeX,sizeZ,1,"8toomuch.png");
	viewmap(&g.layers[8],biomeColours,x,z,sizeX,sizeZ,1,"9snow.png");
	viewmap(&g.layers[9],biomeColours,x,z,sizeX,sizeZ,1,"9zisland5.png");
	viewmap(&g.layers[10],biomeColours,x,z,sizeX,sizeZ,1,"9zzcoolwarm.png");
	viewmap(&g.layers[11],biomeColours,x,z,sizeX,sizeZ,1,"9zzzheatice.png");
	viewmap(&g.layers[12],biomeColours,x,z,sizeX,sizeZ,1,"9zzzzSpecial.png");
	viewmap(&g.layers[13],biomeColours,x,z,sizeX,sizeZ,1,"9zzzzzoom2.png");
	viewmap(&g.layers[14],biomeColours,x,z,sizeX,sizeZ,1,"9zzzzzzoom3.png");
	viewmap(&g.layers[15],biomeColours,x,z,sizeX,sizeZ,1,"9zzzzzzzisland6.png");
	viewmap(&g.layers[16],biomeColours,x,z,sizeX,sizeZ,1,"9zzzzzzzzmoosh.png");
	viewmap(&g.layers[17],biomeColours,x,z,sizeX,sizeZ,1,"9zzzzzzzzzdeepocean.png");
	*/
	return 0;
}
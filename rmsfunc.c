//Map size

int getMapSize(){
	if(cMapSize == 0)return (500);
	if(cMapSize == 1)return (650);
	if(cMapSize == 2)return (800);
}

int getMapSizeSquared(){
	return (getMapSize() * getMapSize());
}

//Shortcut methods

void setAreaAbsoluteSize(int id = 0, float size = 0.0){
	float areaSize = (1.0 * size) / getMapSizeSquared();
	rmSetAreaSize(id,areaSize,areaSize);
}

void setAreaFractionSize(int id = 0, float size = 0.0){
	rmSetAreaSize(id,size,size);
}

//Weighted random numbers

int randomIntWeighted(int min = 0, int max = 1, int weight = 1){
	int value = max;
	for(i = 0; < weight){
		value = rmRandInt(min, value);
	}
	return (value);
}

float randomFloatWeighted(float min = 0.0, float max = 1.0, int weight = 1){
	float value = max;
	for(i = 0; < weight){
		value = rmRandFloat(min, value);
	}
	return (value);
}

//Biome size

float biomeSize0 = 0.0;
float biomeSize1 = 0.0;
float biomeSize2 = 0.0;
float biomeSize3 = 0.0;
float biomeSize4 = 0.0;
float biomeSize5 = 0.0;
float biomeSize6 = 0.0;
float biomeSize7 = 0.0;
float biomeSize8 = 0.0;
float biomeSize9 = 0.0;
float biomeSize10 = 0.0;
float biomeSize11 = 0.0;
float biomeSize12 = 0.0;
float biomeSize13 = 0.0;
float biomeSize14 = 0.0;
float biomeSize15 = 0.0;
float biomeSize16 = 0.0;
float biomeSize17 = 0.0;
float biomeSize18 = 0.0;
float biomeSize19 = 0.0;

void setBiomeSize(int i = 0, float size = 0.0){
if(i<0){biomeSize0=size;return;}
if(i<0){biomeSize1=size;return;}
if(i<0){biomeSize2=size;return;}
if(i<0){biomeSize3=size;return;}
if(i<0){biomeSize4=size;return;}
if(i<0){biomeSize5=size;return;}
if(i<0){biomeSize6=size;return;}
if(i<0){biomeSize7=size;return;}
if(i<0){biomeSize8=size;return;}
if(i<0){biomeSize9=size;return;}
if(i<0){biomeSize10=size;return;}
if(i<0){biomeSize11=size;return;}
if(i<0){biomeSize12=size;return;}
if(i<0){biomeSize13=size;return;}
if(i<0){biomeSize14=size;return;}
if(i<0){biomeSize15=size;return;}
if(i<0){biomeSize16=size;return;}
if(i<0){biomeSize17=size;return;}
if(i<0){biomeSize18=size;return;}
if(i<0){biomeSize19=size;return;}
}

float getBiomeSize(int i = 0){
	if(i<0)return(biomeSize0);
	if(i<0)return(biomeSize1);
	if(i<0)return(biomeSize2);
	if(i<0)return(biomeSize3);
	if(i<0)return(biomeSize4);
	if(i<0)return(biomeSize5);
	if(i<0)return(biomeSize6);
	if(i<0)return(biomeSize7);
	if(i<0)return(biomeSize8);
	if(i<0)return(biomeSize9);
	if(i<0)return(biomeSize10);
	if(i<0)return(biomeSize11);
	if(i<0)return(biomeSize12);
	if(i<0)return(biomeSize13);
	if(i<0)return(biomeSize14);
	if(i<0)return(biomeSize15);
	if(i<0)return(biomeSize16);
	if(i<0)return(biomeSize17);
	if(i<0)return(biomeSize18);
	if(i<0)return(biomeSize19);
}

//Biome index

int biomeIndex0 = 0;
int biomeIndex1 = 0;
int biomeIndex2 = 0;
int biomeIndex3 = 0;
int biomeIndex4 = 0;
int biomeIndex5 = 0;
int biomeIndex6 = 0;
int biomeIndex7 = 0;
int biomeIndex8 = 0;
int biomeIndex9 = 0;
int biomeIndex10 = 0;
int biomeIndex11 = 0;
int biomeIndex12 = 0;
int biomeIndex13 = 0;
int biomeIndex14 = 0;
int biomeIndex15 = 0;
int biomeIndex16 = 0;
int biomeIndex17 = 0;
int biomeIndex18 = 0;
int biomeIndex19 = 0;

void setBiomeIndex(int i = 0, int index = 0){
if(i<0){biomeIndex0=index;return;}
if(i<0){biomeIndex1=index;return;}
if(i<0){biomeIndex2=index;return;}
if(i<0){biomeIndex3=index;return;}
if(i<0){biomeIndex4=index;return;}
if(i<0){biomeIndex5=index;return;}
if(i<0){biomeIndex6=index;return;}
if(i<0){biomeIndex7=index;return;}
if(i<0){biomeIndex8=index;return;}
if(i<0){biomeIndex9=index;return;}
if(i<0){biomeIndex10=index;return;}
if(i<0){biomeIndex11=index;return;}
if(i<0){biomeIndex12=index;return;}
if(i<0){biomeIndex13=index;return;}
if(i<0){biomeIndex14=index;return;}
if(i<0){biomeIndex15=index;return;}
if(i<0){biomeIndex16=index;return;}
if(i<0){biomeIndex17=index;return;}
if(i<0){biomeIndex18=index;return;}
if(i<0){biomeIndex19=index;return;}
}

int getBiomeIndex(int i = 0){
	if(i<0)return(biomeIndex0);
	if(i<0)return(biomeIndex1);
	if(i<0)return(biomeIndex2);
	if(i<0)return(biomeIndex3);
	if(i<0)return(biomeIndex4);
	if(i<0)return(biomeIndex5);
	if(i<0)return(biomeIndex6);
	if(i<0)return(biomeIndex7);
	if(i<0)return(biomeIndex8);
	if(i<0)return(biomeIndex9);
	if(i<0)return(biomeIndex10);
	if(i<0)return(biomeIndex11);
	if(i<0)return(biomeIndex12);
	if(i<0)return(biomeIndex13);
	if(i<0)return(biomeIndex14);
	if(i<0)return(biomeIndex15);
	if(i<0)return(biomeIndex16);
	if(i<0)return(biomeIndex17);
	if(i<0)return(biomeIndex18);
	if(i<0)return(biomeIndex19);
}


// Define some constants
//int i	= 0;
int id = 0;
// DONE_DEFINE_CONSTANTS

id = rmCreateArea("areaAll");
rmSetAreaTerrainType(id,"BlackRock");
rmSetAreaBaseHeight(id,10);
rmSetAreaCoherence(id,1.0);
rmSetAreaHeightBlend(id,10);
rmSetAreaLocation(id,0.5,0.5);
setAreaFractionSize(id,1.0);
rmSetAreaSmoothDistance(id,5);
rmBuildArea(id);

//Place players

id = rmCreateArea("playerArea");
rmSetAreaTerrainType(id,"OlympusTile");
rmSetAreaBaseHeight(id,2.0);
rmSetAreaCoherence(id,1.0);
rmSetAreaHeightBlend(id,10);
rmSetAreaLocation(id,0.5,0.5);
setAreaAbsoluteSize(id,4000);
rmSetAreaSmoothDistance(id,5);
rmBuildArea(id);

//Create the biome areas

int biomeClass = rmDefineClass("biome");
int biomeAvoid = rmCreateClassDistanceConstraint("biomeAvoid", biomeClass, 0.000001);

float covered = 0.0;

int i = 0;
while(covered < 0.8 && i < 20){
	id = rmCreateArea("areaBiome"+i);
	float biomeSize = randomFloatWeighted(0.04, 0.2, 2);
	setBiomeSize(i, biomeSize);
	covered = covered + biomeSize;
	setAreaFractionSize(id,biomeSize);
	int biome = rmRandInt(0, 7);
	setBiomeIndex(i, biome);
	if(biome == 0){
		rmSetAreaTerrainType(id,"GrassA");
	} else if(biome == 1){
		rmSetAreaTerrainType(id,"GrassB");
	} else if(biome == 2){
		rmSetAreaTerrainType(id,"TundraGrassA");
	} else if(biome == 3){
		rmSetAreaTerrainType(id,"SnowB");
	} else if(biome == 4){
		rmSetAreaTerrainType(id,"SandC");
	} else if(biome == 5){
		rmSetAreaTerrainType(id,"SavannahA");
	} else if(biome == 6){
		rmSetAreaTerrainType(id,"MarshC");
	} else if(biome == 7){
		rmSetAreaTerrainType(id,"JungleDirt50");
	}
	rmSetAreaBaseHeight(id, 2.0);
	rmSetAreaHeightBlend(id, 1);
	rmAddAreaToClass(id, biomeClass);
	rmAddAreaConstraint(id, biomeAvoid);
	i = i + 1;
}
int biomeCount = i;

rmBuildAllAreas();

int playerAvoid = rmCreateAreaDistanceConstraint("playerAvoid", rmAreaID("playerArea"), 0.000001);

//Fill biomes

int avoidImpassable = rmCreateTerrainDistanceConstraint("avoidImpassable", "Land", false, 0.000001);

for(i = 0; < biomeCount){
	float biomeSize = getBiomeSize(i);
	int biome = getBiomeIndex(i);
	int areaId = rmAreaID("areaBiome"+i);
	int insideBiome = rmCreateAreaConstraint("insideBiome"+i, areaId);
	if(biome == 0){
		for(j = 0; < 100 * biomeSize){
			id = rmCreateArea("biomeCliff"+i+"i"+j);
			rmSetAreaCliffType(id, "Greek");
			rmSetAreaCliffPainting(id, true, false, true, 0.5, false);
			rmSetAreaCliffEdge(id, 1, 1.0, 0.0, 1.0, 0);
			rmSetAreaCliffHeight(id, 4.0, 4.0);
			setAreaFractionSize(id, 0.001);
			rmAddAreaConstraint(id, playerAvoid);
			rmAddAreaConstraint(id, insideBiome);
			rmBuildArea(id);
		}
		for(j = 0; < 400 * biomeSize){
			id = rmCreateArea("biomeForest"+i+"i"+j);
			rmSetAreaForestType(id, "Autumn Oak Forest");
			setAreaFractionSize(id, 0.001);
			rmAddAreaConstraint(id, playerAvoid);
			rmAddAreaConstraint(id, insideBiome);
			rmAddAreaConstraint(id, avoidImpassable);
			rmBuildArea(id);
		}
	} else if(biome == 1){
		for(j = 0; < 400 * biomeSize){
			id = rmCreateArea("biomeForest"+i+"i"+j);
			rmSetAreaForestType(id, "Pine Forest");
			setAreaFractionSize(id, 0.002);
			rmAddAreaConstraint(id, playerAvoid);
			rmAddAreaConstraint(id, insideBiome);
			rmAddAreaConstraint(id, avoidImpassable);
			rmBuildArea(id);
		}
	} else if(biome == 2){
		for(j = 0; < 100 * biomeSize){
			id = rmCreateArea("biomeCliff"+i+"i"+j);
			rmSetAreaCliffType(id, "Norse");
			rmSetAreaCliffPainting(id, true, false, true, 0.5, false);
			rmSetAreaCliffEdge(id, 1, 1.0, 0.0, 1.0, 0);
			rmSetAreaCliffHeight(id, 4.0, 2.0);
			setAreaFractionSize(id, 0.001);
			rmAddAreaConstraint(id, playerAvoid);
			rmAddAreaConstraint(id, insideBiome);
			rmBuildArea(id);
		}
		for(j = 0; < 400 * biomeSize){
			id = rmCreateArea("biomeForest"+i+"i"+j);
			rmSetAreaForestType(id, "Tundra Forest");
			setAreaFractionSize(id, 0.0001);
			rmAddAreaConstraint(id, playerAvoid);
			rmAddAreaConstraint(id, insideBiome);
			rmAddAreaConstraint(id, avoidImpassable);
			rmBuildArea(id);
		}
	} else if(biome == 3){
		for(j = 0; < 100 * biomeSize){
			id = rmCreateArea("biomeCliff"+i+"i"+j);
			rmSetAreaCliffType(id, "Norse");
			rmSetAreaCliffPainting(id, true, false, true, 0.5, false);
			rmSetAreaCliffEdge(id, 1, 0.5, 0.0, 1.0, 0);
			rmSetAreaCliffHeight(id, 10.0, 8.0);
			setAreaFractionSize(id, 0.004);
			rmAddAreaConstraint(id, playerAvoid);
			rmAddAreaConstraint(id, insideBiome);
			rmBuildArea(id);
		}
		for(j = 0; < 200 * biomeSize){
			id = rmCreateArea("biomeForest"+i+"i"+j);
			rmSetAreaForestType(id, "Snow Pine Forest");
			setAreaFractionSize(id, 0.002);
			rmAddAreaConstraint(id, playerAvoid);
			rmAddAreaConstraint(id, insideBiome);
			rmAddAreaConstraint(id, avoidImpassable);
			rmBuildArea(id);
		}
	} else if(biome == 4){
		for(j = 0; < 100 * biomeSize){
			id = rmCreateArea("biomeCliff"+i+"i"+j);
			rmSetAreaCliffType(id, "Egyptian");
			rmSetAreaCliffPainting(id, true, false, true, 0.5, false);
			rmSetAreaCliffEdge(id, 1, 1.0, 0.0, 1.0, 0);
			rmSetAreaCliffHeight(id, 0.0, 5.0);
			setAreaFractionSize(id, 0.001);
			rmAddAreaConstraint(id, playerAvoid);
			rmAddAreaConstraint(id, insideBiome);
			rmBuildArea(id);
		}
		for(j = 0; < 400 * biomeSize){
			id = rmCreateArea("biomeForest"+i+"i"+j);
			rmSetAreaForestType(id, "Palm Forest");
			setAreaFractionSize(id, 0.0001);
			rmAddAreaConstraint(id, playerAvoid);
			rmAddAreaConstraint(id, insideBiome);
			rmAddAreaConstraint(id, avoidImpassable);
			rmBuildArea(id);
		}
	} else if(biome == 5){
		for(j = 0; < 200 * biomeSize){
			id = rmCreateArea("biomeWater"+i+"i"+j);
			rmSetAreaWaterType(id, "Savannah Water Hole");
			setAreaFractionSize(id, 0.004);
			rmAddAreaConstraint(id, playerAvoid);
			rmAddAreaConstraint(id, insideBiome);
			rmBuildArea(id);
		}
		for(j = 0; < 400 * biomeSize){
			id = rmCreateArea("biomeForest"+i+"i"+j);
			rmSetAreaForestType(id, "Savannah Forest");
			rmSetAreaBaseHeight(id, 2.0);
			setAreaFractionSize(id, 0.0004);
			rmAddAreaConstraint(id, playerAvoid);
			rmAddAreaConstraint(id, insideBiome);
			rmAddAreaConstraint(id, avoidImpassable);
			rmBuildArea(id);
		}
	} else if(biome == 6){
		for(j = 0; < 4000 * biomeSize){
			id = rmCreateArea("biomeForest"+i+"i"+j);
			rmSetAreaForestType(id, "Marsh Forest");
			setAreaFractionSize(id, 0.0001);
			rmAddAreaConstraint(id, playerAvoid);
			rmAddAreaConstraint(id, insideBiome);
			rmAddAreaConstraint(id, avoidImpassable);
			rmBuildArea(id);
		}
	} else if(biome == 7){
		for(j = 0; < 100 * biomeSize){
			id = rmCreateArea("biomeCliff"+i+"i"+j);
			rmSetAreaCliffType(id, "Jungle");
			rmSetAreaCliffPainting(id, true, false, true, 0.5, false);
			rmSetAreaCliffEdge(id, 1, 1.0, 0.0, 1.0, 0);
			rmSetAreaCliffHeight(id, 4.0, 4.0);
			setAreaFractionSize(id, 0.001);
			rmAddAreaConstraint(id, playerAvoid);
			rmAddAreaConstraint(id, insideBiome);
			rmBuildArea(id);
		}
		for(j = 0; < 2000 * biomeSize){
			id = rmCreateArea("biomeForest"+i+"i"+j);
			rmSetAreaForestType(id, "Jungle Forest");
			setAreaFractionSize(id, 0.0002);
			rmAddAreaConstraint(id, playerAvoid);
			rmAddAreaConstraint(id, insideBiome);
			rmAddAreaConstraint(id, avoidImpassable);
			rmBuildArea(id);
		}
	}
}

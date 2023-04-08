rmSetStatusText("",0.01);
rmSetMapSize(300,300);
rmSetSeaLevel(0);
rmSetSeaType("greek river");
rmTerrainInitialize("GrassB",5);
rmSetLightingSet("default");
rmSetGaiaCiv(cCivZeus);
/*

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
rmSetAreaBaseHeight(id,5.0);
rmSetAreaCoherence(id,1.0);
rmSetAreaHeightBlend(id,10);
rmSetAreaLocation(id,0.5,0.5);
setAreaFractionSize(id,0.01);
rmSetAreaSmoothDistance(id,5);
rmBuildArea(id);

//Create the biome areas
int biomeClass = rmDefineClass("biome");
int biomeAvoid = rmCreateClassDistanceConstraint("biomeAvoid", biomeClass, 0.000001);

float covered = 0.0;

int i = 0;
while(covered < 0.85 && i < 20){
	id = rmCreateArea("areaBiome"+i);
	float biomeSize = randomFloatWeighted(0.04, 0.2, 2);
	//setBiomeSize(i, biomeSize);
	covered = covered + biomeSize;
	setAreaFractionSize(id,biomeSize);
	int biome = rmRandInt(0, 7);
	//	setBiomeIndex(i, biome);
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

*/

void CreateRocket(int x = 0, int z = 0){
	int temp = 0;
	if(xGetDatabaseCount(dRocket) > 0){
		for(a = xGetDatabaseCount(dRocket); > 0){
			xDatabaseNext(dRocket);
			xUnitSelect(dRocket, xUnitID);
			trUnitDestroy();
			xFreeDatabaseBlock(dRocket);
		}
		xResetDatabase(dRocket);
	}
	temp = trGetNextUnitScenarioNameNumber();
	UnitCreate(0, "Dwarf", x, z, 0);
	trQuestVarSet("RocketUnit", temp);
	AddUnitToDB(dRocket, xUnitID, temp);
	temp = trGetNextUnitScenarioNameNumber()+3;
	UnitCreate(0, "Dwarf", x, z, 0);
	UnitCreate(0, "Dwarf", x, z, 0);
	UnitCreate(0, "Dwarf", x, z, 0);
	UnitCreate(0, "Dwarf", x, z, 0);
	UnitCreate(0, "Dwarf", x, z, 60);
	UnitCreate(0, "Dwarf", x, z, 120);
	UnitCreate(0, "Dwarf", x, z, 180);
	UnitCreate(0, "Dwarf", x, z, 240);
	UnitCreate(0, "Dwarf", x, z, 300);
	for(a = temp; < temp+6){
		trUnitSelectClear();
		trUnitSelect(""+a);
		trUnitChangeProtoUnit("Spy Eye");
		trUnitSelectClear();
		trUnitSelect(""+a);
		trMutateSelected(kbGetProtoUnitID("Shrine"));
		trUnitSelectClear();
		trUnitSelect(""+a);
		trSetSelectedScale(2,10,2);
		AddUnitToDB(dRocket, xUnitID, a);
	}
	trUnitSelectClear();
	trUnitSelect(""+(temp-1));
	trUnitChangeProtoUnit("Columns");
	trUnitSelectClear();
	trUnitSelect(""+(temp-1));
	trSetSelectedScale(8,8,8);
	trUnitSelectClear();
	trUnitSelect(""+(temp-2));
	trUnitChangeProtoUnit("Spy Eye");
	trUnitSelectClear();
	trUnitSelect(""+(temp-2));
	trMutateSelected(kbGetProtoUnitID("Wonder SPC"));
	trUnitSelectClear();
	trUnitSelect(""+(temp-2));
	trSetSelectedScale(0,0,0);
	trUnitSelectClear();
	trUnitSelect(""+(temp-2));
	trUnitSetAnimationPath("3,0,0,0,0,0");
	//Maybe have black rock so players cant attack
	trUnitSelectClear();
	trUnitSelect(""+(temp-3));
	trUnitChangeProtoUnit("Revealer");
	trUnitSelectByQV("RocketUnit");
	trUnitChangeProtoUnit("Wonder SPC");
	trUnitSelectByQV("RocketUnit");
	trUnitConvert(1);
	trUnitSelectByQV("RocketUnit");
	trSetSelectedScale(1,0.1,1);
	trUnitSelectByQV("RocketUnit");
	trUnitSetAnimationPath("2,1,0,1,1,0");
	AddUnitToDB(dRocket, xUnitID, temp-1);
	AddUnitToDB(dRocket, xUnitID, temp-2);
	AddUnitToDB(dRocket, xUnitID, temp-3);
	if(x != 20){
		//Function for main rocket only
	}
}

void SpawnPlayers(){
	CreateRocket(getMapSize()/2,getMapSize()/2);
	//SPAWN PLAYERS
	int temp = 0;
	trVectorQuestVarSet("CentreMap", xsVectorSet(getMapSize()/2, 0, getMapSize()/2));
	trVectorQuestVarSet("dir", xsVectorSet(0, 0, 14));
	trVectorQuestVarSet("dir2", xsVectorSet(0, 0, 18));
	float baseCos = xsCos(6.283185 / (cNumberNonGaiaPlayers-1)*0.5);
	float baseSin = xsSin(6.283185 / (cNumberNonGaiaPlayers-1)*0.5);
	int heading = 90;
	for(p=1; < cNumberNonGaiaPlayers) {
		xSetPointer(dPlayerData, p);
		trVectorQuestVarSet("base", trVectorQuestVarGet("CentreMap") + trVectorQuestVarGet("dir"));
		trVectorQuestVarSet("tower", trVectorQuestVarGet("CentreMap") + trVectorQuestVarGet("dir2"));
		heading = heading-(360/(cNumberNonGaiaPlayers-1));
		if(heading > 360){
			heading = heading-360;
		}
		if(heading < 0){
			heading = heading+360;
		}
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(p, "Villager Atlantean Hero", trVectorQuestVarGetX("base"), trVectorQuestVarGetZ("base"), heading);
		xSetPointer(dPlayerData, p);
		xSetInt(dPlayerData, xUnitID, temp);
		trPlayerKillAllGodPowers(p);
		trVectorQuestVarSet("dir", rotationMatrix(trVectorQuestVarGet("dir"), baseCos, baseSin));
		trVectorQuestVarSet("dir2", rotationMatrix(trVectorQuestVarGet("dir2"), baseCos, baseSin));
		trUnitSelectClear();
		CreatePillBox(trVectorQuestVarGetX("tower"), trVectorQuestVarGetZ("tower"));
	}
	CreatePillBox(getMapSize()/2+16,getMapSize()/2+16);
	CreatePillBox(getMapSize()/2+16,getMapSize()/2-16);
	paintCircleHeight(getMapSize()/4,getMapSize()/4, 11, "RiverGrassyB", 0);
	trPaintTerrain(getMapSize()/4+7,getMapSize()/4-1,getMapSize()/4+8,getMapSize()/4,2,2);
}

void CaptureReward(int city = 1){
	if(city == 1){
		for(p = 1; < cNumberNonGaiaPlayers){
			trUnforbidProtounit(p, "Farm");
		}
		trOverlayText("Farm unlocked - creates extra villagers", 7);
	}
	if(city == 3){
		for(p = 1; < cNumberNonGaiaPlayers){
			trUnforbidProtounit(p, "Guild");
		}
		trOverlayText("Guild unlocked - constantly creates free ammo", 7);
	}
	if(city == 2){
		for(p = 1; < cNumberNonGaiaPlayers){
			trUnforbidProtounit(p, "Tower");
			trUnforbidProtounit(p, "Sky Passage");
		}
		trOverlayText("Sky Passage and Tower unlocked", 7, -1, 200);
		uiMessageBox("Towers will change to pillboxes when built, sky passages fire weak arrows.");
	}
	if(city == 4){
		for(p = 1; < cNumberNonGaiaPlayers){
			trUnforbidProtounit(p, "Temple");
		}
		trOverlayText("Temple unlocked - recycle unwanted relics into ammo here and research upgrades", 7);
	}
	if(city == 5){
		for(p = 1; < cNumberNonGaiaPlayers){
			trUnforbidProtounit(p, "Palace");
		}
		trOverlayText("Rocket assembled!", 4);
		xsEnableRule("RocketAssembled");
	}
}

void BuildCities(){
	CitiesToMake = 5;
	int Chooser = 0;
	int temp = 0;
	int ABORT = 0;
	vector spawn = vector(0,0,0);
	vector MapMid = xsVectorSet(getMapSize()/2, 0, getMapSize()/2);
	for(a = CitiesToMake; > 0){
		Chooser = 0;
		while(Chooser <= 0){
			ABORT = ABORT+1;
			Chooser = 0;
			trQuestVarSetFromRand("temp", 1, xGetDatabaseCount(dLowTerrain));
			xSetPointer(dLowTerrain, 1*trQuestVarGet("temp"));
			spawn = xGetVector(dLowTerrain, xDeployLoc);
			//If city not too close to map edge
			if((xsVectorGetX(spawn) > 20) && (xsVectorGetX(spawn) < 380) && (xsVectorGetZ(spawn) > 20) && (xsVectorGetZ(spawn) < 380)){
				//If city not too close to start point
				if(distanceBetweenVectors(spawn, MapMid, true) > 5000){
					//debugLog("START - " + xGetDatabaseCount(dCity) + " cities exist");
					for(b = xGetDatabaseCount(dCity); > 0){
						//Check distance to all other cities
						xDatabaseNext(dCity);
						if(distanceBetweenVectors(spawn, xGetVector(dCity, xLocation),true) < 10000){
							Chooser = Chooser-1;
						}
					}
					Chooser = Chooser+1;
				}
			}
			if(ABORT > 500){
				Chooser = 1;
				debugLog("ABORT");
			}
		}
		xAddDatabaseBlock(dCity, true);
		xSetFloat(dCity, xDistance, distanceBetweenVectors(spawn, MapMid));
		xSetVector(dCity, xLocation, spawn);
		xSetInt(dCity, xNumber, 0);
		xSetInt(dCity, xPopulation, 0);
		xSetInt(dCity, xDifficultyStat, 0);
		xSetBool(dCity, xCityAlive, true);
		spawn = spawn/2;
		paintCircleHeight(xsVectorGetX(spawn),xsVectorGetZ(spawn), 11, "OlympusTile", -2);
		trPaintTerrain(xsVectorGetX(spawn),xsVectorGetZ(spawn),xsVectorGetX(spawn),xsVectorGetZ(spawn),getTerrainType("CityTileWaterPool"),getTerrainSubType("CityTileWaterPool"));
		spawn = spawn*2;
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(cNumberNonGaiaPlayers, "Dwarf",xsVectorGetX(spawn),xsVectorGetZ(spawn));
		xSetInt(dCity, xCityFlagID, temp);
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(cNumberNonGaiaPlayers, "Dwarf",xsVectorGetX(spawn),xsVectorGetZ(spawn));
		xSetInt(dCity, xCitySFXID, temp);
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(0, "Dwarf",xsVectorGetX(spawn),xsVectorGetZ(spawn), 90);
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeProtoUnit("Great Box");
		xSetInt(dCity, xCityChestID, temp);
		xUnitSelect(dCity, xCityFlagID);
		trUnitChangeProtoUnit("Spy Eye");
		xUnitSelect(dCity, xCityFlagID);
		trMutateSelected(kbGetProtoUnitID("Flag Numbered"));
		xUnitSelect(dCity, xCityFlagID);
		trUnitSetAnimationPath(""+(5-a)+",0,0,0,0,0");
		xUnitSelect(dCity, xCityFlagID);
		trSetSelectedScale(2,2,2);
		xUnitSelect(dCity, xCitySFXID);
		trUnitChangeProtoUnit("Spy Eye");
		xUnitSelect(dCity, xCitySFXID);
		trMutateSelected(kbGetProtoUnitID("Osiris Box Glow"));
		xUnitSelect(dCity, xCitySFXID);
		trUnitSetAnimationPath("0,0,1,0,0,0");
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(0, "Dwarf",xsVectorGetX(spawn)+2,xsVectorGetZ(spawn)+2, 0);
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeProtoUnit("Revealer");
		xSetInt(dCity, xCityLOSID, temp);
	}
}

void SetupCities(){
	float currentcheck = 0.0;
	float nextcheck = 0.0;
	int rank = 0;
	int temp = 0;
	for(a = xGetDatabaseCount(dCity); > 0){
		rank = 0;
		xDatabaseNext(dCity);
		currentcheck = xGetFloat(dCity, xDistance);
		for(b = xGetDatabaseCount(dCity); > 0){
			xDatabaseNext(dCity);
			nextcheck = xGetFloat(dCity, xDistance);
			if(currentcheck > nextcheck){
				rank = rank+1;
			}
		}
		rank=rank-1;
		xSetInt(dCity, xNumber, (rank+2));
		xSetInt(dCity, xDifficultyStat, rank);
		xUnitSelect(dCity, xCityFlagID);
		trUnitSetAnimationPath(""+(1+rank)+",0,0,0,0,0");
	}
	for(a = xGetDatabaseCount(dCity); > 0){
		xDatabaseNext(dCity);
		if(xGetInt(dCity, xNumber) == 1){
			//Populate City 1
			tempV = xGetVector(dCity, xLocation);
			SpawnEnemy("Minotaur", xsVectorGetX(tempV),xsVectorGetZ(tempV)+4,true,1, 180);
			SpawnEnemy("Militia", xsVectorGetX(tempV)+6,xsVectorGetZ(tempV)-6,true,1, 0);
			SpawnEnemy("Militia", xsVectorGetX(tempV)+6,xsVectorGetZ(tempV)+6,true,1, 180);
			SpawnEnemy("Militia", xsVectorGetX(tempV)-6,xsVectorGetZ(tempV)+6,true,1, 180);
			SpawnEnemy("Militia", xsVectorGetX(tempV)-6,xsVectorGetZ(tempV)-6,true,1, 0);
			
			for(b = 1; < cNumberNonGaiaPlayers){
				SpawnEnemy("Militia", xsVectorGetX(tempV)-8,(xsVectorGetZ(tempV)-(cNumberNonGaiaPlayers*2)+(b*4)),true,1, 90);
				SpawnEnemy("Militia", xsVectorGetX(tempV)+8,(xsVectorGetZ(tempV)-(cNumberNonGaiaPlayers*2)+(b*4)),true,1, 270);
			}
			tempV = tempV/2;
			//from metres to tiles
			//---CITY 1 LAYOUT
			CreateUnitInAtlantisBox(xsVectorGetX(tempV),xsVectorGetZ(tempV)-5, 3, getTerrainType("GrassDirt50"), getTerrainSubType("GrassDirt50"), 0, "Academy", 180);
			trQuestVarSet("temp1", trGetNextUnitScenarioNameNumber());
			UnitCreate(0, "Dwarf",(xsVectorGetX(tempV)+4)*2,(xsVectorGetZ(tempV)+5)*2);
			trQuestVarSet("temp2", trGetNextUnitScenarioNameNumber());
			UnitCreate(0, "Dwarf",(xsVectorGetX(tempV)-4)*2,(xsVectorGetZ(tempV)+5)*2);
			CreateUnitInAtlantisBox(xsVectorGetX(tempV)+4,xsVectorGetZ(tempV)+5, 1,-1, -1, 0, "Fountain", 0, "1,1,0,0,0,0");
			CreateUnitInAtlantisBox(xsVectorGetX(tempV)-4,xsVectorGetZ(tempV)+5, 1,-1, -1, 0, "Fountain", 0, "1,1,0,0,0,0");
			trUnitSelectByQV("temp1");
			trUnitChangeProtoUnit("Flowers");
			trUnitSelectByQV("temp2");
			trUnitChangeProtoUnit("Flowers");
		}
		if(xGetInt(dCity, xNumber) == 2){
			//Populate City 2
			tempV = xGetVector(dCity, xLocation);
			SpawnEnemy("Centaur", xsVectorGetX(tempV),xsVectorGetZ(tempV)+4,true,2, 180);
			SpawnEnemy("Centaur", xsVectorGetX(tempV)+6,xsVectorGetZ(tempV)-6,true,2, 0);
			SpawnEnemy("Centaur", xsVectorGetX(tempV)+6,xsVectorGetZ(tempV)+6,true,2, 180);
			SpawnEnemy("Centaur", xsVectorGetX(tempV)-6,xsVectorGetZ(tempV)+6,true,2, 180);
			SpawnEnemy("Centaur", xsVectorGetX(tempV)-6,xsVectorGetZ(tempV)-6,true,2, 0);
			
			for(b = 1; < cNumberNonGaiaPlayers){
				SpawnEnemy("Toxotes", xsVectorGetX(tempV)-8,(xsVectorGetZ(tempV)-(cNumberNonGaiaPlayers*2)+(b*4)),true,2, 90);
				SpawnEnemy("Toxotes", xsVectorGetX(tempV)+8,(xsVectorGetZ(tempV)-(cNumberNonGaiaPlayers*2)+(b*4)),true,2, 270);
			}
			tempV = tempV/2;
			//from metres to tiles
			//---CITY 2 LAYOUT
			CreateUnitInAtlantisBox(xsVectorGetX(tempV)-6,xsVectorGetZ(tempV), 3, getTerrainType("GrassDirt50"), getTerrainSubType("GrassDirt50"), 0, "Academy", 0);
			CreateUnitInAtlantisBox(xsVectorGetX(tempV)+6,xsVectorGetZ(tempV), 3, getTerrainType("GrassDirt50"), getTerrainSubType("GrassDirt50"), 0, "Archery Range", 0);
			trQuestVarSet("temp1", trGetNextUnitScenarioNameNumber());
			UnitCreate(0, "Dwarf",(xsVectorGetX(tempV)+4)*2,(xsVectorGetZ(tempV)+5)*2);
			trQuestVarSet("temp2", trGetNextUnitScenarioNameNumber());
			UnitCreate(0, "Dwarf",(xsVectorGetX(tempV)-4)*2,(xsVectorGetZ(tempV)-5)*2);
			trQuestVarSet("temp3", trGetNextUnitScenarioNameNumber());
			UnitCreate(0, "Dwarf",(xsVectorGetX(tempV)+4)*2,(xsVectorGetZ(tempV)-5)*2);
			trQuestVarSet("temp4", trGetNextUnitScenarioNameNumber());
			UnitCreate(0, "Dwarf",(xsVectorGetX(tempV)-4)*2,(xsVectorGetZ(tempV)+5)*2);
			CreateUnitInAtlantisBox(xsVectorGetX(tempV)+4,xsVectorGetZ(tempV)+5, 1,-1, -1, 0, "Fountain", 0, "1,1,0,0,0,0");
			CreateUnitInAtlantisBox(xsVectorGetX(tempV)-4,xsVectorGetZ(tempV)+5, 1,-1, -1, 0, "Fountain", 0, "1,1,0,0,0,0");
			CreateUnitInAtlantisBox(xsVectorGetX(tempV)+4,xsVectorGetZ(tempV)-5, 1,-1, -1, 0, "Fountain", 0, "1,1,0,0,0,0");
			CreateUnitInAtlantisBox(xsVectorGetX(tempV)-4,xsVectorGetZ(tempV)-5, 1,-1, -1, 0, "Fountain", 0, "1,1,0,0,0,0");
			trUnitSelectByQV("temp1");
			trUnitChangeProtoUnit("Flowers");
			trUnitSelectByQV("temp2");
			trUnitChangeProtoUnit("Flowers");
			trUnitSelectByQV("temp3");
			trUnitChangeProtoUnit("Flowers");
			trUnitSelectByQV("temp4");
			trUnitChangeProtoUnit("Flowers");
		}
		if(xGetInt(dCity, xNumber) == 3){
			//Populate City 3
			tempV = xGetVector(dCity, xLocation);
			SpawnEnemy("Medusa", xsVectorGetX(tempV),xsVectorGetZ(tempV)+4,true,3, 180);
			SpawnEnemy("Colossus", xsVectorGetX(tempV)+6,xsVectorGetZ(tempV)-6,true,3, 0);
			SpawnEnemy("Colossus", xsVectorGetX(tempV)+6,xsVectorGetZ(tempV)+6,true,3, 180);
			SpawnEnemy("Colossus", xsVectorGetX(tempV)-6,xsVectorGetZ(tempV)+6,true,3, 180);
			SpawnEnemy("Colossus", xsVectorGetX(tempV)-6,xsVectorGetZ(tempV)-6,true,3, 0);
			
			for(b = 1; < cNumberNonGaiaPlayers){
				SpawnEnemy("Cyclops", xsVectorGetX(tempV)-8,(xsVectorGetZ(tempV)-(cNumberNonGaiaPlayers*2)+(b*4)),true,3, 90);
				SpawnEnemy("Cyclops", xsVectorGetX(tempV)+8,(xsVectorGetZ(tempV)-(cNumberNonGaiaPlayers*2)+(b*4)),true,3, 270);
			}
			tempV = tempV/2;
			//from metres to tiles
			//---CITY 3 LAYOUT
			CreateUnitInAtlantisBox(xsVectorGetX(tempV),xsVectorGetZ(tempV)+7, 3, getTerrainType("GrassDirt50"), getTerrainSubType("GrassDirt50"), 0, "Temple", 90);
			CreateUnitInAtlantisBox(xsVectorGetX(tempV)+7,xsVectorGetZ(tempV), 2, getTerrainType("GrassDirt50"), getTerrainSubType("GrassDirt50"), 0, "Shrine", 0);
			CreateUnitInAtlantisBox(xsVectorGetX(tempV)-7,xsVectorGetZ(tempV), 2, getTerrainType("GrassDirt50"), getTerrainSubType("GrassDirt50"), 0, "Shrine", 0);
			trQuestVarSet("temp1", trGetNextUnitScenarioNameNumber());
			UnitCreate(0, "Dwarf",(xsVectorGetX(tempV)+4)*2,(xsVectorGetZ(tempV)+5)*2);
			trQuestVarSet("temp2", trGetNextUnitScenarioNameNumber());
			UnitCreate(0, "Dwarf",(xsVectorGetX(tempV)-4)*2,(xsVectorGetZ(tempV)-5)*2);
			trQuestVarSet("temp3", trGetNextUnitScenarioNameNumber());
			UnitCreate(0, "Dwarf",(xsVectorGetX(tempV)+4)*2,(xsVectorGetZ(tempV)-5)*2);
			trQuestVarSet("temp4", trGetNextUnitScenarioNameNumber());
			UnitCreate(0, "Dwarf",(xsVectorGetX(tempV)-4)*2,(xsVectorGetZ(tempV)+5)*2);
			CreateUnitInAtlantisBox(xsVectorGetX(tempV)+4,xsVectorGetZ(tempV)+5, 1,-1, -1, 0, "Columns", 0, "1,0,0,0,0,0");
			CreateUnitInAtlantisBox(xsVectorGetX(tempV)-4,xsVectorGetZ(tempV)+5, 1,-1, -1, 0, "Columns", 0, "1,0,0,0,0,0");
			CreateUnitInAtlantisBox(xsVectorGetX(tempV)+4,xsVectorGetZ(tempV)-5, 1,-1, -1, 0, "Columns", 0, "1,0,0,0,0,0");
			CreateUnitInAtlantisBox(xsVectorGetX(tempV)-4,xsVectorGetZ(tempV)-5, 1,-1, -1, 0, "Columns", 0, "1,0,0,0,0,0");
			trUnitSelectByQV("temp1");
			trUnitChangeProtoUnit("Flowers");
			trUnitSelectByQV("temp2");
			trUnitChangeProtoUnit("Flowers");
			trUnitSelectByQV("temp3");
			trUnitChangeProtoUnit("Flowers");
			trUnitSelectByQV("temp4");
			trUnitChangeProtoUnit("Flowers");
		}
		if(xGetInt(dCity, xNumber) == 4){
			//Populate City 4
			tempV = xGetVector(dCity, xLocation);
			SpawnEnemy("Circe", xsVectorGetX(tempV),xsVectorGetZ(tempV)+4,true,4, 180);
			SpawnEnemy("Fire Giant", xsVectorGetX(tempV)+6,xsVectorGetZ(tempV)-6,true,4, 0);
			SpawnEnemy("Fire Giant", xsVectorGetX(tempV)+6,xsVectorGetZ(tempV)+6,true,4, 180);
			SpawnEnemy("Fire Giant", xsVectorGetX(tempV)-6,xsVectorGetZ(tempV)+6,true,4, 180);
			SpawnEnemy("Fire Giant", xsVectorGetX(tempV)-6,xsVectorGetZ(tempV)-6,true,4, 0);
			
			for(b = 1; < cNumberNonGaiaPlayers){
				SpawnEnemy("Mountain Giant", xsVectorGetX(tempV)-8,(xsVectorGetZ(tempV)-(cNumberNonGaiaPlayers*2)+(b*4)),true,4, 90);
				SpawnEnemy("Mountain Giant", xsVectorGetX(tempV)+8,(xsVectorGetZ(tempV)-(cNumberNonGaiaPlayers*2)+(b*4)),true,4, 270);
			}
			tempV = tempV/2;
			//from metres to tiles
			//---CITY 4 LAYOUT
			CreateUnitInAtlantisBox(xsVectorGetX(tempV),xsVectorGetZ(tempV)+7, 3, getTerrainType("GrassDirt50"), getTerrainSubType("GrassDirt50"), 0, "Fortress", 180);
			CreateUnitInAtlantisBox(xsVectorGetX(tempV),xsVectorGetZ(tempV)-7, 2, getTerrainType("GrassDirt50"), getTerrainSubType("GrassDirt50"), 0, "Shrine", 90);
			CreateUnitInAtlantisBox(xsVectorGetX(tempV)+7,xsVectorGetZ(tempV), 3, getTerrainType("GrassDirt50"), getTerrainSubType("GrassDirt50"), 0, "Temple", 180);
			CreateUnitInAtlantisBox(xsVectorGetX(tempV)-7,xsVectorGetZ(tempV), 3, getTerrainType("GrassDirt50"), getTerrainSubType("GrassDirt50"), 0, "Temple", 0);
			trQuestVarSet("temp1", trGetNextUnitScenarioNameNumber());
			UnitCreate(0, "Dwarf",(xsVectorGetX(tempV)+4)*2,(xsVectorGetZ(tempV)+5)*2);
			trQuestVarSet("temp2", trGetNextUnitScenarioNameNumber());
			UnitCreate(0, "Dwarf",(xsVectorGetX(tempV)-4)*2,(xsVectorGetZ(tempV)-5)*2);
			trQuestVarSet("temp3", trGetNextUnitScenarioNameNumber());
			UnitCreate(0, "Dwarf",(xsVectorGetX(tempV)+4)*2,(xsVectorGetZ(tempV)-5)*2);
			trQuestVarSet("temp4", trGetNextUnitScenarioNameNumber());
			UnitCreate(0, "Dwarf",(xsVectorGetX(tempV)-4)*2,(xsVectorGetZ(tempV)+5)*2);
			CreateUnitInAtlantisBox(xsVectorGetX(tempV)+5,xsVectorGetZ(tempV)+5, 1,-1, -1, 0, "Columns", 0, "3,0,0,0,0,0");
			CreateUnitInAtlantisBox(xsVectorGetX(tempV)-5,xsVectorGetZ(tempV)+5, 1,-1, -1, 0, "Columns", 0, "3,0,0,0,0,0");
			CreateUnitInAtlantisBox(xsVectorGetX(tempV)+4,xsVectorGetZ(tempV)-5, 1,-1, -1, 0, "Columns", 0, "3,0,0,0,0,0");
			CreateUnitInAtlantisBox(xsVectorGetX(tempV)-4,xsVectorGetZ(tempV)-5, 1,-1, -1, 0, "Columns", 0, "3,0,0,0,0,0");
			trUnitSelectByQV("temp1");
			trUnitChangeProtoUnit("Mist");
			trUnitSelectByQV("temp2");
			trUnitChangeProtoUnit("Mist");
			trUnitSelectByQV("temp3");
			trUnitChangeProtoUnit("Mist");
			trUnitSelectByQV("temp4");
			trUnitChangeProtoUnit("Mist");
		}
		else if(xGetInt(dCity, xNumber) == 5){
			//Placeholder populate the rest
			tempV = xGetVector(dCity, xLocation);
			SpawnEnemy("Titan Kronos", xsVectorGetX(tempV),xsVectorGetZ(tempV)+4,true,xGetInt(dCity, xNumber), 180);
			SpawnEnemy("Fire Giant", xsVectorGetX(tempV)+2,xsVectorGetZ(tempV)+4,true,xGetInt(dCity, xNumber), 180);
			SpawnEnemy("Fire Giant", xsVectorGetX(tempV)+4,xsVectorGetZ(tempV)+4,true,xGetInt(dCity, xNumber), 180);
			SpawnEnemy("Fire Giant", xsVectorGetX(tempV)-2,xsVectorGetZ(tempV)+4,true,xGetInt(dCity, xNumber), 180);
			SpawnEnemy("Fire Giant", xsVectorGetX(tempV)-4,xsVectorGetZ(tempV)+4,true,xGetInt(dCity, xNumber), 180);
		}
	}
}

void CreateLargeGold(int num = 1){
	vector spawn = vector(0,0,0);
	int allow = 0;
	vector MapMid = xsVectorSet(getMapSize()/2, 0, getMapSize()/2);
	int temp = 0;
	while(num > 0){
		trQuestVarSetFromRand("x", 0, 200);
		trQuestVarSetFromRand("z", 0, 200);
		spawn = perlinRoll(myPerlin, 1*trQuestVarGet("x"),1*trQuestVarGet("z"), 1, -8,20, false) ;
		if(distanceBetweenVectors(spawn, MapMid) > 2000){
			//no city
			allow = 0;
			for(b = xGetDatabaseCount(dCity); > 0){
				xDatabaseNext(dCity);
				if(distanceBetweenVectors(spawn, xGetVector(dCity, xLocation)) > 2000){
					allow = allow+1;
				}
			}
			if(allow == CitiesToMake){
				temp = trGetNextUnitScenarioNameNumber();
				UnitCreateV(0, "Dwarf", spawn);
				trUnitSelectClear();
				trUnitSelect(""+temp);
				trUnitChangeProtoUnit("Gold Mine");
				num = num-1;
			}
			else{
				trUnitSelectClear();
				trUnitSelect(""+temp);
				trUnitDestroy();
			}
		}
	}
}

void CreateStartingGold(int num = 1){
	int allow = 0;
	vector spawn = vector(0,0,0);
	vector MapMid = xsVectorSet(getMapSize()/2, 0, getMapSize()/2);
	int temp = 0;
	while(num > 0){
		trQuestVarSetFromRand("x", 0, 200);
		trQuestVarSetFromRand("z", 0, 200);
		spawn = perlinRoll(myPerlin, 1*trQuestVarGet("x"),1*trQuestVarGet("z"), 1, -8,20, false) ;
		if(distanceBetweenVectors(spawn, MapMid) > 2000){
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreateV(0, "Victory Marker", spawn);
			if(trCountUnitsInArea(""+temp, 0, "Victory Marker", 20) == 1){
				//No clustering
				
				//no city
				allow = 0;
				for(b = xGetDatabaseCount(dCity); > 0){
					xDatabaseNext(dCity);
					if(distanceBetweenVectors(spawn, xGetVector(dCity, xLocation)) > 2000){
						allow = allow+1;
					}
				}
				if(allow == CitiesToMake){
					num = num-1;
				}
				else{
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitDestroy();
				}
			}
			else{
				trUnitSelectClear();
				trUnitSelect(""+temp);
				trUnitDestroy();
			}
		}
	}
	if(num == 0){
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeInArea(0, 0, "Victory Marker", "Gold Mine Small", 999.0);
	}
}

void CreateStartingPillBoxes(int num = 1){
	vector spawn = vector(0,0,0);
	vector MapMid = xsVectorSet(getMapSize()/2, 0, getMapSize()/2);
	int temp = 0;
	int allow = 0;
	while(num > 0){
		trQuestVarSetFromRand("x", 0, 200);
		trQuestVarSetFromRand("z", 0, 200);
		spawn = perlinRoll(myPerlin, 1*trQuestVarGet("x"),1*trQuestVarGet("z"), 1, -8,20, false) ;
		if(distanceBetweenVectors(spawn, MapMid) > 2000){
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreateV(0, "Victory Marker", spawn);
			if(trCountUnitsInArea(""+temp, 0, "Tower", 20) == 0){
				//No clustering
				
				//no city
				allow = 0;
				for(b = xGetDatabaseCount(dCity); > 0){
					xDatabaseNext(dCity);
					if(distanceBetweenVectors(spawn, xGetVector(dCity, xLocation)) > 2000){
						allow = allow+1;
					}
				}
				if(allow == CitiesToMake){
					CreatePillBox(xsVectorGetX(spawn), xsVectorGetZ(spawn));
					num = num-1;
				}
			}
			else{
				trUnitSelectClear();
				trUnitSelect(""+temp);
				trUnitDestroy();
			}
		}
	}
	if(num == 0){
		//Destroy unused victory markers
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeInArea(0, 0, "Victory Marker", "Rocket", 999.0);
	}
}

void CreateStartingRelics(int num = 1){
	vector spawn = vector(0,0,0);
	vector MapMid = xsVectorSet(getMapSize()/2, 0, getMapSize()/2);
	int temp = 0;
	int allow = 0;
	float dist = 0.0;
	while(num > 0){
		trQuestVarSetFromRand("x", 0, 200);
		trQuestVarSetFromRand("z", 0, 200);
		spawn = perlinRoll(myPerlin, 1*trQuestVarGet("x"),1*trQuestVarGet("z"), 1, -8,20, false) ;
		dist = distanceBetweenVectors(spawn, MapMid, false);
		if(dist > 26){
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreateV(0, "Victory Marker", spawn);
			if(trCountUnitsInArea(""+temp, 0, "Victory Marker", 20) == 1){
				//No clustering
				
				//no city
				allow = 0;
				for(b = xGetDatabaseCount(dCity); > 0){
					xDatabaseNext(dCity);
					if(distanceBetweenVectors(spawn, xGetVector(dCity, xLocation)) > 2000){
						allow = allow+1;
					}
				}
				if(allow == CitiesToMake){
					num = num-1;
					if(dist < 80){
						//FORCE LEVEL 1 RELICS
						//DeployRelic(xsVectorGetX(spawn), xsVectorGetZ(spawn),1);
						DeployRelic(xsVectorGetX(spawn), xsVectorGetZ(spawn),);
					}
					if((dist < 120) && (dist >= 80)){
						//FORCE LEVEL 2 RELICS
						//DeployRelic(xsVectorGetX(spawn), xsVectorGetZ(spawn),3);
						DeployRelic(xsVectorGetX(spawn), xsVectorGetZ(spawn),);
					}
					if((dist < 160) && (dist >= 120)){
						//FORCE LEVEL 3 RELICS
						//DeployRelic(xsVectorGetX(spawn), xsVectorGetZ(spawn),4);
						DeployRelic(xsVectorGetX(spawn), xsVectorGetZ(spawn),);
					}
					else if(dist >= 160){
						//FORCE LEVEL 4 RELICS
						//DeployRelic(xsVectorGetX(spawn), xsVectorGetZ(spawn),5);
						DeployRelic(xsVectorGetX(spawn), xsVectorGetZ(spawn),);
					}
				}
			}
			else{
				trUnitSelectClear();
				trUnitSelect(""+temp);
				trUnitDestroy();
			}
		}
	}
	if(num == 0){
		//Destroy unused victory markers
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeInArea(0, 0, "Victory Marker", "Rocket", 999.0);
	}
}

void CreateStartingAnimals(int num = 1){
	vector spawn = vector(0,0,0);
	vector MapMid = xsVectorSet(getMapSize()/2, 0, getMapSize()/2);
	int temp = 0;
	int allow = 0;
	float dist = 0.0;
	while(num > 0){
		trQuestVarSetFromRand("x", 0, 200);
		trQuestVarSetFromRand("z", 0, 200);
		spawn = perlinRoll(myPerlin, 1*trQuestVarGet("x"),1*trQuestVarGet("z"), 1, -2,20, false) ;
		dist = distanceBetweenVectors(spawn, MapMid, true);
		if(dist > 670){
			//no city
			allow = 0;
			for(b = xGetDatabaseCount(dCity); > 0){
				xDatabaseNext(dCity);
				if(distanceBetweenVectors(spawn, xGetVector(dCity, xLocation)) > 2000){
					allow = allow+1;
				}
			}
			if(allow == CitiesToMake){
				temp = trGetNextUnitScenarioNameNumber();
				UnitCreateV(0, "Victory Marker", spawn);
				UnitCreateV(0, "Victory Marker", spawn);
				num = num-1;
			}
			else{
				trUnitSelectClear();
				trUnitSelect(""+temp);
				trUnitDestroy();
			}
		}
	}
	if(num == 0){
		//Destroy unused victory markers
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeInArea(0, 0, "Victory Marker", "Deer", 999.0);
	}
}

void CreateStartingBerries(int num = 1){
	vector spawn = vector(0,0,0);
	vector MapMid = xsVectorSet(getMapSize()/2, 0, getMapSize()/2);
	int temp = 0;
	int allow = 0;
	float dist = 0.0;
	while(num > 0){
		trQuestVarSetFromRand("x", 0, 200);
		trQuestVarSetFromRand("z", 0, 200);
		spawn = perlinRoll(myPerlin, 1*trQuestVarGet("x"),1*trQuestVarGet("z"), 1, -1,20, false) ;
		dist = distanceBetweenVectors(spawn, MapMid, true);
		if(dist > 670){
			//no city
			allow = 0;
			for(b = xGetDatabaseCount(dCity); > 0){
				xDatabaseNext(dCity);
				if(distanceBetweenVectors(spawn, xGetVector(dCity, xLocation)) > 2000){
					allow = allow+1;
				}
			}
			if(allow == CitiesToMake){
				temp = trGetNextUnitScenarioNameNumber();
				UnitCreate(0, "Victory Marker", xsVectorGetX(spawn)+2, xsVectorGetZ(spawn)+2);
				UnitCreate(0, "Victory Marker", xsVectorGetX(spawn)+2, xsVectorGetZ(spawn)-2);
				UnitCreate(0, "Victory Marker", xsVectorGetX(spawn)-2, xsVectorGetZ(spawn)+2);
				UnitCreate(0, "Victory Marker", xsVectorGetX(spawn)-2, xsVectorGetZ(spawn)-2);
				num = num-1;
			}
			else{
				trUnitSelectClear();
				trUnitSelect(""+temp);
				trUnitDestroy();
			}
		}
	}
	if(num == 0){
		//Destroy unused victory markers
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeInArea(0, 0, "Victory Marker", "Berry Bush", 999.0);
	}
}

rule WorldCreate
highFrequency
inactive
{
	int temp = 0;
	xsDisableSelf();
	xsEnableRule("DeployPlayers");
	myPerlin = generatePerlinNoise(getMapSize()/2, 10);
	float height = 0;
	float biome = 0.0;
	for(x=0; <= getMapSize()/2) {
		for(y=0; <= getMapSize()/2) {
			height = getPerlinNoise(myPerlin, x, y) * 2.0; // you may need to tweak this modifier
			//Always do the height
			trChangeTerrainHeight(x,y,x,y,height);
			if(height > 2){
				trPaintTerrain(x,y,x,y,getTerrainType("ForestFloorGaia"),getTerrainSubType("ForestFloorGaia"));
			}
			if(height > 3){
				trPaintTerrain(x,y,x,y,getTerrainType("ForestFloorOak"),getTerrainSubType("ForestFloorOak"));
			}
			if((height <= 2) && (height > 0)){
				trPaintTerrain(x,y,x,y,getTerrainType("RiverGrassyC"),getTerrainSubType("RiverGrassyC"));
			}
			if((height <= 0) && (height > -2.5)){
				trPaintTerrain(x,y,x,y,getTerrainType("CliffGreekB"),getTerrainSubType("CliffGreekB"));
			}
			if((height <= -2.5) && (height > -5)){
				trPaintTerrain(x,y,x,y,getTerrainType("GrassDirt25"),getTerrainSubType("GrassDirt25"));
			}
			if(height < -5){
				trPaintTerrain(x,y,x,y,getTerrainType("GrassDirt50"),getTerrainSubType("GrassDirt50"));
			}
			if(height < -6){
				trPaintTerrain(x,y,x,y,getTerrainType("GrassDirt75"),getTerrainSubType("GrassDirt75"));
			}
		}
	}
	//--- Split using MapBuild void
	TerrainTileDBSet("GrassDirt75", dLowTerrain, xDeployLoc);
	SpawnPlayers();
	//---
	BuildCities();
	//---
	smooth(4);
	trPaintTerrain(getMapSize()/4-1,getMapSize()/4-1,getMapSize()/4+1,getMapSize()/4+1,2,13);
	paintTrees2("ForestFloorOak", "Oak Tree");
	//---
	SetupCities();
	CreateLargeGold(6+cNumberNonGaiaPlayers);
	CreateStartingGold(50);
	//---
	CreateStartingPillBoxes(40);
	//---
	CreateStartingRelics(50);
	//---
	CreateStartingAnimals(30);
	CreateStartingBerries(30);
	refreshPassability();
	//perlinRoll(myPerlin, 30,30, 1, -7,20, true) ;
	if(Visible == false){
		trSetFogAndBlackmap(true, true);
	}
	xsEnableRule("CaptureCity");
	xsEnableRule("RocketAssembled");
	xsEnableRule("BeginDay");
	xsEnableRule("GameMechanics");
	NextDay = trTime();
	vector spawn = vector(0,0,0);
	//--Test relic
	DeployRelic(getMapSize()/2+4,getMapSize()/2+10,TestRelic);
	SpawnEnemy("Militia", getMapSize()/2-10,getMapSize()/2);
	trPlayerResetBlackMapForAllPlayers();
	xsEnableRule("BlackMap");
	CityPillbox(1);
	xsEnableRule("RocketAttackWarn");
	xsEnableRule("RocketAttack50Warn");
	xsEnableRule("RocketDead");
	xsEnableRule("PlayerDead");
	
	trUnblockAllSounds();
	trChatHistoryClear();
	
	trTechGodPower(1, "Vision", 100);
	trTechGodPower(1, "Sandstorm", 100);
	trTechGodPower(1, "SPClightning storm", 100);
	trMusicPlay();
	trPlayNextMusicTrack();
	
}

rule BlackMap
highFrequency
inactive
{
	if((trTime()-cActivationTime) >= 1){
		trPlayerResetBlackMapForAllPlayers();
		xsDisableSelf();
	}
}

rule DeployPlayers
highFrequency
inactive
{
	int temp = 0;
	for(p = 1 ; < cNumberNonGaiaPlayers){
		temp = trGetNextUnitScenarioNameNumber();
		trClearCounterDisplay();
		if(trCurrentPlayer() == p){
			trSetCounterDisplay("Current ammo: " + xGetInt(dPlayerData, xAmmo));
		}
	}
	uiZoomToProto("Villager Atlantean Hero");
	uiLookAtProto("Villager Atlantean Hero");
	xsEnableRule("GameTowerGarrison");
	trCounterAbort("rocketparts");
	trCounterAddTime("rocketparts", -100, -20000, "Rocket Parts: " + CartsCaptured + "/" + CitiesToMake, -1);
	xsDisableSelf();
}

rule GameTowerGarrison
highFrequency
inactive
{
	int temp = 0;
	int missileclass = 0;
	int targetid = 0;
	int anim = 0;
	int unit = 0;
	for(p = 1; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		unit = xGetInt(dPlayerData, xUnitID);
		xUnitSelect(dPlayerData, xUnitID);
		xsSetContextPlayer(p);
		targetid = trGetUnitScenarioNameNumber(kbUnitGetTargetUnitID(kbGetBlockID(""+unit)));
		xsSetContextPlayer(0);
		anim = kbUnitGetAnimationActionType(kbGetBlockID(""+unit));
		if(anim == 6){
			for(d = xGetDatabaseCount(dTowers); > 0){
				xDatabaseNext(dTowers);
				if(targetid == xGetInt(dTowers, xUnitID)){
					xUnitSelect(dPlayerData, xUnitID);
					trImmediateUnitGarrison(""+xGetInt(dTowers, xUnitID));
					xSetVector(dPlayerData, xUnitPos, kbGetBlockPosition(""+unit));
					xSetBool(dPlayerData, xInTower, true);
					xUnitSelect(dTowers, xUnitID);
					trUnitConvert(p);
					xSetInt(dTowers, xOwner, p);
					//garrison inside
					xUnitSelect(dPlayerData, xUnitID);
					trImmediateUnitGarrison(""+xGetInt(dTowers, xUnitID));
					//dialog
					missileclass = xGetInt(dPlayerData, xCurrentMissile);
					xSetPointer(dProjectiles, missileclass);
					modifyProtounitAbsolute("Kronny Flying", p, 1, xGetFloat(dProjectiles, xProjSpeed));
					xUnitSelect(dTowers, xTowerSFXID);
					trUnitChangeProtoUnit("Spy Eye");
					xUnitSelect(dTowers, xTowerSFXID);
					trMutateSelected(kbGetProtoUnitID(xGetString(dProjectiles, xProjTowerProto)));
					xUnitSelect(dTowers, xTowerSFXID);
					trUnitSetAnimationPath(xGetString(dProjectiles, xProjTowerProtoAnimPath));
					xUnitSelect(dTowers, xTowerSFXID);
					trSetSelectedScale(xGetFloat(dProjectiles, xProjTowerProtoSize),xGetFloat(dProjectiles, xProjTowerProtoSize),xGetFloat(dProjectiles, xProjTowerProtoSize));
					modifyProtounitAbsolute("Tower", p, 11, xGetInt(dProjectiles, xProjRange));
					modifyProtounitAbsolute("Tower", p, 2, xGetInt(dProjectiles, xProjLOS));
					if(xGetInt(dProjectiles, xProjAmmoCost) <= xGetInt(dPlayerData, xAmmo)){
						if(trCurrentPlayer() == p){
							trClearCounterDisplay();
							uiZoomToProto("Tower");
							//uiLookAtProto("Tower");
							trSetCounterDisplay("<color={PlayerColor("+p+")}>Firing " + xGetString(dProjectiles, xProjName) + "| Ammo remaining - " + xGetInt(dPlayerData, xAmmo));
						}
					}
					else{
						//Not enough ammo
						if(trCurrentPlayer() == p){
							trClearCounterDisplay();
							trSetCounterDisplay("<color={PlayerColor(2)}>Not enough ammo to fire " + xGetString(dProjectiles, xProjName) + "| Ammo - " + xGetInt(dPlayerData, xAmmo) + "/" + xGetInt(dProjectiles, xProjAmmoCost));
							playSound("cantdothat.wav");
						}
						if(trTime() > 1*trQuestVarGet("P"+p+"AmmoWarnMsg")){
							if(trCurrentPlayer() == p){
								uiMessageBox("You have run out of ammo so cannot fire. Mine gold to get more ammo.");
							}
						}
						trQuestVarSet("P"+p+"AmmoWarnMsg", trTime()+60);
					}
					//If the unit is doing attack animation on a tower, garrison inside it
					if(1*trQuestVarGet("P"+p+"FirstTower") == 0){
						trQuestVarSet("P"+p+"FirstTower", 1);
						if(trCurrentPlayer() == p){
							trOverlayText("Your ammo is displayed here --> Mine gold to increase it", 8.0, 530, 130, 470);
						}
					}
				}
			}
		}
		xUnitSelect(dPlayerData, xUnitID);
		if(trUnitGetIsContained("Tower") == false){
			if(trCurrentPlayer() == p){
				if(xGetInt(dPlayerData, xAmmo) == 0){
					trSetCounterDisplay("<color={PlayerColor(2)}>Current ammo: " + xGetInt(dPlayerData, xAmmo));
				}
				else{
					trSetCounterDisplay("Current ammo: " + xGetInt(dPlayerData, xAmmo));
				}
			}
			if(xGetBool(dPlayerData, xInTower) == true){
				for(c = xGetDatabaseCount(dTowers); > 0){
					xDatabaseNext(dTowers);
					if(xGetInt(dTowers, xOwner) == p){
						xSetBool(dPlayerData, xInTower, false);
						xUnitSelect(dTowers, xUnitID);
						trUnitConvert(0);
						xSetInt(dTowers, xOwner, 0);
						xUnitSelect(dTowers, xTowerSFXID);
						trUnitChangeProtoUnit("Cinematic Block");
						if(trCurrentPlayer() == p){
							uiZoomToProto("Villager Atlantean Hero");
							uiLookAtProto("Villager Atlantean Hero");
						}
					}
				}
			}
		}
		xUnitSelect(dPlayerData, xUnitID);
		if(trUnitGetIsContained("Manor") == true){
			xUnitSelect(dPlayerData, xUnitID);
			if(trUnitPercentDamaged() == 0){
				if(trTime() > 1*trQuestVarGet("P"+p+"ManorMsg")){
					if(trCurrentPlayer() == p){
						uiMessageBox("Your citizen is back to full health.");
						playSound("herorevived.wav");
					}
				}
				trQuestVarSet("P"+p+"ManorMsg", trTime()+15);
			}
			
		}
	}
}

rule GameMechanics
highFrequency
active
{
	int resource = 0;
	for(p=1 ; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		resource = trPlayerResourceCount(p, "Gold");
		if(resource > 0){
			trPlayerGrantResources(p, "Gold", -1*resource);
			xSetInt(dPlayerData, xAmmo, xGetInt(dPlayerData, xAmmo)+1*resource);
		}
		xUnitSelect(dPlayerData, xUnitID);
		trUnitChangeInArea(p,p,"Farm", "Villager Atlantean", 999);
	}
}

rule RemoveEnemies
highFrequency
active
{
	for(i = xsMin(xGetDatabaseCount(dEnemies), cNumberNonGaiaPlayers); > 0){
		xDatabaseNext(dEnemies);
		xUnitSelect(dEnemies, xUnitID);
		if(trUnitAlive() == false){
			xFreeDatabaseBlock(dEnemies);
		}
	}
	for(i = xsMin(xGetDatabaseCount(dTowers), cNumberNonGaiaPlayers); > 0){
		xDatabaseNext(dTowers);
		xUnitSelect(dTowers, xUnitID);
		if(trUnitAlive() == false){
			xFreeDatabaseBlock(dTowers);
		}
	}
	if(xGetDatabaseCount(dBuildTowers) > 0){
		for(i = xsMin(xGetDatabaseCount(dBuildTowers), cNumberNonGaiaPlayers); > 0){
			xDatabaseNext(dBuildTowers);
			xUnitSelect(dBuildTowers, xUnitID);
			if(trUnitAlive() == false){
				xFreeDatabaseBlock(dBuildTowers);
			}
			if(trUnitPercentComplete() == 100){
				MakeThisAPillbox(xGetInt(dBuildTowers, xUnitID));
				xFreeDatabaseBlock(dBuildTowers);
			}
		}
	}
	
}

rule TowersFire
highFrequency
active
{
	vector dir = vector(0,0,0);
	vector targetpos = vector(0,0,0);
	vector startpos = vector(0,0,0);
	int targetid = -1;
	int towerid = -1;
	int shotby = 0;
	int missileclass = 0;
	int index = 0;
	bool AttackAllowed = true;
	//cycle through all towers and find ones under player control
	for(c = xGetDatabaseCount(dTowers); > 0){
		xDatabaseNext(dTowers);
		if(xGetInt(dTowers, xOwner) > 0){
			xSetPointer(dPlayerData, xGetInt(dTowers, xOwner));
			if(trTimeMS() >= xGetInt(dPlayerData, xLastShotTime)){
				shotby = xGetInt(dTowers, xOwner);
				towerid = xGetInt(dTowers, xUnitID);
				xsSetContextPlayer(shotby);
				targetid = trGetUnitScenarioNameNumber(kbUnitGetTargetUnitID(kbGetBlockID(""+towerid)));
				xsSetContextPlayer(0);
				if(targetid != -1){
					trUnitSelectClear();
					trUnitSelect(""+targetid);
					if(trUnitAlive()){
						targetpos = kbGetBlockPosition(""+targetid);
						startpos = xGetVector(dTowers, xTowerPos);
						dir = xsVectorNormalize(xsVectorSetY(targetpos-startpos, 0));
						xSetPointer(dPlayerData, shotby);
						missileclass = xGetInt(dPlayerData, xCurrentMissile);
						xSetPointer(dProjectiles, missileclass);
						if(xGetInt(dProjectiles, xProjAmmoCost) <= xGetInt(dPlayerData, xAmmo)){
							//ENOUGH AMMO - FIRE
							if(xGetBool(dProjectiles, xProjUse)){
								if(xGetInt(dProjectiles, xProjCount) == 1){
									FireMissile(dir, xGetPointer(dTowers), shotby);
									xSetInt(dPlayerData, xAmmo, xGetInt(dPlayerData, xAmmo)-xGetInt(dProjectiles, xProjAmmoCost));
									if(trCurrentPlayer() == shotby){
										trSetCounterDisplay("<color={PlayerColor("+shotby+")}>Firing " + xGetString(dProjectiles, xProjName) + "| Ammo remaining - " + xGetInt(dPlayerData, xAmmo));
									}
								}
								else{
									// FIRE MULTIPLE PROJECTILES
									dir = rotationMatrix(dir, xGetFloat(dProjectiles, xProjBaseCos), xGetFloat(dProjectiles, xProjBaseSin));
									for(shots = 0; < xGetInt(dProjectiles, xProjCount)){
										FireMissile(dir, xGetPointer(dTowers), shotby);
										dir = rotationMatrix(dir, xGetFloat(dProjectiles, xProjMoveCos), xGetFloat(dProjectiles, xProjMoveSin));
									}
									xSetInt(dPlayerData, xAmmo, xGetInt(dPlayerData, xAmmo)-xGetInt(dProjectiles, xProjAmmoCost));
									if(trCurrentPlayer() == shotby){
										trSetCounterDisplay("<color={PlayerColor("+shotby+")}>Firing " + xGetString(dProjectiles, xProjName) + "| Ammo remaining - " + xGetInt(dPlayerData, xAmmo));
									}
								}
							}
							else{
								//NO PROJ SHOOTER
								if((xGetInt(dProjectiles, xProjClass) == PROJ_Bolter) || (xGetInt(dProjectiles, xProjClass) == PROJ_BolterClose)){
									//Bolter
									trUnitSelectClear();
									trUnitSelect(""+targetid);
									trTechInvokeGodPower(0, "Bolt", vector(0,0,0), vector(0,0,0));
									trUnitSelectClear();
									trUnitSelect(""+targetid);
									trDamageUnit(xGetInt(dProjectiles, xProjDamage));
								}
								if(xGetInt(dProjectiles, xProjClass) == PROJ_Burner){
									//Burner
									trUnitSelectClear();
									trUnitSelect(""+targetid);
									index = xAddDatabaseBlock(dOnFire, true);
									xSetInt(dOnFire, xUnitID, targetid);
									xSetFloat(dOnFire, xTimeToBurn, trTimeMS()+xGetInt(dProjectiles, xProjFireRate));
									xSetFloat(dOnFire, xTotalBurnDamage, xGetInt(dProjectiles, xProjDamage));
									xSetFloat(dOnFire, xDamagePerTick, xGetFloat(dOnFire, xTotalBurnDamage)/xGetInt(dProjectiles, xProjFireRate));
									//select the burn spy id
									for(u = xGetDatabaseCount(dEnemies); > 0){
										xDatabaseNext(dEnemies);
										if(xGetInt(dEnemies, xUnitID) == targetid){
											break;
										}
									}
									xUnitSelect(dEnemies, xSpyBurn);
									trMutateSelected(kbGetProtoUnitID("Inferno Unit Flame"));
									xSetInt(dOnFire, xBurnSpyID, xGetInt(dEnemies, xSpyBurn));
								}
								if(xGetInt(dProjectiles, xProjClass) == PROJ_Rapture){
									//Rapture Human
									
									if(trCountUnitsInArea(""+targetid, cNumberNonGaiaPlayers, "HumanSoldier", 0) > 0){
										//Human check
										trUnitSelectClear();
										trUnitSelect(""+targetid);
										trUnitChangeProtoUnit("Titan Atlantean");
										trUnitSelectClear();
										trUnitSelect(""+targetid);
										trUnitChangeProtoUnit("Dwarf");
										trUnitSelectClear();
										trUnitSelect(""+targetid);
										trUnitChangeInArea(cNumberNonGaiaPlayers, cNumberNonGaiaPlayers, "Titan Gate Dead", "Hero Death", 1);
										trUnitSelectClear();
										trUnitSelect(""+targetid);
										trUnitChangeProtoUnit("Ragnorok SFX");
									}
									else{
										AttackAllowed = false;
									}
								}
								if((xGetInt(dProjectiles, xProjClass) == PROJ_Curse) || (xGetInt(dProjectiles, xProjClass) == PROJ_CurseFast)){
									//Curse Human
									
									if(trCountUnitsInArea(""+targetid, cNumberNonGaiaPlayers, "HumanSoldier", 0) > 0){
										//Human check
										trUnitSelectClear();
										trUnitSelect(""+targetid);
										trUnitChangeProtoUnit("Titan Atlantean");
										trUnitSelectClear();
										trUnitSelect(""+targetid);
										trUnitChangeProtoUnit("Dwarf");
										trUnitSelectClear();
										trUnitSelect(""+targetid);
										trUnitChangeInArea(cNumberNonGaiaPlayers, cNumberNonGaiaPlayers, "Titan Gate Dead", "Pig", 1);
										trUnitSelectClear();
										trUnitSelect(""+targetid);
										trUnitChangeProtoUnit("Curse SFX");
									}
									else{
										AttackAllowed = false;
									}
								}
								if(xGetInt(dProjectiles, xProjClass) == PROJ_Tremor){
									//Tremor
									trUnitSelectClear();
									trUnitSelect(""+targetid);
									trTechInvokeGodPower(0, "Tremor", kbGetBlockPosition(""+targetid), vector(0,0,0));
									trUnitSelectClear();
									trUnitSelect(""+targetid);
									trDamageUnit(xGetInt(dProjectiles, xProjDamage));
								}
								xSetInt(dPlayerData, xAmmo, xGetInt(dPlayerData, xAmmo)-xGetInt(dProjectiles, xProjAmmoCost));
								if(trCurrentPlayer() == shotby){
									trSetCounterDisplay("<color={PlayerColor("+shotby+")}>Firing " + xGetString(dProjectiles, xProjName) + "| Ammo remaining - " + xGetInt(dPlayerData, xAmmo));
								}
							}
							//[SOUND LOS]
							if(AttackAllowed){
								xUnitSelect(dTowers, xUnitID);
								
								if(trUnitVisToPlayer()){
									playSound(""+xGetString(dProjectiles, xProjSound));
								}
							}
							xSetInt(dPlayerData, xLastShotTime, trTimeMS()+xGetInt(dProjectiles, xProjFireRate));
						}
						else{
							//NOT ENOUGH AMMO
							if(trCurrentPlayer() == shotby){
								trSetCounterDisplay("<color={PlayerColor(2)}>Not enough ammo to fire " + xGetString(dProjectiles, xProjName) + "| Ammo - " + xGetInt(dPlayerData, xAmmo) + "/" + xGetInt(dProjectiles, xProjAmmoCost));
							}
							if(trTime() > 1*trQuestVarGet("P"+shotby+"AmmoWarnMsg")){
								if(trCurrentPlayer() == shotby){
									uiMessageBox("You have run out of ammo so cannot fire. Mine gold to get more ammo.");
									playSound("cantdothat.wav");
								}
							}
							trQuestVarSet("P"+shotby+"AmmoWarnMsg", trTime()+60);
						}
					}
				}
			}
		}
	}
}

rule UnitsOnFire
active
highFrequency
{
	if(trTimeMS() > firetimelast){
		firetimediff = (trTimeMS() - firetimelast); // calculate timediff
		if(xGetDatabaseCount(dOnFire) > 0){
			for(a = xGetDatabaseCount(dOnFire); > 0){
				xDatabaseNext(dOnFire);
				xUnitSelect(dOnFire, xUnitID);
				trDamageUnit(xGetFloat(dOnFire, xDamagePerTick)*firetimediff);
				if(trTimeMS() > xGetFloat(dOnFire, xTimeToBurn)){
					xUnitSelect(dOnFire, xBurnSpyID);
					//trMutateSelected(kbGetProtoUnitID("Cinematic Block"));
					trUnitChangeProtoUnit("Cinematic Block");
					xFreeDatabaseBlock(dOnFire);
				}
			}
		}
		if(xGetDatabaseCount(dStunned) > 0){
			for(a = xGetDatabaseCount(dStunned); > 0){
				xDatabaseNext(dStunned);
				xUnitSelect(dStunned, xUnitID);
				trMutateSelected(xGetInt(dStunned, xStunMutate));
				if(trTimeMS() > xGetFloat(dStunned, xTimeStunned)){
					xUnitSelect(dStunned, xStunSpyID);
					//trMutateSelected(kbGetProtoUnitID("Cinematic Block"));
					trUnitChangeProtoUnit("Cinematic Block");
					xFreeDatabaseBlock(dStunned);
				}
			}
		}
		firetimelast = trTimeMS();
	}
}

//---1s timer loop
rule CaptureCity
inactive
highFrequency
{
	int cityalive = 0;
	vector MapMid = xsVectorSet(getMapSize()/2, 0, getMapSize()/2);
	if(trTime() > citychecktime){
		citychecktime = trTime();
		//change city int
		for(city = 1; <= CitiesToMake){
			cityalive = 0;
			while(xGetInt(dCity, xNumber) != city){
				xDatabaseNext(dCity);
			}
			if(xGetBool(dCity, xCityAlive)){
				for(a = xGetDatabaseCount(dEnemies); > 0){
					xDatabaseNext(dEnemies);
					if(xGetInt(dEnemies, xCityGuard) == city){
						cityalive = 1;
						//There is at least one guard remaining
					}
				}
				
				if(cityalive == 0){
					//---CITY CAPTURED
					CitiesCaptured = CitiesCaptured+1;
					trOverlayText("City captured!", 4);
					playSound("fanfare.wav");
					xSetBool(dCity, xCityAlive, false);
					xUnitSelect(dCity, xCityFlagID);
					trUnitChangeProtoUnit("Olympus Temple SFX");
					xUnitSelect(dCity, xCitySFXID);
					trUnitChangeProtoUnit("Osiris Box Glow");
					xUnitSelect(dCity, xCityChestID);
					trUnitChangeProtoUnit("Great Box Cart");
					xUnitSelect(dCity, xCityLOSID);
					trUnitChangeProtoUnit("Heavenlight");
					xAddDatabaseBlock(dCarts, true);
					xSetInt(dCarts, xUnitID, xGetInt(dCity, xCityChestID));
					xSetInt(dCarts, xFromCity, xGetInt(dCity, xNumber));
					xSetVector(dCarts, xHomeLocation, xGetVector(dCity, xLocation));
					for(c = xGetDatabaseCount(dCityBuildings); > 0){
						xDatabaseNext(dCityBuildings);
						if(xGetInt(dCityBuildings, xCity) == city){
							xUnitSelect(dCityBuildings, xUnitID);
							trDamageUnitPercent(100);
						}
					}
				}
			}
		}
		//Check cart
		if(xGetDatabaseCount(dCarts) > 0){
			for(a = xGetDatabaseCount(dCarts); > 0){
				xDatabaseNext(dCarts);
				if(distanceBetweenVectors(MapMid, kbGetBlockPosition(""+xGetInt(dCarts, xUnitID)), true) < 400){
					//Cart home
					//[THIS WILL CAUSE OOS IF TERRAIN CHANGES]
					trOverlayText("Rocket part returned!", 4);
					playSound("fanfare.wav");
					CartsCaptured = CartsCaptured+1;
					CaptureReward(CartsCaptured);
					trCounterAbort("rocketparts");
					trCounterAddTime("rocketparts", -100, -20000, "Rocket Parts: " + CartsCaptured + "/" + CitiesToMake, -1);
					xUnitSelect(dCarts, xUnitID);
					trUnitChangeProtoUnit("Osiris Box Glow");
					xUnitSelect(dCarts, xUnitID);
					trUnitSetAnimationPath("0,1,0,0,0,0");
					xFreeDatabaseBlock(dCarts);
					if(CartsCaptured < (CitiesToMake)-1){
						CityPillbox(CartsCaptured+1);
					}
				}
				xUnitSelect(dCarts, xUnitID);
				if(trUnitIsOwnedBy(cNumberNonGaiaPlayers)){
					xUnitSelect(dCarts, xUnitID);
					tempV = xGetVector(dCarts, xHomeLocation);
					trUnitMoveToPoint(xsVectorGetX(tempV),0,xsVectorGetZ(tempV),-1,false);
				}
			}
		}
		//Resources
		for(p = 1 ; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			trPlayerGrantResources(p, "Gold",trPlayerUnitCountSpecific(p, "Guild"));
			//Citizen Damage
			if(1*trQuestVarGet("P"+p+"DmgWarn") == 0){
				xUnitSelect(dPlayerData, xUnitID);
				if(trUnitPercentDamaged() > 0){
					trQuestVarSet("P"+p+"DmgWarn", 1);
					trUnforbidProtounit(p, "Manor");
					if(trCurrentPlayer() == p){
						trOverlayText("Manor unlocked - garrison inside to heal", 7);
					}
				}
			}
			
		}
		//Manor heal
		if(xGetDatabaseCount(dManor) > 0){
			for(a = xGetDatabaseCount(dManor); > 0){
				xDatabaseNext(dManor);
				if(xGetBool(dManor, xComplete) == false){
					xUnitSelect(dManor, xUnitID);
					if(trUnitPercentComplete() == 100){
						xSetBool(dManor, xComplete, true);
						xUnitSelect(dManor, xUnitID);
						trUnitChangeProtoUnit("Titan Atlantean");
						xSetInt(dManor, xManorSFXID, yGetLatestReverse("Titan Gate Dead"));
						xUnitSelect(dManor, xUnitID);
						trUnitChangeProtoUnit("Manor");
						xUnitSelect(dManor, xManorSFXID);
						trUnitChangeProtoUnit("Cinematic Block");
					}
				}
				else{
					xUnitSelect(dManor, xUnitID);
					if(trUnitAlive() == false){
						xFreeDatabaseBlock(dManor);
						break;
					}
					xUnitSelect(dManor, xUnitID);
					if(xGetBool(dManor, xHosting) == false){
						if(trUnitGetContained() > 0){
							xSetBool(dManor, xHosting, true);
							xUnitSelect(dManor, xManorSFXID);
							trUnitChangeProtoUnit("Implode Sphere Effect");
							xUnitSelect(dManor, xManorSFXID);
							trUnitOverrideAnimation(18,0,true,true,-1);
							xUnitSelect(dManor, xManorSFXID);
							trUnitSetAnimationPath("0,0,1,1,0,0");
						}
					}
					else{
						if(trUnitGetContained() == 0){
							xSetBool(dManor, xHosting, false);
							xUnitSelect(dManor, xManorSFXID);
							trUnitChangeProtoUnit("Cinematic Block");
						}
					}
					for(p = 1; < cNumberNonGaiaPlayers){
						trDamageUnitsInArea(p, "Unit", 1, -50);
					}
				}
			}
		}
	}
}


rule RocketAssembled
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 4){
		if(CartsCaptured == CitiesToMake){
			trCounterAbort("rocketparts");
			trOverlayText("Palace unlocked - build your own armoured car!", 7);
			xsDisableSelf();
		}
	}
}

rule RocketAttackWarn
inactive
highFrequency
{
	trUnitSelectByQV("RocketUnit");
	if(trUnitPercentDamaged() > 0){
		vector MapMid = xsVectorSet(getMapSize()/2, 0, getMapSize()/2);
		trOverlayText("The rocket is being attacked!", 4);
		playSound("attackwarning.wav");
		for(p = 1; < cNumberNonGaiaPlayers){
			trMinimapFlare(p, 10, MapMid, true);
		}
		xsDisableSelf();
	}
}

rule RocketAttack50Warn
inactive
highFrequency
{
	trUnitSelectByQV("RocketUnit");
	if(trUnitPercentDamaged() > 49){
		vector MapMid = xsVectorSet(getMapSize()/2, 0, getMapSize()/2);
		trOverlayText("The rocket is at half health!", 4);
		playSound("attackwarning.wav");
		for(p = 1; < cNumberNonGaiaPlayers){
			trMinimapFlare(p, 10, MapMid, true);
		}
		xsDisableSelf();
		xsEnableRule("RocketAttack90Warn");
	}
}

rule RocketAttack90Warn
inactive
highFrequency
{
	trUnitSelectByQV("RocketUnit");
	if(trUnitPercentDamaged() > 89){
		vector MapMid = xsVectorSet(getMapSize()/2, 0, getMapSize()/2);
		trOverlayText("Defend the rocket - it is nearly destroyed!", 6);
		playSound("attackwarning.wav");
		for(p = 1; < cNumberNonGaiaPlayers){
			trMinimapFlare(p, 10, MapMid, true);
		}
		xsDisableSelf();
	}
}

rule PlayerDead
inactive
highFrequency
{
	for(p = 1 ; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		if(xGetBool(dPlayerData, xPlayerActive)){
			if((playerIsPlaying(p) == false) || (trPlayerUnitCountSpecific(p, "Villager Atlantean Hero") == 0)){
				trUnitSelectByQV("RocketUnit");
				if(trUnitIsOwnedBy(p)){
					for(q = 1 ; < cNumberNonGaiaPlayers){
						if((playerIsPlaying(q) == true) && (trPlayerUnitCountSpecific(q, "Villager Atlantean Hero") > 0)){
							trUnitConvert(q);
							break;
						}
						
					}
				}
				PlayersDead = PlayersDead+1;
				xSetBool(dPlayerData, xPlayerActive, false);
				trUnitSelectClear();
				trSetPlayerDefeated(p);
				trPlayerKillAllGodPowers(p);
				trPlayerKillAllUnits(p);
				trPlayerKillAllBuildings(p);
				if(kbIsPlayerHuman(p)){
					EvilLaugh();
					PlayerColouredChat(p, trStringQuestVarGet("p"+p+"name") + " is dead!");
				}
				if(PlayersDead == (cNumberNonGaiaPlayers-1)){
					xsDisableRule("RocketDead");
					trShowWinLose("All players have been murdered");
					trEndGame();
				}
			}
		}
	}
}

rule RocketDead
inactive
minInterval 2
{
	trUnitSelectByQV("RocketUnit");
	if(trUnitAlive() == false){
		if(PlayersDead != cNumberNonGaiaPlayers){
			for(p = 1; < cNumberNonGaiaPlayers){
				trSetPlayerDefeated(p);
			}
			trShowWinLose("The rocket has been destroyed");
			trEndGame();
			EvilLaugh();
			xsDisableSelf();
		}
	}
}

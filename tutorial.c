void CreateRocket(int x = 0, int z = 0){
	int temp = 0;
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
	trMutateSelected(kbGetProtoUnitID("Wonder"));
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
		else{
			//Placeholder populate the rest
			tempV = xGetVector(dCity, xLocation);
			SpawnEnemy("Fire Giant", xsVectorGetX(tempV),xsVectorGetZ(tempV)+4,true,xGetInt(dCity, xNumber), 180);
			SpawnEnemy("Fire Giant", xsVectorGetX(tempV)+2,xsVectorGetZ(tempV)+4,true,xGetInt(dCity, xNumber), 180);
			SpawnEnemy("Fire Giant", xsVectorGetX(tempV)+4,xsVectorGetZ(tempV)+4,true,xGetInt(dCity, xNumber), 180);
			SpawnEnemy("Fire Giant", xsVectorGetX(tempV)-2,xsVectorGetZ(tempV)+4,true,xGetInt(dCity, xNumber), 180);
			SpawnEnemy("Fire Giant", xsVectorGetX(tempV)-4,xsVectorGetZ(tempV)+4,true,xGetInt(dCity, xNumber), 180);
		}
	}
}

void CreateLargeGold(int num = 1){
	vector spawn = vector(0,0,0);
	vector MapMid = xsVectorSet(getMapSize()/2, 0, getMapSize()/2);
	int temp = 0;
	while(num > 0){
		trQuestVarSetFromRand("x", 0, 200);
		trQuestVarSetFromRand("z", 0, 200);
		spawn = perlinRoll(myPerlin, 1*trQuestVarGet("x"),1*trQuestVarGet("z"), 1, -8,20, false) ;
		if(distanceBetweenVectors(spawn, MapMid) > 2000){
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreateV(0, "Dwarf", spawn);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Gold Mine");
			num = num-1;
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
						DeployRelic(xsVectorGetX(spawn), xsVectorGetZ(spawn),1);
					}
					if((dist < 120) && (dist >= 80)){
						//FORCE LEVEL 2 RELICS
						DeployRelic(xsVectorGetX(spawn), xsVectorGetZ(spawn),3);
					}
					if((dist < 160) && (dist >= 120)){
						//FORCE LEVEL 3 RELICS
						DeployRelic(xsVectorGetX(spawn), xsVectorGetZ(spawn),4);
					}
					else if(dist >= 160){
						//FORCE LEVEL 4 RELICS
						DeployRelic(xsVectorGetX(spawn), xsVectorGetZ(spawn),5);
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
	CreateStartingRelics(40);
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
	trUnblockAllSounds();
	//--Test relic
	DeployRelic(getMapSize()/2+10,getMapSize()/2+10,6);
	SpawnEnemy("Militia", getMapSize()/2-10,getMapSize()/2);
	trPlayerResetBlackMapForAllPlayers();
	xsEnableRule("BlackMap");
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
					//temporary spawn enemy to test projectile
					for(a = 1; < 10){
						SpawnEnemy("Militia", 10+a, 18);
					}
					//dialog
					missileclass = xGetInt(dPlayerData, xCurrentMissile);
					xSetPointer(dProjectiles, missileclass);
					xUnitSelect(dTowers, xTowerSFXID);
					trUnitChangeProtoUnit("Spy Eye");
					xUnitSelect(dTowers, xTowerSFXID);
					trMutateSelected(kbGetProtoUnitID(xGetString(dProjectiles, xProjTowerProto)));
					xUnitSelect(dTowers, xTowerSFXID);
					trUnitSetAnimationPath(xGetString(dProjectiles, xProjTowerProtoAnimPath));
					if(xGetInt(dProjectiles, xProjAmmoCost) <= xGetInt(dPlayerData, xAmmo)){
						if(trCurrentPlayer() == p){
							trClearCounterDisplay();
							uiZoomToProto("Tower");
							//uiLookAtProto("Tower");
							characterDialog("Firing " + xGetString(dProjectiles, xProjName), "Ammo remaining - " + xGetInt(dPlayerData, xAmmo), "");
						}
					}
					else{
						//Not enough ammo
						if(trCurrentPlayer() == p){
							trClearCounterDisplay();
							characterDialog("Not enough ammo to fire " + xGetString(dProjectiles, xProjName), "Ammo - " + xGetInt(dPlayerData, xAmmo) + "/" + xGetInt(dProjectiles, xProjAmmoCost), "");
							playSound("cantdothat.wav");
						}
					}
					//If the unit is doing attack animation on a tower, garrison inside it
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
							trLetterBox(false);
							uiZoomToProto("Villager Atlantean Hero");
							uiLookAtProto("Villager Atlantean Hero");
						}
					}
				}
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
			xSetInt(dPlayerData, xAmmo, xGetInt(dPlayerData, xAmmo)+5*resource);
		}
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
										characterDialog("Firing " + xGetString(dProjectiles, xProjName), "Ammo remaining - " + xGetInt(dPlayerData, xAmmo), "");
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
										characterDialog("Firing " + xGetString(dProjectiles, xProjName), "Ammo remaining - " + xGetInt(dPlayerData, xAmmo), "");
									}
								}
							}
							else{
								//NO PROJ SHOOTER
								if(xGetInt(dProjectiles, xProjClass) == 3){
									//Bolter
									trUnitSelectClear();
									trUnitSelect(""+targetid);
									trTechInvokeGodPower(0, "Bolt", vector(0,0,0), vector(0,0,0));
									trUnitSelectClear();
									trUnitSelect(""+targetid);
									trDamageUnit(xGetInt(dProjectiles, xProjDamage));
								}
								if(xGetInt(dProjectiles, xProjClass) == 4){
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
								if(xGetInt(dProjectiles, xProjClass) == 6){
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
								xSetInt(dPlayerData, xAmmo, xGetInt(dPlayerData, xAmmo)-xGetInt(dProjectiles, xProjAmmoCost));
								if(trCurrentPlayer() == shotby){
									characterDialog("Firing " + xGetString(dProjectiles, xProjName), "Ammo remaining - " + xGetInt(dPlayerData, xAmmo), "");
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
								characterDialog("Not enough ammo to fire " + xGetString(dProjectiles, xProjName), "Ammo - " + xGetInt(dPlayerData, xAmmo) + "/" + xGetInt(dProjectiles, xProjAmmoCost), "");
							}
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
		firetimelast = trTimeMS();
	}
}

rule CaptureCity
inactive
highFrequency
{
	int cityalive = 0;
	if(trTime() > citychecktime){
		citychecktime = trTime();
		NightAttack("Militia");
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
				if(unitOnTerrain(xGetInt(dCarts, xUnitID), "RiverGrassyB")){
					//Cart home
					//[THIS WILL CAUSE OOS IF TERRAIN CHANGES]
					trOverlayText("Rocket part returned!", 4);
					playSound("fanfare.wav");
					CartsCaptured = CartsCaptured+1;
					trCounterAbort("rocketparts");
					trCounterAddTime("rocketparts", -100, -20000, "Rocket Parts: " + CartsCaptured + "/" + CitiesToMake, -1);
					xUnitSelect(dCarts, xUnitID);
					trUnitChangeProtoUnit("Osiris Box Glow");
					xUnitSelect(dCarts, xUnitID);
					trUnitSetAnimationPath("0,1,0,0,0,0");
					xFreeDatabaseBlock(dCarts);
				}
			}
		}
	}
}

rule RocketAssembled
inactive
highFrequency
{
	if(CartsCaptured == CitiesToMake){
		trCounterAbort("rocketparts");
		trOverlayText("Rocket assembled!", 4);
		xsDisableSelf();
	}
}

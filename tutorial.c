int SpawnEnemy(string pname="", int x = 0, int z = 0, bool stationary = false, int cityid = 0){
	int temp = trGetNextUnitScenarioNameNumber();
	UnitCreate(cNumberNonGaiaPlayers, pname, x,z,0);
	int index = xAddDatabaseBlock(dEnemies, true);
	xSetInt(dEnemies, xUnitID, temp);
	xSetBool(dEnemies, xStationary, stationary);
	xSetInt(dEnemies, xCityGuard, cityid);
	xUnitSelect(dEnemies, xUnitID);
	spyEffect(kbGetProtoUnitID("Cinematic Block"), 2, xsVectorSet(dEnemies, xSpyBurn, index), vector(1,1,1));
	return(temp);
}

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
	paintCircleHeight(getMapSize()/4,getMapSize()/4, 11, "GreekRoadA", 0);
}

void BuildCities(){
	int CitiesToMake = 5;
	int Chooser = 0;
	int temp = 0;
	int ABORT = 0;
	string poi = "";
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
					debugLog("START - " + xGetDatabaseCount(dCity) + " cities exist");
					for(b = xGetDatabaseCount(dCity); > 0){
						//Check distance to all other cities
						xDatabaseNext(dCity);
						poi = " ("+b+" to "+(xGetDatabaseCount(dCity)+1)+") ";
						trChatSend(0, "Distance" + poi + " = " + distanceBetweenVectors(spawn, xGetVector(dCity, xLocation),true));
						if(distanceBetweenVectors(spawn, xGetVector(dCity, xLocation),true) < 10000){
							Chooser = Chooser-1;
						}
					}
					Chooser = Chooser+1;
					if(Chooser == 1){
						trChatSend(0, "<color=0,1,0>Creation allowed</color>");
					}
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
		spawn = spawn/2;
		paintCircleHeight(xsVectorGetX(spawn),xsVectorGetZ(spawn), 11, "OlympusTile", -2);
		trPaintTerrain(xsVectorGetX(spawn),xsVectorGetZ(spawn),xsVectorGetX(spawn),xsVectorGetZ(spawn),getTerrainType("CityTileWaterPool"),getTerrainSubType("CityTileWaterPool"));
		spawn = spawn*2;
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(cNumberNonGaiaPlayers, "Dwarf",xsVectorGetX(spawn),xsVectorGetZ(spawn));
		xSetInt(dCity, xCityFlagID, temp);
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
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(0, "Dwarf",xsVectorGetX(spawn)+2,xsVectorGetZ(spawn)+2, 0);
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeProtoUnit("Revealer");
	}
}

void SetupCities(){
	float currentcheck = 0.0;
	float nextcheck = 0.0;
	int rank = 0;
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
			SpawnEnemy("Militia", xsVectorGetX(tempV)+6,xsVectorGetZ(tempV)-6,true,1);
			SpawnEnemy("Militia", xsVectorGetX(tempV)+6,xsVectorGetZ(tempV)+6,true,1);
			SpawnEnemy("Militia", xsVectorGetX(tempV)-6,xsVectorGetZ(tempV)+6,true,1);
			SpawnEnemy("Militia", xsVectorGetX(tempV)-6,xsVectorGetZ(tempV)-6,true,1);
			break;
		}
	}
}

rule WorldCreate
highFrequency
inactive
{
	int temp = 0;
	xsDisableSelf();
	xsEnableRule("DeployPlayers");
	int myPerlin = generatePerlinNoise(getMapSize()/2, 10);
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
	//DeployRelic(4,4);
	smooth(4);
	trPaintTerrain(getMapSize()/4-1,getMapSize()/4-1,getMapSize()/4+1,getMapSize()/4+1,2,13);
	paintTrees2("ForestFloorOak", "Oak Tree");
	xsEnableRule("BeginDay");
	NextDay = trTime();
	trUnblockAllSounds();
	vector spawn = vector(0,0,0);
	//---
	SetupCities();
	refreshPassability();
	//perlinRoll(myPerlin, 30,30, 1, -7,20, true) ;
	trSetFogAndBlackmap(true, true);
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
						}
					}
				}
			}
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
								xSetInt(dPlayerData, xAmmo, xGetInt(dPlayerData, xAmmo)-xGetInt(dProjectiles, xProjAmmoCost));
								if(trCurrentPlayer() == shotby){
									characterDialog("Firing " + xGetString(dProjectiles, xProjName), "Ammo remaining - " + xGetInt(dPlayerData, xAmmo), "");
								}
							}
							//[SOUND LOS]
							xUnitSelect(dTowers, xUnitID);
							if(trUnitVisToPlayer()){
								playSound(""+xGetString(dProjectiles, xProjSound));
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

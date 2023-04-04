int SpawnEnemy(string pname="", int x = 0, int z = 0, bool stationary = false){
	int temp = trGetNextUnitScenarioNameNumber();
	UnitCreate(cNumberNonGaiaPlayers, "Militia", 25,10,0);
	xAddDatabaseBlock(dEnemies, true);
	xSetInt(dEnemies, xUnitID, temp);
	xSetBool(dEnemies, xStationary, stationary);
	return(temp);
}

rule PaintTerrain
highFrequency
inactive
{
	xsDisableSelf();
	int temp = 0;
	temp = trGetNextUnitScenarioNameNumber();
	UnitCreate(0, "Tower", 10, 10);
	xAddDatabaseBlock(dTowers, true);
	xSetInt(dTowers, xUnitID, temp);
	xSetVector(dTowers, xTowerPos, kbGetBlockPosition(""+temp));
	xSetInt(dTowers, xOwner, 0);
	temp = trGetNextUnitScenarioNameNumber();
	UnitCreate(1, "Hero Norse", 10, 10);
	xSetPointer(dPlayerData, 1);
	xSetInt(dPlayerData, xUnitID, temp);
	xsEnableRule("ConvertContained");
	int myPerlin = generatePerlinNoise(100, 5);
	float height = 0;
	for(x=0; <= 100) {
		for(y=0; <= 100) {
			height = getPerlinNoise(myPerlin, x, y) * 4.0; // you may need to tweak this modifier
			trChangeTerrainHeight(x, y, x, y, height, false);
		}
	}
	smooth(10);
}

rule ConvertContained
highFrequency
inactive
{
	int temp = 0;
	for(p = 1; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		xUnitSelect(dPlayerData, xUnitID);
		if(trUnitGetIsContained("Tower") == true){
			if(xGetBool(dPlayerData, xInTower) == false){
				//cycle through to get tower
				xSetVector(dPlayerData, xUnitPos, kbGetBlockPosition(""+xGetInt(dPlayerData, xUnitID)));
				for(b = xGetDatabaseCount(dTowers); > 0){
					xDatabaseNext(dTowers);
					if(xGetVector(dTowers, xTowerPos) == xGetVector(dPlayerData, xUnitPos)){
						xSetBool(dPlayerData, xInTower, true);
						xUnitSelect(dTowers, xUnitID);
						trUnitConvert(p);
						xSetInt(dTowers, xOwner, p);
						//garrison inside
						xUnitSelect(dPlayerData, xUnitID);
						trImmediateUnitGarrison(""+xGetInt(dTowers, xUnitID));
						//temporary spawn enemy to test projectile
						SpawnEnemy("Militia", 10, 18);
					}
				}
			}
		}
		else if(trUnitGetIsContained("Tower") == false){
			if(xGetBool(dPlayerData, xInTower) == true){
				for(c = xGetDatabaseCount(dTowers); > 0){
					xDatabaseNext(dTowers);
					if(xGetInt(dTowers, xOwner) == p){
						xSetBool(dPlayerData, xInTower, false);
						xUnitSelect(dTowers, xUnitID);
						trUnitConvert(0);
						xSetInt(dTowers, xOwner, 0);
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
	//cycle through all towers and find ones under player control
	for(c = xGetDatabaseCount(dTowers); > 0){
		xDatabaseNext(dTowers);
		if(xGetInt(dTowers, xOwner) > 0){
			if(trTimeMS() >= trQuestVarGet("tempshoot")){
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
						missileclass = xGetInt(dPlayerData, xMissileClass);
						xSetPointer(dProjectiles, missileclass);
						if(xGetInt(dProjectiles, xProjCount) == 1){
							FireMissile(dir, xGetPointer(dTowers), shotby);
						}
						else{
							debugLog("Multiple projs");
						}
						trQuestVarSet("tempshoot", trTimeMS()+xGetInt(dProjectiles, xProjFireRate));
					}
				}
			}
		}
	}
}

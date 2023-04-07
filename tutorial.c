int SpawnEnemy(string pname="", int x = 0, int z = 0, bool stationary = false){
	int temp = trGetNextUnitScenarioNameNumber();
	UnitCreate(cNumberNonGaiaPlayers, "Militia", x,z,0);
	xAddDatabaseBlock(dEnemies, true);
	xSetInt(dEnemies, xUnitID, temp);
	xSetBool(dEnemies, xStationary, stationary);
	return(temp);
}

void CreatePillBox(int x = 0, int z = 0, int heading = 0){
	int temp = 0;
	temp = trGetNextUnitScenarioNameNumber();
	UnitCreate(0, "Dwarf", x, z, heading);
	xAddDatabaseBlock(dTowers, true);
	xSetInt(dTowers, xUnitID, temp);
	xSetVector(dTowers, xTowerPos, kbGetBlockPosition(""+temp));
	xSetInt(dTowers, xOwner, 0);
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trUnitChangeProtoUnit("Titan Atlantean");
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trUnitChangeProtoUnit("Tower");
	trUnitSelectClear();
	trUnitSelect(""+(temp+2));
	trUnitChangeProtoUnit("Cinematic Block");
	xSetInt(dTowers, xTowerSFXID, temp+2);
}

rule PaintTerrain
highFrequency
inactive
{
	int temp = 0;
	xsDisableSelf();
	CreatePillBox(10,10);
	temp = trGetNextUnitScenarioNameNumber();
	UnitCreate(1, "Hero Norse", 10, 10);
	xSetPointer(dPlayerData, 1);
	xSetInt(dPlayerData, xUnitID, temp);
	xsEnableRule("GameTowerGarrison");
	int myPerlin = generatePerlinNoise(100, 5);
	float height = 0;
	for(x=0; <= 100) {
		for(y=0; <= 100) {
			height = getPerlinNoise(myPerlin, x, y) * 4.0; // you may need to tweak this modifier
			trChangeTerrainHeight(x, y, x, y, height, false);
		}
	}
	smooth(10);
	DeployRelic(5,5);
	DeployRelic(5,15);
}

rule GameTowerGarrison
highFrequency
inactive
{
	int temp = 0;
	int missileclass = 0;
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
								uiZoomToProto("Tower");
								//uiLookAtProto("Tower");
								characterDialog("Firing " + xGetString(dProjectiles, xProjName), "Ammo remaining - " + xGetInt(dPlayerData, xAmmo), "");
							}
						}
						else{
							//Not enough ammo
							if(trCurrentPlayer() == p){
								characterDialog("Not enough ammo to fire " + xGetString(dProjectiles, xProjName), "Ammo - " + xGetInt(dPlayerData, xAmmo) + "/" + xGetInt(dProjectiles, xProjAmmoCost), "");
								playSound("cantdothat.wav");
							}
						}
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
									xSetFloat(dOnFire, xDamagePerTick, 50.0*xGetInt(dProjectiles, xProjDamage)/xGetInt(dProjectiles, xProjFireRate));
									spyEffect(kbGetProtoUnitID("Inferno Unit Flame"), 2, xsVectorSet(dOnFire, xBurnSpyID, index), vector(1,1,1));
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
	int time = trTimeMS();
	if(time >= timelastfire){
		if(xGetDatabaseCount(dOnFire) > 0){
			for(a = xGetDatabaseCount(dOnFire); > 0){
				xDatabaseNext(dOnFire);
				xUnitSelect(dOnFire, xUnitID);
				trDamageUnit(xGetFloat(dOnFire, xDamagePerTick));
				xSetFloat(dOnFire, xTimeToBurn, xGetFloat(dOnFire, xTimeToBurn)-50);
				if(time > xGetFloat(dOnFire, xTimeToBurn)){
					xUnitSelect(dOnFire, xBurnSpyID);
					trUnitDestroy();
					xFreeDatabaseBlock(dOnFire);
				}
			}
		}
		timelastfire = timelastfire+50;
	}
}

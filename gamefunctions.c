bool rayCollision(vector start = vector(0,0,0), vector dir = vector(1,0,0), float dist = 0, float width = 0) {
	vector pos = vector(0,0,0);
	vector hitbox = vector(0,0,0);
	float current = 0;
	pos = kbGetBlockPosition(""+xGetInt(dEnemies,xUnitID),true);
	current = distanceBetweenVectors(pos, start, false);
	if (current < dist) {
		hitbox = start + dir * current;
		if (distanceBetweenVectors(pos, hitbox, true) <= width) {
			return(true);
		}
	}
	return(false);
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

rule CollisionDetection
active
highFrequency
{
	float dist = 0;
	int p = 0;
	int missileclass = 0;
	vector pos = vector(0,0,0);
	vector prev = vector(0,0,0);
	bool ProjDead = false;
	bool ProjChange = false;
	for(a = xsMin(xGetDatabaseCount(dMissiles), cNumberNonGaiaPlayers); > 0){
		ProjDead = false;
		xDatabaseNext(dMissiles);
		//Kronny SPeed = 30.0/1000 = 0.03
		p = xGetInt(dMissiles, xOwner);
		xSetPointer(dPlayerData, p);
		missileclass = xGetInt(dPlayerData, xCurrentMissile);
		xSetPointer(dProjectiles, missileclass);
		dist = 0.001*xGetFloat(dProjectiles, xProjSpeed)*(xGetInt(dMissiles, xMissilePrevTime)-xGetInt(dMissiles, xMissileStartTime));
		prev = xGetVector(dMissiles, xMissilePos)+xGetVector(dMissiles, xMissileDir)*dist;
		dist = 0.001*xGetFloat(dProjectiles, xProjSpeed)*(trTimeMS()-xGetInt(dMissiles, xMissilePrevTime))+1;
		for(b = xGetDatabaseCount(dEnemies); > 0){
			xDatabaseNext(dEnemies);
			if(rayCollision(prev, xGetVector(dMissiles, xMissileDir), dist, 1)){
				xUnitSelect(dEnemies, xUnitID);
				trDamageUnit(xGetInt(dProjectiles, xProjDamage));
				/*if(xGetInt(dProjectiles, xProjSpecial) == 0){
					trTechInvokeGodPower(0, "tremor", kbGetBlockPosition(""+xGetInt(dEnemies, xUnitID)), vector(0,0,0));
				}*/
				//Dont do the two below for multi hit projectiles
				if(xGetBool(dProjectiles, xProjPassthrough) == false){
					ProjDead = true;
					if(xGetBool(dProjectiles, xProjDeathSpecial) == true){
						ProjChange = false;
						if(xGetInt(dProjectiles, xProjSpecial) == 1){
							xUnitSelect(dEnemies, xUnitID);
							trDamageUnit(-1*xGetInt(dProjectiles, xProjDamage));
							xUnitSelect(dEnemies, xUnitID);
							trDamageUnitsInArea(cNumberNonGaiaPlayers, "All", 4, xGetInt(dProjectiles, xProjDamage));
							xUnitSelect(dMissiles, xUnitID);
							trUnitChangeProtoUnit("Meteor Impact Ground");
							xUnitSelect(dMissiles, xUnitID);
							trDamageUnitPercent(-100);
						}
						if(xGetInt(dProjectiles, xProjSpecial) == 2){
							xUnitSelect(dEnemies, xUnitID);
							if(trUnitPercentDamaged() >= 50){
								trDamageUnitPercent(100);
								xUnitSelect(dMissiles, xUnitID);
								trUnitChangeProtoUnit("Hero Birth");
								xUnitSelect(dMissiles, xUnitID);
								trUnitSetAnimationPath(xGetString(dProjectiles, xProjRelicAnimPath));
								xUnitSelect(dMissiles, xUnitID);
								trDamageUnitPercent(-100);
							}
						}
					}
					break; //if only hitting one enemy
				}
				else{
					debugLog(""+dist);
					continue;
					//[BUG, HITS ENEMY MULTIPLE TIMES]
				}
			}
		}
		//Projectile timeout
		if(trTimeMS() > xGetInt(dMissiles, xMissileStartTime)+1000){
			ProjDead = true;
			ProjChange = true;
		}
		if(ProjDead){
			if(ProjChange){
				xUnitSelect(dMissiles, xUnitID);
				trUnitChangeProtoUnit("Dust Small");
				xUnitSelect(dMissiles, xUnitID);
				trDamageUnitPercent(-100);
			}
			xFreeDatabaseBlock(dMissiles);
		}
		else{
			xSetInt(dMissiles, xMissilePrevTime, trTimeMS());
		}
	}
}

rule MissileChange
active
highFrequency
{
	int owner = 0;
	int missileclass = 0;
	for(a = xGetDatabaseCount(dIncomingMissiles); > 0){
		xDatabaseNext(dIncomingMissiles);
		owner = xGetInt(dIncomingMissiles, xOwner);
		xSetPointer(dPlayerData, owner);
		missileclass = xGetInt(dPlayerData, xCurrentMissile);
		xSetPointer(dProjectiles, missileclass);
		xUnitSelect(dIncomingMissiles, xUnitID);
		trDamageUnitPercent(-100);
		xUnitSelect(dIncomingMissiles, xUnitID);
		trSetSelectedScale(xGetFloat(dProjectiles, xProjSize),xGetFloat(dProjectiles, xProjSize),xGetFloat(dProjectiles, xProjSize));
		xUnitSelect(dIncomingMissiles, xUnitID);
		trUnitOverrideAnimation(xGetInt(dProjectiles, xProjAnim),0,false,false,-1);
		xUnitSelect(dIncomingMissiles, xUnitID);
		trUnitSetAnimationPath(xGetString(dProjectiles, xProjAnimPath));
		xUnitSelect(dIncomingMissiles, xUnitID);
		trMutateSelected(kbGetProtoUnitID(xGetString(dProjectiles, xProjProto)));
		xAddDatabaseBlock(dMissiles, true);
		xSetInt(dMissiles, xUnitID, xGetInt(dIncomingMissiles, xUnitID));
		xSetInt(dMissiles, xOwner, xGetInt(dIncomingMissiles, xOwner));
		xSetVector(dMissiles, xMissilePos, xGetVector(dIncomingMissiles, xMissilePos));
		xSetVector(dMissiles, xMissileDir, xGetVector(dIncomingMissiles, xMissileDir));
		xSetInt(dMissiles, xMissileStartTime, trTimeMS());
		xSetInt(dMissiles, xMissilePrevTime, trTimeMS());
		xSetInt(dMissiles, xMissileClass, missileclass);
	}
	xClearDatabase(dIncomingMissiles);
}

void FireMissile(vector dir = vector(0,0,0), int towerpointer = -1, int shotby = -1){
	xSetPointer(dTowers, towerpointer);
	trModifyProtounit("Tower", shotby, 5, 1);
	xAddDatabaseBlock(dIncomingMissiles, true);
	xSetInt(dIncomingMissiles, xUnitID, trGetNextUnitScenarioNameNumber());
	UnitCreate(shotby, "Dwarf", 0,0,0);
	xUnitSelect(dIncomingMissiles, xUnitID);
	trImmediateUnitGarrison(""+xGetInt(dTowers, xUnitID));
	trUnitChangeProtoUnit("Dwarf");
	xUnitSelect(dIncomingMissiles, xUnitID);
	trMutateSelected(kbGetProtoUnitID("Kronny Flying"));
	xUnitSelect(dIncomingMissiles, xUnitID);
	trSetUnitOrientation(dir, vector(0,1,0), true);
	xUnitSelect(dIncomingMissiles, xUnitID);
	trSetSelectedScale(0,-4.5,0);
	xUnitSelect(dIncomingMissiles, xUnitID);
	trDamageUnitPercent(100);
	trModifyProtounit("Tower", shotby, 5, -1);
	xSetInt(dIncomingMissiles, xOwner, shotby);
	xSetVector(dIncomingMissiles, xMissilePos, xGetVector(dTowers, xTowerPos));
	xSetVector(dIncomingMissiles, xMissileDir, dir);
}

/*
dMissiles = xInitDatabase("Missiles DB");
xUnitID = xInitAddInt(dMissiles, "missile unit id", -1);
xOwner = xInitAddInt(dMissiles, "missile owner", 0);
xMissilePos = xInitAddVector(dMissiles, "position", vector(0,0,0));
xMissileDir = xInitAddVector(dMissiles, "direction", vector(0,0,0));
xMissilePrev = xInitAddVector(dMissiles, "prev", vector(0,0,0));

dIncomingMissiles = xInitDatabase("Incoming DB");
xUnitID = xInitAddInt(dIncomingMissiles, "missile unit id", -1);
xOwner = xInitAddInt(dIncomingMissiles, "missile owner", -1);
xMissilePos = xInitAddVector(dIncomingMissiles, "position", vector(0,0,0));
xMissileDir = xInitAddVector(dIncomingMissiles, "direction", vector(0,0,0));
*/

void CreateUnitInAtlantisBox(int centrex = 0, int centrez = 0, int size = 1, int tt = 0, int ts = 0, int owner = 0, string proto = "", int heading = 0, string path = ""){
	//INPUT IN TILES
	//Create Unit
	centrex = centrex*2;
	centrez = centrez*2;
	int temp = trGetNextUnitScenarioNameNumber();
	UnitCreate(0, "Dwarf", centrex,centrez, heading);
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trUnitChangeProtoUnit(proto);
	if(path != ""){
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitSetAnimationPath(path);
	}
	
	xAddDatabaseBlock(dCityBuildings, true);
	xSetInt(dCityBuildings, xUnitID, temp);
	xSetInt(dCityBuildings, xCity, xGetInt(dCity, xNumber));
	
	centrex = centrex/2;
	centrez = centrez/2;
	if((tt != -1) && (ts != -1)){
		trPaintTerrain(centrex-size, centrez-size, centrex+size, centrez+size, tt, ts, false);
	}
	
	trPaintTerrain(centrex-size, centrez+size, centrex+size, centrez+size, 0, 75, false);
	trPaintTerrain(centrex+size, centrez-size, centrex+size, centrez+size, 0, 74, false);
	trPaintTerrain(centrex-size, centrez-size, centrex-size, centrez+size, 0, 74, false);
	trPaintTerrain(centrex-size, centrez-size, centrex+size, centrez-size, 0, 75, false);
	
	
	trPaintTerrain(centrex-size, centrez+size, centrex-size, centrez+size, 0, 83, false);
	trPaintTerrain(centrex+size, centrez+size, centrex+size, centrez+size, 0, 80, false);
	
	trPaintTerrain(centrex+size, centrez-size, centrex+size, centrez-size, 0, 81, false);
	trPaintTerrain(centrex-size, centrez-size, centrex-size, centrez-size, 0, 82, false);
	
	
	//Create Box
}

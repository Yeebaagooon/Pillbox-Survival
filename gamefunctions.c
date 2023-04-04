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

rule CollisionDetection
active
highFrequency
{
	float dist = 0;
	vector pos = vector(0,0,0);
	vector prev = vector(0,0,0);
	bool ProjDead = false;
	for(a = xsMin(xGetDatabaseCount(dMissiles), cNumberNonGaiaPlayers); > 0){
		ProjDead = false;
		xDatabaseNext(dMissiles);
		//Kronny SPeed = 30.0/1000 = 0.03
		dist = 0.03*(xGetInt(dMissiles, xMissilePrevTime)-xGetInt(dMissiles, xMissileStartTime));
		prev = xGetVector(dMissiles, xMissilePos)+xGetVector(dMissiles, xMissileDir)*dist;
		dist = 0.03*(trTimeMS()-xGetInt(dMissiles, xMissilePrevTime))+1;
		for(b = xGetDatabaseCount(dEnemies); > 0){
			xDatabaseNext(dEnemies);
			if(rayCollision(prev, xGetVector(dMissiles, xMissileDir), dist, 1)){
				xUnitSelect(dEnemies, xUnitID);
				trDamageUnitPercent(100);
				debugLog("hit");
				//DOnt do the two below for multi hit projectiles
				ProjDead = true;
				break; //if only hitting one enemy
			}
		}
		//Projectile timeout
		if(trTimeMS() > xGetInt(dMissiles, xMissileStartTime)+1000){
			ProjDead = true;
		}
		if(ProjDead){
			xUnitSelect(dMissiles, xUnitID);
			trUnitChangeProtoUnit("Dust Small");
			xUnitSelect(dMissiles, xUnitID);
			trDamageUnitPercent(-100);
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
	for(a = xGetDatabaseCount(dIncomingMissiles); > 0){
		xDatabaseNext(dIncomingMissiles);
		xUnitSelect(dIncomingMissiles, xUnitID);
		trDamageUnitPercent(-100);
		xUnitSelect(dIncomingMissiles, xUnitID);
		trSetSelectedScale(0,0,0);
		xUnitSelect(dIncomingMissiles, xUnitID);
		trUnitOverrideAnimation(2,0,false,false,-1);
		//2 is default idle
		xUnitSelect(dIncomingMissiles, xUnitID);
		trUnitOverrideAnimation(2,0,false,false,-1);
		xUnitSelect(dIncomingMissiles, xUnitID);
		trUnitSetAnimationPath("0,0,0,0,0,0");
		xUnitSelect(dIncomingMissiles, xUnitID);
		trMutateSelected(kbGetProtoUnitID("Hero Birth"));
		xAddDatabaseBlock(dMissiles, true);
		xSetInt(dMissiles, xUnitID, xGetInt(dIncomingMissiles, xUnitID));
		xSetInt(dMissiles, xOwner, xGetInt(dIncomingMissiles, xOwner));
		xSetVector(dMissiles, xMissilePos, xGetVector(dIncomingMissiles, xMissilePos));
		xSetVector(dMissiles, xMissileDir, xGetVector(dIncomingMissiles, xMissileDir));
		xSetInt(dMissiles, xMissileStartTime, trTimeMS());
		xSetInt(dMissiles, xMissilePrevTime, trTimeMS());
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

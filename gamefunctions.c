void EndChats(){
	ColouredIconChat("1,0.5,0", "icons/special e son of osiris icon 64", "<u>" + "Pillbox Survival by Yeebaagooon" + "</u>");
	if(1*trQuestVarGet("CustomContent") == 0){
		ColouredChat("1,0.5,0", "Subscribe on the steam workshop to enable custom content!");
	}
	else{
		ColouredChat("1,0.5,0", "Thank you, noble subscriber!");
	}
}

void FireMissile(vector dir = vector(0,0,0), int towerpointer = -1, int shotby = -1){
	xSetPointer(dTowers, towerpointer);
	trModifyProtounit("Tower", shotby, 5, 1);
	trModifyProtounit("Helepolis", shotby, 5, 1);
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
	trModifyProtounit("Helepolis", shotby, 5, -1);
	xSetInt(dIncomingMissiles, xOwner, shotby);
	if(xGetVector(dTowers, xTowerPos) != vector(-1,-1,-1)){
		xSetVector(dIncomingMissiles, xMissilePos, xGetVector(dTowers, xTowerPos));
	}
	else{
		xSetVector(dIncomingMissiles, xMissilePos, kbGetBlockPosition(""+xGetInt(dTowers, xUnitID)));
	}
	xSetVector(dIncomingMissiles, xMissileDir, dir);
}

/*void FireMissileNoTower(vector dir = vector(0,0,0), vector startpos = vector(0,0,0), int shotby = 0, int classoverride = 0){
	xAddDatabaseBlock(dIncomingMissiles, true);
	xSetInt(dIncomingMissiles, xUnitID, trGetNextUnitScenarioNameNumber());
	UnitCreateV(0, "Dwarf", startpos);
	xUnitSelect(dIncomingMissiles, xUnitID);
	trMutateSelected(kbGetProtoUnitID("Kronny Flying"));
	xUnitSelect(dIncomingMissiles, xUnitID);
	trSetUnitOrientation(dir, vector(0,1,0), true);
	xUnitSelect(dIncomingMissiles, xUnitID);
	trSetSelectedScale(0,-4.5,0);
	xUnitSelect(dIncomingMissiles, xUnitID);
	trDamageUnitPercent(100);
	
	xSetInt(dIncomingMissiles, xOwner, -1);
	xSetVector(dIncomingMissiles, xMissilePos, startpos);
	xSetVector(dIncomingMissiles, xMissileDir, dir);
	
	for(a = xGetDatabaseCount(dProjectiles); > 0){
		xDatabaseNext(dProjectiles);
		if(classoverride == xGetInt(dProjectiles, xProjClass)){
			classoverride = xGetPointer(dProjectiles);
			modifyProtounitAbsolute("Kronny Flying", 0, 1, xGetFloat(dProjectiles, xProjSpeed));
			break;
		}
	}
	
	xSetInt(dIncomingMissiles, xClassOverride, classoverride);
}*/

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

void MakeThisAPillbox(int temp = -1){
	int new = 0;
	new = trGetNextUnitScenarioNameNumber();
	xAddDatabaseBlock(dTowers, true);
	xSetInt(dTowers, xUnitID, temp);
	xSetVector(dTowers, xTowerPos, kbGetBlockPosition(""+temp));
	xSetInt(dTowers, xOwner, 0);
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trUnitConvert(0);
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trUnitChangeProtoUnit("Titan Atlantean");
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trUnitChangeProtoUnit("Tower");
	trUnitSelectClear();
	trUnitSelect(""+(new+1));
	trUnitChangeProtoUnit("Cinematic Block");
	xSetInt(dTowers, xTowerSFXID, new+1);
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
	vector tempV = vector(0,0,0);
	bool ProjDead = false;
	bool ProjChange = false;
	for(a = xsMin(xGetDatabaseCount(dMissiles), cNumberNonGaiaPlayers); > 0){
		ProjDead = false;
		ProjChange = true;
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
				if(xGetBool(dProjectiles, xProjPassthrough) == false){
					trDamageUnit(xGetInt(dProjectiles, xProjDamage));
				}
				else{
					trDamageUnit(xGetInt(dProjectiles, xProjDamage)*0.25);
				}
				/*if(xGetInt(dProjectiles, xProjSpecial) == 0){
					trTechInvokeGodPower(0, "tremor", kbGetBlockPosition(""+xGetInt(dEnemies, xUnitID)), vector(0,0,0));
				}*/
				//Dont do the two below for multi hit projectiles
				if(xGetBool(dProjectiles, xProjPassthrough) == false){
					ProjDead = true;
					if(xGetBool(dProjectiles, xProjDeathSpecial) == true){
						if(xGetInt(dProjectiles, xProjSpecial) == 1){
							//Grenade explosion
							xUnitSelect(dEnemies, xUnitID);
							trDamageUnit(-1*xGetInt(dProjectiles, xProjDamage));
							xUnitSelect(dEnemies, xUnitID);
							trDamageUnitsInArea(cNumberNonGaiaPlayers, "All", 4, xGetInt(dProjectiles, xProjDamage));
							xUnitSelect(dMissiles, xUnitID);
							trUnitChangeProtoUnit("Meteor Impact Ground");
							xUnitSelect(dMissiles, xUnitID);
							trDamageUnitPercent(-100);
							ProjChange = false;
							if(trUnitVisToPlayer()){
								playSound("meteorsmallhit.wav");
							}
						}
						if(xGetInt(dProjectiles, xProjSpecial) == 2){
							//JusticE bullet kill human
							if(trCountUnitsInArea(""+xGetInt(dEnemies, xUnitID), cNumberNonGaiaPlayers, "HumanSoldier", 0) > 0){
								xUnitSelect(dEnemies, xUnitID);
								if(trUnitPercentDamaged() >= 50){
									trDamageUnitsInArea(cNumberNonGaiaPlayers,"HumanSoldier",0,200);
									xUnitSelect(dEnemies, xUnitID);
									if(trUnitPercentDamaged() >= 100){
										xUnitSelect(dMissiles, xUnitID);
										trUnitChangeProtoUnit("Hero Birth");
										xUnitSelect(dMissiles, xUnitID);
										trUnitSetAnimationPath(xGetString(dProjectiles, xProjRelicAnimPath));
										xUnitSelect(dMissiles, xUnitID);
										trDamageUnitPercent(-100);
										ProjChange = false;
										if(trUnitVisToPlayer()){
											playSound("hitpointsmax.wav");
										}
									}
								}
							}
						}
						if(xGetInt(dProjectiles, xProjSpecial) == 4){
							//Taser, add to StunDB
							if(trCountUnitsInArea(""+xGetInt(dEnemies, xUnitID), cNumberNonGaiaPlayers, "HumanSoldier", 0) > 0){
								//Human check
								xAddDatabaseBlock(dStunned, true);
								xSetInt(dStunned, xUnitID, xGetInt(dEnemies, xUnitID));
								xSetFloat(dStunned, xTimeStunned, trTimeMS()+1000);
								xSetInt(dStunned, xStunMutate, kbGetUnitBaseTypeID(kbGetBlockID(""+xGetInt(dEnemies, xUnitID))));
								xSetInt(dStunned, xStunSpyID, xGetInt(dEnemies, xSpyStun));
								xUnitSelect(dEnemies, xSpyStun);
								trMutateSelected(kbGetProtoUnitID("Shockwave stun effect"));
								xUnitSelect(dMissiles, xUnitID);
								trUnitChangeProtoUnit("Lightning Sparks Ground");
								xUnitSelect(dMissiles, xUnitID);
								trDamageUnitPercent(-100);
								ProjChange = false;
							}
						}
						if(xGetInt(dProjectiles, xProjSpecial) == 5){
							//Chicken explosion
							xUnitSelect(dEnemies, xUnitID);
							trDamageUnitsInArea(cNumberNonGaiaPlayers, "All", 5, xGetInt(dProjectiles, xProjDamage));
							xUnitSelect(dMissiles, xUnitID);
							trUnitChangeProtoUnit("Scarab Blood");
							xUnitSelect(dMissiles, xUnitID);
							trDamageUnitPercent(-100);
							ProjChange = false;
							if(trUnitVisToPlayer()){
								playSound("meteorsmallhit.wav");
							}
						}
						if(xGetInt(dProjectiles, xProjSpecial) == 6){
							//Add to Acid DB
							xUnitSelect(dEnemies, xUnitID);
							if(trUnitAlive()){
								xAddDatabaseBlock(dOnFire, true);
								xSetInt(dOnFire, xUnitID, xGetInt(dEnemies, xUnitID));
								xSetFloat(dOnFire, xTimeToBurn, trTimeMS()+2000);
								xSetFloat(dOnFire, xTotalBurnDamage, 400);
								xSetFloat(dOnFire, xDamagePerTick, xGetFloat(dOnFire, xTotalBurnDamage)/xGetInt(dProjectiles, xProjFireRate));
								xUnitSelect(dEnemies, xSpyBurn);
								trMutateSelected(kbGetProtoUnitID("Acid Pool"));
								xSetInt(dOnFire, xBurnSpyID, xGetInt(dEnemies, xSpyBurn));
							}
							xUnitSelect(dMissiles, xUnitID);
							trUnitChangeProtoUnit("Lampades Blood");
							xUnitSelect(dMissiles, xUnitID);
							trDamageUnitPercent(-100);
							ProjChange = false;
							if(trUnitVisToPlayer()){
								playSound("lampadesblood.wav");
							}
						}
						if(xGetInt(dProjectiles, xProjSpecial) == 7){
							//JusticE bullet kill myth
							if(trCountUnitsInArea(""+xGetInt(dEnemies, xUnitID), cNumberNonGaiaPlayers, "MythUnit", 0) > 0){
								xUnitSelect(dEnemies, xUnitID);
								if(trUnitPercentDamaged() >= 50){
									trDamageUnitsInArea(cNumberNonGaiaPlayers,"MythUnit",0,1000);
									xUnitSelect(dEnemies, xUnitID);
									if(trUnitPercentDamaged() >= 100){
										xUnitSelect(dMissiles, xUnitID);
										trUnitChangeProtoUnit("Qilin Heal");
										xUnitSelect(dMissiles, xUnitID);
										trUnitSetAnimationPath(xGetString(dProjectiles, xProjRelicAnimPath));
										xUnitSelect(dMissiles, xUnitID);
										trDamageUnitPercent(-100);
										ProjChange = false;
										if(trUnitVisToPlayer()){
											playSound("\cinematics\a\lostsouls.mp3");
										}
									}
								}
							}
						}
						if(xGetInt(dProjectiles, xProjSpecial) == 8){
							//Rainbow explode
							xUnitSelect(dEnemies, xUnitID);
							if(trUnitPercentDamaged() > 99){
								xUnitSelect(dEnemies, xUnitID);
								trDamageUnitsInArea(cNumberNonGaiaPlayers,"All",5,100);
								xUnitSelect(dEnemies, xUnitID);
								trDamageUnitPercent(-100);
								xUnitSelect(dEnemies, xUnitID);
								trTechInvokeGodPower(0, "Tremor", kbGetBlockPosition(""+xGetInt(dEnemies, xUnitID)), vector(0,0,0));
								xUnitSelect(dEnemies, xUnitID);
								trDamageUnitPercent(100);
								xUnitSelect(dMissiles, xUnitID);
								trUnitChangeProtoUnit("Olympus Temple SFX");
								xUnitSelect(dMissiles, xUnitID);
								trUnitSetAnimationPath(xGetString(dProjectiles, xProjRelicAnimPath));
								xUnitSelect(dMissiles, xUnitID);
								trDamageUnitPercent(-100);
								ProjChange = false;
								if(trUnitVisToPlayer()){
									playSound("meteorbighit.wav");
								}
							}
						}
						if(xGetInt(dProjectiles, xProjSpecial) == 9){
							if((trCountUnitsInArea(""+xGetInt(dEnemies, xUnitID), cNumberNonGaiaPlayers, "HumanSoldier", 0) > 0) || (trCountUnitsInArea(""+xGetInt(dEnemies, xUnitID), cNumberNonGaiaPlayers, "MythUnit", 0) > 0)){
								//Dimensional
								trQuestVarSetFromRand("temp",1,90);
								xUnitSelect(dEnemies, xUnitID);
								trDamageUnitPercent(1*trQuestVarGet("temp"));
								xUnitSelect(dEnemies, xUnitID);
								trSetSelectedScale(0.5,0.5,0.5);
								xUnitSelect(dMissiles, xUnitID);
								trUnitChangeProtoUnit("Ragnorok SFX");
								xUnitSelect(dMissiles, xUnitID);
								trUnitSetAnimationPath(xGetString(dProjectiles, xProjRelicAnimPath));
								xUnitSelect(dMissiles, xUnitID);
								trDamageUnitPercent(-100);
								ProjChange = false;
								if(trUnitVisToPlayer()){
									playSound("pigout.wav");
								}
							}
						}
						if(xGetInt(dProjectiles, xProjSpecial) == 10){
							//Sniper explosion
							xUnitSelect(dEnemies, xUnitID);
							trDamageUnit(-1*xGetInt(dProjectiles, xProjDamage));
							xUnitSelect(dEnemies, xUnitID);
							trDamageUnitsInArea(cNumberNonGaiaPlayers, "All", 6, xGetInt(dProjectiles, xProjDamage));
							xUnitSelect(dMissiles, xUnitID);
							trUnitChangeProtoUnit("Implode Sphere Effect");
							xUnitSelect(dMissiles, xUnitID);
							trDamageUnitPercent(100);
							ProjChange = false;
							if(trUnitVisToPlayer()){
								playSound("meteorsmallhit.wav");
							}
						}
					}
					break; //if only hitting one enemy
					//[DO NOT PUT DEATH EFFECTS FOR PASSTHROUGH HERE, IT GOES BELOW]
				}
				else{
					if(xGetInt(dProjectiles, xProjSpecial) == 11){
						xUnitSelect(dEnemies, xUnitID);
						trTechInvokeGodPower(0, "Bolt", vector(0,0,0), vector(0,0,0));
						break;
					}
					continue;
					//[BUG, HITS ENEMY MULTIPLE TIMES]
				}
			}
		}
		//Projectile timeout
		if(trTimeMS() > xGetInt(dMissiles, xMissileStartTime)+1000){
			ProjDead = true;
			ProjChange = true;
			//THEN THE DEATH EFFECTS FOR PROJECTILES THAT PASSTHROUGH GO HERE
			if(xGetInt(dProjectiles, xProjSpecial) == 3){
				//Flammen
				xUnitSelect(dMissiles, xUnitID);
				tempV = kbGetBlockPosition(""+xGetInt(dMissiles, xUnitID));
				if(xsVectorGetY(tempV) > 4){
					xUnitSelect(dMissiles, xUnitID);
					trUnitChangeProtoUnit("Oak Tree");
					xUnitSelect(dMissiles, xUnitID);
					trTechInvokeGodPower(0, "Forest Fire", vector(0,0,0), vector(0,0,0));
					ProjChange = false;
				}
			}
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

int SpawnEnemy(string pname="", int x = 0, int z = 0, bool stationary = false, int cityid = 0, int heading = 0){
	bool aggro = true;
	if(stationary){
		aggro = false;
	}
	int temp = trGetNextUnitScenarioNameNumber();
	UnitCreate(cNumberNonGaiaPlayers, pname, x,z,heading);
	int index = xAddDatabaseBlock(dEnemies, true);
	xSetInt(dEnemies, xUnitID, temp);
	xSetBool(dEnemies, xStationary, stationary);
	xSetBool(dEnemies, xAggro, aggro);
	xSetInt(dEnemies, xCityGuard, cityid);
	xUnitSelect(dEnemies, xUnitID);
	spyEffect(kbGetProtoUnitID("Cinematic Block"), 2, xsVectorSet(dEnemies, xSpyBurn, index), vector(1,1,1));
	spyEffect(kbGetProtoUnitID("Cinematic Block"), 2, xsVectorSet(dEnemies, xSpyStun, index), vector(1,1,1));
	return(temp);
}

int NightAttack(string unit = ""){
	int attempt = 50;
	int nextUnitName = 0;
	while(attempt > 0){
		trQuestVarSetFromRand("temp", 1, xGetDatabaseCount(dLowTerrain));
		xSetPointer(dLowTerrain, 1*trQuestVarGet("temp"));
		vector spawn = xGetVector(dLowTerrain, xDeployLoc);
		nextUnitName = trGetNextUnitScenarioNameNumber();
		UnitCreateV(cNumberNonGaiaPlayers, "Victory Marker", spawn);
		trUnitSelectClear();
		trUnitSelect(""+nextUnitName);
		bool inLOS = false;
		for(p = 1; < cNumberNonGaiaPlayers){
			if(trUnitHasLOS(p) && trPlayerDefeated(p) == false){
				trUnitDestroy();
				inLOS = true;
			}
		}
		if(inLOS == false){
			//UNIT CREATED - SET TARGET
			//If cart in play go for cart
			nextUnitName = SpawnEnemy(unit, xsVectorGetX(spawn), xsVectorGetZ(spawn));
			if(xGetDatabaseCount(dCarts) > 0){
				trQuestVarSetFromRand("temp", 0, 100);
				if(1*trQuestVarGet("temp") < 70){
					trUnitSelectClear();
					trUnitSelect(""+nextUnitName);
					trUnitMoveToUnit(""+xGetInt(dCarts, xUnitID),-1,true);
				}
			}
			
			//If no carts or failed percent
			trQuestVarSetFromRand("temp", 0, cNumberNonGaiaPlayers);
			if(1*trQuestVarGet("temp") != cNumberNonGaiaPlayers){
				xSetPointer(dPlayerData, 1*trQuestVarGet("temp"));
				if(playerIsPlaying(1*trQuestVarGet("temp"))){
					trUnitSelectClear();
					trUnitSelect(""+nextUnitName);
					trUnitMoveToUnit(""+xGetInt(dPlayerData, xUnitID),-1,true);
				}
				else{
					trUnitSelectClear();
					trUnitSelect(""+nextUnitName);
					trUnitMoveToPoint(200,0,200,-1,true);
				}
			}
			if(1*trQuestVarGet("temp") == cNumberNonGaiaPlayers){
				trUnitSelectClear();
				trUnitSelect(""+nextUnitName);
				trUnitMoveToPoint(200,0,200,-1,true);
			}
			
			attempt = 0;
			return(nextUnitName);
			break;
		}
		attempt = attempt-1;
	}
}

int RocketAttack(string unit = ""){
	int attempt = 50;
	int nextUnitName = 0;
	while(attempt > 0){
		trQuestVarSetFromRand("temp", 1, xGetDatabaseCount(dLowTerrain));
		xSetPointer(dLowTerrain, 1*trQuestVarGet("temp"));
		vector spawn = xGetVector(dLowTerrain, xDeployLoc);
		nextUnitName = trGetNextUnitScenarioNameNumber();
		UnitCreateV(cNumberNonGaiaPlayers, "Victory Marker", spawn);
		trUnitSelectClear();
		trUnitSelect(""+nextUnitName);
		bool inLOS = false;
		for(p = 1; < cNumberNonGaiaPlayers){
			if(trUnitHasLOS(p) && trPlayerDefeated(p) == false){
				trUnitDestroy();
				inLOS = true;
			}
		}
		if(inLOS == false){
			//UNIT CREATED - SET TARGET
			nextUnitName = SpawnEnemy(unit, xsVectorGetX(spawn), xsVectorGetZ(spawn));
			trUnitSelectClear();
			trUnitSelect(""+nextUnitName);
			trUnitMoveToUnit(""+1*trQuestVarGet("RocketUnit"),-1,false);
			attempt = 0;
			return(nextUnitName);
			break;
		}
		attempt = attempt-1;
	}
}

int SpawnBomber(string unit = ""){
	int attempt = 50;
	int nextUnitName = 0;
	int relicname = -1;
	while(attempt > 0){
		trQuestVarSetFromRand("temp", 1, xGetDatabaseCount(dLowTerrain));
		xSetPointer(dLowTerrain, 1*trQuestVarGet("temp"));
		vector spawn = xGetVector(dLowTerrain, xDeployLoc);
		nextUnitName = trGetNextUnitScenarioNameNumber();
		UnitCreateV(cNumberNonGaiaPlayers, "Victory Marker", spawn);
		trUnitSelectClear();
		trUnitSelect(""+nextUnitName);
		bool inLOS = false;
		for(p = 1; < cNumberNonGaiaPlayers){
			if(trUnitHasLOS(p) && trPlayerDefeated(p) == false){
				trUnitDestroy();
				inLOS = true;
			}
		}
		if(inLOS == false){
			//UNIT CREATED - SET TARGET
			nextUnitName = SpawnEnemy("Hero Norse", xsVectorGetX(spawn), xsVectorGetZ(spawn));
			relicname = trGetNextUnitScenarioNameNumber();
			UnitCreate(0, "Relic", xsVectorGetX(spawn), xsVectorGetZ(spawn));
			trUnitSelectClear();
			trUnitSelect(""+relicname);
			trImmediateUnitGarrison(""+nextUnitName);
			trUnitSelectClear();
			trUnitSelect(""+relicname);
			trMutateSelected(kbGetProtoUnitID("Phoenix Egg"));
			trUnitSelectClear();
			trUnitSelect(""+nextUnitName);
			trMutateSelected(kbGetProtoUnitID(""+unit));
			trUnitSelectClear();
			trUnitSelect(""+nextUnitName);
			trUnitMoveToUnit(""+1*trQuestVarGet("RocketUnit"),-1,false);
			xAddDatabaseBlock(dBomb, true);
			xSetInt(dBomb, xUnitID, relicname);
			xSetInt(dBomb, xExplodeTime, trTimeMS()+10000000);
			attempt = 0;
			return(nextUnitName);
			break;
		}
		attempt = attempt-1;
	}
}

void CityPillbox(int c = 0){
	vector central = vector(0,0,0);
	int dist = 24;
	for(a = xGetDatabaseCount(dCity); > 0){
		xDatabaseNext(dCity);
		if(xGetInt(dCity, xNumber) == c){
			central = xGetVector(dCity, xLocation);
			//---22 is edge of white tile, 24 set to lowest
			if(iModulo(2, trTimeMS()) == 0){
				CreatePillBox(xsVectorGetX(central)+dist,xsVectorGetZ(central));
				CreatePillBox(xsVectorGetX(central),xsVectorGetZ(central)+dist);
			}
			else{
				CreatePillBox(xsVectorGetX(central)-dist,xsVectorGetZ(central));
				CreatePillBox(xsVectorGetX(central),xsVectorGetZ(central)-dist);
			}
		}
	}
}

void AddCineText(string text="", int readtime = 3000){
	trQuestVarModify("TotalStrings", "+", 1);
	trStringQuestVarSet("Text"+1*trQuestVarGet("TotalStrings"), text);
	trQuestVarSet("Text"+1*trQuestVarGet("TotalStrings")+"Time", readtime);
	trQuestVarSet("Time"+1*trQuestVarGet("TotalStrings"), 99999999);
}

void PlayCineDialogue(){
	trQuestVarSet("TotalStrings", 0);
	xsEnableRule("PlayCineText");
}

rule PlayCineText
inactive
highFrequency
{
	if(trTimeMS() > 1*trQuestVarGet("NextText")){
		trQuestVarModify("TotalStrings", "+", 1);
		characterDialog("Yeebaagooon", trStringQuestVarGet("Text"+1*trQuestVarGet("TotalStrings")), "icons/special e son of osiris icon 64");
		trQuestVarSet("NextText", trTimeMS()+1*trQuestVarGet("Text"+1*trQuestVarGet("TotalStrings")+"Time"));
		trQuestVarSet("Time"+1*trQuestVarGet("TotalStrings"), 0);
		if( 1*trQuestVarGet("Text"+1*trQuestVarGet("TotalStrings")+"Time") == 0){
			xsEnableRule("CineEnd");
			trLetterBox(false);
			characterDialog("  ");
			xsDisableSelf();
		}
	}
}

void HelpText(int p = 0){
	if(trCurrentPlayer() == p){
		trChatHistoryClear();
		playSound("gamefound.wav");
	}
	ColouredChatToPlayer(p, "1,0.5,0", "<u>BUILDING HELP LIST:</u></color>");
	ColouredChatToPlayer(p, "1,1,1", "<icon=(20)(icons\building manor icons 32)> - Garrison units inside to heal them");
	if(CartsCaptured == 0){
		ColouredChatToPlayer(p, "1,0,1", "Kill enemies in City 1");
		ColouredChatToPlayer(p, "1,0,1", "Then bring the rocket piece back to the rocket");
		ColouredChatToPlayer(p, "1,0,1", "You will then unlock new buildings");
	}
	if(CartsCaptured >= 1){
		ColouredChatToPlayer(p, "1,1,1", "<icon=(20)(icons\icon building farm)> - Villager");
	}
	if(CartsCaptured >= 2){
		ColouredChatToPlayer(p, "1,1,1", "<icon=(20)(icons\building sentry tower icon 64)> - Creates pillbox");
		ColouredChatToPlayer(p, "1,1,1", "<icon=(20)(icons\building skytemple icons 32)> - Normal function with attack");
	}
	if(CartsCaptured >= 3){
		ColouredChatToPlayer(p, "1,1,1", "<icon=(20)(icons\building guild icons 32)> - Creates free ammo");
	}
	if(CartsCaptured >= 4){
		ColouredChatToPlayer(p, "1,1,1", "<icon=(20)(icons\building palace icons 32)> - Armoured car that your citizen controls");
	}
	if(CartsCaptured >= 5){
		ColouredChatToPlayer(p, "1,1,1", "<icon=(20)(icons\icon building temple)> - Recycle relics and buy upgrades");
	}
}

rule Helper01
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 40){
		if(Helpers){
			uiMessageBox("Remember, during the day you should aim to siege cities to recapture rocket parts.");
		}
		xsDisableSelf();
	}
}

rule Helper02
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 8){
		if(Helpers){
			uiMessageBox("Hide! It's night time, expect to be attacked soon.");
		}
		xsDisableSelf();
	}
}

rule Helper03
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 15){
		if(CitiesCaptured == 0){
			if(Helpers){
				uiMessageBox("It's a new day, you really should take the first city. Enemies will keep getting stronger.");
			}
		}
		xsDisableSelf();
	}
}

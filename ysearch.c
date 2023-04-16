rule ysearch
inactive
highFrequency
{
	int id = 0;
	int unittype = 0;
	int temp = 0;
	int closest = 0;
	int closestid = 0;
	float baseCos = 0;
	float baseSin = 0;
	int index = 0;
	vector scale = vector(0,0,0);
	vector dest = vector(0,0,0);
	vector dir = vector(0,0,0);
	vector closevector = vector(0,0,0);
	vector target = vector(0,0,0);
	vector slingvector = vector(0,0,0);
	for(i = spysearch; < trGetNextUnitScenarioNameNumber()) {
		id = kbGetBlockID(""+i, true);
		unittype = kbGetUnitBaseTypeID(id);
		switch(unittype)
		{
			case kbGetProtoUnitID("Spy Eye"):
			{
				if (xGetDatabaseCount(dSpyRequests) > 0) {
					scale = xGetVector(dSpyRequests, xSpyRequestScale);
					dest = xGetVector(dSpyRequests, xSpyRequestDest);
					trUnitSelectClear();
					trUnitSelectByID(id);
					trMutateSelected(xGetInt(dSpyRequests, xSpyRequestProto));
					trSetSelectedScale(xsVectorGetX(scale),xsVectorGetY(scale),xsVectorGetZ(scale));
					trUnitOverrideAnimation(xGetInt(dSpyRequests, xSpyRequestAnim),0,true,false,-1);
					trEventFire(xGetInt(dSpyRequests, xSpyRequestEvent));
					if (aiPlanSetUserVariableInt(1*xsVectorGetX(dest),1*xsVectorGetY(dest),1*xsVectorGetZ(dest),i) == false) {
						debugLog("spy error N/A: " + 1*xsVectorGetX(dest) + "," + 1*xsVectorGetY(dest) + "," + 1*xsVectorGetZ(dest));
					}
					xFreeDatabaseBlock(dSpyRequests);
					spyreset = 0;
				} else {
					debugLog("Spy Buffer is empty");
				}
				break;
			}
			case kbGetProtoUnitID("Tower"):
			{
				trUnitSelectClear();
				trUnitSelectByID(id);
				if(trUnitIsOwnedBy(0) == false){
					if(xGetDatabaseCount(dBuildTowers) > 0){
						for(x = xGetDatabaseCount(dBuildTowers); > 0){
							xDatabaseNext(dBuildTowers);
							if(xGetInt(dBuildTowers, xUnitID) == i){
								break;
							}
						}
					}
					xAddDatabaseBlock(dBuildTowers, true);
					xSetInt(dBuildTowers, xUnitID, i);
				}
				break;
			}
			case kbGetProtoUnitID("Manor"):
			{
				xAddDatabaseBlock(dManor, true);
				xSetInt(dManor, xUnitID, i);
				xSetBool(dManor, xComplete, false);
				break;
			}
			case kbGetProtoUnitID("Dock"):
			{
				trUnitSelectClear();
				trUnitSelectByID(id);
				trUnitDestroy();
				temp = kbUnitGetOwner(id);
				HelpText(temp);
				break;
			}
		}
	}
	if (xGetDatabaseCount(dSpyRequests) > 0) {
		spyreset = spyreset + 1;
		if (spyreset >= 10) {
			debugLog("Spy reset. Failed requests: " + xGetDatabaseCount(dSpyRequests));
			xClearDatabase(dSpyRequests);
			spyreset = 0;
		}
	}
	spysearch = trGetNextUnitScenarioNameNumber();
}

rule UnblockSound
inactive
highFrequency
{
	trUnBlockAllAmbientSounds();
	trUnblockAllSounds();
	xsDisableSelf();
}

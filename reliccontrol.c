void DeployRelic(int x = 0, int z = 0){
	int old = xGetPointer(dProjectiles);
	int temp = trGetNextUnitScenarioNameNumber();
	int index = 0;
	UnitCreate(0, "Dwarf", x, z);
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trUnitChangeProtoUnit("Titan Atlantean");
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trUnitChangeProtoUnit("Relic");
	trQuestVarSetFromRand("temp", 1, 3, true);
	for(a = xGetDatabaseCount(dProjectiles); > 0){
		xDatabaseNext(dProjectiles);
		if(xGetInt(dProjectiles, xProjClass) == 1*trQuestVarGet("temp")){
			index = xGetPointer(dProjectiles);
			break;
		}
	}
	xAddDatabaseBlock(dFreeRelics, true);
	xSetInt(dFreeRelics, xUnitID, temp);
	xSetInt(dFreeRelics, xProjType, 1*trQuestVarGet("temp"));
	xSetInt(dFreeRelics, xProjPointer, index);
	xSetInt(dFreeRelics, xSFXID, temp+2);
	xSetString(dFreeRelics, xSFXProto, xGetString(dProjectiles, xProjRelicSFX));
	xSetInt(dFreeRelics, xSFXExtra, xGetInt(dProjectiles, xProjRelicSpecial));
	trUnitSelectClear();
	trUnitSelect(""+(temp+2));
	trUnitChangeProtoUnit("Spy Eye");
	trUnitSelectClear();
	trUnitSelect(""+(temp+2));
	trMutateSelected(kbGetProtoUnitID(xGetString(dProjectiles, xProjRelicSFX)));
	xSetPointer(dProjectiles, old);
	debugLog(""+xGetDatabaseCount(dFreeRelics));
	debugLog(""+xGetInt(dFreeRelics, xUnitID));
	xUnitSelect(dFreeRelics, xUnitID);
	//trUnitChangeProtoUnit("Militia");
}

rule ProcessFreeRelics
active
highFrequency
{
	int time = trTimeMS();
	int old = xGetPointer(dProjectiles);
	for(a = xGetDatabaseCount(dFreeRelics); > 0){
		xDatabaseNext(dFreeRelics);
		xUnitSelect(dFreeRelics, xUnitID);
		trUnitHighlight(1, true);
		
		if (trUnitGetIsContained("Unit")) {
			for(p=1; < cNumberNonGaiaPlayers) {
				if (trUnitIsOwnedBy(p)) {
					xSetPointer(dProjectiles, xGetInt(dFreeRelics, xProjPointer));
					if (trCurrentPlayer() == p) {
						ColouredChatToPlayer(p, "1,0.5,0", "pickup");
						trSoundPlayFN("researchcomplete.wav","1",-1,"","");
					}
					trUnitSelectClear();
					xSetPointer(dPlayerData, p);
					xSetInt(dPlayerData, xCurrentMissile, xGetInt(dProjectiles, xPointer));
					xFreeDatabaseBlock(dFreeRelics);
					xUnitSelect(dFreeRelics, xSFXID);
					trUnitChangeProtoUnit("Cinematic Block");
					xAddDatabaseBlock(dHeldRelics, true);
					xSetInt(dHeldRelics, xUnitID, xGetInt(dFreeRelics, xUnitID));
					xSetInt(dHeldRelics, xProjType, xGetInt(dFreeRelics, xProjType));
					xSetInt(dHeldRelics, xProjPointer, xGetInt(dFreeRelics, xProjPointer));
					xSetInt(dHeldRelics, xSFXID, xGetInt(dFreeRelics, xSFXID));
					xSetString(dHeldRelics, xSFXProto, xGetString(dFreeRelics, xSFXProto));
					xSetInt(dHeldRelics, xSFXExtra, xGetInt(dFreeRelics, xSFXExtra));
					break;
				}
			}
		}
		xUnitSelect(dFreeRelics, xUnitID);
		if (trUnitIsSelected()) {
			uiClearSelection();
			ColouredChat("1,0.5,0", "chat");
		}
		trUnitSelectClear();
		if(time > timelast){
			if(xGetInt(dFreeRelics, xSFXExtra) == 1){
				xSetPointer(dProjectiles, xGetInt(dFreeRelics, xProjPointer));
				xUnitSelect(dFreeRelics, xSFXID);
				trUnitChangeProtoUnit("Spy Eye");xUnitSelect(dFreeRelics, xSFXID);
				trMutateSelected(kbGetProtoUnitID(xGetString(dProjectiles, xProjRelicSFX)));
			}
		}
	}
	if(time > timelast){
		timelast = timelast+2000;
	}
	xSetPointer(dProjectiles, old);
}

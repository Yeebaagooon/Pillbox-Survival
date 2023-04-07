void RelicDetailedHelp(string coverride = ""){
	if(coverride == ""){
		coverride = "1.0,0.5,0";
	}
	ColouredChat(coverride, xGetString(dProjectiles, xProjDesc));
	ColouredChat(coverride, "Ammo Cost: " + xGetInt(dProjectiles, xProjAmmoCost));
	ColouredChat(coverride, "Fire Rate: " + xGetInt(dProjectiles, xProjFireRate));
	ColouredChat(coverride, "Damage: " + xGetInt(dProjectiles, xProjDamage));
}


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
	//Number of classes
	trQuestVarSetFromRand("temp", 4, 4, true);
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
}

rule ProcessFreeRelics
active
highFrequency
{
	int time = trTimeMS();
	int old = xGetPointer(dProjectiles);
	for(a = xGetDatabaseCount(dFreeRelics); > 0){
		xDatabaseNext(dFreeRelics);
		xSetPointer(dProjectiles, xGetInt(dFreeRelics, xProjPointer));
		xUnitSelect(dFreeRelics, xUnitID);
		if (trUnitGetIsContained("Unit")) {
			for(p=1; < cNumberNonGaiaPlayers) {
				if (trUnitIsOwnedBy(p)) {
					if (trCurrentPlayer() == p) {
						ColouredChatToPlayer(p, "1,0.5,0", "<u>" + xGetString(dProjectiles, xProjName) + " picked up!</u>");
						trSoundPlayFN("researchcomplete.wav","1",-1,"","");
						trSoundPlayFN(xGetString(dProjectiles, xProjSound),"2",-1,"","");
					}
					trUnitSelectClear();
					if(1*trQuestVarGet("P"+p+"HeardOf"+xGetInt(dProjectiles, xPointer)+"") == 0){
						RelicDetailedHelp();
					}
					trQuestVarModify("P"+p+"HeardOf"+xGetInt(dProjectiles, xPointer)+"", "+", 1);
					xSetPointer(dPlayerData, p);
					xSetInt(dPlayerData, xCurrentMissile, xGetInt(dProjectiles, xPointer));
					xUnitSelect(dFreeRelics, xSFXID);
					trUnitChangeProtoUnit("Cinematic Block");
					xAddDatabaseBlock(dHeldRelics, true);
					xSetInt(dHeldRelics, xUnitID, xGetInt(dFreeRelics, xUnitID));
					xSetInt(dHeldRelics, xProjType, xGetInt(dFreeRelics, xProjType));
					xSetInt(dHeldRelics, xProjPointer, xGetInt(dFreeRelics, xProjPointer));
					xSetInt(dHeldRelics, xSFXID, xGetInt(dFreeRelics, xSFXID));
					xSetString(dHeldRelics, xSFXProto, xGetString(dFreeRelics, xSFXProto));
					xSetInt(dHeldRelics, xSFXExtra, xGetInt(dFreeRelics, xSFXExtra));
					xSetInt(dHeldRelics, xHeldBy, p);
					xFreeDatabaseBlock(dFreeRelics);
					break;
				}
			}
		}
		xUnitSelect(dFreeRelics, xUnitID);
		if (trUnitIsSelected()) {
			uiClearSelection();
			ColouredChat("1,1,0", "<u>" + xGetString(dProjectiles, xProjName) + "</u>");
			RelicDetailedHelp("0.8,0.8,0");
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
		//every 2000ms replace the dying units
	}
	xSetPointer(dProjectiles, old);
}

rule ProcessHeldRelics
active
highFrequency
{
	int old = xGetPointer(dProjectiles);
	int dropper = 0;
	int temp = 0;
	for(a = xGetDatabaseCount(dHeldRelics); > 0){
		xDatabaseNext(dHeldRelics);
		xSetPointer(dProjectiles, xGetInt(dHeldRelics, xProjPointer));
		xUnitSelect(dHeldRelics, xUnitID);
		//If relic is dropped
		if (trUnitGetIsContained("Unit") == false) {
			dropper = xGetInt(dHeldRelics, xHeldBy);
			if (trCurrentPlayer() == dropper) {
				ColouredChatToPlayer(dropper, "1,0.5,0", xGetString(dProjectiles, xProjName) + " dropped");
				trSoundPlayFN("foot.wav","1",-1,"","");
			}
			trUnitSelectClear();
			xSetPointer(dPlayerData, dropper);
			xSetInt(dPlayerData, xCurrentMissile, DefaultMissilePointer);
			temp = trGetNextUnitScenarioNameNumber();
			xUnitSelect(dHeldRelics, xUnitID);
			trUnitChangeProtoUnit("Titan Atlantean");
			xUnitSelect(dHeldRelics, xUnitID);
			trUnitChangeProtoUnit("Relic");
			trUnitSelectClear();
			trUnitSelect(""+(temp+1));
			trUnitChangeProtoUnit("Spy Eye");
			trUnitSelectClear();
			trUnitSelect(""+(temp+1));
			trMutateSelected(kbGetProtoUnitID(xGetString(dProjectiles, xProjRelicSFX)));
			xAddDatabaseBlock(dFreeRelics, true);
			xSetInt(dFreeRelics, xUnitID, xGetInt(dHeldRelics, xUnitID));
			xSetInt(dFreeRelics, xProjType, xGetInt(dHeldRelics, xProjType));
			xSetInt(dFreeRelics, xProjPointer, xGetInt(dHeldRelics, xProjPointer));
			xSetInt(dFreeRelics, xSFXID, (temp+1));
			xSetString(dFreeRelics, xSFXProto, xGetString(dHeldRelics, xSFXProto));
			xSetInt(dFreeRelics, xSFXExtra, xGetInt(dHeldRelics, xSFXExtra));
			xFreeDatabaseBlock(dHeldRelics);
			break;
		}
	}
	xSetPointer(dProjectiles, old);
}
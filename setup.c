/*
trUnitChangeProtoUnit("Cinematic Block");
trMutateSelected(kbGetProtoUnitID("Cinematic Block"));
trUnitSelectClear();
trUnitSelect(""+a);
trUnitSelectByQV("temp");
trUnitDestroy();
trOverlayText(3, "lol", 8000);
trUIFadeToColor(0,0,0,800,100,false);
trLetterBox(true);
trSetSelectedScale(0.5,0.5,0.5);
*/

rule EventSetHandler
active
highFrequency
//THESE ONLY WORK IF FIRES FUNCTION, SO USE VOID!
{
	for(p = 1; <= cNumberNonGaiaPlayers){
		trEventSetHandler(p, "ChooseYes");
		trEventSetHandler(12+p, "ChooseNo");
	}
	trEventSetHandler(25, "CustomContent");
	trEventSetHandler(EVENT_REMOVE_CAM_TRACKS, "removeCamTracks");
	trEventSetHandler(46, "CineGo");
	xsDisableSelf();
}

rule Initialise
active
highFrequency
runImmediately
{
	characterDialog("Waiting for everyone to connect.", " ", "icons\special e son of osiris icon 64");
	trUIFadeToColor(31,28,26, 0, 10000, false);
	trFadeOutAllSounds(0.1);
	trFadeOutMusic(0.1);
	if(QuickStart == 0){
	}
	trBlockAllSounds(true);
	trArmyDispatch("0,0", "Cinematic Block", 1, 0, 0, 0, 0, false);
	for(p = 1; <= cNumberNonGaiaPlayers){
		deployLocHeading(0, p*2, "Victory Marker", p, 180);
		trSetCivAndCulture(p, 10, 3); //oranos
	}
	trSetFogAndBlackmap(false, false);
	xsDisableSelf();
}

rule START
active
highFrequency
{
	trPlayerKillAllGodPowers(0);
	for(p = 1; <= cNumberNonGaiaPlayers){
		//	trSetCivAndCulture(p, 3, 1);
		trPlayerGrantResources(p, "Food", -10000.0);
		trPlayerGrantResources(p, "Wood", -10000.0);
		trPlayerGrantResources(p, "Gold", -10000.0);
		trPlayerGrantResources(p, "Favor", -10000.0);
		trPlayerKillAllGodPowers(p);
	}
	xsDisableRule("BasicVC1");
	xsDisableRule("BasicVC2");
	//start fade to black
	//trUIFadeToColor(1,0,0,0,0,true);
	trShowImageDialog("tower icon 32x32", MapName + " by Yeebaagooon");
	gadgetUnreal("ShowImageBox-BordersTop");
	gadgetUnreal("ShowImageBox-BordersBottom");
	gadgetUnreal("ShowImageBox-BordersLeft");
	gadgetUnreal("ShowImageBox-BordersRight");
	gadgetUnreal("ShowImageBox-BordersLeftTop");
	gadgetUnreal("ShowImageBox-BordersLeftBottom");
	gadgetUnreal("ShowImageBox-BordersRightBottom");
	gadgetUnreal("ShowImageBox-BordersRightTop");
	gadgetUnreal("ShowImageBox-CloseButton");
	pause(0);
	characterDialog("Initialising map", " ", "tower icon 32x32");
	xsEnableRule("load1");
	xsDisableSelf();
	//HOTKEYS
	/*
	map("q", "game", "trackInsert(); trackAddWaypoint();trackPlay(-1,26);");
	map("w", "game", "trackInsert(); trackAddWaypoint();trackPlay(-1,27);");
	map("e", "game", "trackInsert(); trackAddWaypoint();trackPlay(-1,28);");
	*/
	%
	for(p=1; < cNumberNonGaiaPlayers) {
		code("trStringQuestVarSet(\"p"+p+"name\", \""+rmGetPlayerName(p)+"\");");
	}
	%
}

rule load1
inactive
highFrequency
{
	characterDialog("Loading map.", ""+MapVersion+"", "tower icon 32x32");
	xsEnableRule("load2");
	trBlockAllSounds(false);
	xsDisableSelf();
	while(cNumberNonGaiaPlayers>=trQuestVarGet("PlayerID")) {
		trQuestVarSet("PlayerID2", 0);
		while(cNumberNonGaiaPlayers>=trQuestVarGet("PlayerID2")) {
			trPlayerSetDiplomacy(trQuestVarGet("PlayerID"), trQuestVarGet("PlayerID2"), "Ally");
			trPlayerSetDiplomacy(trQuestVarGet("PlayerID2"), trQuestVarGet("PlayerID"), "Ally");
		trQuestVarSet("PlayerID2", trQuestVarGet("PlayerID2")+1);}
	trQuestVarSet("PlayerID", trQuestVarGet("PlayerID")+1);}
	
	for(p=1 ; < cNumberNonGaiaPlayers){
		trPlayerSetDiplomacy(0, p, "Enemy");
		trPlayerSetDiplomacy(p, 0, "Enemy");
		//HAVE TO BOTH BE ALLY FOR GARRISON
		trPlayerSetDiplomacy(cNumberNonGaiaPlayers, p, "Enemy");
		trPlayerSetDiplomacy(p, cNumberNonGaiaPlayers, "Enemy");
	}
	trPlayerSetDiplomacy(0, cNumberNonGaiaPlayers, "Enemy");
	trTechSetStatus(0, 304, 4);
	aiSet("NoAI", cNumberNonGaiaPlayers);
	Difficulty = 1*trGetWorldDifficulty();
	//Easy = 0, Mod = 1, Hard = 2, Titan = 3
}

rule load2
inactive
highFrequency
{
	characterDialog("Loading map..", ""+MapVersion+"", "tower icon 32x32");
	xsEnableRule("load3");
	xsEnableRule("Stats");
	xsDisableSelf();
}

rule load3
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 1){
		characterDialog("Loading map...", ""+MapVersion+"", "tower icon 32x32");
		for(p = 1; <= cNumberNonGaiaPlayers){
			trPlayerGrantResources(p, "Food", -10000.0);
			trPlayerGrantResources(p, "Wood", -10000.0);
			trPlayerGrantResources(p, "Gold", -10000.0);
			trPlayerGrantResources(p, "Favor", -10000.0);
			trPlayerKillAllGodPowers(p);
			//this does custom content
			//trSoundPlayFN("\Yeebaagooon\Agricultural Madness\test sound.mp3", "1", 25, "","");
		}
		xsEnableRule("load4");
		xsEnableRule("SetupChoiceUnits");
		trQuestVarSetFromRand("temp", 1,4,true);
		MapSkin = 1*trQuestVarGet("temp");
		if(MapSkin == 1){
			TreeTerrain = "ForestFloorOak";
			TreeBorderTerrain = "ForestFloorGaia";
			Terrain1 = "RiverGrassyC";
			Terrain2 = "CliffGreekB";
			Terrain3 = "GrassDirt25";
			Terrain4 = "GrassDirt50";
			Terrain5 = "GrassDirt75";
			TreeType = "Oak Tree";
			RoadTerrain = "GreekRoadA";
			//---
			Enemy0 = "Militia";
			Enemy1 = "Hoplite";
			Enemy2 = "Toxotes";
			Enemy3 = "Minotaur";
			Enemy4 = "Centaur";
			Enemy5 = "Cyclops";
			Enemy6 = "Manticore";
			Enemy7 = "Colossus";
			Enemy8 = "Medusa";
			//---
			Huntable = "Deer";
			Berry = "Berry Bush";
			//---
			City1Building = "Academy";
			City2Building = "Archery Range";
		}
		if(MapSkin == 2){
			TreeTerrain = "ForestFloorPalm";
			TreeBorderTerrain = "ForestFloorSavannah";
			Terrain1 = "SavannahB";
			Terrain2 = "DirtA";
			Terrain3 = "SandA";
			Terrain4 = "SandC";
			Terrain5 = "ShorelineAegeanC";
			TreeType = "Palm";
			RoadTerrain = "EgyptianRoadA";
			//---
			Enemy0 = "Spearman";
			Enemy1 = "Camelry";
			Enemy2 = "Chariot Archer";
			Enemy3 = "Anubite";
			Enemy4 = "Wadjet";
			Enemy5 = "Sphinx";
			Enemy6 = "Petsuchos";
			Enemy7 = "Scarab";
			Enemy8 = "Mummy";
			//---
			Huntable = "Gazelle";
			Berry = "Dust Devil";
			//---
			City1Building = "Barracks";
			City2Building = "Siege Camp";
		}
		if(MapSkin == 3){
			TreeTerrain = "ForestFloorPineSnow";
			TreeBorderTerrain = "ShorelineNorwegianC";
			Terrain1 = "ShorelineAtlanticB";
			Terrain2 = "SnowGrass25";
			Terrain3 = "SnowGrass50";
			Terrain4 = "SnowGrass75";
			Terrain5 = "GaiaCreepBorderSnow";
			TreeType = "Pine Snow";
			RoadTerrain = "NorseRoadA";
			//---
			Enemy0 = "Ulfsark";
			Enemy1 = "Huskarl";
			Enemy2 = "Throwing Axeman";
			Enemy3 = "Valkyrie";
			Enemy4 = "Troll";
			Enemy5 = "Battle Boar";
			Enemy6 = "Fenris Wolf";
			Enemy7 = "Mountain Giant";
			Enemy8 = "Fire Giant";
			//---
			Huntable = "Elk";
			Berry = "Walrus";
			//---
			City1Building = "Longhouse";
			City2Building = "Longhouse";
		}
		if(MapSkin == 4){
			TreeTerrain = "HadesCliff";
			TreeBorderTerrain = "HadesBuildable1";
			Terrain1 = "HadesBuildable2";
			Terrain2 = "HadesBuildable1";
			Terrain3 = "HadesBuildable2";
			Terrain4 = "HadesBuildable1";
			Terrain5 = "HadesBuildable2";
			TreeType = "Pine Dead";
			RoadTerrain = "Hades8";
			//---
			Enemy0 = "Minion";
			Enemy1 = "Trident Soldier";
			Enemy2 = "Archer Atlantean";
			Enemy3 = "Automaton SPC";
			Enemy4 = "Einheriar";
			Enemy5 = "Cyclops";
			Enemy6 = "Manticore";
			Enemy7 = "Behemoth";
			Enemy8 = "Lampades";
			//---
			Huntable = "Pig";
			Berry = "Skeleton";
			//---
			City1Building = "Dwarf Foundry";
			City2Building = "Dwarven Forge";
		}
		xsDisableSelf();
	}
}

rule load4
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 1){
		//fade out when loaded
		trOverlayTextColour(255, 125, 0);
		gadgetUnreal("ShowImageBox");
		trOverlayText(MapName, 8.0, 574, 28, 1000);
		trSetUnitIdleProcessing(true);
		xsDisableSelf();
		gadgetReal("ShowImageBox-BordersTop");
		gadgetReal("ShowImageBox-BordersBottom");
		gadgetReal("ShowImageBox-BordersLeft");
		gadgetReal("ShowImageBox-BordersRight");
		gadgetReal("ShowImageBox-BordersLeftTop");
		gadgetReal("ShowImageBox-BordersLeftBottom");
		gadgetReal("ShowImageBox-BordersRightBottom");
		gadgetReal("ShowImageBox-BordersRightTop");
		gadgetReal("ShowImageBox-CloseButton");
		aiSet("NoAI", cNumberNonGaiaPlayers);
		trSetUnitIdleProcessing(false);
		//startNPCDialog(1);
		if(CineChoice){
			xsEnableRule("CineJunction");
			trLetterBox(false);
			trUIFadeToColor(31,28,26,1000,1,false);
		}
		else{
			xsEnableRule("WorldCreate");
		}
		xsEnableRule("ysearch");
		//xsEnableRule("CustomContentChat");
	}
}

void CustomContent(int p = 0){
	//xsSetContextPlayer(0);
	xsDisableSelf();
	trQuestVarSet("CustomContent", 1);
}



rule CustomContentChat
inactive
highFrequency
{
	if(1*trQuestVarGet("CustomContent") == 1){
		ColouredIconChat("1,0.5,0", "icons\special e son of osiris icon 64","Custom Content enabled!");
	}
	xsDisableSelf();
}

void CineGo(int unused = 0){
	gadgetUnreal("ShowChoiceBox");
	xsEnableRule("RemoveCineTimers");
	xsEnableRule("SetupCine");
	xsDisableRule("SkipCine");
}

rule CineJunction
highFrequency
inactive
{
	DontDestroyBelow = 1*(trGetNextUnitScenarioNameNumber()-1);
	PlayerChoice(1, "Play cinematic?", "Yes", 1, "No", 2);
	xsDisableSelf();
	trSetObscuredUnits(false);
	PaintAtlantisArea(100,5,120,25,getTerrainType("OlympusTile"),getTerrainSubType("OlympusTile"));
	trPaintTerrain(90,0,130,4,getTerrainType(TreeTerrain),getTerrainSubType(TreeTerrain));
	paintTrees2(TreeTerrain, TreeType);
	int temp = trGetNextUnitScenarioNameNumber();
	UnitCreate(0, "Tower", 210,12,270);
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trSetSelectedScale(2,3,2);
	temp = trGetNextUnitScenarioNameNumber();
	UnitCreate(0, "Tower", 230,12,270);
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trSetSelectedScale(2,3,2);
	trRenderSky(true, "SkySunset");
	trUnitSelectClear();
	createCameraTrack(15000);
	trCameraCut(vector(218.800000,14.370558,104.707848), vector(0.024098,-0.088283,-0.995804), vector(0.002136,0.996095,-0.088258), vector(-0.999707,0.000000,-0.024192));
	addCameraTrackWaypoint();
	trCameraCut(vector(218.800000,14.370558,104.707848), vector(0.024098,-0.088283,-0.995804), vector(0.002136,0.996095,-0.088258), vector(-0.999707,0.000000,-0.024192));
	addCameraTrackWaypoint();
	playCameraTrack();
	//PlayerChoice(1, "Play cinematic:", "Yes", 0, "No", 0);
	//1 for play, 2 for no
	trDelayedRuleActivation("TowerUnits");
	PlayersActive = cNumberNonGaiaPlayers;
	SkipRequired = PlayersActive-1;
	if(PlayersActive == 1){
		SkipRequired = PlayersActive;
	}
	trSetCounterDisplay("</color>Votes to skip: " + 1*trQuestVarGet("SkipVotes") +"/" + SkipRequired);
	trCounterAddTime("cdcine", 13, 0, "<color={PlayerColor("+ cNumberNonGaiaPlayers +")}>Cinematic begins", 46);
	for(p=1 ; < cNumberNonGaiaPlayers){
		PlayerChoice(p, "Skip Cinematic?", "Yes", 3, "No", -1);
	}
	xsEnableRule("SkipCine");
	xsDisableSelf();
}

rule SkipCine
inactive
highFrequency
{
	if(1*trQuestVarGet("SkipVotes") >= SkipRequired){
		xsDisableSelf();
		xsDisableRule("SetupCine");
		SkipRequired = 47;
		trSetObscuredUnits(true);
		xsEnableRule("RemoveCineTimers");
		trLetterBox(true);
		trUIFadeToColor(31,28,26,1,1,true);
		trDelayedRuleActivation("WorldCreate");
		for(a = DontDestroyBelow; < trGetNextUnitScenarioNameNumber()){
			trUnitSelectClear();
			trUnitSelect(""+a);
			trUnitDestroy();
		}
	}
}

rule RemoveCineTimers
inactive
highFrequency
{
	trCounterAbort("cdcine");
	trClearCounterDisplay();
	xsDisableSelf();
	xsDisableRule("SkipCine");
}


rule TowerUnits
highFrequency
inactive
{
	FloatingUnitAnimIdle("Villager Atlantean", 210, 15, 12, 0, 1,1,1);
	FloatingUnitAnimIdle("Pharaoh Of Osiris XP", 230, 15, 12, 0, 1,1,1);
	xsDisableSelf();
}

rule SetupCine
highFrequency
inactive
{
	trLetterBox(true);
	AddCineText("You will need to defend yourself when night comes", 3500);
	AddCineText("Right click to garrison in a gaia tower", 3500);
	AddCineText("Once inside you will fire missiles at enemies by right clicking them", 5000);
	AddCineText("Different missiles are relics scattered throughout the map", 4000);
	AddCineText("Pick them up to use them, click them to find out more information", 5000);
	AddCineText("Firing missiles costs ammo, you'll need to mine gold to increase ammo", 5000);
	AddCineText("Capture cities in the day by killing all stationed guards", 5000);
	AddCineText("Then bring the rocket piece back to the rocket", 4000);
	AddCineText("You'll gain rewards as you bring more pieces back", 3500);
	AddCineText("It's best to do the cities in numerical order", 3500);
	AddCineText("If your citizen or the rocket dies - you lose", 3000);
	PlayCineDialogue();
	CreateRocket(20,20);
	int temp = trGetNextUnitScenarioNameNumber();
	trArmyDispatch("1,1", "Villager Atlantean Hero", 1, 30, 0, 30, 0, true);
	xSetPointer(dPlayerData, 1);
	xSetInt(dPlayerData, xUnitID, temp);
	CreatePillBox(40,40);
	xsDisableSelf();
	xsEnableRule("Cut1");
	xsEnableRule("Cut2");
	xsEnableRule("Cut3");
	xsEnableRule("Cut4");
	xsEnableRule("Cut5");
	xsEnableRule("Cut6");
	xsEnableRule("Cut7");
	xsEnableRule("Cut8");
	xsEnableRule("Cut9");
	xsEnableRule("Cut10");
	createCameraTrack(5000);
	trCameraCut(vector(1.659749,22.823849,55.881481), vector(0.808444,-0.390706,-0.440189), vector(0.343139,0.920515,-0.186834), vector(-0.478198,0.000001,-0.878252));
	addCameraTrackWaypoint();
	trCameraCut(vector(27.210503,22.823849,76.236473), vector(0.248363,-0.390706,-0.886377), vector(0.105416,0.920515,-0.376216), vector(-0.962914,0.000000,-0.269809));
	addCameraTrackWaypoint();
	playCameraTrack();
	playSound("\cinematics\17_in\music.mp3");
	trFadeOutMusic(10);
	playSound("\xpack\xcinematics\6_a\music.mp3");
	Helpers = true;
	for(x = 1 ; < 50){
		UnitCreateRH(0, TreeType ,x+20,x);
		UnitCreateRH(0, TreeType ,x-20,x);
	}
	for(x = 60 ; < 120){
		for(z = 60 ; < 64){
			UnitCreateRH(0, TreeType ,z,x);
			UnitCreateRH(0, TreeType ,x,z);
		}
	}
	for(x = 1 ; < 20){
		trPaintTerrain(x,x+10,x+1,x+11,getTerrainType(TreeTerrain),getTerrainSubType(TreeTerrain));
	}
	for(x = 1 ; < 20){
		trPaintTerrain(x+10,x,x+11,x+1,getTerrainType(TreeTerrain),getTerrainSubType(TreeTerrain));
	}
	trPaintTerrain(28,28,34,60,getTerrainType(TreeTerrain),getTerrainSubType(TreeTerrain));
	trPaintTerrain(28,28,60,34,getTerrainType(TreeTerrain),getTerrainSubType(TreeTerrain));
	replaceTerrainBelowHeightMin("CliffGreekB", Terrain1, 10.0);
	replaceTerrainBelowHeightMin("RiverGrassyC", Terrain2, 10.0);
	replaceTerrainBelowHeightMin("MarshF", Terrain3, 10.0);
	replaceTerrainBelowHeightMin("JungleA", Terrain4, 10.0);
	replaceTerrainBelowHeightMin("GrassB", Terrain5, 10.0);
	replaceTerrainBelowHeightMin("GrassDirt25", Terrain1, 10.0);
}

rule Cut1
inactive
highFrequency
{
	if(1*trQuestVarGet("Time1") == 0){
		xsDisableSelf();
		trArmySelect("1,1");
		trUnitMoveToPoint(40,1,40,-1,false);
		trSetLighting("Night", 3);
	}
}

rule Cut2
inactive
highFrequency
{
	if(1*trQuestVarGet("Time2") == 0){
		xsDisableSelf();
		xUnitSelect(dTowers, xUnitID);
		trUnitConvert(1);
		trArmySelect("1,1");
		trImmediateUnitGarrison(""+xGetInt(dTowers, xUnitID));
		xUnitSelect(dTowers, xUnitID);
		trUnitSetAnimationPath(TowerAnim);
	}
}

rule Cut3
inactive
highFrequency
{
	if(1*trQuestVarGet("Time3") == 0){
		xsDisableSelf();
		int temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(cNumberNonGaiaPlayers, "Militia", 42,42,0);
		xsEnableRule("Cut35");
		AddUnitToDB(dEnemies, xUnitID, temp);
	}
}

rule Cut35
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 2){
		xsDisableSelf();
		xUnitSelect(dEnemies, xUnitID);
		trTechInvokeGodPower(0, "Bolt", vector(0,0,0), vector(0,0,0));
		xUnitSelect(dEnemies, xUnitID);
		trDamageUnit(1000);
	}
}

rule Cut4
inactive
highFrequency
{
	if(1*trQuestVarGet("Time4") == 0){
		xsDisableSelf();
		xUnitSelect(dTowers, xUnitID);
		trUnitConvert(0);
		xUnitSelect(dTowers, xUnitID);
		trUnitEjectContained();
		trArmySelect("1,1");
		trUnitMoveToPoint(44,1,44,-1,false);
		WonderHP = DeployRelic(44,44,2);
		createCameraTrack(9000);
		trCameraCut(vector(27.210503,22.823849,76.236473), vector(0.248363,-0.390706,-0.886377), vector(0.105416,0.920515,-0.376216), vector(-0.962914,0.000000,-0.269809));
		addCameraTrackWaypoint();
		trCameraCut(vector(31.286432,15.863849,62.022667), vector(0.498439,-0.390706,-0.773891), vector(0.211559,0.920515,-0.328472), vector(-0.840715,0.000000,-0.541479));
		addCameraTrackWaypoint();
		playCameraTrack();
		trSetLighting("Dawn", 10);
	}
}

rule Cut5
inactive
highFrequency
{
	if(1*trQuestVarGet("Time5") == 0){
		xsDisableSelf();
		trUnitSelectClear();
		trArmySelect("1,1");
		trUnitDoWorkOnUnit(""+WonderHP);
	}
}

rule Cut6
inactive
highFrequency
{
	if(1*trQuestVarGet("Time6") == 0){
		xsDisableSelf();
		int temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(0, "Victory Marker", 48,48,0);
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeProtoUnit("Gold Mine");
		trArmySelect("1,1");
		trUnitDoWorkOnUnit(""+temp);
		trSetLighting("default", 10);
	}
}

rule Cut7
inactive
highFrequency
{
	if(1*trQuestVarGet("Time7") == 0){
		xsDisableSelf();
		unitTransform("Gold Mine", "Rocket");
		xUnitSelect(dPlayerData, xUnitID);
		trUnitMoveToPoint(44,1,44,-1,false);
		xUnitSelect(dPlayerData, xUnitID);
		trUnitChangeProtoUnit("Rocket");
		xUnitSelect(dTowers, xUnitID);
		trUnitChangeProtoUnit("Rocket");
		xUnitSelect(dFreeRelics, xUnitID);
		trUnitChangeProtoUnit("Rocket");
		xUnitSelect(dFreeRelics, xSFXID);
		trUnitChangeProtoUnit("Rocket");
		//--
		vector spawn = vector(50,2,50);
		int temp = 0;
		xAddDatabaseBlock(dCity, true);
		paintCircleHeight(xsVectorGetX(spawn),xsVectorGetZ(spawn), 11, RoadTerrain, 8);
		trPaintTerrain(xsVectorGetX(spawn),xsVectorGetZ(spawn),xsVectorGetX(spawn),xsVectorGetZ(spawn),getTerrainType("CityTileWaterPool"),getTerrainSubType("CityTileWaterPool"));
		spawn = spawn*2;
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(cNumberNonGaiaPlayers, "Dwarf",xsVectorGetX(spawn),xsVectorGetZ(spawn));
		xSetInt(dCity, xCityFlagID, temp);
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(cNumberNonGaiaPlayers, "Dwarf",xsVectorGetX(spawn),xsVectorGetZ(spawn));
		xSetInt(dCity, xCitySFXID, temp);
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
		trUnitSetAnimationPath("0,0,0,0,0,0");
		xUnitSelect(dCity, xCityFlagID);
		trSetSelectedScale(2,2,2);
		xUnitSelect(dCity, xCitySFXID);
		trUnitChangeProtoUnit("Spy Eye");
		xUnitSelect(dCity, xCitySFXID);
		trMutateSelected(kbGetProtoUnitID("Osiris Box Glow"));
		xUnitSelect(dCity, xCitySFXID);
		trUnitSetAnimationPath("0,0,1,0,0,0");
		spawn = spawn/2;
		CreateUnitInAtlantisBox(xsVectorGetX(spawn),xsVectorGetZ(spawn)-5, 3, getTerrainType("GrassDirt50"), getTerrainSubType("GrassDirt50"), 0, "Academy", 180);
		trQuestVarSet("temp1", trGetNextUnitScenarioNameNumber());
		UnitCreate(0, "Dwarf",(xsVectorGetX(spawn)+4)*2,(xsVectorGetZ(spawn)+5)*2);
		trQuestVarSet("temp2", trGetNextUnitScenarioNameNumber());
		UnitCreate(0, "Dwarf",(xsVectorGetX(spawn)-4)*2,(xsVectorGetZ(spawn)+5)*2);
		CreateUnitInAtlantisBox(xsVectorGetX(spawn)+4,xsVectorGetZ(spawn)+5, 1,-1, -1, 0, "Fountain", 0, "1,1,0,0,0,0");
		CreateUnitInAtlantisBox(xsVectorGetX(spawn)-4,xsVectorGetZ(spawn)+5, 1,-1, -1, 0, "Fountain", 0, "1,1,0,0,0,0");
		trUnitSelectByQV("temp1");
		trUnitChangeProtoUnit("Flowers");
		trUnitSelectByQV("temp2");
		trUnitChangeProtoUnit("Flowers");
		spawn = spawn*2;
		SpawnEnemy(Enemy7, xsVectorGetX(spawn),xsVectorGetZ(spawn)+4,true,1, 180);
		SpawnEnemy(Enemy0, xsVectorGetX(spawn)+6,xsVectorGetZ(spawn)-6,true,1, 0);
		SpawnEnemy(Enemy1, xsVectorGetX(spawn)+6,xsVectorGetZ(spawn)+6,true,1, 180);
		SpawnEnemy(Enemy0, xsVectorGetX(spawn)-6,xsVectorGetZ(spawn)+6,true,1, 180);
		SpawnEnemy(Enemy1, xsVectorGetX(spawn)-6,xsVectorGetZ(spawn)-6,true,1, 0);
		createCameraTrack(4000);
		trCameraCut(vector(153.227936,36.560440,103.891312), vector(-0.882865,-0.421772,-0.206536), vector(-0.410684,0.906702,-0.096075), vector(-0.227789,0.000000,0.973710));
		addCameraTrackWaypoint();
		trCameraCut(vector(132.105057,36.560440,139.265381), vector(-0.600581,-0.421772,-0.679273), vector(-0.279373,0.906702,-0.315978), vector(-0.749169,0.000000,0.662379));
		addCameraTrackWaypoint();
		playCameraTrack();
		for(a = xGetDatabaseCount(dEnemies); > 0){
			xDatabaseNext(dEnemies);
			xUnitSelect(dEnemies, xUnitID);
			trUnitHighlight(4.0, true);
		}
	}
}

rule Cut8
inactive
highFrequency
{
	if(1*trQuestVarGet("Time8") == 0){
		xsDisableSelf();
		createCameraTrack(4060);
		trCameraCut(vector(132.105057,36.560440,139.265381), vector(-0.600581,-0.421772,-0.679273), vector(-0.279373,0.906702,-0.315978), vector(-0.749169,0.000000,0.662379));
		addCameraTrackWaypoint();
		trCameraCut(vector(122.948914,20.540438,122.602219), vector(-0.722058,-0.020397,-0.691532), vector(-0.014731,0.999792,-0.014108), vector(-0.691676,0.000000,0.722208));
		addCameraTrackWaypoint();
		playCameraTrack();
	}
}

rule Cut9
inactive
highFrequency
{
	if(1*trQuestVarGet("Time9") == 0){
		xsDisableSelf();
		createCameraTrack(40000);
		trCameraCut(vector(122.948914,20.540438,122.602219), vector(-0.722058,-0.020397,-0.691532), vector(-0.014731,0.999792,-0.014108), vector(-0.691676,0.000000,0.722208));
		addCameraTrackWaypoint();
		trCameraCut(vector(122.948914,20.540438,122.602219), vector(-0.722058,-0.020397,-0.691532), vector(-0.014731,0.999792,-0.014108), vector(-0.691676,0.000000,0.722208));
		addCameraTrackWaypoint();
		playCameraTrack();
	}
}

rule Cut10
inactive
highFrequency
{
	if(1*trQuestVarGet("Time10") == 0){
		xsDisableSelf();
		createCameraTrack(5000);
		trCameraCut(vector(132.105057,36.560440,139.265381), vector(-0.600581,-0.421772,-0.679273), vector(-0.279373,0.906702,-0.315978), vector(-0.749169,0.000000,0.662379));
		addCameraTrackWaypoint();
		trCameraCut(vector(153.227936,36.560440,103.891312), vector(-0.882865,-0.421772,-0.206536), vector(-0.410684,0.906702,-0.096075), vector(-0.227789,0.000000,0.973710));
		addCameraTrackWaypoint();
		playCameraTrack();
		trUIFadeToColor(31,28,26,200,5800,true);
	}
}

rule CineEnd
inactive
highFrequency
{
	xsDisableSelf();
	trBlockAllSounds();
	trLetterBox(true);
	trCameraCut(vector(-61.896255,123.743729,-61.896255), vector(0.500000,-0.707107,0.500000), vector(0.500000,0.707107,0.500000), vector(0.707107,0.000000,-0.707107));
	xsEnableRule("WorldCreate");
	xResetDatabase(dTowers);
	xResetDatabase(dFreeRelics);
	xResetDatabase(dCity);
	xResetDatabase(dRocket);
	xSetPointer(dPlayerData, 1);
	xSetInt(dPlayerData, xAmmo, 100);
	for(a = DontDestroyBelow; < trGetNextUnitScenarioNameNumber()){
		trUnitSelectClear();
		trUnitSelect(""+a);
		trUnitDestroy();
	}
}


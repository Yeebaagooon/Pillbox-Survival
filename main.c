rmSetStatusText("",0.01);
rmSetMapSize(400,400);
rmSetSeaLevel(0);
rmSetSeaType("greek river");
rmTerrainInitialize("GrassB",5);
rmSetLightingSet("default");
rmSetGaiaCiv(cCivZeus);

int id = 0;
int r = 0;
for(i = 0; < 1000){
	id = rmCreateArea("terrainmix"+i);
	r = rmRandInt(0,4);
	if(r == 0)rmSetAreaTerrainType(id,"CliffGreekB");
	if(r == 1)rmSetAreaTerrainType(id,"RiverGrassyC");
	if(r == 2)rmSetAreaTerrainType(id,"MarshF");
	if(r == 3)rmSetAreaTerrainType(id,"JungleA");
	if(r == 4)rmSetAreaTerrainType(id,"GrassDirt25");
	rmSetAreaBaseHeight(id,5);
	rmSetAreaCoherence(id,-1);
	rmSetAreaHeightBlend(id,10);
	rmSetAreaSize(id,0.01,0.01);
	rmSetAreaSmoothDistance(id,5);
	rmBuildArea(id);
}

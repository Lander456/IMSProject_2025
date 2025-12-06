#ifndef CONFIG_H
#define CONFIG_H
#include <cstddef>

//params used for simulation
struct Config {

    /* == MAP CONFIG == */
    static constexpr double rainAddedMoisture = 0.5;
    static constexpr size_t rainInterval = 10;
    static constexpr size_t fieldFertilisingInterval = 30;
    static constexpr double fieldNitreFertilisedAmmount = 0.5;

    /* == CELLS CONFIG == */
    static constexpr double floodTreshold = 0.7;
    static constexpr double floodNitreTransferedPercentage = 0.0;
    static constexpr double floodMoistureTransferedPercentage = 0.0;
    static constexpr double passiveNitreGain = 0.1;
    static constexpr double maxSoilNitre = 2.0;
    static constexpr double maxSoilShade = 2.0;

    //dirt
    static constexpr double dirtMoisture = 0.5;     
    static constexpr double dirtMoistureDecayRate = 1.0;
    static constexpr double dirtNitre = 0.5;
    static constexpr double dirtNitreDecayRate = 0.8;

    static constexpr double dirtOnRainMoistureCaptured = 0.9;

    //gravel
    static constexpr double gravelMoisture = 0.1;
    static constexpr double gravelMoistureDecayRate = 1.0;
    static constexpr double gravelNitre = 0.3;
    static constexpr double gravelNitreDecayRate = 0.8;

    static constexpr double gravelOnRainMoistureCaptured = 0.2;

    //field
    static constexpr double fieldMoisture = 0.6;
    static constexpr double fieldMoistureDecayRate = 1.0;
    static constexpr double fieldNitre = 0.7;
    static constexpr double fieldNitreDecayRate = 0.85;

    static constexpr double fieldOnRainMoistureCaptured = 0.9;

    //water
    static constexpr int waterMoisturizationRange = 3;
    static constexpr double waterMoisturizationAmmount = 0.01; //note: water effect will overlap -> small value

    /* == VEGETATION CONFIG == */
    static constexpr double staticGrowRate = 0.5;
    static constexpr double shadeWitherFactor = 4.0;
    static constexpr double moistureWitherFactor = 10.0;
    static constexpr double nitreWitherFactor = 4.0;
    static constexpr double defaultSpreadChance = 0.2;
    
    //Acacia
    static constexpr double extraNitrateFactor = 0.2;

    static constexpr double acaciaGrowthRate     = 0.75; 
    static constexpr double acaciaNitrogenBonus  = 1.6;
    static constexpr double acaciaShadeTolerance = 0.4;
    static constexpr double acaciaShadeCreated   = 0.7;
    static constexpr double acaciaSpreadModifier = 1.8;
    static constexpr double acaciaMaxHeight      = 25.0; // 25m
    static constexpr double acaciaSpreadBiomass  = 1.0;

    static constexpr double acaciaMoistureMinTolerance = 0.2;
    static constexpr double acaciaMoistureMaxTolerance = 0.7;
    static constexpr double acaciaNitreMinTolerance    = 0.2;
    static constexpr double acaciaNitreMaxTolerance    = 2.0;
   
    //Shrub
    static constexpr double shrubGrowthRate     = 0.5;
    static constexpr double shrubNitrogenBonus  = 1.15;
    static constexpr double shrubShadeTolerance = 0.5;
    static constexpr double shrubShadeCreated   = 0.4;
    static constexpr double shrubSpreadModifier = 1.0;
    static constexpr double shrubMaxHeight      = 1.5;
    static constexpr double shrubSpreadBiomass  = 0.5;

    static constexpr double shrubMoistureMinTolerance   = 0.4;
    static constexpr double shrubMoistureMaxTolerance   = 0.8;
    static constexpr double shrubNitreMinTolerance      = 0.3;
    static constexpr double shrubNitreMaxTolerance      = 0.9;

    //Grass
    static constexpr double grassGrowthRate     = 1.0;             
    static constexpr double grassNitrogenBonus  = 1.05;
    static constexpr double grassShadeTolerance = 0.2;
    static constexpr double grassShadeCreated   = 0.1;
    static constexpr double grassSpreadModifier = 1.5;         
    static constexpr double grassMaxHeight      = 0.6;
    static constexpr double grassSpreadBiomass  = 0.0;

    static constexpr double grassMoistureMinTolerance = 0.3;
    static constexpr double grassMoistureMaxTolerance = 0.9;
    static constexpr double grassNitreMinTolerance    = 0.2;
    static constexpr double grassNitreMaxTolerance    = 0.8;

    //Trees
    static constexpr double treeGrowthRate      = 0.25;
    static constexpr double treeNitrogenBonus   = 1.1;
    static constexpr double treeShadeTolerance  = 0.8;
    static constexpr double treeShadeCreated    = 0.9;
    static constexpr double treeSpreadModifier  = 0.7;
    static constexpr double treeMaxHeight       = 20.0;
    static constexpr double treeSpreadBiomass  = 3.0;

    static constexpr double treeMoistureMinTolerance = 0.3;
    static constexpr double treeMoistureMaxTolerance = 0.7;
    static constexpr double treeNitreMinTolerance = 0.3;
    static constexpr double treeNitreMaxTolerance = 0.8;
};


#endif //CONFIG_H
#ifndef CONFIG_H
#define CONFIG_H
#include <cstddef>

//params used for simulation
struct Config {

    /* == MAP CONFIG == */
    static constexpr double rainAddedMoistureMin = 7.95; // 90mm - daily water gain 10.5mm
    static constexpr double rainAddedMoistureMax = 28.95; // 300mm - 10.5 mm = record flood - daily water gain
    static constexpr size_t rainInterval = 36;
    static constexpr size_t fieldFertilisingInterval = 182; //half a year
    static constexpr double fieldNitreFertilisedAmmount = 0.44; // 41.75 kg N/ha 
    static constexpr size_t floodDrainageSpeed = 3; //number of squares flood moves per iteration (higher for faster drainage) 
    

    /* == CELLS CONFIG == */
    static constexpr double passiveMoistureGain = 1.05; // average rainfall 31.5/3 mm (rains every 3 days)
    static constexpr double passiveNitreGain = 0.01;
    static constexpr double maxSoilShade = 2.0;
    static constexpr double maxSoilNitre = 2.0;
    static constexpr double nitrePercentageOnFlood = 0.45;
    //dirt
    static constexpr double dirtFC = 23.63; // field capacity = max % moisture cell can hold
    static constexpr double dirtMoisture = 17.93; //50% AWC (middle value of water from soil vegatation can use )
    static constexpr double dirtMoistureDecayRate = 0.9415; // stabilises default moisture on 50% AWC with current passiveMoistureGain
    static constexpr double dirtOnRainMoistureCaptured = 0.9;

    static constexpr double dirtNitre = 1.0;
    static constexpr double dirtNitreDecayRate = 0.99; //stabilises cells nitre on 1 with current passiveNitreGain

    //gravel
    static constexpr double gravelFC = 18.21; // field capacity = max % moisture cell can hold
    static constexpr double gravelMoisture = 12.745; //50% AWC (middle value of water from soil vegatation can use )
    static constexpr double gravelMoistureDecayRate = 0.9177; //stabilises default moisture on 50% AWC with current passiveMoistureGain
    static constexpr double gravelOnRainMoistureCaptured = 0.2;

    static constexpr double gravelNitre = 7.0;
    static constexpr double gravelNitreDecayRate = 0.9985715; //stabilises cells nitre on 7 with current passiveNitreGain


    //field
    static constexpr double fieldFC = 23.63; //same FC as dirt
    static constexpr double fieldMoisture = 17.93; //50% AWC (middle value of water from soil vegatation can use )
    static constexpr double fieldMoistureDecayRate = 0.9415;
    static constexpr double fieldOnRainMoistureCaptured = 0.9;

    static constexpr double fieldNitre = 0.01;
    static constexpr double fieldNitreDecayRate = 0.99;


    //water
    static constexpr int waterMoisturizationRange = 8;
    static constexpr double waterMoisturizationAmmount = 0.01; //note: water effect will overlap -> small value

    /* == VEGETATION CONFIG == */
    static constexpr double staticGrowRate = 0.001;
    static constexpr double shadeWitherFactor = 50.0;
    static constexpr double nitreWitherFactor = 100.0;
    static constexpr double defaultSpreadChance = 0.2;
    
    //Acacia
    static constexpr double acaciaExtraNitrate= 0.003;

    static constexpr double acaciaGrowthRate     = 2.0; 
    static constexpr double acaciaNitrogenBonus  = 1.6;
    static constexpr double acaciaShadeTolerance = 0.4;
    static constexpr double acaciaShadeCreated   = 0.7;
    static constexpr double acaciaSpreadModifier = 1.8;
    static constexpr double acaciaMaxHeight      = 25.0; // 25m
    static constexpr double acaciaSpreadBiomass  = 1.0;

    static constexpr double acaciaNitreMaxTolerance    = 10.0;
   
    //Shrub
    static constexpr double shrubGrowthRate     = 1.5;
    static constexpr double shrubNitrogenBonus  = 1.15;
    static constexpr double shrubShadeTolerance = 0.5;
    static constexpr double shrubShadeCreated   = 0.4;
    static constexpr double shrubSpreadModifier = 1.0;
    static constexpr double shrubMaxHeight      = 1.5;
    static constexpr double shrubSpreadBiomass  = 0.5;

    static constexpr double shrubNitreMaxTolerance      = 1.088;

    //Grass
    static constexpr double grassGrowthRate     = 4.0;             
    static constexpr double grassNitrogenBonus  = 1.05;
    static constexpr double grassShadeTolerance = 0.2;
    static constexpr double grassShadeCreated   = 0.0;
    static constexpr double grassSpreadModifier = 1.5;         
    static constexpr double grassMaxHeight      = 0.6;
    static constexpr double grassSpreadBiomass  = 0.0;

    static constexpr double grassNitreMaxTolerance    = 1.079;

    //Trees
    static constexpr double treeBaseBiomas      = 18.0;
    static constexpr double treeGrowthRate      = 0.8;
    static constexpr double treeNitrogenBonus   = 1.1;
    static constexpr double treeShadeTolerance  = 0.8;
    static constexpr double treeShadeCreated    = 0.9;
    static constexpr double treeSpreadModifier  = 0.7;
    static constexpr double treeMaxHeight       = 20.0;
    static constexpr double treeSpreadBiomass  = 3.0;

    static constexpr double treeNitreMaxTolerance = 1.1;
};


#endif //CONFIG_H
#ifndef CONFIG_H
#define CONFIG_H

//params used for simulation
struct Config {

    /* == MAP CONFIG == */
    static constexpr double rainAddedMoisture = 0.5;
    static constexpr double rainInterval = 20.0;
    static constexpr double fieldFertilisingInterval = 50.0;
    static constexpr double fieldNitreFertilisedAmmount = 0.5;

    /* == CELLS CONFIG == */
    static constexpr double floodTreshold = 0.7;
    static constexpr double floodNitreTransferedPercentage = 0.5;
    static constexpr double floodMoistureTransferedPercentage = 0.5;

    //dirt
    static constexpr double dirtMoisture = 0.5;
    static constexpr double dirtMoistureDecayRate = 0.9;
    static constexpr double dirtNitre = 1.0;
    static constexpr double dirtNitreDecayRate = 0.9;

    static constexpr double dirtOnRainMoistureCaptured = 0.9;


    //gravel
    static constexpr double gravelMoisture = 0.1;
    static constexpr double gravelMoistureDecayRate = 0.9;
    static constexpr double gravelNitre = 0.3;
    static constexpr double gravelNitreDecayRate = 0.9;

    static constexpr double gravelOnRainMoistureCaptured = 0.2;

    //field
    static constexpr double fieldMoisture = 0.6;
    static constexpr double fieldMoistureDecayRate = 0.8;
    static constexpr double fieldNitre = 0.3;
    static constexpr double fieldNitreDecayRate = 0.9;

    static constexpr double fieldOnRainMoistureCaptured = 0.9;

    //water
    static constexpr int waterMoisturizationRange = 3;
    static constexpr int waterMoisturizationAmmount = 0.1; //note: water effect will overlap -> small value

    /* == VEGETATION CONFIG == */
    static constexpr double staticGrowRate = 1.0;

};


#endif //CONFIG_H
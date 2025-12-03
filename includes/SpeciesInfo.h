//
// Created by tadeas on 2025-11-27.
//

#ifndef IMS_SPECIESINFO_H
#define IMS_SPECIESINFO_H


class SpeciesInfo {
public:
    double growthRate;
    double nitrogenBonus;
    double shadeTolerance;
    double shadeCreated;
    double spreadModifier;
    double maxHeight;

    double moistureMinTolerance;
    double moistureMaxTolerance;
    double nitreMinTolerance;
    double nitreMaxTolerance;
    double minimalSpreadBiomass;

    SpeciesInfo(const double g = 0, const double n = 0, const double sT = 1, 
        const double sC = 0,  const double s = 1, const double h = 1,
        const double mMin = 0, const double mMax = 1, const double nMin = 0, const double nMax = 1, const double bMin = 0.5
        )
        : growthRate(g), nitrogenBonus(n),shadeTolerance(sT),
        shadeCreated(sC), spreadModifier(s), maxHeight(h),
        moistureMinTolerance(mMin), moistureMaxTolerance(mMax),
        nitreMinTolerance(nMin), nitreMaxTolerance(nMax), minimalSpreadBiomass(bMin)
        {}
};


#endif //IMS_SPECIESINFO_H
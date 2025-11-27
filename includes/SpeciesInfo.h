//
// Created by tadeas on 2025-11-27.
//

#ifndef IMS_SPECIESINFO_H
#define IMS_SPECIESINFO_H


class SpeciesInfo {
public:
    double growthRate;
    double nitrogenBonus;
    double spreadModifier;

    SpeciesInfo(double g = 0, double n = 0, double s = 1)
        : growthRate(g), nitrogenBonus(n), spreadModifier(s) {};
};


#endif //IMS_SPECIESINFO_H
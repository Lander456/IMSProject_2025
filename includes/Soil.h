//
// Created by tadeas on 2025-11-27.
//

#ifndef IMS_SOIL_H
#define IMS_SOIL_H


class Soil {
private:
    double nitrate;
    double moisture;

public:

    [[nodiscard]] double getNitrate() const { return nitrate; }
    void addNitrate(const double amt) { nitrate += amt; }
    void decayNitre(const double rate) { nitrate *= rate; }

    [[nodiscard]] double getMoisture() const { return moisture; }
    void addMoisture(const double amt) { moisture += amt; }
    void decayMoisture(const double rate) { moisture *= rate; }

    Soil(const double nitrate, const double moisture) : nitrate(nitrate), moisture(moisture) {}
};


#endif //IMS_SOIL_H
//
// Created by tadeas on 2025-11-27.
//

#ifndef IMS_SOIL_H
#define IMS_SOIL_H


class Soil {
private:
    double nitrate;

public:
    Soil(double n = 1.0) : nitrate(n) {}

    double getNitrate() const { return nitrate; }
    void addNitrate(double amt) { nitrate += amt; }
    void decay(double rate) { nitrate *= rate; }
};


#endif //IMS_SOIL_H
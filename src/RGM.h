//
// Created by tadeze on 12/2/16.
//

#ifndef PROJECT4_RGM_H
#define PROJECT4_RGM_H

#include <armadillo>
#include "tools.h"
//Robust guassian model
class RGM {
 arma::mat data;
public:
    RGM(){};
    RGM(std::vector<std::vector<double> > &_data)
    {
        data =vec2mat(_data);

    }
    arma::mat vec2mat(std::vector<std::vector<double> >&vec);
    arma::vec getEigenValues(arma::mat M);
    cloudpp radiusXYZ(arma::mat covariance,arma::mat mean);
    virtual ~RGM(){};
    arma::mat covariance();
    cloudpp singleRadiusXYZ();
    std::vector<cloudpp> gmmRadiusXYZ(int k);

};


#endif //PROJECT4_RGM_H

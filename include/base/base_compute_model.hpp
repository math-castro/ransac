#pragma once

#include<vector>

/*Base class for all ComputeModels*/
template<class Model, class Measurement>
class BaseComputeModel {
    virtual Model operator()(std::vector<Measurement> measurements) = 0;
};

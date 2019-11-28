#pragma once

#include<vector>

/*Base class for all ComputeError*/
template<class Model, class Measurement>
class BaseComputeError {
    virtual double operator()(const Model& model, const Measurement& measurement) = 0;
};

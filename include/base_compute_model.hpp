#pragma once

#include<vector>

template<class Model, class Measurement>
class BaseComputeModel {
    virtual Model operator()(const std::vector<Measurement>& measurements) = 0;
};

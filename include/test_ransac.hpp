#pragma once

#include <vector>
#include <iostream>

#include "base_compute_model.hpp"

struct TestModel {};
struct TestMeasurement {};
struct TestComputeModel : public BaseComputeModel<TestModel, TestMeasurement>{
    TestModel operator()(const std::vector<TestMeasurement>& m) {
        m.size();
        std::cout << "TestComputeModel::operator()" << std::endl;
        return TestModel();
    };
};
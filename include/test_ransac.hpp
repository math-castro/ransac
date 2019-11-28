#pragma once

#include <vector>
#include <iostream>

#include "base_compute_model.hpp"
#include "base_compute_error.hpp"

struct TestModel {};
struct TestMeasurement {};
struct TestComputeModel : public BaseComputeModel<TestModel, TestMeasurement>{
    TestModel operator()(const std::vector<TestMeasurement>& m) {
        m.size();
        std::cout << "TestComputeModel::operator()" << std::endl;
        return TestModel();
    };
};
struct TestComputeError : public BaseComputeError<TestModel, TestMeasurement> {
    double operator()(const TestModel& model, const TestMeasurement& measurement) {
        std::cout << "TestComputeError::operator()" << std::endl;
        return 0;
    }
};
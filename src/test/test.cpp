#include <vector>

#include "test/test_ransac.hpp"
#include "ransac.hpp"

using namespace std;

int main() {
  ransac<TestModel, TestMeasurement, TestComputeModel, TestComputeError>(
      vector<TestMeasurement>(), 0, 0, 0);

  return EXIT_SUCCESS;
}
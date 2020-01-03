# Generic RANSAC in C++ and Image Stitching
Implementation of a generic RANSAC (Random sample consensus) in C++ and of Image Stitching (Panorama) of multiple images (mosaic stitching).

## Dependencies
- CMake
- OpenCV
- C++17

<hr>

## TO-DO

- RANSAC
  - Change RANSAC's sample for an optimized implementation
- Generic -> Specific:
  - Implement homography classes: 
    - [x] homography model,
    - [x] pair measurement,
    - [x] compute homography,
    - [x] compute error of homography
  - Implement linear classes: 
    - linear model,
    - point measurement,
    - compute line,
    - compute error from line
- Image Stitching:
  - How to match multiple images
  - Convert homographies -> cylindrical projection
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

/**
 * Optical Proximity Correction (OPC) Simulator
 * 
 * This simulator models the lithography process where a target mask pattern
 * is distorted by the optical system (Point Spread Function).
 * It then applies a basic Rule-Based or Iterative OPC correction to adjust 
 * the mask so the printed wafer image matches the target.
 */

const int GRID_SIZE = 20;
const double THRESHOLD = 0.5;

typedef std::vector<std::vector<double>> Grid;

class OPCSimulator {
public:
    Grid targetMask;
    Grid correctedMask;
    Grid waferImage;

    OPCSimulator() {
        targetMask.assign(GRID_SIZE, std::vector<double>(GRID_SIZE, 0.0));
        correctedMask.assign(GRID_SIZE, std::vector<double>(GRID_SIZE, 0.0));
        waferImage.assign(GRID_SIZE, std::vector<double>(GRID_SIZE, 0.0));
    }

    // Initialize a simple rectangular pattern
    void initializePattern() {
        for (int i = 7; i < 13; ++i) {
            for (int j = 7; j < 13; ++j) {
                targetMask[i][j] = 1.0;
            }
        }
        correctedMask = targetMask;
    }

    // Simulate the optical lithography process using a Gaussian Blur (PSF)
    void simulateLithography(const Grid& inputMask, Grid& outputImage) {
        double sigma = 1.0;
        int kernelSize = 3;
        
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                double intensity = 0.0;
                double weightSum = 0.0;

                for (int ki = -kernelSize; ki <= kernelSize; ++ki) {
                    for (int kj = -kernelSize; kj <= kernelSize; ++kj) {
                        int ni = i + ki;
                        int nj = j + kj;

                        if (ni >= 0 && ni < GRID_SIZE && nj >= 0 && nj < GRID_SIZE) {
                            double weight = std::exp(-(ki * ki + kj * kj) / (2 * sigma * sigma));
                            intensity += inputMask[ni][nj] * weight;
                            weightSum += weight;
                        }
                    }
                }
                outputImage[i][j] = (intensity / weightSum >= THRESHOLD) ? 1.0 : 0.0;
            }
        }
    }
};

int main() {
    return 0;
}
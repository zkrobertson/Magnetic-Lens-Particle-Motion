import numpy as np

if __name__ == "__main__":
    B = 20e-4
    eV = 1
    q = 1.602e-19
    mass = np.arange(1, 20, 1) * 1.67e-27

    velocity = np.sqrt(2 * q * eV / mass)
    r = mass * velocity / B / q * 10000

    print("Gyro Radius: ", r)

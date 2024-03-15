import numpy as np

if __name__ == "__main__":
    r = 3 * 2.54 / 100
    r = 0.040
    eV = 400
    q = 1.602e-19
    mass = np.arange(1, 20, 1) * 1.67e-27
    mass = 32 * 1.67e-27

    velocity = np.sqrt(2 * q * eV / mass)
    B = mass * velocity / r / q * 10000

    print("B-Field: ", B)

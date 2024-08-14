import numpy as np

if __name__ == "__main__":
    charge = [1.602e-19]
    mass = [18 * 1.67e-27]

    eV = 2400
    r = 0.06

    velocity = [np.sqrt(2 * q * eV / m) for q, m in zip(charge, mass)]

    B = [10000 * v * m / q / r for v, q, m in zip(velocity, charge, mass)]
    print(B)

    # eV = velocity**2 * mass / q / 2

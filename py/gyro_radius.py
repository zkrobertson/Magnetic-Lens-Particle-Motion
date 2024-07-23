import numpy as np

if __name__ == "__main__":
    charge = [i * 1.602e-19 for i in range(1, 3)]
    mass = [i * 1.67e-27 for i in range(1, 3)]

    eV = 1000
    B = 1700e-4

    velocity = [np.sqrt(2 * q * eV / m) for q, m in zip(charge, mass)]

    r = [v * m / q / B for v, q, m in zip(velocity, charge, mass)]

    # eV = velocity**2 * mass / q / 2

    print(f"H+: r = {r[0]}")
    print(f"He++: r = {r[1]}")

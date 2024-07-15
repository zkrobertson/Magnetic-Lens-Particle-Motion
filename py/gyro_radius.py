import numpy as np

if __name__ == "__main__":
    q = 1.602e-19
    mass = 1 * 1.67e-27
    eV = np.arange(700, 2000, 100)
    B = 1700e-4

    velocity = np.sqrt(2 * q * eV / mass)
    r = velocity * mass / q / B

    # eV = velocity**2 * mass / q / 2

    for e, r in zip(eV, r):
        print(f"For {e} eV the mean turning radius at {B*10000} gauss is {r*100} cm")

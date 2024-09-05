import numpy as np

# Must provide these two
charge = 1  # -1 for electron, 1 for ion, 2 for double ion...
mass = 18  # AMU

# Provide all but one
# One can be a numpy.ndarray
energy = np.arange(100, 2400, 100)  # eV
B = None  # Gauss
r = 0.12  # meters

if __name__ == "__main__":
    charge = charge * 1.602e-19
    mass = mass * 1.66e-27

    if B is not None:
        B = B * 1e-4

    if r is None:
        velocity = np.sqrt(2 * charge * energy / mass)
        r = velocity * mass / B / charge
    elif energy is None:
        velocity = B * r * charge / mass
        energy = 1 / 2 * mass / charge * np.power(velocity, 2)
    elif B is None:
        velocity = np.sqrt(2 * charge * energy / mass)
        B = velocity * mass / r / charge

    mass = mass * 6.022e26
    charge = charge / 1.602e-19
    B = B * 1e4

    print(f"For an particle with Mass {mass} AMU and charge {charge}")
    print(f"\tMagnetic Field: {B} Gauss")
    print(f"\tEnergy: {energy} eV")
    print(f"\tGyro Radius: {r} meters")

import ParticleSimulation as ps

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Requires Mag-Field File location, Ion energy, Time step, Ion mass, Starting Position
singleIonExample = ps.MonteCarlo(
    "/Users/kramer/Development/CEPPE/LANL/code/magfields/VectorField.fld",
    1000.0,  # eV
    1e-8,  # integrator time step [seconds]
    18,  # AMU
    [
        0.0,
        5e-3,
        0.5e-3,
    ],  # starting position is defined by the origin of the relative coordinate system the .fld file was created with
)

# Results file location
singleIonExample_ResultsFile = (
    "/Users/kramer/Development/CEPPE/LANL/code/build/single_ion_logfile.csv"
)

# Run the simulation
singleIonExample.run(singleIonExample_ResultsFile)
singleIonDF = pd.read_csv(singleIonExample_ResultsFile, names=["X", "Y", "Z"])


# Create plots with matplotlib
my_plot = plt.figure().add_subplot(projection="3d")

r = 3 * 2.54 / 100
T = 1000
t = np.linspace(0, 1000)

bottom_semi_circle_z = r * np.cos(np.pi * t / T) + 3 * 2.54 / 100
bottom_semi_circle_x = r * np.sin(np.pi * t / T)

y = np.zeros(np.shape(t))
my_plot.plot(bottom_semi_circle_z, bottom_semi_circle_x, y)

y2 = y + 0.0254
my_plot.plot(bottom_semi_circle_z, bottom_semi_circle_x, y2)


# Axis conversions for plotting... sorry its a bit complicated
my_plot.plot(singleIonDF["Z"], singleIonDF["X"], singleIonDF["Y"])
my_plot.set_xlabel("Z")
my_plot.set_ylabel("X")
my_plot.set_zlabel("Y")

my_plot.axis("equal")
plt.show()

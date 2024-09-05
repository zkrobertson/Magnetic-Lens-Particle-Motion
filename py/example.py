import ParticleSimulation as ps
import pandas as pd

mySim = ps.MonteCarlo(
    "/Users/kramer/Development/CEPPE/LANL/code/magfields/VectorField.fld",
    1000.0,
    100,
    "default",
    [1, 2, 3],
)

mySim.run("test_output.csv")


df = pd.read_csv("monte_carlo_logfile.csv")
keys = df.keys()

passed = df.loc["pass" == 1]
failed = df.loc["pass" == 0]

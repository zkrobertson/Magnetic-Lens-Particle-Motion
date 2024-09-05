import ParticleSimulation as ps
import pandas as pd

monteCarloExample = ps.MonteCarlo(
    "/Users/kramer/Development/CEPPE/LANL/code/magfields/VectorField.fld",
    1000.0,  # eV
    1e-8,  # integrator time step
    10000,  # number of iterations
    "default",  # random position function
    [1, 2, 4, 14, 16, 17, 18],  # available masses
)

monteCarloExample_ResultsFile = (
    "/Users/kramer/Development/CEPPE/LANL/code/build/monte_carlo_logfile.csv"
)

monteCarloExample.run(monteCarloExample_ResultsFile)
monteCarloDF = pd.read_csv(monteCarloExample_ResultsFile)

print(monteCarloDF.head())

passed = monteCarloDF.loc[monteCarloDF["pass?"] == 1]
failed = monteCarloDF.loc[monteCarloDF["pass?"] == 0]

print(f"Pass Efficiency = {100 * len(passed.index) / len(monteCarloDF.index)} %")

import ParticleSimulation as ps
import pandas as pd

# Requires Mag-Field File location, Ion energy, Ion mass, Starting Position
singleIonExample = ps.MonteCarlo(
    "/Users/kramer/Development/CEPPE/LANL/code/magfields/VectorField.fld",
    1000.0,  # eV
    18,  # AMU
    [
        0.0,
        5e-3,
        1e-3,
    ],  # Depends on the origin of the relative coordinate system the .fld file was created with
)

singleIonExample_ResultsFile = (
    "/Users/kramer/Development/CEPPE/LANL/code/build/single_ion_logfile.csv"
)
singleIonExample.run(singleIonExample_ResultsFile)
singleIonDF = pd.read_csv(singleIonExample_ResultsFile)

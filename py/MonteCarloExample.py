
monteCarloExample = ps.MonteCarlo(
    "/Users/kramer/Development/CEPPE/LANL/code/magfields/VectorField.fld",
    1000.0,  # eV
    100,  # number of iterations
    "default",  # random position function
    [1, 2, 3],  # available masses
)


monteCarloExample_ResultsFile = (
    "/Users/kramer/Development/CEPPE/LANL/code/build/monte_carlo_logfile.csv"
)
monteCarloExample.run(monteCarloExample_ResultsFile)
monteCarloDF = pd.read_csv(singleIonExample_ResultsFile)

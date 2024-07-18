import matplotlib.pyplot as plt
import pandas as pd

if __name__ == "__main__":
    data = pd.read_csv(
        "./../src/build/final_positions.csv", names=["Mass", "X", "Y", "Z"]
    )

    fig, ax = plt.subplots(1, 1)
    ion_mass = ax.scatter(data["Z"], data["Y"], c=data["Mass"])
    # incident_ions = plt.scatter(data["Z"], data["Y"], c=data["Mass"])
    fig.colorbar(ion_mass)
    ax.set_ylim(0, 0.010)
    ax.set_xlim(0.022, 0.1236)
    ax.set_ylabel("Location in Exit Aperature [m]")
    ax.set_xlabel("Location in Exit Aperature [m]")
    ax.set_aspect(1)

    plt.figure()
    plt.show()

    quit()

    masses = [1, 2, 4, 12, 14, 16, 18]

    plt.subplot(313)
    plt.xlim(0.02, 0.15)
    plt.title("Bottom")
    for m in masses:
        gas = data.loc[data["Mass"] == m]
        gas = gas.loc[gas["Y"] < 0.003]
        distribution = plt.hist(gas["Z"], 50)

    plt.subplot(312)
    plt.xlim(0.02, 0.15)
    plt.title("Middle")
    for m in masses:
        gas = data.loc[data["Mass"] == m]
        gas = gas.loc[gas["Y"] > 0.003]
        gas = gas.loc[gas["Y"] < 0.006]
        distribution = plt.hist(gas["Z"], 50)

    plt.subplot(311)
    plt.xlim(0.02, 0.15)
    plt.title("Top")
    for m in masses:
        gas = data.loc[data["Mass"] == m]
        gas = gas.loc[gas["Y"] > 0.006]
        distribution = plt.hist(gas["Z"], 50)

    plt.show()

import matplotlib.pyplot as plt
import pandas as pd

if __name__ == "__main__":
    data = pd.read_csv(
        "./../src/build/final_positions.csv", names=["Mass", "X", "Y", "Z"]
    )

    fig, ax = plt.subplots(1, 1)
    ion_mass = ax.scatter(data["Z"], data["Y"], c=data["Mass"])
    # incident_ions = plt.scatter(data["Z"], data["Y"], c=data["Mass"])
    ax.set_ylim(0, 0.010)
    ax.set_xlim(0.022, 0.1236)
    ax.set_ylabel("Location in Exit Aperature [m]")
    ax.set_xlabel("Location in Exit Aperature [m]")
    ax.set_title("1050 eV")
    ax.set_aspect(1)

    plt.figure()

    masses = [1, 2, 4, 14, 16, 17, 18]

    plt.xlim(0.022, 0.1236)
    plt.title("2400 eV")
    for m in masses:
        gas = data.loc[data["Mass"] == m]
        distribution = plt.hist(gas["Z"], 50)

    plt.show()

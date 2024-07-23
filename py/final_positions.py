import matplotlib.pyplot as plt
import pandas as pd

if __name__ == "__main__":
    data_1001 = pd.read_csv(
        "./../src/build/final_positions_1001eV.csv", names=["Mass", "X", "Y", "Z"]
    )
    data_1050 = pd.read_csv(
        "./../src/build/final_positions_1050eV.csv", names=["Mass", "X", "Y", "Z"]
    )

    fig, ax = plt.subplots(2, 1)
    ion_mass = ax[0].scatter(data_1001["Z"], data_1001["Y"], c=data_1001["Mass"])
    # incident_ions = plt.scatter(data["Z"], data["Y"], c=data["Mass"])
    ax[0].set_ylim(0, 0.010)
    ax[0].set_xlim(0.022, 0.1236)
    ax[0].set_ylabel("Location in Exit Aperature [m]")
    ax[0].set_xlabel("Location in Exit Aperature [m]")
    ax[0].set_title("1001 eV")
    ax[0].set_aspect(1)

    ion_mass = ax[1].scatter(data_1050["Z"], data_1050["Y"], c=data_1050["Mass"])
    # incident_ions = plt.scatter(data["Z"], data["Y"], c=data["Mass"])
    ax[1].set_ylim(0, 0.010)
    ax[1].set_xlim(0.022, 0.1236)
    ax[1].set_ylabel("Location in Exit Aperature [m]")
    ax[1].set_xlabel("Location in Exit Aperature [m]")
    ax[1].set_title("1050 eV")
    ax[1].set_aspect(1)

    plt.figure()

    masses = [1, 2, 4, 14, 16, 17, 18]

    plt.subplot(211)
    plt.xlim(0.022, 0.1236)
    plt.title("1001 eV")
    for m in masses:
        gas = data_1001.loc[data_1001["Mass"] == m]
        distribution = plt.hist(gas["Z"], 50)

    plt.subplot(212)
    plt.xlim(0.022, 0.1236)
    plt.title("1050 eV")
    for m in masses:
        gas = data_1050.loc[data_1050["Mass"] == m]
        distribution = plt.hist(gas["Z"], 50)

    plt.show()

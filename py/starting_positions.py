import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

if __name__ == "__main__":
    data = pd.read_csv(
        "./../src/build/starting_positions.csv", names=["Mass", "Y", "Z", "Collected"]
    )

    passed = data.loc[data["Collected"] == 1]
    failed = data.loc[data["Collected"] == 0]
    print("Number Passed:", np.size(passed))
    print("Number Failed:", np.size(failed))

    fig, ax = plt.subplots(1, 1)
    passed = ax.scatter(passed["Z"], passed["Y"], c=passed["Mass"])
    fig.colorbar(passed)
    ax.set_xlim(0, 0.003)
    ax.set_ylim(0, 0.01)
    ax.set_aspect(1)
    ax.set_xlabel("Location in Entrance Aperature [m]")
    ax.set_ylabel("Location in Entrance Aperature [m]")
    plt.show()

    quit()

    plt.subplot(121)
    passed_plot = plt.scatter(passed["Z"], passed["Y"], c=passed["Mass"])
    plt.colorbar(passed_plot)
    plt.ylim((0, 0.010))
    plt.xlim((0, 0.003))
    plt.title("Passed")

    plt.subplot(122)
    failed_plot = plt.scatter(failed["Z"], failed["Y"], c=failed["Mass"], cmap="grey")
    plt.colorbar(failed_plot)
    plt.ylim((0, 0.010))
    plt.xlim((0, 0.003))
    plt.title("Failed")

    plt.show()

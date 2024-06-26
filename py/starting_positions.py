import matplotlib.pyplot as plt
import pandas as pd


if __name__ == "__main__":
    data = pd.read_csv(
        "./../build/starting_positions.csv", names=["Mass", "Y", "Z", "Collected"]
    )

    passed = data.loc[data["Collected"] == 1]
    failed = data.loc[data["Collected"] == 0]

    plt.subplot(121)
    passed_plot = plt.scatter(passed["Z"], passed["Y"], c=passed["Mass"])
    plt.colorbar(passed_plot)
    plt.ylim((0, 0.025))
    plt.xlim((0, 0.025))
    plt.title("Passed")

    plt.subplot(122)
    failed_plot = plt.scatter(failed["Z"], failed["Y"], c=failed["Mass"], cmap="grey")
    plt.colorbar(failed_plot)
    plt.ylim((0, 0.025))
    plt.xlim((0, 0.025))
    plt.title("Failed")

    plt.show()

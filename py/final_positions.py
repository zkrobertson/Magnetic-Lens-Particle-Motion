import matplotlib.pyplot as plt
import pandas as pd

if __name__ == "__main__":
    data = pd.read_csv("./../build/final_positions.csv", names=["Mass", "X", "Y", "Z"])
    print(data)

    incident_ions = plt.scatter(data["Z"], data["Y"], c=data["Mass"])
    plt.colorbar(incident_ions)
    plt.ylim((0, 0.025))
    plt.xlim(0.02, 0.15)

    plt.figure()

    masses = [1, 2, 4, 12, 14, 16, 18]

    plt.subplot(313)
    plt.xlim(0.02, 0.15)
    plt.title("Bottom")
    for m in masses:
        gas = data.loc[data["Mass"] == m]
        gas = gas.loc[gas["Y"] < 0.008]
        distribution = plt.hist(gas["Z"], 50)

    plt.subplot(312)
    plt.xlim(0.02, 0.15)
    plt.title("Middle")
    for m in masses:
        gas = data.loc[data["Mass"] == m]
        gas = gas.loc[gas["Y"] > 0.008]
        gas = gas.loc[gas["Y"] < 0.016]
        distribution = plt.hist(gas["Z"], 50)

    plt.subplot(311)
    plt.xlim(0.02, 0.15)
    plt.title("Top")
    for m in masses:
        gas = data.loc[data["Mass"] == m]
        gas = gas.loc[gas["Y"] > 0.016]
        distribution = plt.hist(gas["Z"], 50)

    plt.show()

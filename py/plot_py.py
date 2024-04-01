import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

if __name__ == "__main__":
    my_plot = plt.figure().add_subplot(projection="3d")

    r = 3 * 2.54 / 100
    T = 1000
    t = np.linspace(0, 1000)

    bottom_semi_circle_z = r * np.cos(np.pi * t / T) + 3 * 2.54 / 100
    bottom_semi_circle_x = r * np.sin(np.pi * t / T) + 1.5 * 2.54 / 100

    y = np.zeros(np.shape(t))
    my_plot.plot(bottom_semi_circle_z, bottom_semi_circle_x, y)

    y2 = y + 0.0254
    my_plot.plot(bottom_semi_circle_z, bottom_semi_circle_x, y2)

    data = pd.read_csv("./../build/single_ion_path.csv", names=["X", "Y", "Z"])
    my_plot.plot(data["Z"], data["X"], data["Y"])
    my_plot.set_xlabel("Z")
    my_plot.set_ylabel("X")
    my_plot.set_zlabel("Y")

    my_plot.axis("equal")
    plt.show()

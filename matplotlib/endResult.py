from funcs import read_sim_params
import matplotlib.pyplot as plt
import configparser
import os

def read_uav_file(filepath):
    xs, ys = [], []
    with open(filepath, "r") as f:
        for line in f:
            _, x, y, _ = map(float, line.split())
            xs.append(x)
            ys.append(y)
    return xs, ys

def plot_uav_path(uav_index):
    filename = f"../UAV{uav_index}.txt"
    if not os.path.isfile(filename):
        print(f"File {filename} not found.")
        return
    xs, ys = read_uav_file(filename)
    plt.figure()
    plt.plot(xs, ys, marker='o')
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.title(f"UAV {uav_index} Path")
    plt.xlim(min(xs)-1, max(xs)+1)
    plt.ylim(min(ys)-1, max(ys)+1)
    plt.grid(True)

if __name__ == "__main__":
    N_uav = read_sim_params()
    for i in range(0, N_uav):
        plot_uav_path(i)
    plt.show()  # Opens all figures at once
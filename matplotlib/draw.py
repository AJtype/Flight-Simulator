from funcs import read_sim_params
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import configparser
import os

# --- Read UAV file ---
def read_uav_file(filepath):
    times, xs, ys, azimuths = [], [], [], []
    with open(filepath, "r") as f:
        for line in f:
            t, x, y, azi = map(float, line.split())
            times.append(t)
            xs.append(x)
            ys.append(y)
            azimuths.append(azi)
    return times, xs, ys, azimuths

# --- Create animation for a single UAV ---
def animate_uav(uav_index):
    filename = f"../UAV{uav_index}.txt"
    if not os.path.isfile(filename):
        print(f"File {filename} not found.")
        return None

    times, xs, ys, _ = read_uav_file(filename)

    fig, ax = plt.subplots()
    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.set_title(f"UAV {uav_index} Movement Over Time")
    ax.grid(True)

    line, = ax.plot([], [], marker="o")

    def update(frame):
        line.set_data(xs[:frame], ys[:frame])
        ax.set_xlim(min(xs)-1, max(xs)+1)
        ax.set_ylim(min(ys)-1, max(ys)+1)
        return line,

    ani = animation.FuncAnimation(fig, update, frames=len(xs), interval=80, repeat=False)
    return fig, ani

# --- Main loop ---
if __name__ == "__main__":
    N_uav = read_sim_params()
    animations = []

    for i in range(0, N_uav):
        result = animate_uav(i)
        if result is not None:
            animations.append(result)

    plt.show()  # opens all figures/tabs at once
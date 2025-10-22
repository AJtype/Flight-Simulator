import matplotlib.pyplot as plt
import matplotlib.animation as animation

# Read file
times, xs, ys, azimuths = [], [], [], []
# with open("../UAV/UAV0.txt", "r") as f:
with open("../UAV0.txt", "r") as f:
    for line in f:
        t, x, y, azi = map(float, line.split())
        times.append(t)
        xs.append(x)
        ys.append(y)

# Plot setup
fig, ax = plt.subplots()
ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_title("Object Movement Over Time")

line, = ax.plot([], [], marker="o")

def update(frame):
    line.set_data(xs[:frame], ys[:frame])
    ax.set_xlim(min(xs)-1, max(xs)+1)
    ax.set_ylim(min(ys)-1, max(ys)+1)
    return line,

ani = animation.FuncAnimation(fig, update, frames=len(xs), interval=80, repeat=False)
plt.show()

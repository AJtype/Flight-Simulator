import matplotlib.pyplot as plt

# Read file
xs, ys = [], []
# with open("../UAV/UAV0.txt", "r") as f:
with open("../UAV0.txt", "r") as f:
    for line in f:
        t, x, y, azi = map(float, line.split())
        xs.append(x)
        ys.append(y)

# Plot entire path instantly
plt.figure()
plt.plot(xs, ys, marker='o')  # Shows all points and path
plt.xlabel("X")
plt.ylabel("Y")
plt.title("Object Path")
plt.xlim(min(xs)-1, max(xs)+1)
plt.ylim(min(ys)-1, max(ys)+1)
plt.show()
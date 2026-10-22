import numpy as np
import matplotlib.pyplot as plt
import os
import textwrap

# ------------------- CONFIG -------------------
FIG_DIR = "figures"
FONT_SIZE = 14

os.makedirs(FIG_DIR, exist_ok=True)


def style_axes(ax):
    ax.tick_params(labelsize=0.8 * FONT_SIZE)
    ax.grid(which='major', color='grey', linewidth=1.3)
    ax.grid(which='minor', color='lightgrey', linewidth=1.0)


# ------------------- FIGURE 1: LINE AND PARABOLA -------------------
def plot_line_and_parabola():
    fig, ax = plt.subplots(figsize=(6, 6), constrained_layout=True)

    s = np.linspace(0, 1, 200)

    ax.plot(s, s, linewidth=2.5, color='red',
            label="non equilibrium, based on injection rate")

    ax.plot(s, s ** 2, linewidth=2.5, color='blue',
            label="equilibrium based on injection rate")

    ax.set_xlabel("Saturation S", fontsize=FONT_SIZE)
    ax.set_ylabel("Permeability k", fontsize=FONT_SIZE)
    ax.set_xlim(0, 1)
    ax.set_ylim(0, 1)
    ax.set_aspect('equal', adjustable='box')
    style_axes(ax)

    # Wrap long labels and put legend at top
    handles, labels = ax.get_legend_handles_labels()
    wrapped = ["\n".join(textwrap.wrap(l, 30)) for l in labels]
    ax.legend(handles, wrapped, loc='upper center',
              bbox_to_anchor=(0.5, 1.22), ncol=2,
              fontsize=FONT_SIZE - 4, frameon=True)

    plt.savefig(f"{FIG_DIR}/line_and_parabola.png", dpi=300, bbox_inches='tight')
    plt.close()


# ------------------- FIGURE 2: HORIZONTAL LINE AT y = 0.55 -------------------
def plot_constant_line():
    fig, ax = plt.subplots(figsize=(6, 6), constrained_layout=True)

    s = np.linspace(0, 1, 200)
    y = np.full_like(s, 0.55)

    ax.plot(s, y, linewidth=2.5, color='green',
            label="permeability non equilibrium based on average velocity of water")

    ax.set_xlabel("Saturation S", fontsize=FONT_SIZE)
    ax.set_ylabel("Permeability k", fontsize=FONT_SIZE)
    ax.set_xlim(0, 1)
    ax.set_ylim(0, 1)
    ax.set_aspect('equal', adjustable='box')
    style_axes(ax)

    handles, labels = ax.get_legend_handles_labels()
    wrapped = ["\n".join(textwrap.wrap(l, 30)) for l in labels]
    ax.legend(handles, wrapped, loc='upper center',
              bbox_to_anchor=(0.5, 1.12), ncol=1,
              fontsize=FONT_SIZE - 4, frameon=True)

    plt.savefig(f"{FIG_DIR}/constant_0p55.png", dpi=300, bbox_inches='tight')
    plt.close()


# ------------------- MAIN -------------------
if __name__ == "__main__":
    plot_line_and_parabola()
    plot_constant_line()
    print(f"Done. Generated 2 plots in {FIG_DIR}/")

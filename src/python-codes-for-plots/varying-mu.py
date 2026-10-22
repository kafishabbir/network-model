import json
import os
import shutil
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import MultipleLocator, FuncFormatter

# ------------------- CONFIG -------------------
DATA_FILE = "data.json"
FIG_DIR = "figures"

# Generate time windows from 0.10 to 0.90 in 0.10 steps
TIME_WINDOWS = {}
TIME_DISPLAY = {}

time_points = [0.5, 1, 1.5, 2, 2.5, 3, 3.0, 3.5, 4, 4.5, 5, 5.5, 6]

for t in time_points:
    label = f"t{int(t*100):03d}"
    TIME_WINDOWS[label] = (t - 0.005, t + 0.005)  # Wider window for larger spacing
    TIME_DISPLAY[label] = t

FONT_SIZE = 14

# ------------------- UTILS -------------------
def comma_formatter(x, pos):
    return f"{x:.1f}".replace(".", ",")

def clear_figures():
    if os.path.exists(FIG_DIR):
        shutil.rmtree(FIG_DIR)
    os.makedirs(FIG_DIR)

def load_data():
    with open(DATA_FILE) as f:
        return json.load(f)["simulations"]

# ------------------- EXTRACT METADATA FROM JSON -------------------
def extract_metadata(sims):
    """Extract all parameters from each simulation's parameter section"""
    for sim in sims:
        params = sim.get("parameter", {})
        
        constant_physical = params.get("constant_physical", {})
        sigma = constant_physical.get("sigma")
        viscosity_oil = constant_physical.get("viscosity_oil", 1.0)
        viscosity_water = constant_physical.get("viscosity_water", 1.0)
        
        geometry = params.get("geometry", {})
        radius_contrast = geometry.get("radius_contrast")
        
        simulation_params = params.get("simulation", {})
        n_initial_disturbance = simulation_params.get("n_initial_disturbance")
        
        if n_initial_disturbance is None:
            n_initial_disturbance = params.get("geometry_distributions", {}).get("n_initial_disturbance")
        
        viscosity_ratio = viscosity_water / viscosity_oil
        
        sim["_meta"] = {
            "sigma": sigma,
            "radius_contrast": radius_contrast,
            "viscosity_oil": viscosity_oil,
            "viscosity_water": viscosity_water,
            "viscosity_ratio": viscosity_ratio,
            "n_initial_disturbance": n_initial_disturbance
        }
    
    return sims

# ------------------- GET UNIQUE VALUES -------------------
def get_unique_values(sims, key):
    """Get sorted unique values for a given metadata key"""
    values = set()
    for sim in sims:
        if "_meta" in sim and sim["_meta"].get(key) is not None:
            values.add(sim["_meta"][key])
    return sorted(list(values))

# ------------------- CURVES -------------------
def extract_curves(sim):
    curves = {}

    for state in sim["measured"]["states"]:
        t = state["measured"]["time_elapsed"]

        for label, (tmin, tmax) in TIME_WINDOWS.items():
            if label not in curves and tmin <= t <= tmax:
                sat = state["calculated"]["saturation_vs_x"]
                x = [p[0] for p in sat]
                s = [p[1] for p in sat]
                curves[label] = (x, s)

    return curves

# ------------------- STYLE -------------------
def style_axes(ax):
    ax.set_aspect('equal')

    ax.set_xlim(0, 1)
    ax.set_ylim(0, 1)

    ax.set_xlabel("x", fontsize=FONT_SIZE)
    ax.set_ylabel("S(x)", fontsize=FONT_SIZE)

    ax.tick_params(labelsize=0.8 * FONT_SIZE)

    ax.xaxis.set_major_locator(MultipleLocator(0.2))
    ax.yaxis.set_major_locator(MultipleLocator(0.2))
    ax.xaxis.set_minor_locator(MultipleLocator(0.1))
    ax.yaxis.set_minor_locator(MultipleLocator(0.1))

    # ax.xaxis.set_major_formatter(FuncFormatter(comma_formatter))
    # ax.yaxis.set_major_formatter(FuncFormatter(comma_formatter))

    ax.grid(which='major', color='grey', linewidth=1.3)
    ax.grid(which='minor', color='lightgrey', linewidth=1.0)

# ------------------- SAFE FIGURE -------------------
def make_figure():
    return plt.subplots(figsize=(5, 4.5), constrained_layout=True)

# ------------------- PLOT FOR FIXED SIGMA -------------------
def plot_fixed_sigma(sims, sigma, plot_counter):
    """Plot different viscosity ratios for a fixed sigma across all time points"""
    
    # Get unique viscosity ratio values for this sigma
    viscosity_ratios = set()
    for sim in sims:
        m = sim["_meta"]
        if abs(m["sigma"] - sigma) < 1e-6:  # Compare with tolerance
            viscosity_ratios.add(m["viscosity_ratio"])
    viscosity_ratios = sorted(list(viscosity_ratios))
    
    if not viscosity_ratios:
        return plot_counter
    
    # Create colormap for different viscosity ratios
    # Use viridis_r so high mu (first) is dark blue/purple, low mu (last) is yellow/green
    cmap = plt.cm.viridis_r  # Reverse viridis
    colors = [cmap(i / len(viscosity_ratios)) for i in range(len(viscosity_ratios))]
    
    for tlabel in TIME_WINDOWS:
        fig, ax = make_figure()
        has_data = False
        
        for idx, mu_ratio in enumerate(viscosity_ratios):
            for sim in sims:
                m = sim["_meta"]
                if abs(m["sigma"] - sigma) >= 1e-6:
                    continue
                if abs(m["viscosity_ratio"] - mu_ratio) >= 1e-6:
                    continue
                
                curves = extract_curves(sim)
                if tlabel not in curves:
                    continue
                
                x, s = curves[tlabel]
                
                # Format viscosity ratio label
                if mu_ratio < 0.01:
                    label = f"{mu_ratio:.4f}"
                elif mu_ratio < 0.1:
                    label = f"{mu_ratio:.3f}"
                else:
                    label = f"{mu_ratio:.2f}"
                
                ax.plot(x, s, linewidth=1.5, marker='o', markersize=3, label=label, color=colors[idx])
                has_data = True
                break  # Found the sim for this mu, move to next mu
        
        if not has_data:
            plt.close()
            continue
        
        style_axes(ax)
        
        time_value = TIME_DISPLAY[tlabel]
        ax.set_title(f"$t = {time_value:.2f}s$", fontsize=FONT_SIZE+2)
        
        # Create legend with title
        legend = ax.legend(loc='center left', bbox_to_anchor=(1.02, 0.5), 
                          fontsize=FONT_SIZE-2, title=r"$\mu_w/\mu_o$", 
                          title_fontsize=FONT_SIZE)
        
        # Add text box with sigma value
        # Format sigma for display
        if sigma < 0.01:
            sigma_str = f"{sigma:.4f}"
        elif sigma < 0.1:
            sigma_str = f"{sigma:.3f}"
        else:
            sigma_str = f"{sigma:.2f}"
        
        text_str = f"$\\sigma = {sigma_str}$ $[kg/s^2]$"
        ax.text(1.05, 0.95, text_str, transform=ax.transAxes, 
                fontsize=FONT_SIZE,
                verticalalignment='bottom', bbox=dict(boxstyle='round', facecolor='white', alpha=0.8))
        
        fname = f"{FIG_DIR}/plot-{plot_counter:04d}.png"
        plt.savefig(fname, dpi=300, bbox_inches='tight')
        plt.close()
        
        plot_counter += 1
    
    return plot_counter

# ------------------- MAIN -------------------
def main():
    clear_figures()

    sims = load_data()
    sims = extract_metadata(sims)

    sigma_values = get_unique_values(sims, "sigma")
    
    print(f"Found sigma values: {sigma_values}")
    print(f"Total simulations: {len(sims)}")
    print(f"Time points: {list(TIME_DISPLAY.values())}")
    
    print("\nGenerating plots...")

    plot_counter = 1
    for sigma in sigma_values:
        print(f"  Plotting fixed sigma = {sigma:.4f}...")
        plot_counter = plot_fixed_sigma(sims, sigma, plot_counter)

    print(f"\nDone. Generated {plot_counter - 1} plots in {FIG_DIR}/")

if __name__ == "__main__":
    main()

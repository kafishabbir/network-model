import json
import os
import shutil
import numpy as np
import matplotlib.pyplot as plt

# ------------------- CONFIG -------------------
DATA_FILE = "data.json"
FIG_DIR = "figures"

FONT_SIZE = 14

# ------------------- UTILS -------------------
def clear_figures():
    if os.path.exists(FIG_DIR):
        shutil.rmtree(FIG_DIR)
    os.makedirs(FIG_DIR)

def load_data():
    with open(DATA_FILE) as f:
        return json.load(f)["simulations"]

# ------------------- EXTRACT METADATA -------------------
def extract_metadata(sims):
    """Extract inlet water saturation from the simulation parameter block."""
    for sim in sims:
        inlet_water_saturation = (
            sim.get("parameter", {})
               .get("simulation", {})
               .get("inlet_water_saturation", 0)
        )
        sim["_meta"] = {"inlet_water_saturation": inlet_water_saturation}
    return sims

# ------------------- GET UNIQUE VALUES -------------------
def get_unique_values(sims, key):
    values = set()
    for sim in sims:
        if "_meta" in sim and sim["_meta"].get(key) is not None:
            values.add(sim["_meta"][key])
    return sorted(list(values))

# ------------------- EXTRACT HIGH FREQUENCY DATA -------------------
def extract_high_freq_data(sim):
    high_freq = sim["measured"]["high_frequency_data_v"]

    times = []
    saturations = []
    pressures = []
    velocities_water = []

    flow_rate_all = []
    flow_rate_injected = []
    flow_rate_evacuated = []

    perm_avg_velocity_water = []
    perm_total_flow_rate = []
    perm_inject_fluid_injected = []
    perm_inject_fluid_evacuated = []

    for entry in high_freq:
        times.append(entry["time"])
        saturations.append(entry["saturation"])
        pressures.append(entry["pressure"])
        velocities_water.append(entry["average_velocity_water"])

        flow_rate_all.append(entry["flow_rate_all_fluids_all_boundaries"])
        flow_rate_injected.append(entry["flow_rate_inject_fluid_input_boundary"])
        flow_rate_evacuated.append(entry["flow_rate_inject_fluid_output_boundary"])

        perm_avg_velocity_water.append(entry["permeability_using_average_velocity_water"])
        perm_total_flow_rate.append(entry["permeability_using_total_flow_rate"])
        perm_inject_fluid_injected.append(entry["permeability_using_inject_fluid_injected"])
        perm_inject_fluid_evacuated.append(entry["permeability_using_inject_fluid_evacuated"])

    return {
        "time": np.array(times),
        "saturation": np.array(saturations),
        "pressure": np.array(pressures),
        "velocity_water": np.array(velocities_water),
        "flow_rate_all": np.array(flow_rate_all),
        "flow_rate_injected": np.array(flow_rate_injected),
        "flow_rate_evacuated": np.array(flow_rate_evacuated),
        "perm_avg_velocity_water": np.array(perm_avg_velocity_water),
        "perm_total_flow_rate": np.array(perm_total_flow_rate),
        "perm_inject_fluid_injected": np.array(perm_inject_fluid_injected),
        "perm_inject_fluid_evacuated": np.array(perm_inject_fluid_evacuated),
    }

# ------------------- FORMAT SATURATION LABEL -------------------
def format_saturation(saturation):
    """Format inlet water saturation as a dimensionless label."""
    return f"Sw,in = {saturation:.2f}"

# ------------------- STYLE -------------------
def style_axes(ax):
    ax.tick_params(labelsize=0.8 * FONT_SIZE)
    ax.grid(which='major', color='grey', linewidth=1.3)
    ax.grid(which='minor', color='lightgrey', linewidth=1.0)

def make_figure():
    return plt.subplots(figsize=(6, 5), constrained_layout=True)

def _colors(n):
    cmap = plt.cm.viridis
    return [cmap(i / max(n - 1, 1)) for i in range(n)]

# ------------------- PLOT S VS T -------------------
def plot_s_vs_t(sims, saturations, plot_counter):
    fig, ax = make_figure()
    colors = _colors(len(saturations))

    for idx, sw_in in enumerate(saturations):
        for sim in sims:
            if sim["_meta"]["inlet_water_saturation"] != sw_in:
                continue
            data = extract_high_freq_data(sim)
            ax.plot(data["time"], data["saturation"], linewidth=2,
                    label=format_saturation(sw_in), color=colors[idx])
            break

    ax.set_xlabel("Time [s]", fontsize=FONT_SIZE)
    ax.set_ylabel("Saturation", fontsize=FONT_SIZE)
    ax.set_xlim(0, None)
    ax.set_ylim(0, 1.05)
    style_axes(ax)
    ax.legend(loc='center left', bbox_to_anchor=(1.02, 0.5),
              fontsize=FONT_SIZE-3, title="Inlet Water Saturation")
    plt.savefig(f"{FIG_DIR}/S_vs_t.png", dpi=300, bbox_inches='tight')
    plt.close()
    return plot_counter + 1

# ------------------- PLOT Q AND V_W VS T (NORMALIZED) -------------------
def plot_q_and_vw_vs_t(sims, saturations, plot_counter):
    fig, ax = make_figure()
    colors = _colors(len(saturations))

    for idx, sw_in in enumerate(saturations):
        for sim in sims:
            if sim["_meta"]["inlet_water_saturation"] != sw_in:
                continue
            data = extract_high_freq_data(sim)
            label = format_saturation(sw_in)
            q = data["flow_rate_all"]
            q_norm = q / np.max(q) if np.max(q) > 0 else q
            ax.plot(data["time"], q_norm, linewidth=2, linestyle='-',
                    label=f"{label} (Q)", color=colors[idx])
            break

    for idx, sw_in in enumerate(saturations):
        for sim in sims:
            if sim["_meta"]["inlet_water_saturation"] != sw_in:
                continue
            data = extract_high_freq_data(sim)
            label = format_saturation(sw_in)
            vw = data["velocity_water"]
            vw_norm = vw / np.max(vw) if np.max(vw) > 0 else vw
            ax.plot(data["time"], vw_norm, linewidth=2, linestyle='--',
                    label=f"{label} (V_w)", color=colors[idx])
            break

    ax.set_xlabel("Time [s]", fontsize=FONT_SIZE)
    ax.set_ylabel("Normalized Value", fontsize=FONT_SIZE)
    ax.set_xlim(0, None)
    ax.set_ylim(0, 1.1)
    style_axes(ax)
    ax.legend(loc='center left', bbox_to_anchor=(1.02, 0.5),
              fontsize=FONT_SIZE-4, title="Inlet Water Saturation")
    plt.savefig(f"{FIG_DIR}/Q_and_Vw_vs_t.png", dpi=300, bbox_inches='tight')
    plt.close()
    return plot_counter + 1

# ------------------- PLOT P VS T -------------------
def plot_p_vs_t(sims, saturations, plot_counter):
    fig, ax = make_figure()
    colors = _colors(len(saturations))

    for idx, sw_in in enumerate(saturations):
        for sim in sims:
            if sim["_meta"]["inlet_water_saturation"] != sw_in:
                continue
            data = extract_high_freq_data(sim)
            ax.plot(data["time"], data["pressure"], linewidth=2,
                    label=format_saturation(sw_in), color=colors[idx])
            break

    ax.set_xlabel("Time [s]", fontsize=FONT_SIZE)
    ax.set_ylabel("Pressure [Pa]", fontsize=FONT_SIZE)
    ax.set_xlim(0, None)
    style_axes(ax)
    ax.legend(loc='center left', bbox_to_anchor=(1.02, 0.5),
              fontsize=FONT_SIZE-3, title="Inlet Water Saturation")
    plt.savefig(f"{FIG_DIR}/P_vs_t.png", dpi=300, bbox_inches='tight')
    plt.close()
    return plot_counter + 1

# ------------------- GENERIC K(S) PLOT -------------------
def plot_k_vs_s(sims, saturations, plot_counter, perm_key, title, fname, filter_s=None):
    fig, ax = make_figure()
    colors = _colors(len(saturations))

    for idx, sw_in in enumerate(saturations):
        for sim in sims:
            if sim["_meta"]["inlet_water_saturation"] != sw_in:
                continue
            data = extract_high_freq_data(sim)
            sat = data["saturation"]
            perm = data[perm_key]
            if filter_s is not None:
                mask = sat > filter_s
                sat = sat[mask]
                perm = perm[mask]
            ax.plot(sat, perm, linewidth=2,
                    label=format_saturation(sw_in), color=colors[idx])
            break

    ax.set_xlabel("Saturation", fontsize=FONT_SIZE)
    ax.set_ylabel("Permeability k(S)", fontsize=FONT_SIZE)
    ax.set_xlim(0, 1.05)
    ax.set_title(title, fontsize=FONT_SIZE)
    style_axes(ax)
    ax.legend(loc='center left', bbox_to_anchor=(1.02, 0.5),
              fontsize=FONT_SIZE-3, title="Inlet Water Saturation")
    plt.savefig(f"{FIG_DIR}/{fname}", dpi=300, bbox_inches='tight')
    plt.close()
    return plot_counter + 1

# ------------------- COMPUTE END AVERAGE -------------------
def end_average(sat, perm, n_points=10):
    """Average the last n_points of perm (sorted by sat) and return (s_avg, k_avg)."""
    order = np.argsort(sat)
    sat = sat[order]
    perm = perm[order]
    if len(sat) == 0:
        return None, None
    n = min(n_points, len(sat))
    s_avg = float(np.mean(sat[-n:]))
    k_avg = float(np.mean(perm[-n:]))
    return s_avg, k_avg

# ------------------- POLYFIT + R^2 -------------------
def polyfit_with_r2(x, y, degree):
    """Return coefficients and R^2 for a polynomial fit. Handles degenerate cases."""
    x = np.asarray(x, dtype=float)
    y = np.asarray(y, dtype=float)
    if len(x) < degree + 1 or np.ptp(x) == 0:
        return None, None
    coeffs = np.polyfit(x, y, degree)
    y_pred = np.polyval(coeffs, x)
    ss_res = np.sum((y - y_pred) ** 2)
    ss_tot = np.sum((y - np.mean(y)) ** 2)
    r2 = 1.0 - ss_res / ss_tot if ss_tot > 0 else 1.0
    return coeffs, r2

# ------------------- PLOT K(S) WITH FIT MARKERS -------------------
def plot_k_vs_s_with_fits(sims, saturations, plot_counter, perm_key, title, fname,
                          filter_s=None, n_avg_points=10):
    """Plot the k(S) curves, mark end-averages as red dots, and overlay
    line + parabola fits through those dots. R^2 values appear in the legend."""
    fig, ax = make_figure()
    colors = _colors(len(saturations))

    s_pts = []
    k_pts = []
    sw_labels = []

    for idx, sw_in in enumerate(saturations):
        for sim in sims:
            if sim["_meta"]["inlet_water_saturation"] != sw_in:
                continue
            data = extract_high_freq_data(sim)
            sat = data["saturation"]
            perm = data[perm_key]
            if filter_s is not None:
                mask = sat > filter_s
                sat = sat[mask]
                perm = perm[mask]

            # Underlying curve (thin) for reference
            ax.plot(sat, perm, linewidth=1.2, alpha=0.45, color=colors[idx])

            s_avg, k_avg = end_average(sat, perm, n_points=n_avg_points)
            if s_avg is not None:
                s_pts.append(s_avg)
                k_pts.append(k_avg)
                sw_labels.append(sw_in)
                ax.plot(s_avg, k_avg, 'o', markersize=9,
                        markerfacecolor='red', markeredgecolor='darkred',
                        zorder=5)
            break

    # ---- Fit line and parabola through the red dots ----
    legend_handles = []
    if len(s_pts) >= 2:
        s_arr = np.asarray(s_pts, dtype=float)
        k_arr = np.asarray(k_pts, dtype=float)
        s_fit = np.linspace(s_arr.min(), s_arr.max(), 200)

        # Linear fit
        line_coeffs, line_r2 = polyfit_with_r2(s_arr, k_arr, degree=1)
        if line_coeffs is not None:
            ax.plot(s_fit, np.polyval(line_coeffs, s_fit),
                    linestyle='--', linewidth=2, color='black',
                    label=f"Line fit (R² = {line_r2:.4f})")

        # Parabola fit (quadratic)
        para_coeffs, para_r2 = polyfit_with_r2(s_arr, k_arr, degree=2)
        if para_coeffs is not None:
            ax.plot(s_fit, np.polyval(para_coeffs, s_fit),
                    linestyle='-', linewidth=2, color='dimgray',
                    label=f"Parabola fit (R² = {para_r2:.4f})")

    # Dummy handle for red dots legend entry
    from matplotlib.lines import Line2D
    red_dot = Line2D([0], [0], marker='o', color='w',
                     markerfacecolor='red', markeredgecolor='darkred',
                     markersize=9,
                     label=f"Avg of last {n_avg_points} pts")

    # Compose legend
    handles, labels = ax.get_legend_handles_labels()
    handles.append(red_dot)
    labels.append(red_dot.get_label())

    ax.set_xlabel("Saturation", fontsize=FONT_SIZE)
    ax.set_ylabel("Permeability k(S)", fontsize=FONT_SIZE)
    ax.set_xlim(0, 1.05)
    ax.set_title(title, fontsize=FONT_SIZE)
    style_axes(ax)
    ax.legend(handles=handles, labels=labels,
              loc='center left', bbox_to_anchor=(1.02, 0.5),
              fontsize=FONT_SIZE-4)
    plt.savefig(f"{FIG_DIR}/{fname}", dpi=300, bbox_inches='tight')
    plt.close()
    return plot_counter + 1

# ------------------- ALL PERMEABILITY PLOTS -------------------
def plot_all_permeabilities(sims, saturations, plot_counter):
    methods = [
        ("perm_avg_velocity_water",   "Average Velocity of Water",   "k_avg_velocity_water"),
        ("perm_total_flow_rate",      "Total Flow Rate",             "k_total_flow_rate"),
        ("perm_inject_fluid_injected","Injected Fluid (Injected)",   "k_inject_fluid_injected"),
        ("perm_inject_fluid_evacuated","Injected Fluid (Evacuated)", "k_inject_fluid_evacuated"),
    ]

    for perm_key, method_name, base in methods:
        # ---- Set 1: all S ----
        print(f"  Plotting k(S) from {method_name} (full)...")
        plot_counter = plot_k_vs_s(
            sims, saturations, plot_counter,
            perm_key=perm_key,
            title=f"Based on {method_name}",
            fname=f"{base}_vs_S_full.png",
        )

        # ---- Set 2: S > 0.1 ----
        print(f"  Plotting k(S) from {method_name} (S > 0.1)...")
        plot_counter = plot_k_vs_s(
            sims, saturations, plot_counter,
            perm_key=perm_key,
            title=f"Based on {method_name} (S > 0.1)",
            fname=f"{base}_vs_S_filtered.png",
            filter_s=0.1,
        )

        # ---- Set 3: end-average red dots + fits (S > 0.1) ----
        print(f"  Plotting k(S) from {method_name} with end-averages + fits (S > 0.1)...")
        plot_counter = plot_k_vs_s_with_fits(
            sims, saturations, plot_counter,
            perm_key=perm_key,
            title=f"{method_name}: End-Averages with Line & Parabola Fits (S > 0.1)",
            fname=f"{base}_vs_S_filtered_fits.png",
            filter_s=0.1,
            n_avg_points=10,
        )
    return plot_counter

# ------------------- MAIN -------------------
def main():
    clear_figures()

    sims = load_data()
    sims = extract_metadata(sims)

    saturations = get_unique_values(sims, "inlet_water_saturation")

    print(f"Found inlet water saturations: {saturations}")
    print(f"Total simulations: {len(sims)}")

    print("\nGenerating plots...")
    plot_counter = 1

    print("  Plotting Saturation vs Time...")
    plot_counter = plot_s_vs_t(sims, saturations, plot_counter)

    print("  Plotting Q and V_w vs Time (normalized)...")
    plot_counter = plot_q_and_vw_vs_t(sims, saturations, plot_counter)

    print("  Plotting Pressure vs Time...")
    plot_counter = plot_p_vs_t(sims, saturations, plot_counter)

    plot_counter = plot_all_permeabilities(sims, saturations, plot_counter)

    print(f"\nDone. Generated {plot_counter - 1} plots in {FIG_DIR}/")

if __name__ == "__main__":
    main()

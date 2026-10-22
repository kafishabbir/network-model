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
    """Extract inlet pressure from the simulation parameter block."""
    for sim in sims:
        inlet_pressure = sim.get("parameter", {}).get("simulation", {}).get("inlet_pressure", 0)
        sim["_meta"] = {"inlet_pressure": inlet_pressure}
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
    """
    Extract all data from high_frequency_data_v.
    Field names match the actual JSON structure.
    """
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

# ------------------- FORMAT PRESSURE LABEL -------------------
def format_pressure(pressure):
    if pressure >= 1e6:
        return f"{pressure/1e6:.1f} MPa"
    elif pressure >= 1e3:
        return f"{pressure/1e3:.0f} kPa"
    else:
        return f"{pressure:.0f} Pa"

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
def plot_s_vs_t(sims, pressures, plot_counter):
    fig, ax = make_figure()
    colors = _colors(len(pressures))

    for idx, pressure in enumerate(pressures):
        for sim in sims:
            if sim["_meta"]["inlet_pressure"] != pressure:
                continue
            data = extract_high_freq_data(sim)
            ax.plot(data["time"], data["saturation"], linewidth=2,
                    label=format_pressure(pressure), color=colors[idx])
            break

    ax.set_xlabel("Time [s]", fontsize=FONT_SIZE)
    ax.set_ylabel("Saturation", fontsize=FONT_SIZE)
    ax.set_xlim(0, None)
    ax.set_ylim(0, 1.05)
    style_axes(ax)
    ax.legend(loc='center left', bbox_to_anchor=(1.02, 0.5),
              fontsize=FONT_SIZE-2, title="Inlet Pressure")
    plt.savefig(f"{FIG_DIR}/S_vs_t.png", dpi=300, bbox_inches='tight')
    plt.close()
    return plot_counter + 1

# ------------------- PLOT Q AND V_W VS T (NORMALIZED) -------------------
def plot_q_and_vw_vs_t(sims, pressures, plot_counter):
    fig, ax = make_figure()
    colors = _colors(len(pressures))

    for idx, pressure in enumerate(pressures):
        for sim in sims:
            if sim["_meta"]["inlet_pressure"] != pressure:
                continue
            data = extract_high_freq_data(sim)
            label = format_pressure(pressure)
            q = data["flow_rate_all"]
            q_norm = q / np.max(q) if np.max(q) > 0 else q
            ax.plot(data["time"], q_norm, linewidth=2, linestyle='-',
                    label=f"{label} (Q)", color=colors[idx])
            break

    for idx, pressure in enumerate(pressures):
        for sim in sims:
            if sim["_meta"]["inlet_pressure"] != pressure:
                continue
            data = extract_high_freq_data(sim)
            label = format_pressure(pressure)
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
              fontsize=FONT_SIZE-3, title="Inlet Pressure")
    plt.savefig(f"{FIG_DIR}/Q_and_Vw_vs_t.png", dpi=300, bbox_inches='tight')
    plt.close()
    return plot_counter + 1

# ------------------- PLOT P VS T -------------------
def plot_p_vs_t(sims, pressures, plot_counter):
    fig, ax = make_figure()
    colors = _colors(len(pressures))

    for idx, pressure in enumerate(pressures):
        for sim in sims:
            if sim["_meta"]["inlet_pressure"] != pressure:
                continue
            data = extract_high_freq_data(sim)
            ax.plot(data["time"], data["pressure"], linewidth=2,
                    label=format_pressure(pressure), color=colors[idx])
            break

    ax.set_xlabel("Time [s]", fontsize=FONT_SIZE)
    ax.set_ylabel("Pressure [Pa]", fontsize=FONT_SIZE)
    ax.set_xlim(0, None)
    style_axes(ax)
    ax.legend(loc='center left', bbox_to_anchor=(1.02, 0.5),
              fontsize=FONT_SIZE-2, title="Inlet Pressure")
    plt.savefig(f"{FIG_DIR}/P_vs_t.png", dpi=300, bbox_inches='tight')
    plt.close()
    return plot_counter + 1

# ------------------- GENERIC K(S) PLOT -------------------
def plot_k_vs_s(sims, pressures, plot_counter, perm_key, title, fname, filter_s=None):
    fig, ax = make_figure()
    colors = _colors(len(pressures))

    for idx, pressure in enumerate(pressures):
        for sim in sims:
            if sim["_meta"]["inlet_pressure"] != pressure:
                continue
            data = extract_high_freq_data(sim)
            sat = data["saturation"]
            perm = data[perm_key]
            if filter_s is not None:
                mask = sat > filter_s
                sat = sat[mask]
                perm = perm[mask]
            ax.plot(sat, perm, linewidth=2,
                    label=format_pressure(pressure), color=colors[idx])
            break

    ax.set_xlabel("Saturation", fontsize=FONT_SIZE)
    ax.set_ylabel("Permeability k(S)", fontsize=FONT_SIZE)
    ax.set_xlim(0, 1.05)
    ax.set_title(title, fontsize=FONT_SIZE)
    style_axes(ax)
    ax.legend(loc='center left', bbox_to_anchor=(1.02, 0.5),
              fontsize=FONT_SIZE-2, title="Inlet Pressure")
    plt.savefig(f"{FIG_DIR}/{fname}", dpi=300, bbox_inches='tight')
    plt.close()
    return plot_counter + 1

# ------------------- ALL PERMEABILITY PLOTS -------------------
def plot_all_permeabilities(sims, pressures, plot_counter):
    methods = [
        ("perm_avg_velocity_water",   "Average Velocity of Water",        "k_avg_velocity_water"),
        ("perm_total_flow_rate",       "Total Flow Rate",                 "k_total_flow_rate"),
        ("perm_inject_fluid_injected", "Injected Fluid (Injected)",       "k_inject_fluid_injected"),
        ("perm_inject_fluid_evacuated","Injected Fluid (Evacuated)",      "k_inject_fluid_evacuated"),
    ]

    for perm_key, method_name, base in methods:
        print(f"  Plotting k(S) from {method_name} (full)...")
        plot_counter = plot_k_vs_s(
            sims, pressures, plot_counter,
            perm_key=perm_key,
            title=f"Based on {method_name}",
            fname=f"{base}_vs_S_full.png",
        )
        print(f"  Plotting k(S) from {method_name} (S > 0.1)...")
        plot_counter = plot_k_vs_s(
            sims, pressures, plot_counter,
            perm_key=perm_key,
            title=f"Based on {method_name} (S > 0.1)",
            fname=f"{base}_vs_S_filtered.png",
            filter_s=0.1,
        )
    return plot_counter

# ------------------- MAIN -------------------
def main():
    clear_figures()

    sims = load_data()
    sims = extract_metadata(sims)

    pressures = get_unique_values(sims, "inlet_pressure")

    print(f"Found inlet pressures: {pressures}")
    print(f"Total simulations: {len(sims)}")

    print("\nGenerating plots...")
    plot_counter = 1

    print("  Plotting Saturation vs Time...")
    plot_counter = plot_s_vs_t(sims, pressures, plot_counter)

    print("  Plotting Q and V_w vs Time (normalized)...")
    plot_counter = plot_q_and_vw_vs_t(sims, pressures, plot_counter)

    print("  Plotting Pressure vs Time...")
    plot_counter = plot_p_vs_t(sims, pressures, plot_counter)

    plot_counter = plot_all_permeabilities(sims, pressures, plot_counter)

    print(f"\nDone. Generated {plot_counter - 1} plots in {FIG_DIR}/")

if __name__ == "__main__":
    main()

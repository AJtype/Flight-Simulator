import configparser
import os

# --- Read simulation parameters ---
def read_sim_params(filepath="../SimParams.ini"):
    config = configparser.ConfigParser()
    with open(filepath) as f:
        ini_data = "[sim]\n" + f.read()  # fake section
    config.read_string(ini_data)
    return int(config["sim"]["N_uav"])
import pandas as pd
import matplotlib.pyplot as plt

# ett slipp gjort på 8min og ett slipp gjort på ca 17min.
input_file: str = "datalog.csv"

with open(input_file, "r") as file:
    lines = file.readlines()

# Identify indices where headers repeat
header: str = "Timestamp,ExtPressure (kPa),IntPressure (kPa),Temp (C),AccelX,AccelY,AccelZ,GyroX,GyroY,GyroZ"
split_indices: list[int] = [i for i, line in enumerate(lines) if line.strip() == header]
split_indices.append(len(lines))  

print(f"Indeces: {split_indices[:-1]}")

# Drops: 500k - 520k, 1010k - 1030k


data: list[tuple[float, ...]] = []
time_offset: int = 0
for i in range(len(split_indices) - 1):
    start: int = split_indices[i] + 1 
    end: int = split_indices[i + 1]

    # Assuming 0 ms in restart    
    part: list[str] = lines[start:end]
    if i > 0:
        time_offset += int(lines[start - 2].split(",")[0])
    
    for sample in part:
        res = []
        for idx, val in enumerate(sample.strip().split(",")):
            val = float(val)
            if idx == 0: 
                # timestamp 
                val += time_offset
            res.append(val)
        data.append(tuple(res))

    
df = pd.DataFrame(data, columns=header.split(","))    
df = df.apply(pd.to_numeric, errors="ignore")


plt.figure()

# Plot ExtPressure
plt.plot(df["Timestamp"], df["AccelX"], label="AccelX", color="blue")
# fig.set_ylabel("Ext Pressure (kPa)")
plt.legend()
plt.show()

# plt.figure()

# # Plot ExtPressure
# plt.plot(df["Timestamp"], df["AccelZ"], label="Temp (C)", color="blue")
# # fig.set_ylabel("Ext Pressure (kPa)")
# plt.legend()
# plt.show()fig, axes = plt.subplots(5, 1, figsize=(10, 12), sharex=True)

import numpy as np

from scipy.spatial.transform import Rotation as rot


pos: np.ndarray = np.zeros(3)
vel: np.ndarray = np.zeros(3)
rpy: np.ndarray = np.zeros(3) # Assuming gimbal lock not a problem

def T(rpy: np.ndarray) -> np.ndarray:
    c_phi = np.cos(rpy[0])
    s_phi = np.sin(rpy[0])

    c_theta = np.cos(rpy[1])
    s_theta = np.sin(rpy[1])

    t_theta = s_theta / c_theta

    return np.array(
        [
            [1, s_phi * t_theta, c_phi * t_theta], 
            [0, c_theta, -s_phi],
            [0, s_phi / c_theta, c_phi / c_theta]
        ]
    )
    

def R(rpy: np.ndarray) -> np.ndarray:
    R = rot.from_euler(seq="xyz", angles=rpy, degrees=False)
    return R.as_matrix()

print(R(np.array([np.pi/2, 0, 0])))

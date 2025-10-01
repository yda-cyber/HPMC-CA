# HPMC-CA

## System Requirements

**Operating System:**  
Linux

**Software Dependencies:**
- Python ≥ 3.9
- Jupyter Notebook

**Python Packages:**
- hoomd-blue == 5.0.0  
- fresnel == 0.13.5  
- imageio == 2.36.1  
- numpy ≥ 1.26.4  
- matplotlib ≥ 3.9.2  
- ipykernel == 6.29.5  

**Hardware Requirements:**  
No non-standard hardware required

---

## Installation Guide

### 1. Create a Conda or Mamba Environment

We recommend creating a fresh environment using mamba or conda to manage dependencies cleanly.

    mamba create -n hoomd-env python=3.11
    mamba activate hoomd-env

### 2. Install HOOMD-blue from Source

Due to the need for modification and recompilation, install HOOMD-blue from source:

GitHub: https://github.com/glotzerlab/hoomd-blue  
Documentation: https://hoomd-blue.readthedocs.io/en/v5.0.0/

### 3. Modify and Recompile HOOMD-blue

Add the following files into the HOOMD-blue source tree before compilation:

    ExternalFieldTypeHarmonic.h → {HOOMD_SRC}/hoomd/include/hoomd/hpmc/
    typeharmonic.py → {HOOMD_SRC}/hoomd/hpmc/external/

Depending on version of HOOMD-Blue, locations may vary. But you will find harmonic.py/ Harmonic.h in these folders.

You will also need to add those files into CMakeList.txt corrspondingly. In addition, add "TypeHarmonic" into hoomd.hpmc.external.__init__ to allow import.

Then compile HOOMD-blue following its official instructions.

### 4. Install Remaining Packages

Install the remaining Python packages using mamba or pip:

    mamba install fresnel=0.13.5 imageio=2.36.1 numpy=1.26.4 matplotlib=3.9.2 ipykernel=6.29.5

### 5. Register Kernel and Launch Jupyter

Register the environment for use in Jupyter:

    python -m ipykernel install --user --name hoomd-env --display-name "Python (hoomd-env)"
    jupyter notebook

### 6. Execute

Open the provided notebook and execute all cells sequentially.

---

## Demo

**Instruction:**  
A demo notebook is included and contains parameter explanations and usage instructions.

**Expected Output:**  
GIFs showing the symmetry transition process.

**Typical Runtime:**  
~3–4 hours depending on CPU.

![Symmetry Transition](Movie%20S1%20In-1Start.gif)

---

## License

This project is licensed under the MIT License.  
You are free to use, modify, and distribute this code with proper attribution.

---

## Additional Information

For further methodological details and reproducibility instructions,  
please see the supplementary information for the METHODS section.

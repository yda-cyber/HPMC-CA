# HPMC-CA

README

System Requirements:
  Operating System:

    Linux

  Software Dependencies:

    Python ≥ 3.9
    Jupyter Notebook

  Python Packages:
    hoomd-blue == 5.0.0
    fresnel == 0.13.5
    imageio == 2.36.1
    numpy ≥ 1.26.4
    matplotlib ≥ 3.9.2
    ipykernel == 6.29.5

  Hardware Requirements:
    No non-standard hardware required

Installation Guide
  0. Create a Conda or Mamba Environment
    We recommend creating a fresh environment using mamba or conda to manage dependencies cleanly.
      mamba create -n hoomd-env python=3.11
      mamba activate hoomd-env

  1. Install HOOMD-blue from Source
    Due to the need for modification and recompilation, install HOOMD-blue from source:
      GitHub: https://github.com/glotzerlab/hoomd-blue

    Installation instructions for HOOMD-blue: 
      HOOMD-blue Documentation: https://hoomd-blue.readthedocs.io/en/v5.0.0/

  2. Modify and Recompile HOOMD-blue
    Add the following files into the HOOMD-blue source tree before compilation:
      ExternalFieldTypeHarmonic.h → {HOOMD_SRC}/hoomd/include/hoomd/hpmc/
      typeharmonic.py → {HOOMD_SRC}/hoomd/hpmc/external/
    Then recompile HOOMD-blue as instructed in the documentation.

  3. Install Remaining Packages
    Install the rest of the Python packages using mamba or pip:
      mamba install fresnel=0.13.5 imageio=2.36.1 numpy=1.26.4 matplotlib=3.9.2 ipykernel=6.29.5

  4. Register Kernel and Launch Jupyter
    Prior to run in Jupter the mamba environment need to be registered.
      python -m ipykernel install --user --name hoomd-env --display-name "Python (hoomd-env)"
      jupyter notebook

  5. Execute
    Open the provided notebook and execute all cells sequentially.


Demo
  Instruction:
    A demo notebook is included and contains parameter explanations and usage instructions.

  Expected Output:
    GIFs showing the symmetry transition process;

  Typical Runtime:
    ~3–4 hours, depending on CPU used. 


License
  This project is licensed under the MIT License.
  You are free to use, modify, and distribute this code with proper attribution.

  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
  TORT OR OTHERWISE, ARISING FROM, 
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


Additional Information
  For further methodological details and reproducibility instructions, 
  please see the supplementary information for METHODS section.

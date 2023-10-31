import subprocess
# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'Tsunami-Simulation'
copyright = '2023, Justus Dreßler, Thorsten Kröhl, Julius Halank'
author = 'Justus Dreßler, Thorsten Kröhl, Julius Halank'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = ['sphinx_rtd_theme',    
              "sphinxcontrib.video",
              "breathe"]

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

subprocess.call('doxygen', shell=True)

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = "sphinx_rtd_theme"
html_static_path = ['_static']


#breathe configuration
breathe_projects = { "tsunami23": "_build_doxygen/xml/" }

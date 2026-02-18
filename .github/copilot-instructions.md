# Copilot Instructions

## Python environment

All Python packages must be installed into the project's virtual environment (`.venv`), never globally.

- Always use `.venv\Scripts\python.exe -m pip install` or activate `.venv` first before any `pip install` command.
- Never run bare `pip install` without activating `.venv`.
- When suggesting terminal commands, always prefix pip calls with the venv python:
  ```
  .venv\Scripts\python.exe -m pip install <package>
  ```

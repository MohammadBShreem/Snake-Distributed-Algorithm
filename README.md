# Snake-Distributed-Algorithm

authors:
  * [Mohammad SHREM](https://www.linkedin.com/in/mohammadbshreem/) <mohammad.shrem@edu.univ-fcomte.fr>
  * [Mariam AL KHALAF]() <mariam.al_khalaf@edu.univ-fcomte.fr>

supervisor:
  * [Prof. Benoit PIRANDA](https://www.femto-st.fr/fr/personnel-femto/bpiranda) <benoit.piranda@univ-fcomte.fr>

project relaized in [VisibleSim](https://github.com/VisibleSim/VisibleSim)

---

# SnakeMoveCode Simulation

This project implements a simulation for controlling the movement of sliding cube modules using a "snake movement" algorithm. The goal is to achieve coordinated movement towards a predefined goal position while handling leader election and visualizing the simulation.

## Features
- **Leader Election**: Distributed process to select a leader module among connected cubes.
- **Coordinated Movement**: Attempts to move modules in the X or Y direction towards the goal position.
- **Visualization**: Renders the simulation and goal position using OpenGL.
- **Dynamic Messaging**: Handles communication between modules via message-passing.

## Code Overview
### Key Components
1. **Leader Election**:
   - `myElectFirstFunc`: Determines the leader by sending messages to neighbors. The leader is marked with a red color.

2. **Movement Logic**:
   - `tryToMove`, `tryToMoveX`, `tryToMoveY`: Functions that control module movement towards the goal position.
   - Movement decisions are made based on the module's current position and neighboring availability.

3. **Configuration**:
   - Parses XML configuration files to define the leader status and the goal position.

4. **Visualization**:
   - Uses OpenGL to display the goal position on a simulated grid.

---

## Discussion: 

This code defines a class SnakeMoveCode designed for controlling the movement of sliding cube modules in a simulation, resembling a "snake movement" pattern. Below is a brief explanation of the key components:

1. Class Initialization (SnakeMoveCode):

Initializes the class with a host module and binds an event (ELECTFIRST_MSG_ID) to the myElectFirstFunc method.

2. Startup Behavior (startup):

The leader module sets its color to red and begins trying to move if it hasn't reached the goal position.

3. Movement Functions (tryToMove, tryToMoveX, tryToMoveY):

Implements movement logic in the X and Y directions. The module tries to move towards the goalPosition if possible, checking adjacent positions.

4. Leader Election and Messaging (myElectFirstFunc):

Handles a distributed leader election process, assigning the leader role to a module if it has no neighbors.

5. Motion End Handling (onMotionEnd):

Triggers after a motion completes. If movement fails, the module sets its color to yellow and reattempts leader election.

6. Configuration Parsing (parseUserBlockElements, parseUserElements):

Reads configuration settings, such as leader status and goal position, from an XML document.

7. Rendering (onGlDraw):

Visualizes the goal position in the simulation grid using OpenGL.

---

## Conclusion:
Despite implementing a robust framework for leader election, movement logic, and rendering, the project did not meet its requirements. This might be due to issues such as incorrect goal positions, unhandled movement scenarios, or challenges in integrating the leader election with the movement logic. However, the team put forth their best effort, and the attempt provided valuable insights for future improvements.

# Question 5: Vi Editor Crash Recovery Evaluation

## Evaluation of Recovery Mechanisms

| Mechanism | Description | Reliability during a System Crash |
| :--- | :--- | :--- |
| **Swap Files (`.swp`)** | Automatically creates a hidden file (e.g., `.filename.swp`) that logs unsaved buffer modifications in real-time on the disk. | **Highest** |
| **Auto-recovery** | A feature that leverages the saved swap file data upon restarting the editor to restore uncommitted buffer states. | **High** |
| **Backup Files (`~`)** | Saves a copy of the *previously saved* version of the file, not the current unsaved edits. | Medium |
| **Undo History** | Tracks changes in volatile RAM. This is lost completely if the system loses power or crashes. | Low |
| **Registers** | Temporary memory storage holding yanked/copied text clips. Cleared entirely upon sudden power loss. | Low |

## Proposed Most Reliable Recovery Strategy
The **Swap File (`.swp`) Recovery Method** (initiated via `vi -r`) is the most reliable strategy following a system crash. 

**Justification:**
Unlike undo history and registers, which rely on volatile RAM and are wiped during a crash, swap files maintain a persistent, real-time log of unwritten edits directly on the hard drive. When the system reboots, the developer can run `vi -r filename` to read the surviving `.swp` file and restore all unsaved configuration changes perfectly, ensuring no critical work is lost.

## Executed Commands for Demonstration
* `vi config.txt`: Opened a new configuration file.
* `Ctrl+Z` and `kill -9 %1`: Suspended and forcefully killed the vi process to simulate an unexpected system crash.
* `ls -a`: Verified the survival of the hidden `.config.txt.swp` file.
* `vi -r config.txt`: Triggered the swap file recovery process.

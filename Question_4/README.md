# Question 4: Real-time Log Monitoring Pipeline

## Executed Pipeline Command
`tail -f system.log | grep --line-buffered "ERROR" | tee -a error_report.log > /dev/null`

## Explanation of Efficiency & Components
* **Pipes (`|`)**: Connect the standard output (`stdout`) of one command directly into the standard input (`stdin`) of the next, keeping data in volatile memory and completely avoiding slow, intermediate disk reads/writes.
* **`tail -f`**: Continuously reads and outputs only newly appended lines at the end of the log file in real-time, rather than inefficiently parsing the entire historical file from the beginning.
* **`grep --line-buffered`**: Filters the incoming data stream for "ERROR" matches. The `--line-buffered` flag forces it to push matches down the pipeline immediately upon finding them, preventing lag in real-time monitoring.
* **Redirection & `tee -a`**: `tee` splits the stream, appending (`-a`) the error messages to a persistent `error_report.log` file for the system administrator to review later.
* **`/dev/null`**: The final redirect (`> /dev/null`) acts as a "black hole" that discards the remaining standard output. This completely suppresses unnecessary console spam, freeing up terminal UI resources while the process runs quietly in the background.

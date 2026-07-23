# Question 1: Duplicate Detection & Backup Script

## Executed Commands and Explanations

* **`mkdir -p "$BACKUP_DIR"`**
  This command creates the backup directory if it doesn't already exist. The `-p` flag ensures no error is thrown if the directory is already present.
* **`> "$REPORT_FILE"` and `2> "$ERROR_LOG"`**
  These commands initialize or clear the report and error log files before execution. The `>` redirects standard output to create/empty the report, while `2>` specifically redirects only standard error streams to the error log.
* **`declare -A checksums`**
  This initializes an associative array to store the MD5 hashes of processed files. It allows for highly efficient $O(1)$ lookups to instantly check if a newly calculated hash already exists.
* **`md5sum "$file" 2>> "$ERROR_LOG" | awk '{print $1}'`**
  `md5sum` generates a unique cryptographic hash of the file's contents to detect duplicates regardless of the filename, with any errors appended to the error log using `2>>`. The output is piped `|` into `awk`, which extracts just the hash string (the first column) and drops the filename.
* **`cp "$file" "$BACKUP_DIR/" 2>> "$ERROR_LOG"`**
  This command copies unique files into the designated backup directory. Any permission or read errors encountered during the copy process are quietly appended to the error log without disrupting the script.

## Files Generated
* `process_submissions.sh`: The main executable script.
* `report.txt`: Contains the list of duplicated files and the final execution summary.
* `error.log`: Captures any operational errors during hashing or copying.

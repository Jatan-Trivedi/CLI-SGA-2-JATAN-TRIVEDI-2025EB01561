#!/bin/bash

# Define directories and logs
SUB_DIR="./submissions"
BACKUP_DIR="./backup"
REPORT_FILE="report.txt"
ERROR_LOG="error.log"

# Clear previous logs and create backup directory
mkdir -p "$BACKUP_DIR"
> "$REPORT_FILE"
2> "$ERROR_LOG"

processed=0
duplicated=0
backed_up=0

declare -A checksums

# Process each file in the submissions folder
for file in "$SUB_DIR"/*; do
    # Ensure it's a regular file
    if [ -f "$file" ]; then
        ((processed++))
        
        # Calculate MD5 hash to detect duplicate content
        hash=$(md5sum "$file" 2>> "$ERROR_LOG" | awk '{print $1}')
        
        if [ -n "${checksums[$hash]}" ]; then
            ((duplicated++))
            echo "[DUPLICATE] $file is a duplicate of ${checksums[$hash]}" >> "$REPORT_FILE"
        else
            checksums[$hash]="$file"
            cp "$file" "$BACKUP_DIR/" 2>> "$ERROR_LOG"
            if [ $? -eq 0 ]; then
                ((backed_up++))
            fi
        fi
    fi
done

# Write summary to report
echo "--------------------------------" >> "$REPORT_FILE"
echo "Execution Summary:" >> "$REPORT_FILE"
echo "Files Processed : $processed" >> "$REPORT_FILE"
echo "Duplicates Found: $duplicated" >> "$REPORT_FILE"
echo "Files Backed Up : $backed_up" >> "$REPORT_FILE"

cat "$REPORT_FILE"

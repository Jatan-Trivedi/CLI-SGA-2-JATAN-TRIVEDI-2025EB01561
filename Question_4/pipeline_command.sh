#!/bin/bash
tail -f system.log | grep --line-buffered "ERROR" | tee -a error_report.log > /dev/null

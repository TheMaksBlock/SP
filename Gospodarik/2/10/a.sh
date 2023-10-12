sort -t: -k2 -n people | head -n1 | awk -F: '{print $1}'


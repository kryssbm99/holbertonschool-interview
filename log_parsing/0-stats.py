#!/usr/bin/python3
"""
Log Parsing

Processes HTTP GET request logs from stdin and calculates the total
file size and occurrences of each response status code.

Expected log format:
<IP Address> - [<date>] "GET /projects/260 HTTP/1.1" <status code> <file size>
"""


def print_log_totals(total_file_size, code_counts):
    """Prints total file size and status code counts."""
    print("File size: {}".format(total_file_size))
    for code, count in code_counts.items():
        if count > 0:
            print("{}: {}".format(code, count))


if __name__ == '__main__':
    from sys import argv, stdin, stderr
    from collections import OrderedDict
    from datetime import datetime

    line_no = 0
    total_file_size = 0
    code_counts = OrderedDict.fromkeys([200, 301, 400, 401, 403,
                                        404, 405, 500], 0)
    try:
        for line in stdin:
            line_no += 1
            parts = line.split('- ', 1)
            if len(parts) != 2:
                continue

            time_part = parts[1].split(']')
            timecode = time_part[0].lstrip(' [')
            try:
                datetime.strptime(timecode, '%Y-%m-%d %H:%M:%S.%f')
            except ValueError:
                stderr.write("{}: {}: invalid timecode\n".format(argv[0], line_no))
                continue

            request_part = time_part[1].split('"')
            if len(request_part) < 2 or request_part[1] != 'GET /projects/260 HTTP/1.1':
                stderr.write("{}: {}: unexpected HTTP request\n".format(argv[0], line_no))
                continue

            status_size = request_part[2].strip().split()
            if len(status_size) < 2:
                continue

            if status_size[0].isdigit():
                code = int(status_size[0])
                if code in code_counts:
                    code_counts[code] += 1

            if status_size[1].isdigit():
                total_file_size += int(status_size[1])

            if line_no % 10 == 0:
                print_log_totals(total_file_size, code_counts)
        print_log_totals(total_file_size, code_counts)

    except KeyboardInterrupt:
        print_log_totals(total_file_size, code_counts)
        raise

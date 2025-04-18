# Script for calculating line count of O2Craft 

import os
from datetime import date

excludes = ['.git', '.vs', 'SFML', 'yaml-cpp', 'json.hpp', 'sqlit3.c', 'sqlite3.h']

def get_cpp_files(path):
    output = []
    everything = os.listdir(path)

    for thing in everything:
        new_path = os.path.join(path, thing)

        if thing not in excludes:
            if os.path.isfile(new_path):
                tokens = thing.split('.')
                extension = tokens[len(tokens)-1]
                if extension == 'cpp' or extension == 'h':
                    output.append(new_path)
            else:
                sub_files = get_cpp_files(new_path)
                for file in sub_files:
                    output.append(file)

    return output


def get_line_count(filepath):
    count = 0

    with open(filepath) as file:
        count = len(file.readlines())

    return count


filepaths = get_cpp_files('.')
total = 0
for filepath in filepaths:
    total += get_line_count(filepath)

print("Total lines of C++ source code and headers as of", date.today(), '=', total, "lines")
print("==[ Done ]==")

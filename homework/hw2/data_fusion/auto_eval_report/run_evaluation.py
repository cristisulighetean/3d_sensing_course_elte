import sys
import os
from os.path import join, isdir

def run_eval():
    if len(sys.argv) < 2:
        return "Usage: python3 script_name data_path"

data_path = sys.argv[1]

dir_list = [join(data_path,f) for f in os.listdir(data_path) if isdir(os.path.join(data_path, f))]
dir_list = [ f+"/" for f in dir_list]

count = 1

for folder in dir_list:
    command = "./build/data_fusion " + folder
    ret_code = os.system(command)
    print(f"{count} folders processed out of {len(dir_list)}")
    print(f"Last return code {ret_code}\n")
    count += 1


run_eval()


import subprocess
import os

files = ["main.cpp", "lib/wrapper.cpp", "lib/IO.cpp", "lib/chip8.cpp", "lib/instructions.cpp", "lib/debugger.cpp"]
libs = ["SDL3.dll", "SDL3_ttf.dll", "-lcomdlg32", "-lole32"]
obj_files = ["main.o", "wrapper.o", "IO.o", "chip8.o", "instructions.o", "debugger.o", "lib/tinyfiledialogs.c"]

output_file = "main"

def create_args():
    args = {
        "compile": ["g++", "-c"],
        "link": ["g++", "-LC:/mingw/lib"]
    }
    
    for file in obj_files:
        args["link"].append(file)

    args["link"].append("-l")
    for lib in libs:
        args["link"].append(lib)
    
    for file in files:
        args["compile"].append(file)

    args["link"].append(f"-o")
    args["link"].append(output_file)

    return args


args = create_args()

for arg in args.values():
    print(arg)
    process = subprocess.run(arg, capture_output=True, encoding="UTF-8")

    print(process.stdout)
    print(process.stderr)

print("Done building")
    
    

    





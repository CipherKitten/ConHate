import os
import subprocess
import glob
cflags = "-DCCORD_SIGINTCATCH"
cfiles = glob.glob("./src/isrc/*.c")
compileCommand = f"gcc {cflags} -g -o0 -I/opt/concord/include -L/opt/concord/lib -Isrc/include ./src/main.c {' '.join(cfiles)} -ldiscord -lcurl  -o build/conhate"


def createBuildDir():
    if os.path.isdir("build"):
        return

    os.makedirs("build")


def compile():
    compileCommandList = compileCommand.split()
    subprocess.check_output(compileCommandList)

def main():
    
    createBuildDir()
    compile()

    print("«««««««««STARTING MEMORY LEAK DETECTION»»»»»»»»»»»»»»»»")
    try:
        subprocess.check_output(['valgrind', '--leak-check=full', 'build/conhate']) 
    except:
        print("Valgrind segaulted :/")

    print("«««««««««««««««««BUILD FINISHED»»»»»»»»»»»»»»»»»»»»")

if __name__ == "__main__":
    main()

import subprocess
import glob
cflags = "-DCCORD_SIGINTCATCH"
cfiles = glob.glob("./src/isrc/*.c")
compileCommand = f"gcc {cflags} -g -I/opt/concord/include -L/opt/concord/lib -Isrc/include ./src/main.c {' '.join(cfiles)} -ldiscord -lcurl  -o build/conhate"

def compile():
    compileCommandList = compileCommand.split()
    subprocess.check_output(compileCommandList)

def main():
    
    compile()

    print("«««««««««STARTING MEMORY LEAK DETECTION»»»»»»»»»»»»»»»»")
    subprocess.check_output(['valgrind', '--leak-check=full', 'build/conhate']) 
    print("«««««««««««««««««BUILD FINISHED»»»»»»»»»»»»»»»»»»»»")
    pass
if __name__ == "__main__":
    main()

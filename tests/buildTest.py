import glob
import subprocess
cflags = "-DCCORD_SIGINTCATCH"
cfiles = glob.glob("../src/isrc/*.c")
compileCommand = f"gcc {cflags} -I/opt/concord/include -L/opt/concord/lib -I../src/include test.c {' '.join(cfiles)} -ldiscord -lcurl -o testbuild/conhateTest"

def compile():
    compileCommandList = compileCommand.split()
    subprocess.check_output(compileCommandList)


def main():
    compile()


if __name__ == "__main__":
    main()

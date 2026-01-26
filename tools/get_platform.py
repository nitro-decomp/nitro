import platform


class Platform:
    def __init__(self, *, system: str, machine: str, exe: str):
        self.system = system
        '''Name of operating system: "windows" or "linux"'''
        self.machine = machine
        '''Name of machine architecture: "x86_64"'''
        self.exe = exe
        '''Executable file extension: ".exe" for Windows, "" otherwise'''


def get_platform() -> Platform | None:
    system = platform.system().lower()
    machine = platform.machine().lower()
    match system:
        case "windows":
            exe = ".exe"
        case "linux":
            exe = ""
        case _:
            print(f"Unknown system '{system}'")
            return None
    match machine:
        case "amd64" | "x86_64":
            machine = "x86_64"
        case machine:
            print(f"Unknown machine: {machine}")
            return None

    return Platform(system=system, machine=machine, exe=exe)

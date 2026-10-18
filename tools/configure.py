#!/usr/bin/env python3

import json
import os
from pathlib import Path
import argparse
import sys
import subprocess
from typing import Any, Generator

import ninja_syntax
from get_platform import get_platform


DEFAULT_WIBO_PATH = "./wibo"


parser = argparse.ArgumentParser(description="Generates build.ninja")
parser.add_argument('-w', type=str, default=DEFAULT_WIBO_PATH, dest="wine", required=False, help="Path to Wine/Wibo (linux only)")
parser.add_argument("--compiler", type=Path, required=False, help="Path to pre-installed compiler root directory")
parser.add_argument("--no-extract", action="store_true", help="Skip extract step")
parser.add_argument("--dsd", type=Path, required=False, help="Path to pre-installed dsd CLI")
args = parser.parse_args()


class Game:
    def __init__(
        self,
        *,
        name: str,
        mwcc_version: str,
        cc_flags: list[str] | None = None,
        ld_flags: list[str] | None = None,
        sdk_version: str,
        check_filter_args: list[str] | None = None,
    ):
        self.name = name
        self.mwcc_version = mwcc_version
        self.cc_flags = cc_flags or []
        self.ld_flags = ld_flags or []
        self.sdk_version = sdk_version
        self.check_filter_args = check_filter_args or []


# Config
DSD_VERSION = 'v0.12.1'
WIBO_VERSION = '0.6.16'
OBJDIFF_VERSION = 'v3.8.1'
GAMES = [
    Game(
        name="pm4_jp",
        mwcc_version="2.0/sp1p5",
        sdk_version="0x4027531",
    ),
    Game(
        name="diamondtrust_us",
        mwcc_version="dsi/1.3p1",
        sdk_version="0x5057533",
    ),
    Game(
        name="gtactw_eu",
        mwcc_version="2.0/sp2p3",
        cc_flags=["-thumb"],
        sdk_version="0x4027531",
        check_filter_args=["--main", "--itcm", "--dtcm"],
    ),
    Game(
        name="LEGO_GAME_NAME",
        mwcc_version="1.2/base",
        cc_flags=["-d NITRO_DEBUG=1"],
        sdk_version="0x2027533", # TODO: double check this is the correct version
    ),
]
DECOMP_ME_COMPILERS = {
    "1.2/b56": "mwcc_20_56",
    "1.2/base": "mwcc_20_72",
    "1.2/sp2": "mwcc_20_79",
    "1.2/sp2p3": "mwcc_20_82",
    "1.2/sp3": "mwcc_20_84",
    "1.2/sp4": "mwcc_20_87",
    "2.0/base": "mwcc_30_114",
    "2.0/sp1": "mwcc_30_123",
    "2.0/sp1p2": "mwcc_30_126",
    "2.0/sp1p5": "mwcc_30_131",
    "2.0/sp1p6": "mwcc_30_133",
    "2.0/sp1p7": "mwcc_30_134",
    "2.0/sp2": "mwcc_30_136",
    "2.0/sp2p2": "mwcc_30_137",
    "2.0/sp2p3": "mwcc_30_138",
    "2.0/sp2p4": "mwcc_30_139",
    "dsi/1.1": "mwcc_40_1018",
    "dsi/1.1p1": "mwcc_40_1024",
    "dsi/1.2": "mwcc_40_1026",
    "dsi/1.2p1": "mwcc_40_1027",
    "dsi/1.2p2": "mwcc_40_1028",
    "dsi/1.3": "mwcc_40_1034",
    "dsi/1.3p1": "mwcc_40_1036",
    "dsi/1.6sp1": "mwcc_40_1051",
    "dsi/1.6sp2": "mwcc_40_1051",
}
CC_FLAGS = " ".join([
    "-O4,p",                # Optimize maximally for performance
    "-enum int",            # Use int-sized enums
    "-char signed",         # Char type is signed
    "-str reuse",           # Reuse strings
    "-proc arm946e",        # Target processor
    "-gccext,on",           # Enable GCC extensions
    "-fp soft",             # Compute float operations in software
    "-inline noauto",       # Inline only functions marked with 'inline'
    "-lang=c",              # Set language to C
    "-Cpp_exceptions off",  # Disable C++ exceptions
    "-interworking",        # Enable ARM/Thumb interworking
#    "-ipa file",            # Enable inter-procedural analysis
    "-requireprotos",       # Require function prototypes
    "-sym on",              # Debug info, including line numbers
    "-gccinc",              # Interpret #include "..." and #include <...> equally
    "-nolink",              # Do not link
    "-msgstyle gcc",        # Use GCC-like messages (some IDEs will make file names clickable)
])
CC_FLAG_OVERRIDES: dict[str, list[str]] = {}
# Passed to all modules and final arm9.o link
LD_FLAGS = " ".join([
    "-proc arm946e",        # Target processor
    "-dead",                # Strip unused code
    "-nostdlib",            # No C/C++ standard library
    "-interworking",        # Enable ARM/Thumb interworking
    "-map closure,unused",  # Generate map file
    "-msgstyle gcc",        # Use GCC-like messages (some IDEs will make file names clickable)
    "-m _start",            # Set entry function
])
DSD_BASE_FLAGS = " ".join([
    "--force-color", # Force color output
])


# Paths
current_path     = Path(__name__)
root_path        = current_path.parent
build_ninja_path = root_path / "build.ninja"
arm7_bios_path   = root_path / "arm7_bios.bin"
config_path      = root_path / "config"
build_path       = root_path / "build"
src_path         = root_path / "src"
libs_path        = root_path / "libs"
extract_path     = root_path / "extract"
tools_path       = root_path / "tools"
lock_file_path = root_path / "configure.lock"
mwcc_root        = args.compiler or tools_path / "mwccarm"


# Includes
includes = [
    root_path / "include"
]
for root, dirs, _ in os.walk(libs_path):
    for dir in dirs:
        if dir == "include":
            includes.append(Path(root) / dir)
CC_INCLUDES = " ".join(f"-i {include}" for include in includes)


# Platform info
platform = get_platform() or exit(1)
EXE = platform.exe
WINE = args.wine if platform.system != "windows" else ""
DSD = str(args.dsd or os.path.join('.', str(root_path / f"dsd{EXE}")))
OBJDIFF = os.path.join('.', str(root_path / f"objdiff-cli{EXE}"))
PYTHON = sys.executable
TRANSFORM_DEP = "tools/transform_dep.py"


class Project:
    def __init__(self, *, game: Game, delinks_json: Any | None):
        self.game = game
        '''Game name and version'''
        self.game_config = config_path / game.name
        '''Root directory for dsd configs'''

        self.platform = platform
        '''Host platform information'''
        self.delinks_json = delinks_json
        '''Delinks JSON data from dsd'''

        self.game_build = build_path / game.name
        '''Path to build directory'''
        self.game_extract = extract_path / game.name
        '''Path to extract directory'''

        self.delinks_files = get_config_files(self.game_config, "delinks.txt")
        '''Paths to every delinks.txt file'''
        self.relocs_files = get_config_files(self.game_config, "relocs.txt")
        '''Paths to every relocs.txt file'''
        self.symbols_files = get_config_files(self.game_config, "symbols.txt")
        '''Paths to every symbols.txt file'''
        
        mwcc_path        = mwcc_root / game.mwcc_version
        self.cc = os.path.join('.', str(mwcc_path / "mwccarm.exe"))
        self.ld = os.path.join('.', str(mwcc_path / "mwldarm.exe"))
        
        self.mwcc_implicit = [self.cc]
        if platform.system != "windows":
            self.mwcc_implicit.append(TRANSFORM_DEP)
            if WINE == DEFAULT_WIBO_PATH:
                self.mwcc_implicit.append(WINE)

    def dsd_configs(self) -> list[str]:
        return self.delinks_files + self.relocs_files + self.symbols_files

    def arm9_config_yaml(self) -> Path:
        return self.game_config / "arm9" / "config.yaml"

    def baserom(self) -> Path:
        return extract_path / f'{self.game.name}.nds'

    def baserom_config(self) -> Path:
        return self.game_extract / 'config.yaml'

    def source_files(self) -> Generator[Path, Any, Any]:
        yield from get_c_cpp_files([src_path, libs_path])

    def source_object_files(self) -> Generator[Path, Any, Any]:
        for source_file in self.source_files():
            yield self.game_build / source_file.with_suffix(".o")

    def nitro_o(self) -> Path:
        return self.game_build / "nitro.o"

    def arm9_disassembly_dir(self) -> Path:
        return self.game_build / "asm"

    def objdiff_project(self) -> Path:
        return self.game_build / "objdiff.json"

    def objdiff_report_project(self) -> Path:
        return self.game_build / "report" / "objdiff.json"

    def objdiff_report(self) -> Path:
        return self.game_build / "report" / "report.json"

    def files(self) -> list[dict[str, str]]:
        if self.delinks_json is None:
            return []
        return self.delinks_json['files']

    def delink_files(self) -> list[str]:
        delink_files = [file['delink_file'] for file in self.files()]
        return list(set(delink_files))

    def arm9_lcf_file(self) -> str:
        if self.delinks_json is None:
            return ""
        return self.delinks_json['arm9_lcf_file']

    def arm9_objects_file(self) -> str:
        if self.delinks_json is None:
            return ""
        return self.delinks_json['arm9_objects_file']


def check_can_run_dsd() -> bool:
    try:
        output = subprocess.run([DSD, "--version"], capture_output=True, text=True, check=True)
        if args.dsd is not None:
            # Custom dsd specified, don't check version number
            return True
        version = output.stdout.strip().split(" ")[-1]
        if not version.startswith("v"):
            version = "v" + version

        # If it's not the correct version, Ninja will download it and then rerun this script
        return version == DSD_VERSION
    except subprocess.CalledProcessError:
        return False
    except FileNotFoundError:
        return False


def main() -> int:
    if platform is None:
        return

    can_run_dsd = check_can_run_dsd()

    with build_ninja_path.open("w") as file:
        n = ninja_syntax.Writer(file)

        n.rule(
            name="download_tool",
            command=f'{PYTHON} tools/download_tool.py $tool $tag --path $path'
        )
        n.newline()

        if arm7_bios_path.is_file():
            n.variable("arm7_bios_flag", f"--arm7-bios {arm7_bios_path.relative_to(root_path)}")
        else:
            n.variable("arm7_bios_flag", "")
        n.newline()

        n.rule(
            name="extract",
            command=f"{DSD} {DSD_BASE_FLAGS} rom extract --rom $in --output-path $output_path $arm7_bios_flag"
        )
        n.newline()

        n.rule(
            name="delink",
            command=f"{DSD} {DSD_BASE_FLAGS} delink --config-path $config_path"
        )
        n.newline()

        n.rule(
            name="disassemble",
            command=f"{DSD} {DSD_BASE_FLAGS} dis --config-path $config_path --asm-path $output_path --ual"
        )
        n.newline()

        # -MMD excludes all includes instead of just system includes for some reason, so use -MD instead.
        mwcc_cmd = f'{WINE} "$cc" {CC_FLAGS} {CC_INCLUDES} $cc_flags -d $game_version -MD -c $in -o $basedir'
        if platform.system != "windows":
            mwcc_cmd += f" && $python {TRANSFORM_DEP} $basefile.d $basefile.d"
        n.rule(
            name="mwcc",
            command=mwcc_cmd,
            depfile="$basefile.d",
        )
        n.newline()

        n.rule(
            name="lcf",
            command=f"{DSD} {DSD_BASE_FLAGS} lcf -c $config_path"
        )
        n.newline()

        n.rule(
            name="mwld",
            command=f'{WINE} "$ld" {LD_FLAGS} $extra_ld_flags @$objects_file $lcf_file -o $out'
        )
        n.newline()

        n.rule(
            name="objdiff",
            command=f"{DSD} {DSD_BASE_FLAGS} objdiff --config-path $config_path --scratch --custom-make ninja $extra_flags"
        )
        n.newline()

        n.rule(
            name="objdiff_report",
            command=f"{OBJDIFF} report generate --project $project_path --output $out"
        )
        n.newline()

        n.rule(
            name="merge_objdiff",
            command=f"{PYTHON} tools/merge_objdiff.py $games",
        )
        n.newline()

        n.rule(
            name="m2ctx",
            command=f"{PYTHON} tools/m2ctx.py -f $out $in"
        )
        n.newline()

        n.rule(
            name="check_modules",
            command=f"{DSD} {DSD_BASE_FLAGS} check modules --config-path $config_path --fail $extra_flags"
        )
        n.newline()

        n.rule(
            name="check_symbols",
            command=f"{DSD} {DSD_BASE_FLAGS} check symbols --config-path $config_path --elf-path $elf_path --fail --max-lines 20 $extra_flags"
        )
        n.newline()

        n.rule(
            name="apply",
            command=f"{DSD} {DSD_BASE_FLAGS} apply --config-path $config_path --elf-path $elf_path"
        )
        n.newline()

        configure_cmdline = subprocess.list2cmdline(sys.argv[1:])
        n.rule(
            name="configure",
            command=f"{PYTHON} tools/configure.py {configure_cmdline}",
            generator=True
        )
        n.newline()

        projects = []
        for game in GAMES:
            delinks_json = None
            if can_run_dsd:
                out = subprocess.run([
                    DSD,
                    "--force-color",
                    "json",
                    "delinks",
                    "--config-path", config_path / game.name / "arm9" / "config.yaml"
                ], capture_output=True, text=True)
                if out.returncode != 0:
                    print(f"Error running dsd:\n{out.stderr.strip()}")
                    return 1
                delinks_json = json.loads(out.stdout)
            project = Project(game=game, delinks_json=delinks_json)
            if project.baserom().exists():
                projects.append(project)

        create_compilation_database()

        add_download_tool_builds(n, projects)
        add_configure_build(n, projects)

        if can_run_dsd:
            add_extract_builds(n, projects)
            add_delink_and_lcf_builds(n, projects)
            add_disassemble_builds(n, projects)
            add_mwcc_builds(n, projects)
            add_mwld_builds(n, projects)
            add_check_builds(n, projects)
            add_objdiff_builds(n, projects)
            add_apply_builds(n, projects)

        if can_run_dsd:
            n.default(["objdiff", "delink"])
        else:
            n.default(["download_tools"])
    
    return 0


def add_download_tool_builds(n: ninja_syntax.Writer, projects: list[Project]):
    downloads: list[str] = []

    if args.dsd is None:
        downloads.append(DSD)
        n.build(
            rule="download_tool",
            outputs=DSD,
            variables={
                "tool": "dsd",
                "tag": DSD_VERSION,
                "path": DSD,
            },
        )
        n.newline()

    downloads.append(OBJDIFF)
    n.build(
        rule="download_tool",
        outputs=OBJDIFF,
        variables={
            "tool": "objdiff",
            "tag": OBJDIFF_VERSION,
            "path": OBJDIFF,
        }
    )
    n.newline()

    if args.compiler is None:
        mw_tools = []
        for project in projects:
            mw_tools.append(project.cc)
            mw_tools.append(project.ld)
        downloads.extend(mw_tools)
        n.build(
            rule="download_tool",
            outputs=mw_tools,
            variables={
                "tool": "mwccarm",
                "tag": "latest",
                "path": str(tools_path),
            },
        )
        n.newline()

    if platform.system != "windows" and WINE == DEFAULT_WIBO_PATH:
        downloads.append(WINE)
        n.build(
            rule="download_tool",
            outputs=WINE,
            variables={
                "tool": "wibo",
                "tag": WIBO_VERSION,
                "path": WINE,
            },
        )
        n.newline()

    n.build(
        inputs=downloads,
        rule="phony",
        outputs="download_tools",
    )
    n.newline


def add_extract_builds(n: ninja_syntax.Writer, projects: list[Project]):
    if not args.no_extract:
        for project in projects:
            n.build(
                inputs=str(project.baserom()),
                implicit=DSD,
                rule="extract",
                outputs=str(project.baserom_config()),
                variables={
                    "output_path": str(project.game_extract)
                }
            )
            n.newline()


def add_mwld_builds(n: ninja_syntax.Writer, projects: list[Project]):
    for project in projects:
        n.comment("Run linker")
        objects_to_link = [file['object_to_link'] for file in project.files()]
        elf_file = str(project.nitro_o())
        lcf_file = project.arm9_lcf_file()
        objects_file = project.arm9_objects_file()
        if len(objects_to_link) > 0:
            n.build(
                inputs=[*objects_to_link, lcf_file, objects_file],
                implicit=project.ld,
                rule="mwld",
                outputs=elf_file,
                variables={
                    "ld": project.ld,
                    'lcf_file': str(lcf_file),
                    'objects_file': str(objects_file),
                    "extra_ld_flags": project.game.ld_flags,
                }
            )
            n.newline()

        n.build(
            inputs=elf_file,
            rule="phony",
            outputs=f"arm9_{project.game.name}",
        )
        n.newline()

    n.build(
        inputs=[f"arm9_{project.game.name}" for project in projects],
        rule="phony",
        outputs="arm9"
    )
    n.newline()

def add_mwcc_builds(n: ninja_syntax.Writer, projects: list[Project]):
    for project in projects:
        ctx_files = []
        for source_file in project.source_files():
            src_obj_path = project.game_build / source_file
            cc_flags: list[str] = project.game.cc_flags.copy()
            if is_cpp(source_file):
                cc_flags.append("-lang=c++")
            elif is_c(source_file):
                cc_flags.append("-lang=c")
            for prefix, override_flags in CC_FLAG_OVERRIDES.items():
                if Path(prefix) in source_file.parents:
                    cc_flags.extend(override_flags)
            cc_flags.append(f"-d NITRO_VERSION={project.game.sdk_version}")
            n.build(
                inputs=str(source_file),
                implicit=project.mwcc_implicit,
                rule="mwcc",
                outputs=str(src_obj_path.with_suffix(".o")),
                variables={
                    "cc": project.cc,
                    "game_version": project.game.name,
                    "cc_flags": " ".join(cc_flags),
                    "basedir": os.path.dirname(src_obj_path),
                    "basefile": str(src_obj_path.with_suffix("")),
                },
            )
            n.newline()

            extension = source_file.suffix
            ctx_file = str(src_obj_path.with_suffix(f".ctx{extension}"))
            ctx_files.append(ctx_file)
            n.build(
                inputs=str(source_file),
                rule="m2ctx",
                outputs=ctx_file,
            )
            n.newline()
        
        n.build(
            inputs=ctx_files,
            rule="phony",
            outputs=f"m2ctx_{project.game.name}"
        )
        n.newline()
    
    n.build(
        inputs=[f"m2ctx_{project.game.name}" for project in projects],
        rule="phony",
        outputs="m2ctx",
    )
    n.newline()


def get_c_cpp_files(dirs: list[Path]):
    for dir in dirs:
        for root, _, files in os.walk(dir):
            root = Path(root)
            for file in files:
                if is_cpp(file) or is_c(file):
                    yield root / file


def is_cpp(name: str | Path):
    return Path(name).suffix in [".cpp"]


def is_c(name: str | Path):
    return Path(name).suffix in [".c"]


def add_delink_and_lcf_builds(n: ninja_syntax.Writer, projects: list[Project]):
    for project in projects:
        rom_config = str(project.baserom_config())
        delink_files = project.delink_files()
        if len(delink_files) > 0:
            n.comment("Delink ELF binaries when any delinks.txt file is modified")
            n.build(
                inputs=project.dsd_configs() + [rom_config],
                implicit=DSD,
                rule="delink",
                outputs=delink_files,
                variables={
                    "config_path": str(project.arm9_config_yaml()),
                }
            )
            n.newline()

            n.build(
                inputs=delink_files,
                rule="phony",
                outputs=f"delink_{project.game.name}"
            )
            n.newline()

        lcf_file = project.arm9_lcf_file()
        objects_file = project.arm9_objects_file()
        n.build(
            inputs=project.delinks_files + [str(rom_config)],
            implicit=DSD,
            rule="lcf",
            outputs=[lcf_file, objects_file],
            variables={
                "config_path": str(project.arm9_config_yaml()),
            }
        )
        n.newline()
        
    n.build(
        inputs=[f"delink_{project.game.name}" for project in projects],
        rule="phony",
        outputs="delink",
    )
    n.newline()


def add_disassemble_builds(n: ninja_syntax.Writer, projects: list[Project]):
    for project in projects:
        n.build(
            inputs=project.dsd_configs(),
            implicit=DSD,
            rule="disassemble",
            outputs=f"dis_{project.game.name}",
            variables={
                "config_path": str(project.arm9_config_yaml()),
                "output_path": str(project.arm9_disassembly_dir()),
            }
        )
        n.newline()

    n.build(
        inputs=[f"dis_{project.game.name}" for project in projects],
        rule="phony",
        outputs="dis",
    )
    n.newline()


def add_check_builds(n: ninja_syntax.Writer, projects: list[Project]):
    for project in projects:
        n.build(
            inputs=str(project.nitro_o()),
            rule="check_modules",
            outputs=f"check_modules_{project.game.name}",
            variables={
                "config_path": str(project.arm9_config_yaml()),
                "extra_flags": project.game.check_filter_args,
            },
        )
        n.newline()

        n.build(
            inputs=str(project.nitro_o()),
            rule="check_symbols",
            outputs=f"check_symbols_{project.game.name}",
            variables={
                "config_path": str(project.arm9_config_yaml()),
                "elf_path": str(project.nitro_o()),
                "extra_flags": project.game.check_filter_args,
            },
        )
        n.newline()

        n.build(
            inputs=[f"check_modules_{project.game.name}", f"check_symbols_{project.game.name}"],
            rule="phony",
            outputs=f"check_{project.game.name}",
        )
        n.newline()
    
    n.build(
        inputs=[f"check_modules_{project.game.name}" for project in projects],
        rule="phony",
        outputs="check_modules"
    )
    n.newline()
    
    n.build(
        inputs=[f"check_symbols_{project.game.name}" for project in projects],
        rule="phony",
        outputs="check_symbols"
    )
    n.newline()
    
    n.build(
        inputs=["check_modules", "check_symbols"],
        rule="phony",
        outputs="check"
    )
    n.newline()


def add_objdiff_builds(n: ninja_syntax.Writer, projects: list[Project]):
    for project in projects:
        n.build(
            inputs=project.dsd_configs(),
            implicit=DSD,
            rule="objdiff",
            outputs=str(project.objdiff_project()),
            variables={
                "config_path": str(project.arm9_config_yaml()),
                "extra_flags": " ".join([
                    f"--output-path {project.objdiff_project().parent}",
                    f"--compiler {DECOMP_ME_COMPILERS[project.game.mwcc_version]}", # decomp.me compiler name
                    f'--c-flags "{CC_FLAGS} {" ".join(project.game.cc_flags)}"',              # decomp.me compiler flags
                ])
            }
        )
        n.newline()

        delink_files = project.delink_files()
        n.build(
            inputs=project.dsd_configs(),
            implicit=[OBJDIFF] + delink_files + [str(f) for f in project.source_object_files()],
            rule="objdiff",
            outputs=str(project.objdiff_report_project()),
            variables={
                "config_path": str(project.arm9_config_yaml()),
                "extra_flags": " ".join([
                    f"--output-path {project.objdiff_report_project().parent}",
                    "--skip-absent-objects"
                ])
            },
        )
        n.newline()

        n.build(
            inputs=str(project.objdiff_report_project()),
            rule="objdiff_report",
            outputs=str(project.objdiff_report()),
            variables={
                "project_path": str(project.objdiff_report_project().parent)
            }
        )
        n.newline()

        n.build(
            inputs=str(project.objdiff_report()),
            rule="phony",
            outputs=f"report_{project.game.name}",
        )
        n.newline()

    n.build(
        inputs=[str(project.objdiff_project()) for project in projects],
        rule="merge_objdiff",
        outputs="objdiff.json",
        variables={
            "games": " ".join(project.game.name for project in projects)
        }
    )
    n.newline()

    n.build(
        inputs="objdiff.json",
        rule="phony",
        outputs="objdiff",
    )
    n.newline()

    n.build(
        inputs=[f"report_{project.game.name}" for project in projects],
        rule="phony",
        outputs="report",
    )
    n.newline()


def add_configure_build(n: ninja_syntax.Writer, projects: list[Project]):
    this_file = str(Path(__file__).resolve())
    dsd_configs = []
    for project in projects:
        dsd_configs.extend(project.dsd_configs())
    n.build(
        outputs="build.ninja",
        rule="configure",
        implicit=[
            this_file,
            # Require dsd to exist when rerunning configure.py
            DSD,
            *dsd_configs,
        ]
    )


def add_apply_builds(n: ninja_syntax.Writer, projects: list[Project]):
    for project in projects:
        n.build(
            inputs=project.dsd_configs() + [str(project.nitro_o())],
            implicit=DSD,
            rule="apply",
            outputs=f"apply_{project.game.name}",
            variables={
                "config_path": str(project.arm9_config_yaml()),
                "elf_path": str(project.nitro_o()),
            }
        )
        n.newline()
    
    n.build(
        inputs=[f"apply_{project.game.name}" for project in projects],
        rule="phony",
        outputs="apply",
    )
    n.newline()


def get_config_files(game_config: Path, name: str) -> list[str]:
    return [
        f"{root}/{file}"
        for root, _, files in os.walk(game_config)
        for file in files
        if file == name
    ]


def create_compilation_database():
    db_path = root_path / "compile_commands.json"
    db: list[dict] = []
    abs_root_path = root_path.absolute()
    for src_file in get_c_cpp_files([src_path, libs_path]):
        db.append({
            "directory": str(abs_root_path),
            "arguments": ["#"], # clangd ignores entries with empty arguments
            "file": str(src_file)
        })
    with db_path.open("w") as f:
        f.write(json.dumps(db))


if os.name == "nt":
    # Not implemented
    def acquire_lock(fd: int, *, blocking: bool) -> bool:
        return True
    
    def release_lock(fd: int):
        pass
else:
    import fcntl

    def acquire_lock(fd: int, *, blocking: bool) -> bool:
        flags = fcntl.LOCK_EX
        if not blocking:
            flags |= fcntl.LOCK_NB
        try:
            fcntl.flock(fd, flags)
        except OSError:
            return False
        return True
    
    def release_lock(fd: int):
        fcntl.flock(fd, fcntl.LOCK_UN)

if __name__ == "__main__":
    with lock_file_path.open("a") as file:
        fd = file.fileno()
        if not acquire_lock(fd, blocking=False):
            print("Another instance of configure.py is running, waiting...")
            acquire_lock(fd, blocking=True)
            release_lock(fd)
            sys.exit(0)
        file.seek(0)
        file.truncate()
        file.write(str(os.getpid()))
        file.flush()
        result = main()
        release_lock(fd)
    lock_file_path.unlink()
    sys.exit(result)

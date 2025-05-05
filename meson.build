project(
  'biplup-run', 'c',
  version: '1.0.0',
  license: 'Zlib',
  meson_version: '>=0.60.0',
  default_options: ['buildtype=debugoptimized', 'warning_level=2', 'c_std=c11', 'cpp_std=c++20'])

# Set up recommended compiler and linker flags.
subdir('meson/toolchain')
# If you're working on meson-gba
if get_option('dev')
  subdir('meson/dev')
  subdir_done()
endif

# The name of the project.
name = 'biplup-run'

# All of the source files used by the project.
sources = [
  'src/input.c',
  'src/text.c',
  'src/kinematics.c',
  'src/object_utils.c',
  'src/system_utils.c',
  'src/main.c',
  'src/assets/blob.s',
  'src/assets/cactus_1_32.s',
  'src/assets/dino_walk_32.s',
  'src/assets/dactyl_fly_32.s',
  'src/assets/cloud_32.s',
  'src/assets/biplup_walk_32.s',
  'src/assets/biplup_walk_32_bw.s',
  'src/assets/sudowoodo_32_bw.s',
  'src/assets/aero_fly_32_bw.s',
  'src/assets/swablu_bw.s',
  'src/assets/bg_with_road.s'
]

# All of the include directories used by the project.
includes = [
  'include',
]

# All of the test sources used by the project.
test_sources = [
  'tests/test_executable.c',
  'tests/test_system_utils.c',
  'tests/test_object_utils.c',
  'tests/test_text.c',
  'tests/test_kinematics.c',
  'tests/test_input.c',
  'src/input.c',
  'src/text.c',
  'src/kinematics.c',
  'src/object_utils.c',
  'src/system_utils.c',
  'src/assets/blob.s',
  'src/assets/cactus_1_32.s',
  'src/assets/dino_walk_32.s',
  'src/assets/dactyl_fly_32.s',
  'src/assets/cloud_32.s',
  'src/assets/biplup_walk_32.s',
  'src/assets/biplup_walk_32_bw.s',
  'src/assets/sudowoodo_32_bw.s',
  'src/assets/aero_fly_32_bw.s',
  'src/assets/swablu_bw.s',
  'src/assets/bg_with_road.s'
]

# All of the test include directories used by the project.
test_includes = [
  'include',
  'test_include'
]

# Dependencies. gba-meson provides a large number of GBA development libraries.
# Check them out and add the ones you want to use to this list.
dependencies = [
  dependency('minrt'),
  dependency('libtonc')
]

# The main executable for the game. We give it a '.elf' file extension,
# just to make the file more easy to differentiate from a raw ROM.
elf = executable(
  name,
  sources,
  include_directories: includes,
  dependencies: dependencies,
  name_suffix: 'elf'
)

# The test executable for the game.
test_elf = executable(
   'unit_tests',
   test_sources,
   include_directories: test_includes,
   dependencies: dependencies,
   name_suffix: 'elf'
)

# Get the 'makerom' program from sdk-seven.
makerom = find_program('makerom')

# Build a raw GBA ROM file from the ELF file.
rom = custom_target(
  name + '-rom',
  input: elf,
  output: name + '.gba',
  command: [makerom, '@INPUT@', '@OUTPUT@'],
  build_by_default: true
)

test_rom = custom_target(
  'test-rom',
  input: test_elf,
  output: 'unit_tests.gba',
  command: [makerom, '@INPUT@', '@OUTPUT@'],
  build_by_default: true
)
